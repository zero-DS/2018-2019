#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable : 4996)

int displayMainMenu();
void searching();
void filtering();
void price();
void sorting();
void buying();

struct cleaner
{
	char name[30];
	int waterclean;
	int cable;
	int price;
	int numPurchase;
	int rating;
};

struct cleaner cleanerlist[10] = {
	{ "Dyson100", 0, 1, 10000, 30, 4 },
{ "Dyson200", 1, 0, 15000, 27, 5 },
{ "Samsung100", 0, 0, 12000, 19, 3 },
{ "Samsung200", 1, 0, 14000, 44, 5 },
{ "Samsung300", 1, 1, 20000, 28, 4 },
{ "Lg100", 0, 1, 8000, 16, 2 },
{ "Lg200", 0, 1, 14000, 23, 4 },
{ "Mi150", 0, 0, 6000, 31, 3 },
{ "Mi250", 1, 0, 9000, 47, 5 }
};

int main()
{
	int selectNum;
	int trueFalse = 1;
	while (trueFalse)
	{
		system("cls");
		selectNum = displayMainMenu();
		system("cls");

		switch (selectNum) {
		case 1: searching(); break;
		case 2: filtering(); break;
		case 3: price(); break;
		case 4: sorting(); break;
		case 5: buying(); break;
		case 0:
			trueFalse = 0;
			printf("감사합니다 또 오세요.^^\n");
			break;
		default: printf("잘못누르셨어요ㅠㅠㅠ\n"); break;
		}
		system("pause");
	}
	return 0;
}

int displayMainMenu()
{
	int menuNum;
	printf("\n\n");
	printf("\t++++++++++++++++++++++++++++++++++\n");
	printf("\t         VACUUM SHOPPING\n");
	printf("\t++++++++++++++++++++++++++++++++++\n\n");
	printf("\t 1. 검색\n\n");
	printf("\t 2. 필터링\n\n");
	printf("\t 3. 가격대\n\n");
	printf("\t 4. 정렬\n\n");
	printf("\t 5. 구매\n\n");
	printf("\t++++++++++++++++++++++++++++++++++\n");
	printf("\t 0. 종료\n");
	printf("\t++++++++++++++++++++++++++++++++++\n");
	printf("\t  >> ");
	scanf("%d", &menuNum);
	return menuNum;
}

void searching() {
	char key;
	int exist=0;
	printf("\n\n");
	printf("\t+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\n\t  보시고 싶은 청소기를 검색하실 수 있습니다. ");
	printf("\n\n\t+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	getchar();
	printf("\n\t  검색하고 싶은 청소기의 첫글자를 적어주세요: ");
	scanf("%c", &key);
	for (int i = 0; i < 9; i++) {
		if (key == cleanerlist[i].name[0]) {
			printf("\n\t   %s\n", cleanerlist[i].name);
			exist ++;
		}
	}
	if (exist == 0) printf("  찾으시는 청소기가 없습니다.\n");
}

void filtering() {
	int water, wire;
	printf("\n\n");
	printf("\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\n\t  물청소기능과 무선 유선여부를 필터링하실 수 있습니다.\n");
	printf("\n\t  물청소기능을 원하시면 1, 않으시면 0을 입력하시고\n");
	printf("\n\t  유선기능을 원하시면 1, 무선기능을 원하시면 0을 입력하세요.\n\n");
	printf("\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\n\t  물청소기능 : ");
	scanf("%d", &water);
	printf("\n\t  무선 유선 여부 : ");
	scanf("%d", &wire);
	for (int i = 0; i < 9; i++) {
		if ((water == cleanerlist[i].waterclean) && (wire == cleanerlist[i].cable)) {
			printf("\n\t  %s\n", cleanerlist[i].name);
		}
		if (water != 0 && water != 1) {
			printf("\n\t  0또는 1의 숫자를 입력해주세요.\n");
			break;
		}
		if (wire != 0 && wire != 1) {
			printf("\n\t  0또는 1의 숫자를 입력해주세요.\n");
			break;
		}

	}
}

void price() {
	int min, max;
	int exist=0;
	printf("\n\n");
	printf("\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\n\t  원하는 가격대의 청소기의 목록을 보기위해 최저가와 최고가를 입력해주세요.\n\n");
	printf("\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\n\t  최저가 : ");
	scanf("%d", &min);
	printf("\n\t  최고가 : ");
	scanf("%d", &max);
	for (int i = 0; i < 9; i++) {
		if (min <= cleanerlist[i].price&&max >= cleanerlist[i].price) {
			printf("\n\t  제품명: %s 가격: %d\n", cleanerlist[i].name, cleanerlist[i].price);
			exist++;
		}
	}
	if (exist == 0)printf("\n\t  원하시는 가격대의 청소기가 없습니다.\n");
}

void sorting() {
	char namelist[10][30], tmp[30];
	int buying[10], score[10], money[10];
	int sort, i, j, t;
	for (i = 0; i < 10; i++)
	{
		strcpy(namelist[i], cleanerlist[i].name);
		buying[i] = cleanerlist[i].numPurchase;
		score[i] = cleanerlist[i].rating;
		money[i] = cleanerlist[i].price;
	}
	printf("\n\n");
	printf("\t+++++++++++++++++++++++++++++++++++++++\n");
	printf("\n\t  정렬을 할 수 있습니다.\n\n\t  1. 구매순\n\n\t  2. 평점순\n\n\t  3. 가격순\n\n");
	printf("\t+++++++++++++++++++++++++++++++++++++++\n");
	printf("\n\t  어떤 정렬을 하시겠습니까? : ");
	scanf("%d", &sort);
	switch (sort) {
	case 1:
		for (j = 0; j < 9; j++) {
			for (i = 0; i < 8; i++) {
				if (buying[i] < buying[i + 1]) {
					strcpy(tmp, namelist[i]);
					strcpy(namelist[i], namelist[i + 1]);
					strcpy(namelist[i + 1], tmp);
					t = buying[i];
					buying[i] = buying[i + 1];
					buying[i + 1] = t;
				}
			}
		}
		for (i = 0; i < 9; i++) {
			printf("\n\t  제품명: %s 구매수: %d\n", namelist[i], buying[i]);
		}
		printf("\n");
		break;
	case 2:
		for (j = 0; j < 9; j++) {
			for (i = 0; i < 8; i++) {
				if (score[i] < score[i + 1]) {
					strcpy(tmp, namelist[i]);
					strcpy(namelist[i], namelist[i + 1]);
					strcpy(namelist[i + 1], tmp);
					t = score[i];
					score[i] = score[i + 1];
					score[i + 1] = t;
				}
			}
		}
		for (i = 0; i < 9; i++) {
			printf("\n\t  제품명: %s 평점: %d\n", namelist[i], score[i]);
		}
		printf("\n");
		break;
	case 3:
		for (j = 0; j < 9; j++) {
			for (i = 0; i < 8; i++) {
				if (money[i] > money[i + 1]) {
					strcpy(tmp, namelist[i]);
					strcpy(namelist[i], namelist[i + 1]);
					strcpy(namelist[i + 1], tmp);
					t = money[i];
					money[i] = money[i + 1];
					money[i + 1] = t;
				}
			}
		}
		for (i = 0; i < 9; i++) {
			printf("\n\t  제품명: %s 가격: %d\n", namelist[i], money[i]);
		}
		printf("\n");
		break;
	default:
		printf("\n\t  1, 2, 3의 숫자 중 하나를 입력해주세요.\n\n  ");
		break;
	}
}

void buying() {
	int selectbuy;
	printf("\n\n");
	printf("\t+++++++++++++++++++++++++++++++++++++++\n");
	printf("\n\t  구매하실 청소기의 번호를 적어주세요: ");
	for (int i = 0; i < 9; i++) printf("\n\n\t  %d. %s", i + 1, cleanerlist[i].name);
	printf("\n\n\t+++++++++++++++++++++++++++++++++++++++\n");
	printf("\n\n\t  >> ");
	scanf("%d", &selectbuy);
	cleanerlist[selectbuy - 1].numPurchase++;
	printf("\n\t  %s 모델이 구매되셨습니다!!\n\n", cleanerlist[selectbuy - 1].name);
}

