#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct node {
	int data;
	struct node * child;
	struct node * sibling;
}node;
node * createNode(int data) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->child = NULL;
	newNode->sibling = NULL;
	newNode->data = data;
	return newNode;
}
void addNode(node* parent, node* child) {
	if (parent->child == NULL) parent->child = child;
	else {
		node*curr = parent->child;
		while (curr->sibling != NULL)curr = curr->sibling;
		curr->sibling = child;
	}
}
void printTree(node* node, int depth) {
	int i = 0;
	for (i = 0; i < depth; i++)printf(" ");
	printf("%d\n", node->data);
	if (node->child != NULL) printTree(node->child, depth + 1);
	if (node->sibling != NULL)printTree(node->sibling, depth);
}
void pathsum(node* node,int sum) {
	if (node->child == NULL) {
		printf("단말 노드 %d : %d\n", node->data, sum + (node->data));
	}
	if (node->child != NULL) pathsum(node->child, sum + (node->data));
	if (node->sibling != NULL) {
		sum -= node->data;
		pathsum(node->sibling, sum + (node->data));
	}
}
int main() {
	node*root = createNode(1);
	node*B = createNode(2);
	node*C = createNode(3);
	node*D = createNode(4);
	node*E = createNode(5);
	node*F = createNode(6);
	node*G = createNode(7);
	node*H = createNode(8);
	node*I = createNode(9);
	node*J = createNode(10);
	node*K = createNode(11);
	node*L = createNode(12);
	addNode(root, B);
	addNode(B, C);
	addNode(C, D);
	addNode(C, E);
	addNode(B, F);
	addNode(root, G);
	addNode(root, H);
	addNode(H, I);
	addNode(I, J);
	addNode(I, K);
	addNode(H, L);
	printf("트리의 구조는:\n");
	printTree(root, 0);
	pathsum(root, 0);
	return 0;
}