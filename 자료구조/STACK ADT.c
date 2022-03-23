#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define Max_size 100
typedef struct stack {
	char arr[Max_size];
	int top;
}stack;
char command[30];
int i;
int len;

void initstack(stack * pstack) {
	pstack->top = -1;
}
int is_empty(stack * pstack) {
	if (pstack->top == -1) return 1;
	else return 0;
}
int is_full(stack * pstack) {
	if (pstack->top == Max_size - 1) return 1;
	else return 0;
}
void push(stack * pstack, char data) {
	pstack->top++;
	pstack->arr[pstack->top] = data;
}
char pop(stack * pstack) {
	int tmp;
	tmp = pstack->top;
	pstack->top -= 1;
	return pstack->arr[tmp];
}
void numpop(stack * pstack) {
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
	if (num > pstack->top+1) {
		printf("\t POP하려는 요소의 개수가 스택의 요소의 수보다 큽니다.\n");
		i++;
		return;
	}
	for (int k = 1; k < num; k++) {
		printf("\t %c\n", pop(pstack));
	}
}
void print(stack * pstack) {
	stack tmpstack;
	initstack(&tmpstack);
	char tmp;
	if (is_empty(pstack) == 1) {
		printf("\t _\n");
		return;
	}
	printf("\t ");
	while (pstack->top != -1) {
		tmp = pop(pstack);
		push(&tmpstack, tmp);
	}
	while ((&tmpstack)->top != -1) {
		tmp = pop(&tmpstack);
		if ((&tmpstack)->top == -1) printf("[%c] ", tmp);
		else printf("%c ", tmp);
		push(pstack, tmp);
	}
	printf("\n");
}
void peek(stack * pstack) {
	if (is_empty(pstack) == 1) {
		printf("\t ERROR (peek할 요소가 없습니다.)\n");
		return;
	}
	else printf("\t %c\n", pstack->arr[pstack->top]);
}
int is_member(stack * pstack, char data) {
	stack tmpstack;
	initstack(&tmpstack);
	int returnvalue = 0;
	char tmp;
	while (pstack->top != -1) {
		tmp = pop(pstack);
		if (tmp == data) returnvalue = 1;
		push(&tmpstack, tmp);
	}
	while ((&tmpstack)->top != -1) {
		tmp = pop(&tmpstack);
		push(pstack, tmp);
	}
	return returnvalue;
}
void top(stack * pstack) {
	if (is_empty(pstack) == 1) {
		printf("\t ERROR (스택에 요소가 없습니다.)\n");
		return;
	}
	else printf("\t ( %d, %c )\n", pstack->top + 1, pstack->arr[pstack->top]);
}
void replace(stack * pstack, char data) {
	pop(pstack);
	push(pstack, data);
}
void clear(stack * pstack) {
	while (pstack->top != -1) {
		pop(pstack);
	}
}
void displayMainMenu() {
	printf("\n");
	printf("\t+++++++++++++++++++++++++++++++++++\n");
	printf("\t   STACK ABSTRACT DATA TYPE\n");
	printf("\t+++++++++++++++++++++++++++++++++++\n\n");
	printf("\t  +  : 자료 추가\n\n");
	printf("\t  L  : 자료 전체 출력\n\n");
	printf("\t  P  : TOP의 자료 반환\n\n");
	printf("\t  =  : 자료 교체\n\n");
	printf("\t  -  : 자료 삭제\n\n");
	printf("\t  F  : 스택이 꽉 찼는지 확인\n\n");
	printf("\t  E  : 스택이 비었는지 확인\n\n");
	printf("\t  T  : TOP의 위치와 자료 반환\n\n");
	printf("\t  C  : 배열 전체 비우기\n\n");
	printf("\t  ?  : 자료의 존재 확인\n\n");
	printf("\t  #  : 자료의 갯수 확인\n\n");
	printf("\t  Q  : 프로그램 종료\n\n");
	printf("\t+++++++++++++++++++++++++++++++++++\n");
	printf("\t각 명령어는 띄어쓰기, 엔터로 구분함\n");
	printf("\t+++++++++++++++++++++++++++++++++++\n");
}
int main() {
	stack s;
	initstack(&s);
	int tf = 1;
	while (tf) {
		system("cls");
		displayMainMenu();
		printf("\t 명령어를 입력해주세요:");
		gets(command);
		len = strlen(command);
		for (i = 0; i < len; i++) {
			if (command[i] == '+') {
				if (is_full(&s) == 1) {
					printf("\t 스택이 꽉 찼습니다.\n");
					break;
				}
				else push(&s, command[++i]);
			}
			else if ('0' <= command[i] && command[i] <= '9') numpop(&s);
			else if (command[i] == '-') {
				if (is_empty(&s) == 1) {
					printf("\t ERROR (pop할 요소가 없습니다.)\n");
					break;
				}
				else printf("\t %c\n", pop(&s));
			}
			else if (command[i] == 'L') print(&s);
			else if (command[i] == 'P') peek(&s);
			else if (command[i] == 'F') {
				if (is_full(&s) == 0) printf("\t FALSE\n");
				else printf("\t TRUE\n");
			}
			else if (command[i] == 'E') {
				if (is_empty(&s) == 0) printf("\t FALSE\n");
				else printf("\t TRUE\n");
			}
			else if (command[i] == '?') {
				if (is_member(&s,command[++i]) == 0) printf("\t FALSE\n");
				else printf("\t TRUE\n");
			}
			else if (command[i] == '=') replace(&s, command[++i]);
			else if (command[i] == 'T') top(&s);
			else if (command[i] == 'C') clear(&s);
			else if (command[i] == '#') printf("\t 데이터의 개수:%d\n", (&s)->top + 1);
			else if (command[i] == 'Q') {
				printf("\t 프로그램을 종료합니다.\n");
				tf = 0;
			}
		}
		print(&s);
		system("pause");
	}
	return 0;
}