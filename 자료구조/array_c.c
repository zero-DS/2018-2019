#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#pragma warning (disable : 4996)
int main() {
	int size1,size2;
	printf("�� �迭�� ũ�⸦ ���� �Է����ּ���: ");
	scanf("%d %d", &size1,&size2);

	int *a = malloc(sizeof(int) * size1);
	int *b = malloc(sizeof(int) * size2);
	int *combine = malloc(sizeof(int)*(size1 + size2));
	int tmp,j=0,k=0,i=0;
	printf("ù��° �迭�� ���� %d���� �Է����ּ���:",size1);
	for (int i = 0; i < size1; i++) {
		scanf("%d", &a[i]);
	}
	printf("�ι�° �迭�� ���� %d���� �Է����ּ���:",size2);
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
	printf("\n����, ���յ� �迭�� ���: ");
	for (int i = 0; i < (size1+size2); i++) {
		printf("%d ", combine[i]);
	}
	system("pause");

	return 0;
}