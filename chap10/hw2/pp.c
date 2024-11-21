#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *next;
};

struct node *head=NULL, *tail=NULL;

void addq(int data){
	struct node *n_node = (struct node *)malloc(sizeof(struct node));
	n_node->data = data;
	n_node->next = NULL;
	if(tail != NULL){
		tail->next = n_node;
	}
	tail = n_node;

	if(head == NULL)
		head = n_node;
}

int delete(){
	if(head == NULL){
		printf("Queue is empty!!\n");
		return -1;
	}

	struct node *temp = head;
	int data = temp -> data;
	head = head->next;

	if(head == NULL){
		tail==NULL;
	}

	free(temp);
	return data;
}

int main(){
	int num;
	int count=0;
	while(scanf("%d",&num) > 0){
		addq(num);
		count++;
	}

	printf("Print queue\n");
	while(count != 0){
		printf("%d\n",delete());
		count --;
	}
}
