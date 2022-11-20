/*
DC Practical:
LZ77 Encoding and Decoding:
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Global variables
int lindex=-1; //it keeps track of where was the last character inserted in look ahead buffer to see its full..
FILE *fout;

int wsize,la,sb; //wsize is window size, and la is lookahead, sb is a search buffer
char *l,*s;//array for look ahead and search buffer.

void display(){
    int i=0;
    for(i=0;i<sb;i++){
        printf("%c ",s[i]);
    }
    printf(" | ");
    for(i=0;i<=lindex;i++){
        printf("%c ",l[i]);
    }
    //printf("\tlindex=%d ,la=%d, sb=%d",lindex,la,sb);
}

int insertInBuffer(char c){ //zero means success -1 means full
    if(lindex<la-1){
        lindex++;
        l[lindex] = c;
    }
    else{    
        return -1;
    }
    return 0;
}

int searchInSeachBuffer(char c,int offset){
    int i,len=0;
    // if(offset>0){
    //     offset++;
    // }
    for(i=sb-1-offset;i>=0;i--){
        if(c == s[i]){
            return i;
        }
    }
    return -1; //means not found
}
int lenFound(int j){
    int i=0,len=0;
    for(;j<sb;j++,i++){
        if(s[j] != l[i]){
            return len;
        }
        len++;
    }
    for(j=0;i<la;i++,j++){
        if(l[j] != l[i]){
            return len;
        }
        len++;
    }
    return len;
}
void dumpLeft(int len,int dumpInFile){
    char c;
    int i=0,j;
    while(len>0){
        c = s[0];
        for(i=1;i<sb;i++){
            s[i-1] = s[i];
        }
        s[i-1] = l[0] ;
        for(i=1;i<sb;i++){
            l[i-1] = l[i];
        }
        if(dumpInFile == 1 && c!=NULL){
            fputc(c,fout);
        }
        len--;
        lindex--;//so that there would be empty space for new values
    }
}
void lz77Encode(){
    int i=0,j=0,t=sb,tlen,offset=0,len=0,z=0; //negative minumn so that max value can be assign
    //t is temporary index.
    while(t!=-1){
        t = searchInSeachBuffer(l[0],sb-t);
        tlen = lenFound(t);
        //printf("{t=%d ,tlen=%d}  ",t,tlen);
        if(tlen > len){
            len = tlen;
            offset = sb-t; // calculating offset from actual returned index
        }
    }
    fprintf(fout,"<%d,%d,c(%c)>\n",offset,len,l[len]);
    printf("<%d,%d,c(%c)>\n",offset,len,l[len]);
    dumpLeft(len+1,0);
}
void lz77Decode(int of,int len, char t){
    int a=len,i=sb-1-of;
    lindex = -1;//empty the look ahead
    printf("\n%d,%d,\n",a,i);
    insertInBuffer(t);
    display();
    printf("\t|| ");
    while(a > 0){
        if(i<sb){
            insertInBuffer(s[i]);
        }
        else{
            insertInBuffer(l[i-sb]);
        }
        i++;
        a--;
    }
    dumpLeft(len+1,1);
    display();
    printf("\n");
}
int main(){
    char st[100],charSet[26],line[100],in[100],out[100],w[20],t;
    int m,i=0,temp,of,len,j;


    //Inputs
    printf("Enter input file name (press enter to use in.txt): ");
    fgets(in,100,stdin);
    if(strcmp(in,"")){
        strcpy(in,"in.txt");
    }
    printf("Enter output file name (press enter to use out.txt): ");
    fgets(out,100,stdin);
    if(strcmp(out,"")){
        strcpy(out,"out.txt");
    }
    printf("Enter buffer size : ");
    scanf("%d",&la);
    printf("Enter Look search buffer : ");
    scanf("%d",&sb);
    wsize = sb+la; //calculating search buffer.
    printf("window size is %d\n",wsize);

    l = (char *)calloc(la,sizeof(char)); //creating the array,
    s = (char *)calloc(sb,sizeof(char)); //creating the array.


    
    FILE *fin = fopen(in,"r");
    if(fin == NULL){
        printf("Please create a input file name %s\n\n",in);
    }
    else{
        fout = fopen(out,"w");
        
        while((t=fgetc(fin))!=EOF){

           temp = insertInBuffer(t);
           printf("[sc : %c]\n",t);
           display();
           printf("\n");
            if(temp == -1){
                lz77Encode();
                insertInBuffer(t);
                printf("\n-------------------------\n");
            }    
                 
        }
        while(lindex >=0 ){
            lz77Encode();
        }
    }
    fclose(fin);
    fclose(fout);
    
    fin = fopen(out,"r");
    fout = fopen("decode.txt","w");

     while(fgets(line,sizeof(line),fin)){
        
        for(i=1;line[i]!=',';i++){
            w[i-1] = line[i];
        }
        w[i-1] = '\0';
        of = atoi(w);
        i++;
        for(j=0;line[i]!=',';i++,j++){
            w[j] = line[i];
        }
        len = atoi(w);
        i+=3;
        t = line[i];

        l = (char *)calloc(la,sizeof(char)); //creating the array,
        s = (char *)calloc(sb,sizeof(char)); //creating the array.
        lz77Decode(of,len,t);
             
    }

}