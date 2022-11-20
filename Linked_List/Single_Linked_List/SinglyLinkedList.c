#include<stdio.h>

struct node{
    int info;
    struct node *next;
};
struct node *head = NULL;

//To get a new Node using malloc
struct node * getNewNode(){
    return ((struct node*) malloc(sizeof(struct node)) );
}
void insertAtStart(int x){
    struct node *newNode;
    newNode = getNewNode(); //get a new node
    newNode->info = x; //insert the value in the newnode

    newNode->next = head; //copy address of first node into the next of newnode.
    head = newNode;//make newnode the new head node
}
int insertAfter(int x,int skey){ //return value explaination : 0 means failed non-zero means success
    //this function insert after the search value provided.
    struct node *temp,*newNode;
    
    temp = head; //copy the head for traversal.
    while(temp != NULL){
        if(temp->info == skey){
            newNode = getNewNode(); //get a new node
            newNode->info = x; //insert the value in the newnode
            
            newNode->next = temp->next;
            temp->next = newNode;
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
void insertAtEnd(int x){
    struct node *temp,*newNode;
    newNode = getNewNode(); //get a new node
    newNode->info = x; //insert the value in the newnode
    newNode->next = NULL;//insert NULL character to the next as it will be going to the last anyway.

    temp = head; //copy the head for traversal.

    if(head == NULL){ //checking if the head is null then this newnode would become first node.
        head = newNode;
        return; //exit
    }

    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;// add newnode to the end of the list.
}

//Deleting values.
//Return value explaination: -1 means Emty , 0 means faild and +value means success
int deteleAtStart(){
    struct node *temp;
    if(head == NULL){
        return -1;
    }
    temp = head; //save the head.
    head = head->next; // move the head one step forward
    free(temp); //delete the first node.
    return 1;
}
int deleteAtEnd(){
    struct node *temp,*prev;
    if(head == NULL){
        return -1;
    }
    temp = head;
    while(temp->next != NULL){
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    free(temp);
    return 1;
}
int deleteValue(int skey){
    struct node *temp,*prev;
    if(head == NULL){
        return -1;
    }
    temp = head;
    
    //Special case: if the search value is the first node the the head has to be change.
    if(head->info == skey){
        head = head->next;
        free(temp);
        return 1;
    }
    
    //Normal case in which loop occurs
    while(temp != NULL){
        if(temp->info == skey){
            prev->next = temp->next;
            free(temp);
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
}

//Reversing Entire Linked list.
//Return value explaination: -1 means Emty , 0 means faild and +value means success
int reverse(){
    struct node *temp,*swap,*ahead,*prev;
    //temp is use to point current, prev to point previous, ahead to keep next node, and swap is temporary just for swaping.
    if(head == NULL){
        return -1;
    }

    temp = head; //save the head.
    prev = NULL;

    while(temp != NULL){
        ahead = temp->next;
        swap = prev;
        prev = temp;
        temp->next = swap;

        temp = ahead;
    }
    
    head = prev; 
    return 1;
}

int count(){
    struct node *temp;
    int count=0;
    temp = head; //copy the head for traversal.

    while(temp != NULL){
        count++;//count the node.
        temp = temp->next;
    }
    return count;
}
void display(){
    struct node *temp;
    temp = head; //copy the head for traversal.

    if(head == NULL){
        printf("IT\'S EMPTY");
        return;
    }
    while(temp != NULL){
        printf("%d  ",temp->info); //display the info.
        temp = temp->next;
    }
}
void displayForNerds(){
    struct node *temp;
    temp = head; //copy the head for traversal..
    printf("head points at : %u\n\n",head);
    
    if(head == NULL){
        printf("IT\'S EMPTY");
        return;
    }
    while(temp != NULL){
        printf("temp points at: %u  | ",temp);
        printf("\t[temp->info : %d  | temp->next : %u]\n",temp->info,temp->next); 
        temp = temp->next;
    }
}

void menu(){
    int i=1;
    printf("\n\n------------MENU-------------------------------\n");
    printf("%d. Count the number of Node/s\n",i++);
    printf("%d. Display entire Linked List\n",i++);
    printf("%d. To insert at begining\n",i++);
    printf("%d. To insert at end\n",i++);
    printf("%d. To insert at after some node value\n",i++);
    printf("%d. To delete at begining\n",i++);
    printf("%d. To delete at end\n",i++);
    printf("%d. To delete a particular node by value\n",i++);
    printf("%d. Reverse entire Linked list\n",i++);
     printf("%d. Display nodes with full details (for nerds)\n",i++);
    printf("-1. TO EXIT");
}
int main(){
	int choice=-9999,x,skey,temp;

    while(choice != -1){
        printf("\n\nEnter your choice (To see menu type 0): ");
        scanf("%d",&choice);

        switch (choice){
            case -1:break; //just so that we not to see that Wrong option error. because after switch it will go to the while condition and then stop.
            case 0: menu();
                    break;
            case 1: printf("No of Nodes : %d",count());
                    break;
            case 2: display();
                    break;
            case 3: printf("Enter value to insert : ");
                    scanf("%d",&x);
                    insertAtStart(x);
                    printf("Inserted Successfully");
                    break;
            case 4: printf("Enter value to insert : ");
                    scanf("%d",&x);
                    insertAtEnd(x);
                    printf("Inserted Successfully");
                    break;
            case 5: display();
                    printf("\nEnter value to insert : ");
                    scanf("%d",&x);
                    printf("Enter the node value after which you want to insert : ");
                    scanf("%d",&skey);
                    temp = insertAfter(x,skey);
                    printf("%s",(temp==1)?"Inserted Successfully":"Search Value Not Found");
                    break;
            case 6: temp = deteleAtStart();
                    printf("%s",(temp==1)?"Deleted Successfully":"It's Empty");
                    break;
            case 7: temp = deleteAtEnd();
                    printf("%s",(temp==1)?"Deleted Successfully":"It's Empty");
                    break;
            case 8: display();
                    printf("\nEnter value to delete : ");
                    scanf("%d",&skey);
                    temp = deleteValue(skey);
                    printf("%s",(temp>0)?"Deleted Successfully":(temp==-1)?"It's Empty":"Search Value Not Found");
                    break;
            case 9: temp = reverse();
                    printf("%s",(temp>0)?"Reversed Successfully":(temp==-1)?"It's Empty":"Search Value Not Found");
                    break;
            case 10 : displayForNerds();
                    break;
            default:    printf("\nERROR: WRONG OPTION\n");
                        break;
        }
    }

	return 0;
}
