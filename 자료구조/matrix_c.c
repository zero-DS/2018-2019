#include <stdio.h>
#include <math.h>
#pragma warning (disable : 4996)
void matsum();
void matdif();
void matmul();
int arr1[4][4] = { 0, };
int arr2[4][4] = { 0, };
int tmp,menu;
int main() {
	
	printf("�ΰ��� ����� ���� �Է¹޾� ������ ������ �� �ֽ��ϴ�.\n");
	printf("ù��° ����� �Է��ϼ���: \n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d", &arr1[i][j]);
		}
	}
	printf("\n�ι�° ����� �Է��ϼ���: \n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d", &arr2[i][j]);
		}
	}
	printf("������ ������ �� �ֽ��ϴ�.\n");
	printf("1�� ��, 2�� ��, 3�� ���� ������ �� �ֽ��ϴ�.\n");
	printf("���ڸ� �Է����ּ���: ");
	scanf("%d", &menu);
	switch (menu) {
	case 1: matsum(); system("pause"); break;
	case 2: matdif(); system("pause"); break;
	case 3: matmul(); system("pause"); break;
	default: printf("1, 2, 3���� ���ڸ� �Է����ּ���."); break;
	}
	return 0;

}
void matsum() {
	printf("�� ����� �� : \n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", arr1[i][j] + arr2[i][j]);
		}
		printf("\n");
	}
}
void matdif() {
	printf("�� ����� �� : \n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", abs(arr1[i][j] - arr2[i][j]));
		}
		printf("\n");
	}
}
void matmul() {
	printf("�� ����� �� : \n");
	for (int i = 0; i < 3; i++) {
		for (int p = 0; p < 3; p++) {
			tmp = 0;
			for (int j = 0; j < 3; j++) {
				tmp += arr1[i][j] * arr2[j][p];
			}
			printf("%d ", tmp);
		}
		printf("\n");
	}

}