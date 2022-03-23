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
	
	printf("두개의 행렬을 각각 입력받아 연산을 실행할 수 있습니다.\n");
	printf("첫번째 행렬을 입력하세요: \n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d", &arr1[i][j]);
		}
	}
	printf("\n두번째 행렬을 입력하세요: \n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d", &arr2[i][j]);
		}
	}
	printf("연산을 실행할 수 있습니다.\n");
	printf("1은 합, 2는 차, 3은 곱을 실행할 수 있습니다.\n");
	printf("숫자를 입력해주세요: ");
	scanf("%d", &menu);
	switch (menu) {
	case 1: matsum(); system("pause"); break;
	case 2: matdif(); system("pause"); break;
	case 3: matmul(); system("pause"); break;
	default: printf("1, 2, 3중의 숫자를 입력해주세요."); break;
	}
	return 0;

}
void matsum() {
	printf("두 행렬의 합 : \n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", arr1[i][j] + arr2[i][j]);
		}
		printf("\n");
	}
}
void matdif() {
	printf("두 행렬의 차 : \n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", abs(arr1[i][j] - arr2[i][j]));
		}
		printf("\n");
	}
}
void matmul() {
	printf("두 행렬의 곱 : \n");
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