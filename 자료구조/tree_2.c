#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct node {
	char data;
	struct node * left;
	struct node * right;
}node;
node* makeNode() {
	node* nd = (node*)malloc(sizeof(node));
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}
void setData(node* pnode, char data) {
	pnode->data = data;
}
void makeLeftSub(node* main, node* sub) {
	if (main->left != NULL) free(main->left);
	main->left = sub;
}
void makeRightSub(node* main, node* sub) {
	if (main->right != NULL) free(main->right);
	main->right = sub;
}
char getData(node* pnode) {
	return pnode->data;
}
node * getLeftSub(node * pnode) {
	return pnode->left;
}
node * getRightSub(node * pnode) {
	return pnode->right;
}
void reverse(node* pnode) {
	if (pnode->left != NULL) reverse(pnode->left);
	if (pnode->right != NULL) reverse(pnode->right);
	node*tmp = pnode->left;
	pnode->left = pnode->right;
	pnode->right = tmp;
}
void printTree(node* pnode, int depth) {
	int i = 0;
	for (i = 0; i < depth; i++)printf(" ");
	printf("%c\n", pnode->data);
	if (pnode->left != NULL) printTree(pnode->left, depth + 1);
	if (pnode->right != NULL)printTree(pnode->right, depth+1);
}
void printDesc(node* pnode, int depth) {
	if(depth!=0) printf("%c\n", pnode->data);
	if (pnode->left != NULL) {
		printf("%c의 left는: ",pnode->data);
		printDesc(pnode->left,depth+1);
	}
	if (pnode->right != NULL) {
		printf("%c의 right는: ", pnode->data);
		printDesc(pnode->right,depth+1);
	}
}
int main() {
	node* A = makeNode();
	node* B = makeNode();
	node* C = makeNode();
	node* D = makeNode();
	node* E = makeNode();
	node* F = makeNode();
	node* G = makeNode();

	setData(A, 'a');
	setData(B, 'b');
	setData(C, 'c');
	setData(D, 'd');
	setData(E, 'e');
	setData(F, 'f');
	setData(G, 'g');

	makeLeftSub(A, B);
	makeRightSub(A, C);
	makeLeftSub(B, D);
	makeRightSub(B, E);
	makeRightSub(C, F);
	makeLeftSub(F, G);
	printTree(A, 0);
	printDesc(A, 0);
	printf("\n좌우 child를 바꾼 이후:\n");
	reverse(A);
	printTree(A, 0);
	printDesc(A,0);
	system("pause");
	return 0;
}