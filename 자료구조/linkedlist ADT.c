#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

typedef struct node {
	char data;
	struct node* next;
}node;

typedef struct list {
	node* head;
	node* curr;
	node* bfor;
	int cnt;
}list;
char command[30];
int len;
int i;
char data;
void displayMainMenu() {
	printf("\n");
	printf("\t++++++++++++++++++++++++++++++++++\n");
	printf("\t     L-L ABSTRACT DATA TYPE\n");
	printf("\t++++++++++++++++++++++++++++++++++\n\n");
	printf("\t  +  : �ڷ� �߰�\n\n");
	printf("\t +0  : �� �տ� �ڷ� �߰�\n\n");
	printf("\t  N  : ���� �ڷ�� �̵�\n\n");
	printf("\t  P  : ���� �ڷ�� �̵�\n\n");
	printf("\t  G  : �ڷ� ��ȯ\n\n");
	printf("\t  <  : �� ������ �̵�\n\n");
	printf("\t  >  : �� �ڷ� �̵�\n\n");
	printf("\t���� : ���ڹ�° ĭ���� �̵�\n\n");
	printf("\t  =  : �ڷ� ��ü\n\n");
	printf("\t  -  : �ڷ� ����\n\n");
	printf("\t  C  : �迭 ��ü ����\n\n");
	printf("\t  ?  : �ڷ��� ���� Ȯ��\n\n");
	printf("\t  #  : �ڷ��� ���� Ȯ��\n\n");
	printf("\t  Q  : ���α׷� ����\n\n");
	printf("\t++++++++++++++++++++++++++++++++++\n");
	printf("\t�� ��ɾ�� ����, ���ͷ� ������\n");
	printf("\t++++++++++++++++++++++++++++++++++\n");
}
void createList(list* plist){
	plist->head = (node*)malloc(sizeof(node));
	plist->head->next = NULL;
	plist->bfor = NULL;
	plist->cnt = 0;
}
void addTail(list* plist, char addData) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->data = addData;
	plist->bfor = plist->curr;
	newnode->next = plist->curr->next;
	plist->curr->next = newnode;
	plist->curr = newnode;
	plist->cnt++;
}
void add(list* plist, char addData) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->data = addData;
	if (plist->head->next == NULL) {
		newnode->next = plist->head->next;
		plist->head->next = newnode;
		plist->curr = newnode;
	}
	else if (command[i] == '0') {
		newnode->data = command[++i];
		newnode->next = plist->head->next;
		plist->head->next = newnode;
		plist->curr = newnode;
	}
	else {
		if (plist->curr->next == NULL) {
			addTail(plist, addData);
			return;
		}
		plist->bfor = plist->curr;
		newnode->next = plist->curr->next;
		plist->curr->next = newnode;
		plist->curr = newnode;
	}
	plist->cnt++;
}

void print(list* plist) {
	if (plist->head->next == NULL) {
		printf("\t ����Ʈ�ȿ� �ڷᰡ �����ϴ�!\n");
		return;
	}
	else {
		node* tmp = plist->head->next;
		printf("\t ");
		while (tmp != NULL) {
			if (tmp == plist->curr) printf("[%c] ", tmp->data);
			else printf("%c ", tmp->data);
			tmp = tmp->next;
		}
		printf("\n");
	}
}
char get_data(list* plist) {
	if (plist->head->next == NULL) {
		printf("\t ����Ʈ�ȿ� �ڷᰡ �����ϴ�.\n");
		return;
	}
	return plist->curr->data;
}
void delete(list* plist) {
	node* tmp;
	if (plist->head->next == NULL) {
		printf("\t ����Ʈ�ȿ� �ڷᰡ �����ϴ�.\n");
		return;
	}
	else {
		if (plist->curr->next == NULL) {
			tmp = plist->curr;
			plist->bfor->next = NULL;
			plist->bfor =plist->head;
			plist->curr = plist->head->next;
			free(tmp);
		}
		else
		{
			tmp = plist->bfor->next;
			plist->bfor->next = tmp->next;
			free(tmp);
			plist->curr = plist->bfor->next;
		}
		plist->cnt--;
	}
}
void next(list* plist) {
	if (plist->head->next == NULL) {
		printf("\t ����Ʈ�ȿ� �ڷᰡ �����ϴ�.\n");
		return;
	}
	if (plist->curr->next == NULL) printf("\t ������ ����̱� ������ �̵��Ұ�\n");
	else {
		plist->bfor = plist->curr;
		plist->curr = plist->curr->next;
	}
}
void pre(list* plist) {
	node* tmp;
	if (plist->head->next == NULL) {
		printf("\t ����Ʈ�ȿ� �ڷᰡ �����ϴ�.\n");
		return;
	}
	if (plist->curr == plist->head->next) printf("\t ��ó�� ����̱� ������ �̵��Ұ�\n");
	else {
		tmp = plist->head;
		plist->curr = plist->bfor;
		while (tmp->next != plist->curr) {
			tmp = tmp->next;
		}
		plist->bfor = tmp;
		plist->bfor->next = plist->curr;
	}
}
void traverse_front(list* plist) {
	if (plist->head->next == NULL) {
		printf("\t ����Ʈ�ȿ� �ڷᰡ �����ϴ�.\n");
		return;
	}
	plist->curr = plist->head->next;
	plist->bfor = plist->head;
}
void traverse_num(list* plist) {
	if (plist->head->next == NULL) {
		printf("\t ����Ʈ�ȿ� �ڷᰡ �����ϴ�.\n");
		return;
	}
	int j = i;
	int cnt = 0;
	int traversecnt[10];
	int mul = 1;
	int num = 0;
	int cntlen;
	while ('0' <= command[j] && command[j] <= '9') {
		traversecnt[cnt] = command[j];
		cnt++;
		j++;
		i++;
	}
	i--;
	j = 0;
	traversecnt[cnt] = '\0';
	for (int k = cnt - 1; k >= 0; k--) {
		num += ((traversecnt[k] - 48) * mul);
		mul *= 10;
		j++;
	}
	if (num > plist->cnt) {
		printf("\t �Է��Ͻ� ���ڰ� ����Ʈ�� ũ�⺸�� Ů�ϴ�.\n");
		return;
	}
	traverse_front(plist);
	for (int k = 1; k < num; k++) {
		next(plist);
	}
}
void traverse_rear(list* plist) {
	if (plist->head->next == NULL) {
		printf("\t ����Ʈ�ȿ� �ڷᰡ �����ϴ�.\n");
		return;
	}
	while (plist->curr->next != NULL) {
		plist->bfor = plist->curr;
		plist->curr = plist->curr->next;
	}
}
void replace(list* plist, char newData) {
	if (plist->head->next == NULL) {
		printf("\t ����Ʈ�ȿ� �ڷᰡ �����ϴ�.\n");
		return;
	}
	plist->curr->data = newData;
}
void is_empty(list* plist) {
	if (plist->head->next == NULL) printf("\t True\n");
	else printf("\t False\n");
}
void is_member(list* plist, char isData) {
	if (plist->head->next == NULL) {
		printf("\t ����Ʈ�ȿ� �ڷᰡ �����ϴ�.\n");
		return;
	}
	int count=0;
	node* tmp = plist->head;
	plist->curr = plist->head;
	while (tmp != NULL) {
		if (tmp->data == isData) {
			printf("\t %d:", count);
			break;
		}
		tmp= tmp->next;
		plist->curr = plist->curr->next;
		count++;
	}
	if (count>plist->cnt) printf("\t %c�� �������� �ʽ��ϴ�.\n", isData);
}
void clear_list(list* plist) {
	if (plist->head->next == NULL) {
		printf("\t �̹� ����Ʈ�ȿ� �ڷᰡ �����ϴ�.\n");
		return;
	}
	node* tmp;
	plist->curr = plist->head->next;
	plist->bfor = plist->head;
	while (plist->curr != NULL) {
		tmp = plist->curr;
		plist->bfor->next = plist->curr->next;
		plist->curr = plist->curr->next;
		free(tmp);
	}
	printf("\t _\n");
}
int quit() {
	return 0;
}

int main() {
	
	int truefalse=1;
	list* A=(list*)malloc(sizeof(list));
	createList(A);
	
	while (truefalse) {
		system("cls");
		displayMainMenu();
		printf("\t ��ɾ� �Է�: ");
		gets(command);
		len = strlen(command);
		for (i = 0; i < len; i++) {
			if (command[i] == '+') {
				data = command[++i];
				add(A, data);
			}
			else if (command[i] == 'L') print(A);
			else if (command[i] == 'G') printf("\t ���� ������: %c\n", get_data(A));
			else if (command[i] == '-') delete(A);
			else if (command[i] == 'N') next(A);
			else if (command[i] == 'P') pre(A);
			else if (command[i] == '#') printf("\t ����Ʈ���� ������ ��: %d\n", A->cnt);
			else if (command[i] == '=') {
				data = command[++i];
				replace(A, data);
			}
			else if (command[i] == '?') {
				data = command[++i];
				is_member(A, data);
			}
			else if (command[i] == 'E') is_empty(A);
			else if (command[i] == '<') traverse_front(A);
			else if ('0' <= command[i] && command[i] <= '9') traverse_num(A);
			else if (command[i] == '>') traverse_rear(A);
			else if (command[i] == 'C') clear_list(A);
			else if (command[i] == 'Q') truefalse = quit();
		}
		print(A);
		system("pause");
	}
	return 0;
}

