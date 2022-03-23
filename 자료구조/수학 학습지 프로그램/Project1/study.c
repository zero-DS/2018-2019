//#define _CRT_SECURE_NO_WARNINGS_
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define TESTNUM 100
#define BAR_MAX 12

typedef struct _Question {
	char ask[300];
	char answer[30];  //객관식과 주관식을 모두 구현하기위해 문자열로 구현
	int field; // 분야1~5 -> field별 배열 운영
} Quest;

typedef struct _prosol {
	char Problem[101][300];
	char Solution[101][30];
} Prosol;  // 모든 문제와 답을 저장하는 구조체.

typedef struct _RQuestion {
	Quest* question;
	struct _RQuestion* next;
} RQuest;

typedef struct _Test {
	Quest questions[11]; // 한 시험당 10개의 문제
						 //char answer[11][30];
	int totalscore; // 점수
} Test;

typedef struct _GradingQueue {
	int head;
	int tail;
	char answer[11][30]; // 10개문제의 각각의 답 저장
} GQue;

typedef struct _Field {
	int quoted; // 풀었던 문제 수
	int correct; // 그 중 맞은 문제수
	int achievement; // 성취도
} Field;

typedef struct _Fields {
	Field* Arithmetic, *Fractional, *Time, *ProblemSolve, *Unit;
} Fields;

typedef struct _Review {
	RQuest rquestion;
	RQuest* now;
	RQuest* head;
	RQuest* tail;
	int numOfReview;
} Review;
//QuestFile->EveryQuest[100]
//-> int형변수
// 메뉴 디스플레이에 들어갈 ADT 1.테스트보기 2. 오답노트 확인 3. 성적통지표 (지금까지 본 시험점수 & 분야별 성취도) 0. 종료

void Enqueue(GQue* gque, char* data);
char* Dequeue(GQue* gque);

void AroundLine();
int DisplayMainMenu();
Test* MakeTest(Test* test, Prosol prosol);
void RemoveFromReview(Review* review);
void ShowReview(Review* review);
void DoTest(Test* test, Review* review, Fields* fields, GQue* useranswer, int* testscore, int testcount);
int Grading(Test* test, Review* review, GQue* gque, Fields* fields); // 채점
void RenewField(Test* test, Fields* fields, int i, int c);
void MakeReview(Test* test, Review* review, int i); // 오답노트에 틀린문제 추가
void InitReview(Review* review);
void PrintBars(int Xpos, int Ypos, int barnumber); //막대그래프 출력하기
void gotoxy(int x, int y);//ui
void mainThree(Fields* fields, int* testscore, int testcount);
void initFieldsAchieve(Fields* fields);

Prosol newProsol = { 0, };
int main() {

	int testscore[TESTNUM], testcount = 0; // 시험을 본 횟수, 각 시험별 점수 -> 평균계산 시 필요
										   //int i, j, k, l;
	Test tests[10]; // 사용자가 치룬 시험
	srand((unsigned)time(NULL));
	Review review; InitReview(&review); review.now = &review.rquestion;
	Field Arithmetic, Fractional, ProblemSolve, Time, Unit;
	Fields myFields; myFields.Arithmetic = &Arithmetic; myFields.Time = &Time; myFields.Fractional = &Fractional; myFields.ProblemSolve = &ProblemSolve; myFields.Unit = &Unit;
	GQue useranswer; useranswer.head = 0; useranswer.tail = 0;

	FILE* newfile = fopen("All_Q.txt", "r");
	for (int i = 0; i <= 99; i++) fgets(newProsol.Problem[i], 300, newfile);
	newfile = fopen("All_A.txt", "r");
	for (int i = 0; i <= 99; i++) fgets(newProsol.Solution[i], 300, newfile);

	initFieldsAchieve(&myFields);
	//Openfile(newProsol);
	/*
	for (i = 0; i <= 9; i++) {
	for (j = 0; j <= 9; j++) {
	printf("%s", tests[i].questions[j].ask);
	gets(tests[i].answer);
	int len = tests[i].questions[j].ask;
	for (k = 0; k < len; k++) {
	if (tests[i].answer[k] == ' ')
	for (l = k; k < len; l++)
	tests[i].answer[j][k] = tests[i].answer[j][k + 1];
	}
	}
	}  // 답안의 스페이스 제거*/

	int cmd;
	while (1) {
		cmd = DisplayMainMenu();
		fflush(stdin);
		if (cmd == 0) return 0;
		else if (cmd == 1) {
			system("cls");
			DoTest(MakeTest(&tests[testcount], newProsol), &review, &myFields, &useranswer, testscore, testcount);
			testcount++;
		}
		else if (cmd == 2) {
			system("cls");
			ShowReview(&review);
		}
		else if (cmd == 3) {
			system("cls");
			mainThree(&myFields, testscore, testcount);
		}

		else printf("Wrong Command!!");

		system("pause"); system("cls");
	}
}

void AroundLine()
{
	//gotoxy(34, 55); printf("★ Q-rious ★");

	gotoxy(6, 3); printf("┏");
	for (int i = 4; i < 12; i++) {
		gotoxy(6, i);
		printf("┃");
	}
	gotoxy(6, 11); printf("┗");
	for (int i = 7; i < 73; i++) {
		gotoxy(i, 3);
		printf("━");
	}
	gotoxy(73, 3); printf("┓");
	for (int i = 7; i < 73; i++) {
		gotoxy(i, 11);
		printf("━");
	}
	for (int i = 4; i < 12; i++) {
		gotoxy(73, i);
		printf("┃");
	}
	gotoxy(73, 11); printf("┛");

	for (int i = 3; i < 55; i++) {
		gotoxy(4, i);
		printf("┃");
	}
	gotoxy(4, 2); printf("┏");
	for (int i = 5; i < 75; i++) {
		gotoxy(i, 2);
		printf("━");
	}
	gotoxy(4, 55); printf("┗");
	for (int i = 5; i < 75; i++) {
		gotoxy(i, 55);
		printf("━");
	}
	gotoxy(75, 2); printf("┓");
	for (int i = 3; i < 55; i++) {
		gotoxy(75, i);
		printf("┃");
	}
	gotoxy(75, 55); printf("┛");
}
int DisplayMainMenu()
{
	system("mode con cols=80 lines=60");
	system("cOLoR 0E");
	printf("\n\n\n\n\n");
	printf("\t   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
	for (int i = 0; i < 16; i++)
		printf("\t   ┃                                                      ┃ \n");
	printf("\t   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
	gotoxy(24, 10); printf("■"); gotoxy(21, 11); printf("■■■■"); gotoxy(23, 12); printf("■■"); gotoxy(22, 13); printf("■  ■");
	gotoxy(23, 14); printf("■■"); gotoxy(30, 12); printf("■"); gotoxy(30, 13); printf("■■"); gotoxy(30, 14); printf("■");
	gotoxy(26, 16); printf("■■■"); gotoxy(30, 18); printf("■"); gotoxy(30, 17); printf("■");
	gotoxy(38, 10); printf("■"); gotoxy(37, 11); printf("■■"); gotoxy(36, 12); printf("■  ■"); gotoxy(35, 14); printf("■■■■");
	gotoxy(36, 16); printf("■  ■"); gotoxy(36, 17); printf("■■■"); gotoxy(36, 18); printf("■■■"); gotoxy(45, 12); printf("■■■");
	gotoxy(47, 13); printf("■"); gotoxy(46, 14); printf("■■"); gotoxy(45, 15); printf("■  ■"); gotoxy(53, 12); printf("■");
	gotoxy(53, 13); printf("■"); gotoxy(53, 14); printf("■"); gotoxy(53, 15); printf("■"); // 학습지
	gotoxy(14, 36); printf("■■■■"); gotoxy(14, 37); printf("■    ■"); gotoxy(14, 38); printf("■  ■■"); gotoxy(14, 39); printf("■■■■");
	gotoxy(20, 40); printf("■■"); gotoxy(24, 38); printf("■■■"); gotoxy(32, 36); printf("■"); gotoxy(32, 37); printf("■■■");
	gotoxy(32, 38); printf("■  ■"); gotoxy(32, 39); printf("■"); gotoxy(32, 40); printf("■"); gotoxy(40, 36); printf("■");
	gotoxy(40, 38); printf("■"); gotoxy(40, 39); printf("■"); gotoxy(40, 40); printf("■"); gotoxy(44, 36); printf("■■■");
	gotoxy(44, 37); printf("■  ■"); gotoxy(44, 38); printf("■  ■"); gotoxy(44, 39); printf("■  ■"); gotoxy(44, 40); printf("■■■");
	gotoxy(52, 36); printf("■  ■"); gotoxy(52, 37); printf("■  ■"); gotoxy(52, 38); printf("■  ■"); gotoxy(52, 39); printf("■  ■");
	gotoxy(52, 40); printf("■■■"); gotoxy(60, 36); printf("■■■"); gotoxy(60, 37); printf("■"); gotoxy(60, 38); printf("■■■");
	gotoxy(60, 39); printf("    ■"); gotoxy(60, 40); printf("■■■ \n"); // Q-rious

	gotoxy(53, 22); printf("version 1.0.2");

	gotoxy(46, 17); printf("For. ");
	gotoxy(15, 25); printf("NAME >> ");
	char name[10]; gets(name); // 처음에 이름 입력받고 인사
	gotoxy(50, 17); printf("%s♥", name);

	int menu;
	gotoxy(40, 26); printf("초등학생용 맞춤형 학습지"); gotoxy(44, 27); printf("1. 테스트 보기");
	gotoxy(44, 28); printf("2. 오답노트 확인"); gotoxy(44, 29); printf("3. 성적통지표"); gotoxy(44, 30); printf("0. 나가기 \n");
	gotoxy(44, 31); printf(">> ");
	scanf("%d", &menu);
	return menu;
}
void DoTest(Test* test, Review* review, Fields* fields, GQue* useranswer, int* testscore, int testcount) {

	//gotoxy(50, 22); printf("Correct Answer :)"); //printf("Wrong Answer :("); // 맞는지 틀리는지
	char userans[30];

	for (int i = 0; i < 10; i++) {
		AroundLine();
		gotoxy(20, 5); printf("■■■■■"); gotoxy(24, 6); printf("■"); gotoxy(24, 7); printf("■"); gotoxy(24, 8); printf("■");
		gotoxy(24, 9); printf("■"); gotoxy(32, 5); printf("■■■■"); gotoxy(32, 7); printf("■■■■"); gotoxy(32, 9); printf("■■■■");
		gotoxy(32, 6); printf("■"); gotoxy(32, 8); printf("■"); gotoxy(42, 5); printf("■■■■"); gotoxy(42, 6); printf("■");
		gotoxy(48, 8); printf("■"); gotoxy(42, 7); printf("■■■■"); gotoxy(42, 9); printf("■■■■"); gotoxy(52, 5); printf("■■■■■");
		gotoxy(56, 6); printf("■"); gotoxy(56, 7); printf("■"); gotoxy(56, 8); printf("■"); gotoxy(56, 9); printf("■");
		gotoxy(34, 54); printf("★ Q-rious ★");
		gotoxy(8, 13); printf("# Q.%d", i + 1);
		gotoxy(69, 13); printf("%d/10", i + 1);
		gotoxy(10, 15);
		int len = strlen(test->questions[i].ask), k = 16, l = 0;
		CONSOLE_SCREEN_BUFFER_INFO curInfo;
		for (int j = 0; j < len; j++) {
			printf("%c", test->questions[i].ask[j]); // 문제 지우기
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
			if (curInfo.dwCursorPosition.X % 70 == 68) {
				printf("\n");
				gotoxy(10, k);
				k++;
				l = 1;
			}
			if (curInfo.dwCursorPosition.X % 70 == 69 && l == 0) {
				printf("\n");
				gotoxy(10, k);
				k++;
			}
		}
		gotoxy(13, 20); printf("▶ "); scanf("%s", userans); // 답 지우기
		len = strlen(userans);
		for (int j = 0; j < len; j++) {
			if (userans[j] == ' ')
				userans[j] = userans[j + 1];
		}
		Enqueue(useranswer, userans);
		gotoxy(23, 30);
		system("pause"); system("cls");
	}
	testscore[testcount] = Grading(test, review, useranswer, fields);
}
int Grading(Test* test, Review* review, GQue* gque, Fields* fields) {
	int wrongidx[10], idx = 0;

	for (int i = 0; i < 10; i++) {
		if (!strcmp(test->questions[i].answer, Dequeue(gque))) {
			//gotoxy(50, 22); printf("Correct Answer :)"); 
			RenewField(test, fields, i, 0);
		}
		else {
			//gotoxy(50, 22); printf("Wrong Answer :("); 
			RenewField(test, fields, i, 1);
			MakeReview(test, review, i);
			wrongidx[idx] = i; idx++;
		}
	}
	AroundLine();
	gotoxy(20, 5); printf("■■■■■"); gotoxy(24, 6); printf("■"); gotoxy(24, 7); printf("■"); gotoxy(24, 8); printf("■");
	gotoxy(24, 9); printf("■"); gotoxy(32, 5); printf("■■■■"); gotoxy(32, 7); printf("■■■■"); gotoxy(32, 9); printf("■■■■");
	gotoxy(32, 6); printf("■"); gotoxy(32, 8); printf("■"); gotoxy(42, 5); printf("■■■■"); gotoxy(42, 6); printf("■");
	gotoxy(48, 8); printf("■"); gotoxy(42, 7); printf("■■■■"); gotoxy(42, 9); printf("■■■■"); gotoxy(52, 5); printf("■■■■■");
	gotoxy(56, 6); printf("■"); gotoxy(56, 7); printf("■"); gotoxy(56, 8); printf("■"); gotoxy(56, 9); printf("■");
	gotoxy(34, 54); printf("★ Q-rious ★");

	gotoxy(16, 18); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	for (int i = 0; i < 3; i++) {
		gotoxy(16, 19 + i);
		printf("┃                                             ┃ \n");
	}
	gotoxy(16, 21); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
	gotoxy(22, 19); printf("시험 점수 : %d점\n", 10 - idx);
	gotoxy(22, 20); printf("틀린 문제 : ");
	for (int i = 0; i < idx; i++) {
		printf("%d ", wrongidx[i] + 1);
	}
	gotoxy(23, 30);

	return 10 - idx;
}
void RenewField(Test* test, Fields* fields, int i, int c) {
	if (c == 0) {
		if (test->questions[i].field == 1) {
			fields->Arithmetic->quoted++;
			fields->Arithmetic->correct++;
		}
		if (test->questions[i].field == 2) {
			fields->Fractional->quoted++;
			fields->Fractional->correct++;
		}
		if (test->questions[i].field == 3) {
			fields->ProblemSolve->quoted++;
			fields->ProblemSolve->correct++;
		}
		if (test->questions[i].field == 4) {
			fields->Time->quoted++;
			fields->Time->correct++;
		}
		if (test->questions[i].field == 5) {
			fields->Unit->quoted++;
			fields->Unit->correct++;
		}
	}
	else {
		if (test->questions[i].field == 1) fields->Arithmetic->quoted++;
		if (test->questions[i].field == 2) fields->Fractional->quoted++;
		if (test->questions[i].field == 3) fields->ProblemSolve->quoted++;
		if (test->questions[i].field == 4) fields->Time->quoted++;
		if (test->questions[i].field == 5) fields->Unit->quoted++;
	}
}
void InitReview(Review* review) {
	review->head = NULL;
	review->tail = NULL;
	review->now = NULL;
	review->numOfReview = 0;
}
void MakeReview(Test* test, Review* review, int i) {
	if (review->numOfReview == 0) {
		review->head = (RQuest*)malloc(sizeof(RQuest));
		review->head->question = &test->questions[i];
		review->tail = review->head;
	}
	else {
		review->tail->next = (RQuest*)malloc(sizeof(RQuest));
		review->tail = review->tail->next;
		review->tail->question = &test->questions[i];
	}
	review->numOfReview++;
} // 오답노트에 틀린문제 추가
void RemoveFromReview(Review* review) {
	// 리뷰 연결리스트에서 이 문제 삭제

	RQuest* delete = review->now;
	RQuest* before = review->head;
	while (before->next == review->now) before = before->next;

	if (review->numOfReview == 1) {
		free(review->head);
		InitReview(review);
	}
	else {
		if (review->now == review->head) {
			review->now = review->now->next;
			review->head = review->now;
		}
		else {

			if (review->now != review->tail) {
				review->now = review->now->next;
				before->next = review->now;
			}
			else {
				review->tail = before;
				review->now = review->head;
			}
		}
		free(delete);
		review->numOfReview--;
	}
}
void ShowReview(Review* review) {
	int idx = review->numOfReview;
	char review_answer[10];
	char choice;
	review->now = review->head;
	if (review->numOfReview == 0) {
		AroundLine();
		gotoxy(9, 5); printf("■■■■");
		gotoxy(9, 6); printf("■    ■");
		gotoxy(9, 7); printf("■■■■");
		gotoxy(9, 8); printf("■   ■");
		gotoxy(9, 9); printf("■    ■"); //R
		gotoxy(19, 5); printf("■■■■");
		gotoxy(19, 6); printf("■");
		gotoxy(19, 7); printf("■■■■");
		gotoxy(19, 8); printf("■");
		gotoxy(19, 9); printf("■■■■");
		gotoxy(29, 5); printf("■      ■");
		gotoxy(30, 6); printf("■    ■");
		gotoxy(31, 7); printf("■  ■");
		gotoxy(32, 8); printf("■■");
		gotoxy(33, 9); printf("■");
		gotoxy(41, 5); printf("■■");
		gotoxy(42, 6); printf("■");
		gotoxy(42, 7); printf("■");
		gotoxy(42, 8); printf("■");
		gotoxy(41, 9); printf("■■");
		gotoxy(47, 5); printf("■■■■");
		gotoxy(47, 6); printf("■");
		gotoxy(47, 7); printf("■■■■");
		gotoxy(47, 8); printf("■");
		gotoxy(47, 9); printf("■■■■");
		gotoxy(57, 5); printf("■     ^^     ■");
		gotoxy(58, 6); printf("■    ■    ■");
		gotoxy(59, 7); printf("■  ■■  ■");
		gotoxy(60, 8); printf("■■  ■■");
		gotoxy(61, 9); printf("■    ■");
		gotoxy(34, 41); printf("★ Q-rious ★");
	}
	for (int i = 0; i < idx; i++) {
		AroundLine();
		gotoxy(9, 5); printf("■■■■");
		gotoxy(9, 6); printf("■    ■");
		gotoxy(9, 7); printf("■■■■");
		gotoxy(9, 8); printf("■   ■");
		gotoxy(9, 9); printf("■    ■"); //R
		gotoxy(19, 5); printf("■■■■");
		gotoxy(19, 6); printf("■");
		gotoxy(19, 7); printf("■■■■");
		gotoxy(19, 8); printf("■");
		gotoxy(19, 9); printf("■■■■");
		gotoxy(29, 5); printf("■      ■");
		gotoxy(30, 6); printf("■    ■");
		gotoxy(31, 7); printf("■  ■");
		gotoxy(32, 8); printf("■■");
		gotoxy(33, 9); printf("■");
		gotoxy(41, 5); printf("■■");
		gotoxy(42, 6); printf("■");
		gotoxy(42, 7); printf("■");
		gotoxy(42, 8); printf("■");
		gotoxy(41, 9); printf("■■");
		gotoxy(47, 5); printf("■■■■");
		gotoxy(47, 6); printf("■");
		gotoxy(47, 7); printf("■■■■");
		gotoxy(47, 8); printf("■");
		gotoxy(47, 9); printf("■■■■");
		gotoxy(57, 5); printf("■     ^^     ■");
		gotoxy(58, 6); printf("■    ■    ■");
		gotoxy(59, 7); printf("■  ■■  ■");
		gotoxy(60, 8); printf("■■  ■■");
		gotoxy(61, 9); printf("■    ■");
		gotoxy(34, 41); printf("★ Q-rious ★");
		gotoxy(8, 13); printf("# Q.%d", i + 1);
		gotoxy(69, 13); printf("%d/%d", i + 1, idx);
		// 여기여기여기여기여기이겨ㅣㅇ겨ㅣㅇ겨ㅣㅇ기
		gotoxy(10, 15);
		//printf("%s", review->now->question->ask);
		int len = strlen(review->now->question->ask), k = 16, l = 0;
		CONSOLE_SCREEN_BUFFER_INFO curInfo;
		for (int j = 0; j < len; j++) {
			printf("%c", review->now->question->ask[j]); // 문제 지우기
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
			if (curInfo.dwCursorPosition.X % 70 == 68) {
				printf("\n");
				gotoxy(10, k);
				k++;
				l = 1;
			}
			if (curInfo.dwCursorPosition.X % 70 == 69 && l == 0) {
				printf("\n");
				gotoxy(10, k);
				k++;
			}
		}
		gotoxy(13, 20); printf("▶ "); scanf("%s", review_answer);
		if (!strcmp(review->now->question->answer, review_answer)) {
			gotoxy(50, 22); printf("Correct Answer :)");
			RemoveFromReview(review);
		}
		else {
			gotoxy(50, 22); printf("Wrong Answer :)");
			gotoxy(50, 23); printf("a. 다음에 다시 도전하기 \n");
			gotoxy(50, 24); printf("b. 정답 확인하기");

			int exit = 0, count = 0;
			while (!exit) {
				gotoxy(50, 25);   printf("▶ "); scanf("%c", &choice);
				if (choice == 'a') {
					exit = 1;
					gotoxy(51, 26); printf("다음에 다시 도전하세요! \n");
					review->now = review->now->next;
				}
				else if (choice == 'b') {
					exit = 1;
					gotoxy(51, 26); printf("정답: %s\n", review->now->question->answer);
					RemoveFromReview(review);
				}
				else {
					exit = 0;
				}
			}
		}
		gotoxy(23, 30);
		system("pause"); system("cls");
	}
}
Test* MakeTest(Test* test, Prosol prosol) {
	for (int j = 0; j <= 99; j += 20) {
		int ran1 = rand() % 20, ran2 = rand() % 20;
		while (ran1 == ran2) ran2 = rand() % 20;
		strcpy(test->questions[j / 10].ask, prosol.Problem[ran1 + j]);
		strcpy(test->questions[j / 10 + 1].ask, prosol.Problem[ran2 + j]);
		strcpy(test->questions[j / 10].answer, prosol.Solution[ran1 + j]);
		strcpy(test->questions[j / 10 + 1].answer, prosol.Solution[ran2 + j]);
		test->questions[j / 10].field = j / 20 + 1;
		test->questions[j / 10 + 1].field = j / 20 + 1;
	}

	for (int j = 0; j < 9; j++) {
		int len = strlen(test->questions[j].ask);
		test->questions[j].ask[len - 1] = '\0';
	}  // 텍스트 문장 마지막의 엔터 제거
	for (int j = 0; j < 9; j++) {
		int len = strlen(test->questions[j].answer);
		test->questions[j].answer[len - 1] = '\0';
	}
	return test;
}
void Enqueue(GQue* gque, char* data) {
	gque->tail = (gque->tail + 1) % 10;
	strcpy(gque->answer[gque->tail], data);
}
char* Dequeue(GQue* gque) {
	gque->head = (gque->head + 1) % 10;
	return gque->answer[gque->head];
}
void gotoxy(int x, int y) {
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void PrintBars(int Xpos, int Ypos, int barnumber) {
	gotoxy(Xpos, Ypos);
	for (int i = 1; i <= barnumber; i++) {
		printf("■");
		gotoxy(Xpos, Ypos - i);
	}
}
void mainThree(Fields* fields, int* testscore, int testcount) {
	AroundLine();
	gotoxy(11, 5); printf("■■■■"); gotoxy(11, 6); printf("■    ■"); gotoxy(11, 7); printf("■■■■"); gotoxy(11, 8); printf("■   ■");
	gotoxy(11, 9); printf("■    ■"); gotoxy(21, 5); printf("■■■■"); gotoxy(21, 6); printf("■"); gotoxy(21, 7); printf("■■■■");
	gotoxy(21, 8); printf("■"); gotoxy(21, 9); printf("■■■■"); gotoxy(31, 5); printf("■■■■"); gotoxy(31, 6); printf("■");
	gotoxy(37, 8); printf("■"); gotoxy(31, 7); printf("■■■■"); gotoxy(31, 9); printf("■■■■"); gotoxy(41, 5); printf("■    ■");
	gotoxy(41, 6); printf("■    ■"); gotoxy(41, 7); printf("■    ■"); gotoxy(41, 8); printf("■    ■"); gotoxy(41, 9); printf("■■■■");
	gotoxy(51, 5); printf("■"); gotoxy(51, 6); printf("■"); gotoxy(51, 7); printf("■"); gotoxy(51, 8); printf("■");
	gotoxy(51, 9); printf("■■■■"); gotoxy(59, 5); printf("■■■■■"); gotoxy(63, 6); printf("■"); gotoxy(63, 7); printf("■");
	gotoxy(63, 8); printf("■"); gotoxy(63, 9); printf("■");
	gotoxy(34, 54); printf("★ Q-rious ★");

	if (testcount == 0) {
		gotoxy(16, 18); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		for (int i = 0; i < 4; i++) {
			gotoxy(16, 19 + i);
			printf("┃                                             ┃ \n");
		}
		gotoxy(16, 23); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
		gotoxy(28, 20);
		printf("시험을 보고 들어오세요 :)");
		gotoxy(23, 30);
		return;
	}

	int aArray[6] = { 0 };
	aArray[0] = (fields->Arithmetic->correct * BAR_MAX) / fields->Arithmetic->quoted;
	aArray[1] = (fields->Fractional->correct * BAR_MAX) / fields->Fractional->quoted;
	aArray[2] = (fields->ProblemSolve->correct * BAR_MAX) / fields->ProblemSolve->quoted;
	aArray[3] = (fields->Time->correct * BAR_MAX) / fields->Time->quoted;
	aArray[4] = (fields->Unit->correct * BAR_MAX) / fields->Unit->quoted;

	for (int i = 0; i < 15; i++) {
		gotoxy(17, 14 + i);
		printf("┃");
	}
	for (int i = 0; i < 16; i++) {
		gotoxy(17, 33 + i);
		printf("┃");
	}
	for (int i = 0; i < 48; i++) {
		gotoxy(17 + i, 29);
		printf("━");
	}
	for (int i = 0; i < 48; i++) {
		gotoxy(17 + i, 49);
		printf("━");
	}

	gotoxy(7, 15); printf("분야별");
	gotoxy(7, 16); printf("성취도");
	gotoxy(7, 34); printf("최근");
	gotoxy(7, 35); printf("5회차");
	gotoxy(7, 36); printf("점수");


	gotoxy(19, 30);
	printf("Arith");
	gotoxy(29, 30);
	printf("Fract");
	gotoxy(38, 30);
	printf("Problem");
	gotoxy(49, 30);
	printf("Time");
	gotoxy(59, 30);
	printf("Unit");
	for (int i = 0; i < 5; i++) {
		PrintBars((i + 2) * 10, 28, aArray[i]);
	}
	gotoxy(20, 14);
	printf("(%d/%d)", fields->Arithmetic->correct, fields->Arithmetic->quoted);
	gotoxy(30, 14);
	printf("(%d/%d)", fields->Fractional->correct, fields->Fractional->quoted);
	gotoxy(40, 14);
	printf("(%d/%d)", fields->ProblemSolve->correct, fields->ProblemSolve->quoted);
	gotoxy(50, 14);
	printf("(%d/%d)", fields->Time->correct, fields->Time->quoted);
	gotoxy(60, 14);
	printf("(%d/%d)", fields->Unit->correct, fields->Unit->quoted);

	if (testcount >= 6) {
		gotoxy(24, 25);
		printf("최근 응시한 5회");
		for (int i = testcount - 5; i < testcount; i++) {
			gotoxy((i - testcount + 6) * 10, 50);
			printf("%d회차", i + 1);
		}
		for (int i = testcount - 5; i < testcount; i++) {
			PrintBars((i - testcount + 6) * 10, 48, (testscore[i] * BAR_MAX) / 10);
		}
		//gotoxy(2, 42);
		//printf("점수 >> ");
		for (int i = testcount - 5; i < testcount; i++) {
			gotoxy((i - testcount + 6) * 10, 48 + testscore[i]);
			printf("%d", testscore[i]);
		}
	}
	else if (testcount == 0) {
		gotoxy(1, 25);
		printf("\n아직 테스트를 보지 않아 점수를 확인하실 수 없습니다.\n");
	}
	else {
		for (int i = 0; i < testcount; i++) {
			gotoxy((i + 2) * 10 - 1, 50);
			printf("%d회차", i + 1);
		}
		for (int i = 0; i < testcount; i++) {
			PrintBars((i + 2) * 10, 48, (testscore[i] * BAR_MAX) / 10);
		}
		//gotoxy(2, 42);
		//printf("점수 >> ");
		for (int i = 0; i < testcount; i++) {
			gotoxy((i + 2) * 10, 48 - testscore[i]);
			printf("%d", testscore[i]);
		}
	}
	gotoxy(23, 59); printf("");
}
void initFieldsAchieve(Fields* fields) {
	fields->Arithmetic->correct = 0;
	fields->Arithmetic->quoted = 0;
	fields->Fractional->correct = 0;
	fields->Fractional->quoted = 0;
	fields->ProblemSolve->correct = 0;
	fields->ProblemSolve->quoted = 0;
	fields->Time->correct = 0;
	fields->Time->quoted = 0;
	fields->Unit->correct = 0;
	fields->Unit->quoted = 0;
}