#include <stdio.h>
#include <stdlib.h>

struct node         
{
    int data;
    struct node* link;
};

struct node* NewNodeCreate (int x)      
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data=x;
    newNode->link=NULL;
    return newNode;
};

void insertnode_begining(struct node** head, int x)
{
    struct node* temp = NewNodeCreate(x);
    temp->link = *head;
    *head = temp;
}

void insertnode_end(struct node** head, int x)
{
    struct node* temp = NewNodeCreate(x);
    struct node* temp1 = *head;
    while(temp1->link!=NULL)
    {
        temp1 = temp1->link;
    }
    temp1->link = temp;
}

void insertnode_position(struct node** head, int x, int p)
{
    struct node* temp1 = NewNodeCreate(x);
    if (p == 0) 
    {
        insertnode_begining(head,x);
        return;
    }
    struct node* temp = *head;
    for (int i = 0; temp != NULL && i < p - 1; i++) 
    {
        temp = temp->link;
    }
    temp1->link = temp->link;
    temp->link = temp1;
}

void deletenode_begining(struct node** head)
{
	struct node* temp = *head; 
    *head = temp->link;
    free(temp);
}

void deletenode_end(struct node** head)
{
    struct node* temp = *head;
    while (temp->link->link != NULL) 
    {
        temp = temp->link;
    }
    free(temp->link);
    temp->link = NULL;
}

void deletenode_position(struct node** head, int p)
{
    struct node* temp = *head;
    if (p == 0) 
    {
        deletenode_begining(head);
        return;
    }
    for (int i = 0; temp != NULL && i < p - 1; i++) 
    {
        temp = temp->link;
    }
    struct node* link = temp->link->link;
    free(temp->link);
    temp->link = link;;
}

void search(struct node* head, int a)
{
	struct node* temp = head;
	while(temp!=NULL)
	{
		if(temp->data == a) 
		{
			printf("\n%d Found in List!",a);
			return;
		}
		temp = temp->link;
	}
	printf("\n%d Not foundin List",a);
}

void display(struct node* head)
{
    struct node* temp = head;
    while (temp != NULL) 
    {
        printf("%d >>> ", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");
}


int main()
{
    struct node* head = NULL;
    
    insertnode_begining(&head, 5);
    display(head); 
    
    insertnode_end(&head, 10);
    display(head); 
    
    insertnode_end(&head, 20);
    display(head); 
    
    insertnode_end(&head, 30);
    display(head); 
    
    insertnode_position(&head, 15, 2);
    display(head);
    
    deletenode_begining(&head);
    display(head); 
    
    deletenode_end(&head);
    display(head); 
    
    deletenode_position(&head, 1);
    display(head);
    
    printf("Searching for 10\n");
    search(head, 10);
    return 0;
}
