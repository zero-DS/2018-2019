#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

void displayMainMenu();
void insert(char array[], char data);
void traverse_front();
void traverse_rear();
void delete(char array[]);
void get_data(char array[]);
void replace(char array[], char new_data);
void empty(char array[]);
void move(char array[]);
int data_count(char array[]);
void print(char array[]);
void sort(char array[]);

char command[30] = { 0 };
int len;
int size = 0;
int index = -1;
int i;
int main()
{
	char my_array[30] = { 0 };
	int trueFalse = 1;
	while (trueFalse)
	{
		system("cls");
		displayMainMenu();
		printf("\t ��ɾ� �Է� : ");
		gets(command);
		len = strlen(command);
		for (i = 0; i < len; i++) {
			if (command[i] == '+') {
				insert(my_array, command[++i]);
			}
			else if (command[i] == '<') {
				if (size == 0) {
					printf("\t �迭�ȿ� �ڷᰡ �����ϴ�.\n");
					break;
				}
				traverse_front();
			}
			else if (command[i] == '>') {
				if (size == 0) {
					printf("\t �迭�ȿ� �ڷᰡ �����ϴ�.\n");
					break;
				}
				traverse_rear();
			}
			else if (command[i] == '-') {
				if (size == 0) {
					printf("\t �迭�ȿ� �ڷᰡ �����ϴ�.\n");
					break;
				}
				delete(my_array);
			}
			else if (command[i] == '=') {
				if (size == 0) {
					printf("\t �迭�ȿ� �ڷᰡ �����ϴ�.\n");
					break;
				}
				replace(my_array, command[++i]);
			}
			else if (command[i] == '@') {
				if (size == 0) {
					printf("\t �迭�ȿ� �ڷᰡ �����ϴ�.\n");
					break;
				}
				get_data(my_array);
			}
			else if (command[i] == 'E') {
				if (size == 0) {
					printf("\t �迭�ȿ� �ڷᰡ �����ϴ�.\n");
					break;
				}
				empty(my_array);
			}
			else if (command[i] == 'L') {
				if (size == 0) {
					printf("\t �迭�ȿ� �ڷᰡ �����ϴ�.\n");
					break;
				}
				print(my_array);
			}
			else if (command[i] == 'N') {
				if (size == 0) {
					printf("\t �迭�ȿ� �ڷᰡ �����ϴ�.\n");
					break;
				}
				if (index == size - 1) {
					printf("\t �� �ڷ� �� �� �����ϴ�");
					break;
				}
				else index++;
			}
			else if (command[i] == 'P') {
				if (size == 0) {
					printf("\t �迭�ȿ� �ڷᰡ �����ϴ�.\n");
					break;
				}
				if (index == 0) {
					printf("\t �� ������ �� �� �����ϴ�");
					break;
				}
				else index--;
			}
			else if (command[i] == 'C') {
				printf("\t %d���� �����Ͱ� �ֽ��ϴ�\n", data_count(my_array));
			}
			else if (command[i] == 'M') {
				if (size == 0) {
					printf("\t �迭�ȿ� �ڷᰡ �����ϴ�.\n");
					break;
				}
				else if (size == 1) {
					printf("\t �迭�ȿ� �ڷᰡ �Ѱ��ۿ� �����ϴ�.\n");
					break;
				}
				move(my_array);
			}
			else if (command[i] == 'S') {
				if (size == 0) {
					printf("\t �迭�ȿ� �ڷᰡ �����ϴ�.\n");
					break;
				}
				sort(my_array);
			}
		}
		printf("\t ");
		for (int j = 0; j < size; j++) {
			if (j == index) {
				printf("[%c] ", my_array[j]);
			}
			else printf("%c ", my_array[j]);
		}
		system("pause");
	}
	return 0;
}

void displayMainMenu()
{
	printf("\n");
	printf("\t++++++++++++++++++++++++++++++++++\n");
	printf("\t     ARRAY ABSTRACT DATA TYPE\n");
	printf("\t++++++++++++++++++++++++++++++++++\n\n");
	printf("\t M : �ڷ� �ű��\n\n");
	printf("\t N : ���� �ڷ�\n\n");
	printf("\t P : ���� �ڷ�\n\n");
	printf("\t < : �� ������\n\n");
	printf("\t > : �� �ڷ�\n\n");
	printf("\t @ : ���� �ڷ� ��ȯ\n\n");
	printf("\t = : �ڷ� ��ü\n\n");
	printf("\t - : �ڷ� ����\n\n");
	printf("\t E : �迭 ��ü ����\n\n");
	printf("\t S : �迭�� ����\n\n");
	printf("\t++++++++++++++++++++++++++++++++++\n");
	printf("\t�� ��ɾ�� ����, ���ͷ� ������\n");
	printf("\t      �迭�� ũ��� 30�Դϴ�.\n");
	printf("\t++++++++++++++++++++++++++++++++++\n");

}
void insert(char array[], char data) {
	size++;
	for (int j = size - 1; j > index; j--) {
		array[j + 1] = array[j];
	}
	index++;
	array[index] = data;
}
void traverse_front() {
	index = 0;
}
void traverse_rear() {
	index = size - 1;
}
void delete(char array[]) {
	if (index == size - 1) {
		array[index] = 0;
		size--;
		index = 0;
	}
	else {
		for (int j = index + 1; j < size; j++) {
			array[j - 1] = array[j];
		}
		size--;
	}
}
void get_data(char array[]) {
	printf("\t Return %c\n", array[index]);
}
void replace(char array[], char new_data) {
	array[index] = new_data;
}
void empty(char array[]) {
	for (int j = 0; j < size; j++) {
		array[j] = 0;
	}
	size = 0;
	index = -1;
	printf("\t empty array\n");
}
void move(char array[]) {
	char tmp;
	if (command[i + 1] == 'P') {
		if (index == 0) return;
		else {
			tmp = array[index];
			array[index] = array[index - 1];
			array[index - 1] = tmp;
		}
	}
	else if (command[i + 1] == 'N') {
		if (index == size - 1) return;
		
		else {
			tmp = array[index];
			array[index] = array[index + 1];
			array[index + 1] = tmp;
		}
	}
	else if ('0' <= command[i + 1] && command[i + 1] <= '9') {
		if (command[i + 2] == ' ' || command[i + 2] == '\0') {
			if (command[i + 1] - '0' > index) {
				tmp = array[index];
				for (int j = index+1; j <=command[i + 1] - '0'; j++) {
					array[j - 1] = array[j];
				}
				array[command[i + 1] - '0'] = tmp;
				index = command[i + 1] - '0';
			}
			else if (command[i + 1] - '0' <= index) {
				tmp = array[index];
				for (int j = index-1; j >= command[i + 1] - '0'; j--) {
					array[j + 1] = array[j];
				}
				array[command[i + 1] - '0'] = tmp;
				index = command[i + 1] - '0';
			}
		}
		else {
			if ((command[i + 1] - '0') * 10 + (command[i + 2] - '0') > index) {
				tmp = array[index];
				for (int j = index + 1; j <=(command[i + 1] - '0') * 10 + (command[i + 2] - '0'); j++) {
					array[j - 1] = array[j];
				}
				array[(command[i + 1] - '0') * 10 + (command[i + 2] - '0')] = tmp;
				index = (command[i + 1] - '0') * 10 + (command[i + 2] - '0');
			}
			else if ((command[i + 1] - '0') * 10 + (command[i + 2] - '0') <= index) {
				tmp = array[index];
				for (int j = index; j >= (command[i + 1] - '0') * 10 + (command[i + 2] - '0'); j--) {
					array[j + 1] = array[j];
				}
				array[(command[i + 1] - '0') * 10 + (command[i + 2] - '0')] = tmp;
				index = (command[i + 1] - '0') * 10 + (command[i + 2] - '0');
			}
		}
	}
	else {
		printf("\t �������� ���� Ȥ�� N, P�� �Է����ּ���.\n");
	}
}
int data_count(char array[]) {
	int cnt=0;
	for (int j = index; j < size; j++) {
		cnt++;
	}
	for (int j = 0; j < index; j++) {
		cnt++;
	}
	return cnt;
}
void print(char array[]) {
	printf("\t �迭�� ������:");
	for (int j = 0; j < size; j++) {
		printf("%c ", array[j]);
	}
	printf("\n");
}
void sort(char array[]) {
	char tmp;
	for (int k = 0; k < size; k++) {
		for (int j = 0; j < size-1; j++) {
			if (array[j] > array[j + 1]) {
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
		}
	}
}
