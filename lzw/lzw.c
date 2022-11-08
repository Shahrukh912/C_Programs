/*
DC Practical:
LZW Encoding:
*/

#include<stdio.h>
#include<string.h>

//Global variables
char dict[100][100]={{"\0"}};
int lr=-1; //it keeps count on which the last string was added.
FILE *fout;

int findIndex(char *s){
    int i=0;
    while(i<=lr){
       if(strcmp(dict[i],s)==0){
            return i;
       } 
       i++;
    }
    return -1;
}
void displayDict(){
    int i=0;
    printf("Code\tword\n");
    while(i<=lr){
        printf("%d\t%s\n",i,dict[i]);
        i++;
    }
}
void makeInitialDict(char *s){
    int i=0;
    while(s[i] !='\0'){
        if(isalpha(s[i])){
            lr++;
            dict[lr][0] = s[i];
            dict[lr][1] = '\0';
            //printf("%d %d %s\n",lr,s[i],dict[lr]);
        }
        i++;
    }
}

void insertInDict(char *s){
    lr++;
    strcpy(dict[lr],s);
}

void insertInFile(int m,int coma){
    int r=0;
    if(m==0){
        fputc('0',fout);
        fputc(',',fout);
        return;
    }
    while (m!=0){
        r = r*10 + (m%10);
        m/=10;
    }
    while(r!=0){
        m = r%10;
        fputc(m+48,fout);
        r/=10;
    }
    if(coma == 1){
        fputc(',',fout);
    }
}

int main(){
    char s[100],charSet[26],in[100],out[100],w[20],t;
    int m,i=0;
    

    //Inputs
    printf("Enter character set for initial dict(seperated by space) : ");
    fgets(s,100,stdin);
    makeInitialDict(s);
    printf("Enter input file name (press enter to use in.txt): ");
    fgets(in,100,stdin);
    if(strcmp(in,"")){
        strcpy(in,"in.txt");
    }
    printf("Enter output file name (press enter to use out.txt): ");
    fgets(out,100,stdin);

    displayDict();
    if(strcmp(out,"")){
        strcpy(out,"out.txt");
    }
    
    //
    FILE *fin = fopen(in,"r");
    if(fin == NULL){
        printf("Please create a input file name %s\n\n",in);
    }
    else{
        fout = fopen(out,"w");
        w[0] = '\0';
        
        while((t=fgetc(fin))!=EOF){
            //printf("[%c %s %d]\t",t,w,strlen(w));
            w[i++] = t;
            w[i] = '\0';
            //printf("\t f[%s]",w);
            
            //printf("\n%s | ",w);
            m = findIndex(w);

            if(m == -1){
                insertInDict(w);
                w[strlen(w)-1] = '\0';//remove last word;
                m = findIndex(w); //find index of the word from dict
                insertInFile(m,1); //add in th output
                //printf("%d\n\n",m);
                w[0]=t; //set the last
                i=1;
                w[1] = '\0';//enter NULL to make it string
                //displayDict();
            }
            
        }
        m = findIndex(w);
        if(m != -1){
            insertInFile(m,0);        
        }

        
    }
    fclose(fin);
    fclose(fout);
    

}