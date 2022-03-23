#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning (disable:4996)
typedef struct stack {
	char arr[100];
	int top;
}stack;
void initstack(stack * pstack) {
	pstack->top = -1;
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

int check(char* senten, int len) {
	stack newstack;
	initstack(&newstack);
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < len; i++) {
		if (senten[i] == 39) {
			if (cnt1%2==0) push(&newstack, 39);
			else pop(&newstack);
			cnt1++;
		}
		else if (senten[i] == 34){
			if (cnt2 % 2 == 0) push(&newstack, 34);
			else pop(&newstack);
			cnt2++;
		}
		else if (senten[i] == 40)push(&newstack, 40);    //(
		else if (senten[i] == 41) {
			if ((&newstack)->arr[(&newstack)->top] == 40) pop(&newstack);
			else return 0;
		}
		else if (senten[i] == 123)push(&newstack, 123);  //{
		else if (senten[i] == 125){
			if ((&newstack)->arr[(&newstack)->top] == 123) pop(&newstack);
			else return 0;
		}
		else if (senten[i] == 91)push(&newstack, 91);    //[
		else if (senten[i] == 93) {
			if ((&newstack)->arr[(&newstack)->top] == 91) pop(&newstack);
			else return 0;
		}
	}
	if ((&newstack)->top==-1) return 1;
	else return 0;
}

int main() {
	char* sentence;
	sentence = (char*)malloc(sizeof(char));
	int len;
	printf("검사할 문장을 입력하세요:");
	gets(sentence);
	len = strlen(sentence);
	if (check(sentence, len) == 1) {
		printf("문법적으로 옳습니다.\n");
		system("pause");
		return 0;
	}
	else {
		printf("문법적으로 틀립니다.\n");
		system("pause");
		return 0;
	}
	
}