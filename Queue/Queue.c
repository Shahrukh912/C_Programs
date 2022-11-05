#include<stdio.h>
#define ERROR -999999

//Global variables.
int size = 5;
int front = -1,rear = -1;
int Queue[5]; //make this same as the size variable.

int enqueue(int x){ //return defination 0 means success and ERROR means error.
    //checking for overflow
    if(rear == size - 1){
        return ERROR; 
    }
    //Inserting
    rear++;
    Queue[rear] = x;

    //setting the front pointer for initial insert
    if(front == -1){
        front = 0;
    }    
    return 0;
}

int dequeue(){
    int x;
    if(front == -1){
        return ERROR;
    }
    //deletion
    x = Queue[front];
    front ++;
    
    //Resetting both the pointers
    if(front>rear){
        front = -1;
        rear = -1;
    }
    return x; // it means first it returns the top value and then decrease the top.
}

int peek(){
    if(front == -1){
        return ERROR;
    }
    return Queue[front]; //return the last value
}

void display(){
    int i;
    if(front == -1){
        printf("Its Empty");
    }
    for(i=front;i<=rear;i++){
        printf("%d  ",Queue[i]);
    }
}


int countDigits(int x){
    int i=0;
    if(x == 0){
        return 1;
    }
    else if(x<0){
        i++;
        //x*=-1;
    }
    for(;x!=0;i++,x/=10);
    return i;
}
void displayForNerds(){
    int i,fcount=0,rcount=0;
    printf("front : %d  | rear : %d  (^ is for front pointer, * is for rear pointer)\n",front,rear);
    if(front == -1){
        printf("Its Empty\n");
        fcount = rcount = (size+1)*4;
    }

    
    for(i=0;i<front;i++){
        printf("__  ");
        rcount = fcount+=4; //increment 4 character.
    }
    for(;i<=rear;i++){
        printf("%d  ",Queue[i]);
        if(i != rear)
            rcount += (countDigits(Queue[i])+2);
    }
    for(;i<=size;i++){
        printf("__  ");
    }

    //displaying the pointers for the front and rear 
    printf("\n");
    for(i=0;i<fcount;i++){
        printf(" ");
    }
    printf("^");
    for(;i<rcount;i++){
        printf(" ");
    }
    printf("*");
}


void menu(){
    int i=1;
    printf("\n\n------------MENU-------------------------------\n");
    printf("%d. Enqueue/s\n",i++);
    printf("%d. Dequeue\n",i++);
    printf("%d. PEEK (get the last inserted value without deleting)\n",i++);
    printf("%d. Display\n",i++);
    printf("%d. Display Details\n",i++);
    printf("-1. TO EXIT");
}
int main(){
	int choice=-9999,x,returnVal;

    while(choice != -1){
        printf("\n\nEnter your choice (To see menu type 0): ");
        scanf("%d",&choice);

        switch (choice){
            case -1:break; //just so that we would not to see that Wrong option error. because after switch it will go to the while condition and then stop.
            case 0: menu();
                    break;
            case 1: printf("Enter Value : ");
                    scanf("%d",&x);
                    returnVal = enqueue(x);
                    printf("%s",(returnVal == ERROR)?"OVERFLOW":"Enqueued Successfully");
                    break;
            case 2: returnVal = dequeue();
                    if(returnVal == ERROR){
                        printf("UNDERFLOW");
                    }
                    else{
                        printf("Dequeued value : %d",returnVal);
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
            case 5: displayForNerds();
                    break;       
            default:    printf("\nERROR: WRONG OPTION\n");
                        break;
        }
    }

	return 0;
}
