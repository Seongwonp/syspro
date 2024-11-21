#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *next;
};

struct node *top = NULL;

void push(int data){
	struct node *n_node = (struct node *)malloc(sizeof(struct node));
	if(n_node == NULL){
		printf("Memory error\n");
		return;
	}
	n_node->data = data;
	n_node->next = top;
	top = n_node;
}

int pop(){
	if(top == NULL){
		printf("Stack is empty!!\n");
		return -1;
	}
	struct node *temp = top;

	int data = temp->data;
	top = top->next;
	free(temp);
	return data;
}


int main(){
	int num;
	while(scanf("%d",&num)>0){
		push(num);
	}

	printf("Print stack\n");

	while(top!=NULL){
		printf("%d\n",pop());
	}

	return 0;
}
