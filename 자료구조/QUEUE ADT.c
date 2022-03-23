#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define Max_size 6
typedef struct queue {
	int front;
	int rear;
	char quArr[Max_size+1];
}queue;
char command[30];
int i, len;
void queueInit(queue *pq) {
	pq->front = 0;
	pq->rear = 0;
}
int is_empty(queue *pq) {
	if (pq->front == pq->rear) return 1;
	else return 0;
}
int is_full(queue* pq) {
	if ((pq->rear + 1) % (Max_size+1) == pq->front) return 1;
	else return 0;
}
int nextIndex(int position) {
	if (position == Max_size) return 0;
	else return position + 1;
}
void enqueue(queue *pq, char data) {
	if (is_full(pq) == 1) {
		printf("\t ť�� �� á���ϴ�.\n");
		return;
	}
	pq->rear = nextIndex(pq->rear);
	pq->quArr[pq->rear] = data;
}
char dequeue(queue* pq) {
	if (is_empty(pq) == 1) {
		printf("\t ť�� ���� ����ֽ��ϴ�.\n");
		return;
	}
	pq->front = nextIndex(pq->front);
	return pq->quArr[pq->front];
}
void numdequeue(queue* pq) {
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
	if (num == 0) return;
	for (int k = 1; k < num; k++) {
		printf("\t %c\n",dequeue(pq));
	}
}
void print(queue *pq) {
	if (is_empty(pq) == 1) {
		printf("\t _\n");
		return;
	}
	else {
		printf("\t ");
		if (pq->front < pq->rear) {
			for (int i = pq->front + 1; i <= pq->rear; i++) {
				printf("%c ", pq->quArr[i]);
			}
		}
		else {
			for (int i = pq->front + 1; i < Max_size+1; i++) {
				printf("%c ", pq->quArr[i]);
			}
			for (int i = 0; i <= pq->rear; i++) {
				printf("%c ", pq->quArr[i]);
			}
		}
		printf("\n");
	}
}
void peek(queue* pq) {
	if (is_empty(pq) == 1) {
		printf("\t ť�� ���� ����ֽ��ϴ�.\n");
		return;
	}
	printf("\t %c\n", pq->quArr[pq->front + 1]);
}
void head(queue* pq) {
	printf("\t %d\n", (pq->front % Max_size) -1);
}
void tail(queue* pq) {
	printf("\t %d\n", (pq->rear % Max_size) -1);
}
int data_count(queue* pq) {
	int returnvalue=0;
	if (pq->front < pq->rear) {
		for (int i = pq->front + 1; i <= pq->rear; i++) {
			returnvalue++;
		}
	}
	else {
		for (int i = pq->front + 1; i < Max_size+1; i++) {
			returnvalue++;
		}
		for (int i = 0; i <= pq->rear; i++) {
			returnvalue++;
		}
	}
	return returnvalue;
}
int is_member(queue* pq, char data) {
	if (is_empty(pq) == 1) {
		printf("\t ť�� ���� ����ֽ��ϴ�.\n");
		return;
	}
	else {
		if (pq->front < pq->rear) {
			for (int i = pq->front + 1; i <= pq->rear; i++) {
				if (data == pq->quArr[i]) return 1;
			}
		}
		else {
			for (int i = pq->front + 1; i < Max_size+1; i++) {
				if (data == pq->quArr[i]) return 1;
			}
			for (int i = 0; i <= pq->rear; i++) {
				if (data == pq->quArr[i]) return 1;
			}
		}
		return -1;
	}
}
void replace(queue* pq, char ndata) {
	if (is_empty(pq) == 1) {
		printf("\t ť�� ���� ����ֽ��ϴ�.\n");
		return;
	}
	pq->quArr[pq->rear] = ndata;
}
void clear(queue* pq) {
	if (is_empty(pq) == 1) {
		printf("\t ť�� ���� ����ֽ��ϴ�.\n");
		return;
	}
	else {
		while (data_count(pq) != 0) {
			dequeue(pq);
		}
	}
}
void displayMainMenu() {
	printf("\n");
	printf("\t+++++++++++++++++++++++++++++++++++\n");
	printf("\t     QUEUE ABSTRACT DATA TYPE\n");
	printf("\t+++++++++++++++++++++++++++++++++++\n\n");
	printf("\t  +  : �ڷ� �߰�\n\n");
	printf("\t  L  : �ڷ� ��ü ���\n\n");
	printf("\t  P  : HEAD�� �ڷ� Ȯ��\n\n");
	printf("\t  =  : TAIL�� �ڷ� ��ü\n\n");
	printf("\t  -  : HEAD�� �ڷ� ��ȯ\n\n");
	printf("\t  F  : ������ �� á���� Ȯ��\n\n");
	printf("\t  E  : ������ ������� Ȯ��\n\n");
	printf("\t  T  : TAIL�� ��ġ ��ȣ Ȯ��\n\n");
	printf("\t  H  : HEAD�� ��ġ ��ȣ Ȯ��\n\n");
	printf("\t  C  : �迭 ��ü ����\n\n");
	printf("\t  ?  : �ڷ��� ���� Ȯ��\n\n");
	printf("\t  #  : �ڷ��� ���� Ȯ��\n\n");
	printf("\t  Q  : ���α׷� ����\n\n");
	printf("\t+++++++++++++++++++++++++++++++++++\n");
	printf("\t�� ��ɾ�� ����, ���ͷ� ������\n");
	printf("\t+++++++++++++++++++++++++++++++++++\n");
}
int main(){
	queue q;
	queueInit(&q);
	int truefalse = 1;
	while (truefalse) {
		system("cls");
		displayMainMenu();
		printf("\t ��ɾ �Է����ּ���:");
		gets(command);
		len = strlen(command);
		for (i = 0; i < len; i++) {
			if (command[i] == '+') enqueue(&q, command[++i]);
			else if (command[i] == 'L') print(&q);
			else if (command[i] == 'P') peek(&q);
			else if (command[i] == '-') printf("\t %c\n",dequeue(&q));
			else if ('0' <= command[i]&&command[i] <= '9') numdequeue(&q);
			else if (command[i] == 'F') {
				if (is_full(&q) == 1) printf("\t TRUE\n");
				else printf("\t FALSE\n");
			}
			else if (command[i] == 'E') {
				if (is_empty(&q) == 1) printf("\t TRUE\n");
				else printf("\t FALSE\n");
			}
			else if (command[i] == '#') printf("\t �������� ����: %d\n", data_count(&q));
			else if (command[i] == 'H') head(&q);
			else if (command[i] == 'T') tail(&q);
			else if (command[i] == '?') {
				if (is_member(&q, command[++i]) == 1) printf("\t 1\n");
				else printf("\t -1\n");
			}
			else if (command[i] == '=') replace(&q, command[++i]);
			else if (command[i] == 'C') clear(&q);
			else if (command[i] == 'Q') {
				printf("\t ���α׷��� �����մϴ�.\n");
				truefalse = 0;
			}
		}
		print(&q);
		system("pause");
	}
	return 0;
}