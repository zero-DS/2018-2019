#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#pragma warning (disable : 4996)
int main() {
	int size1,size2;
	printf("두 배열의 크기를 각각 입력해주세요: ");
	scanf("%d %d", &size1,&size2);

	int *a = malloc(sizeof(int) * size1);
	int *b = malloc(sizeof(int) * size2);
	int *combine = malloc(sizeof(int)*(size1 + size2));
	int tmp,j=0,k=0,i=0;
	printf("첫번째 배열의 원소 %d개를 입력해주세요:",size1);
	for (int i = 0; i < size1; i++) {
		scanf("%d", &a[i]);
	}
	printf("두번째 배열의 원소 %d개를 입력해주세요:",size2);
	for (int i = 0; i < size2; i++) {
		scanf("%d", &b[i]);
	}
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size1 - 1; j++) {
			if (a[j] > a[j + 1]) {
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
	for (int i = 0; i < size2; i++) {
		for (int j = 0; j < size2 - 1; j++) {
			if (b[j] > b[j + 1]) {
				tmp = b[j];
				b[j] = b[j + 1];
				b[j + 1] = tmp;
			}
		}
	}
	i = 0, j = 0, k = 0;
	a[size1] = INT_MAX, b[size2] = INT_MAX;
	while (1) {
		
		if (a[j] <= b[k]) {
			combine[i] = a[j];
			if (j < size1) {
				j++;
				i++;
			}
		}
		else if (a[j] > b[k]) {
			combine[i] = b[k];
			if (k < size2) {
				k++;
				i++;
			}
		}
		if (i == (size1+size2)) break;
	}
	printf("\n정렬, 병합된 배열의 결과: ");
	for (int i = 0; i < (size1+size2); i++) {
		printf("%d ", combine[i]);
	}
	system("pause");

	return 0;
}