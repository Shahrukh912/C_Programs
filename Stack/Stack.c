#include<stdio.h>
#define ERROR -999999

//Global variables.
int size = 5;
int top = -1;
int stack[5]; //make this same as the size variable.

int push(int x){ //return defination 0 means success and ERROR means error.
    if(top == size - 1){
        return ERROR; 
    }
    top++;
    stack[top] = x;
    return 0;
}

int pop(){
    if(top == -1){
        return ERROR;
    }
    return stack[top--]; // it means first it returns the top value and then decrease the top.
}
int peek(){
    if(top == -1){
        return ERROR;
    }
    return stack[top]; //return the last value
}

void display(){
    int i;
    for(i=0;i<=top;i++){
        printf("%d  ",stack[i]);
    }
}

void menu(){
    int i=1;
    printf("\n\n------------MENU-------------------------------\n");
    printf("%d. PUSH/s\n",i++);
    printf("%d. POP\n",i++);
    printf("%d. PEEK (get the last inserted value without deleting)\n",i++);
    printf("%d. Display\n",i++);
    printf("-1. TO EXIT");
}
int main(){
	int choice=-9999,x,returnVal;

    while(choice != -1){
        printf("\n\nEnter your choice (To see menu type 0): ");
        scanf("%d",&choice);

        switch (choice){
            case -1:break; //just so that we not to see that Wrong option error. because after switch it will go to the while condition and then stop.
            case 0: menu();
                    break;
            case 1: printf("Enter Value : ");
                    scanf("%d",&x);
                    returnVal = push(x);
                    printf("%s",(returnVal == ERROR)?"OVERFLOW":"Pushed");
                    break;
            case 2: returnVal = pop();
                    if(returnVal == ERROR){
                        printf("UNDERFLOW");
                    }
                    else{
                        printf("Poped val : %d",returnVal);
                    }
                    break;
            case 3: returnVal = peek();
                    if(returnVal == ERROR){
                        printf("UNDERFLOW");
                    }
                    else{
                        printf("Peeked val : %d",returnVal);
                    }
                    break;
            case 4: display();
                    break;
            default:    printf("\nERROR: WRONG OPTION\n");
                        break;
        }
    }

	return 0;
}
