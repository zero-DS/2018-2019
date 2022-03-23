#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct node {
	int data;
	struct node * left;
	struct node * right;
}node;
typedef struct tree {
	int height;
	node* root;
}tree;
char command[100];
int i,len;
int heightcnt, nodecnt;
int findflag;
node * insertNode(node* pnode, int data);
void printR(node * pnode);
void print(node*pnode);
void inorder_traversal(node* pnode);
void right_root_left_traversal(node* pnode);
node* get_min(node* pnode);
node* get_max(node* pnode);
node* findNode(node* pnode, int node_value);
void find_node(node* pnode, int node_value);
node* delete_node(node* pnode, int node_value);
void height(node* pnode);
void get_right_child(node* pnode, int node_value);
void get_left_child(node* pnode, int node_value);
void count_node(node* pnode);
void clear(node* pnode);
void displayMainMenu();
int longnum();
int main() {
	
	node* root = NULL;
	int tf = 1;
	while (tf) {
		system("cls");
		displayMainMenu();
		printf("\t 명령어를 입력해주세요:");
		gets(command);
		len = strlen(command);
		for (i = 0; i < len; i++) {
			if (command[i] == '+') {
				root = insertNode(root, longnum());
			}
			else if (command[i] == 'P') {
				printf("\t ");
				print(root);
			}
			else if (command[i] == 'I') {
				printf("\t ");
				inorder_traversal(root);
			}
			else if (command[i] == 'R') {
				printf("\t ");
				right_root_left_traversal(root);
			}
			else if (command[i] == 'N') printf("\t %d\n", get_min(root)->data);
			else if (command[i] == 'X') printf("\t %d\n", get_max(root)->data);
			else if (command[i] == '-') {
				delete_node(root, longnum());
			}
			else if (command[i] == 'F') {
				findflag = 0;
				find_node(root, longnum());
			}
			else if (command[i] == 'H') {
				heightcnt = 0;
				height(root);
				printf("\t %d\n", heightcnt);
			}
			else if (command[i] == 'G') {
				i++;
				get_right_child(root, longnum());
			}
			else if (command[i] == 'L') {
				i++;
				get_left_child(root, longnum());
			}
			else if (command[i] == '#') {
				nodecnt = 0;
				count_node(root);
				printf("\t %d\n", nodecnt);
			}
			else if (command[i] == 'C') {
				clear(root);
				printf("\t _\n");
			}
			else if (command[i] == 'Q') tf = 0;
		}
		system("pause");
	}
	/*
	root = insertNode(root, 33);
	root = insertNode(root, 22);
	root = insertNode(root, 44);
	root = insertNode(root, 30);
	root = insertNode(root, 40);
	print(root);
	system("pause");
	inorder_traversal(root);
	printf("\n");
	right_root_left_traversal(root);
	printf("\n");
	
	printf("%d\n",get_min(root)->data);

	printf("%d\n", get_min(root)->data);
	
	find_node(root, 40);
	findflag = 0;
	find_node(root, 25);
	delete_node(root, 33);
	print(root);
	root = insertNode(root, 33);
	print(root);
	height(root);
	printf("%d\n", heightcnt);
	findflag = 0;
	get_right_child(root, 30);
	findflag = 0;
	get_left_child(root, 22);
	count_node(root);
	printf("%d\n", nodecnt);
	clear(root);
	*/


	return 0;
}

node * insertNode(node* pnode, int data) {
	if (pnode == NULL) {
		pnode = (node*)malloc(sizeof(node));
		pnode->left = NULL;
		pnode->right = NULL;
		pnode->data = data;
		return pnode;
	}
	else {
		if (pnode->data > data) {
			pnode->left = insertNode(pnode->left, data);
		}
		else if (pnode->data < data) {
			pnode->right = insertNode(pnode->right, data);
		}
	}
	return pnode;
}
void printR(node * pnode) {
	if (pnode == NULL) return;
	if (pnode->left == NULL && pnode->right == NULL) {
		printf("%d", pnode->data);
		return;                     //양쪽 다 없음
	}
	else if (pnode->left != NULL && pnode->right != NULL) {
		printf("%d", pnode->data);
		printf("(");
		printR(pnode->left);
		printf(",");
		printR(pnode->right);
		printf(")");                //양쪽 다 존재
	}
	else if (pnode->left != NULL && pnode->right == NULL) {
		printf("%d", pnode->data);
		printf("(");
		printR(pnode->left);
		printf(",)");                //왼쪽만 존재
	}
	else if (pnode->left == NULL && pnode->right != NULL) {
		printf("%d", pnode->data);
		printf("(,");
		printR(pnode->right);
		printf(")");                //오른쪽만 존재
	}
}
void print(node*pnode) {
	printf("(");
	printR(pnode);
	printf(")");
	printf("\n");
}
void inorder_traversal(node* pnode) {
	if (pnode == NULL) return;
	inorder_traversal(pnode->left);
	printf("%d ", pnode->data);
	inorder_traversal(pnode->right);
}
void right_root_left_traversal(node* pnode) {
	if (pnode == NULL) return;
	right_root_left_traversal(pnode->right);
	printf("%d ", pnode->data);
	right_root_left_traversal(pnode->left);
}
node* get_min(node* pnode) {
	node* tmp = pnode;
	while (tmp->left != NULL) tmp = tmp->left;
	return tmp;
}
node* get_max(node* pnode) {
	node* tmp = pnode;
	while (tmp->right != NULL) tmp = tmp->right;
	return tmp;
}
node* findNode(node* pnode, int node_value) {
	if (pnode == NULL) return NULL;
	if (pnode->data == node_value) {
		findflag = 1;
		return pnode;
	}
	else if (pnode->data > node_value) return findNode(pnode->left, node_value);
	else return findNode(pnode->right, node_value);
}
void find_node(node* pnode, int node_value) {
	node* target = NULL;
	target = findNode(pnode, node_value);
	if (findflag == 0) {
		printf("\t Error\n");
		return;
	}
	else {
		printf("\t Root ");
		while (1) {
			if (pnode->data < target->data) {
				printf("> Right ");
				pnode = pnode->right;
			}
			else if (pnode->data > target->data) {
				printf("> Left ");
				pnode = pnode->left;
			}
			else break;
		}
		printf("\n");
	}
}
/*
void delete_node(node* pnode, int node_value) {
	node* tmp = NULL;
	node* printtmp = pnode;
	node* printtmp2 = pnode;
	node* delNode = NULL;
	if (pnode->left == NULL && pnode->right == NULL) {
		pnode = findNode(pnode, node_value);
		free(pnode);
		print(printtmp);
		//양쪽 다 없음
	}
	else if (pnode->left != NULL && pnode->right != NULL) {
		//1번경우 왼쪽 서브트리의 가장큰값
		pnode = findNode(pnode, node_value);
		maxtmp = 0;
		get_max(pnode->left);
		pnode->data = maxtmp;
		delete_node(printtmp, maxtmp);
		print(printtmp);
		//2번경우 오른쪽 서브트리의 가장 작은값
		pnode = findNode(pnode, node_value);
		mintmp = 1000;
		get_min(pnode->left);
		pnode->data = mintmp;
		delete_node(printtmp2, mintmp);
		print(printtmp2);
		//양쪽 다 존재
	}
	else if (pnode->left != NULL && pnode->right == NULL) {
		pnode = findNode(pnode, node_value);
		tmp = pnode;
		pnode = pnode->left;
		free(tmp);
		print(printtmp);
		//왼쪽만 존재
	}
	else if (pnode->left == NULL && pnode->right != NULL) {
		pnode = findNode(pnode, node_value);
		tmp = pnode;
		pnode = pnode->right;
		free(tmp);
		print(printtmp);
		//오른쪽만 존재
	}
}
*/

node* delete_node(node* pnode, int node_value) {
	node* tmp = NULL;

	if (pnode == NULL) return NULL;
	if (pnode->data > node_value) pnode->left = delete_node(pnode->left, node_value);
	else if (pnode->data < node_value)pnode->right = delete_node(pnode->right,node_value);
	else {
		if (pnode->left != NULL && pnode->right != NULL) {
			tmp = get_min(pnode->right);
			pnode->data = tmp->data;
			pnode->right = delete_node(pnode->right, tmp->data);
		}
		else {
			if (pnode->left == NULL) tmp = pnode->right;
			else tmp = pnode->left;
			free(pnode);
			return tmp;
		}
	}
	return pnode;
}

void height(node* pnode) {
	if (pnode == NULL)return;
	heightcnt++;
	height(pnode->left);
	height(pnode->right);
}
void get_right_child(node* pnode, int node_value) {
	pnode = findNode(pnode, node_value);
	if (pnode->right != NULL) printf("%d\n", pnode->right->data);
	else printf("NULL\n");
}
void get_left_child(node* pnode, int node_value) {
	pnode = findNode(pnode, node_value);
	if (pnode->left != NULL) printf("%d\n", pnode->left->data);
	else printf("NULL\n");
}
void count_node(node* pnode) {
	if (pnode == NULL) return;
	nodecnt++;
	count_node(pnode->left);
	count_node(pnode->right);
}
void clear(node* pnode) {
	if (pnode == NULL) return;
	if (pnode->left == NULL && pnode->right == NULL) free(pnode);
	else {
		clear(pnode->left);
		clear(pnode->right);
	}
}
void displayMainMenu() {
	printf("\n");
	printf("\t+++++++++++++++++++++++++++++++++++\n");
	printf("\t   BST ABSTRACT DATA TYPE\n");
	printf("\t+++++++++++++++++++++++++++++++++++\n\n");
	printf("\t  +  : 노드 추가\n\n");
	printf("\t  P  : 트리 출력\n\n");
	printf("\t  I  : 전위 순회\n\n");
	printf("\t  R  : 오른쪽 루트 왼쪽 순회\n\n");
	printf("\t  -  : 노드 삭제\n\n");
	printf("\t  N  : 가장 작은 노드\n\n");
	printf("\t  X  : 가장 큰 노드\n\n");
	printf("\t  F  : 노드 검색\n\n");
	printf("\t  C  : 트리 전체 비우기\n\n");
	printf("\t  G  : 오른쪽 자식 구하기\n\n");
	printf("\t  L  : 왼쪽 자식 구하기\n\n");
	printf("\t  H  : 트리의 높이 확인\n\n");
	printf("\t  #  : 노드의 갯수 확인\n\n");
	printf("\t  Q  : 프로그램 종료\n\n");
	printf("\t+++++++++++++++++++++++++++++++++++\n");
	printf("\t각 명령어는 띄어쓰기, 엔터로 구분함\n");
	printf("\t+++++++++++++++++++++++++++++++++++\n");
}
int longnum() {
	i++;
	int j = i;
	int cnt = 0;
	int cntarr[10];
	int mul = 1;
	int num = 0;
	int cntlen;
	while ('0' <= command[j] && command[j] <= '9') {
		cntarr[cnt] = command[j];
		cnt++;
		j++;
		i++;
	}
	i--;
	j = 0;
	cntarr[cnt] = '\0';
	for (int k = cnt - 1; k >= 0; k--) {
		num += ((cntarr[k] - 48) * mul);
		mul *= 10;
		j++;
	}
	return num;
}