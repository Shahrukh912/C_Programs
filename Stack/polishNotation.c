#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define ERROR -999999
#define SIZE 100

//Global variables
char ex[SIZE]; //to store the user entered expression
char res[SIZE]; //to store the result of conversion
char s[SIZE]; //stack
int top=-1,k; //Top pointer for s. k is use for index of res


//CODE FOR STACK
int push(char x){ //return defination 0 means success and ERROR means error.
    if(top == SIZE - 1){
        return ERROR; 
    }
    top++;
    s[top] = x;
    return 0;
}

char pop(){
    if(top == -1){
        return NULL;
    }
    return s[top--]; // it means first it returns the top value and then decrease the top.
}
char peek(){
    if(top == -1){
        return NULL;
    }
    return s[top]; //return the last value
}
void displayStack(){
    int i;
    for(i=0;i<=top;i++){
        printf("%c",s[i]);
    }
}
//-------------------
int getPriority(char sign){
    if(sign == '(' || sign == ')' ){
        return 0;
    }
    else if(sign == '+' || sign == '-'){
        return 1;
    }
    else if(sign == '*' || sign == '/' || sign == '%'){
        return 2;
    }
    else if(sign == '^'){
        return 3;
    }
    else{
        return -1;
    }
}
char handleSignStack(char sign){
    int sp,temp; //sp means sign priority
    char p;

    p = peek();

    if(sign == '('){
        push(sign);
        return NULL;
    }
    else if(sign == ')'){
        while( (p=pop()) != '('){
            res[k] = p;
            k++;
        }
        res[k] = '\0';
        return NULL;
    }
    else if( p != NULL){
        sp = getPriority(sign);
        temp = getPriority(p);

        if(temp < sp){
            push(sign);
            return NULL;
        }
        else{
            return pop();
        }
    }
    else{
        push(sign);
        return NULL;
    }    
}

void postfix(){
    int i;
    k=0;
    char temp=NULL;
    
    printf("Scanned Char \t\tStack \t\tPostfix\n");
    for(i=0;ex[i]!=NULL;i++){
        printf("%c\t\t\t",ex[i]);
        if(ex[i] == ' '){
            continue;
        }
        else if( isalnum(ex[i]) !=0){ //isalnum return non zero if the char is number or englishAlphabet character
            //printf("Fuck\n");
            res[k] = ex[i];
            k++;
        }
        else{
            while( (temp=handleSignStack(ex[i])) != NULL){
                res[k] = temp;
                k++;
            }     
        }
        res[k] = '\0'; //Adding NULL character so that it does not show garbage value
        displayStack();
        printf("\t\t%s\n",res);
    }

    //Empty the stack and put in the result(postfix string)
    while( (temp=pop()) != NULL){
        res[k] = temp;
        k++;
    }
    res[k] = '\0'; //Adding NULL character so that it does not show garbage value
    printf("\t\t\t\t\t%s",res);
    printf("\n\nPOSTFIX : %s",res);
}

void menu(){
    int i=1;
    printf("\n\n------------MENU-------------------------------\n");
    printf("%d. to Postfix\n",i++);
    printf("%d. to Prefix\n",i++);
    printf("-1. TO EXIT");
}
int main(){
	int choice=-9999,x,skey,temp;
    printf("Enter expression (without spaces): ");
    gets(ex);
    while(choice != -1){
        printf("\n\nEnter your choice (To see menu type 0): ");
        scanf("%d",&choice);

        switch (choice){
            case -1:break; //just so that we not to see that Wrong option error. because after switch it will go to the while condition and then stop.
            case 0: menu();
                    break;
            case 1: postfix();
                    break;
            case 2: //display();
                    break;
            default:    printf("\nERROR: WRONG OPTION\n");
                        break;
        }
    }

	return 0;
}
