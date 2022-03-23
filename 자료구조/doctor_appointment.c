#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)

typedef struct Queue {
	int pInfo[10][10];//0번째 칸에 몇번쨰 환자 1번째칸에 끝나는 시간 
	int pNum;
	int currPNum;
	int cureTime;
	int front;
	int rear;
}queue;

void initQueue(queue* pq);
int randomCure();
int randomPatient();
void enqueue(queue * pq, int data, int cT);
int dequeue(queue * pq);
int main() {
	queue doctor1, doctor2, doctor3;
	initQueue(&doctor1);
	initQueue(&doctor2);
	initQueue(&doctor3);
	int time1 = 900, time2 = 900, time3 = 900;
	int i1=0, i2=0, i3=0;
	int ranC1 = 0, ranC2 = 0, ranC3 = 0;
	int flag1 = 0, flag2 = 0, flag3 = 0;
	int flag11 = 0, flag22 = 0, flag33 = 0;
	int len1=0, len2=0, len3=0;
	while (time1<1800) {
		ranC1 = randomCure();
		len1 = strlen((&doctor1)->pInfo);
		for (int i = 0; i < len1; i++) {
			if ((&doctor1)->pInfo[i][1] >= time1) {
				dequeue(&doctor1);
				(&doctor1)->currPNum--;
			}
		}
		
		if (time1 > 1200 && flag1 == 0) {
			flag1 = 1;
			printf("%d시각의 대기자수는 %d", time1, (&doctor1)->currPNum);
		}
		if (time1 > 1500 && flag11 == 0) {
			flag11 = 1;
			printf("%d시각의 대기자수는 %d", time1, (&doctor1)->currPNum);
		}
		i1++;
		time1 += randomPatient();
		enqueue(&doctor1, i1, time1+ranC1);
		(&doctor1)->pNum++;
		(&doctor1)->currPNum++;
		(&doctor1)->cureTime += ranC1;
	}
	while (time2<1800) {
		ranC2 = randomCure();
		len2 = strlen((&doctor2)->pInfo);
		for (int i = 0; i < len2; i++) {
			if ((&doctor2)->pInfo[i][1] >= time2) {
				dequeue(&doctor2);
				(&doctor2)->currPNum--;
			}
		}
	
		if (time2 > 1200 && flag2 == 0) {
			flag2 = 1;
			printf("%d시각의 대기자수는 %d", time2, (&doctor2)->currPNum);
		}
		if (time2 > 1500 && flag22 == 0) {
			flag22 = 1;
			printf("%d시각의 대기자수는 %d", time2, (&doctor2)->currPNum);
		}
		i2++;
		time2 += randomPatient();
		enqueue(&doctor2, i2,time2+randomCure());
		(&doctor2)->pNum++;
		(&doctor2)->currPNum++;
		(&doctor2)->cureTime += ranC2;
	}
	while (time3<1800) {
		ranC3 = randomCure();
		len3 = strlen((&doctor3)->pInfo);
		for (int i = 0; i < len1; i++) {
			if ((&doctor3)->pInfo[i][1] >= time3) {
				dequeue(&doctor3);
				(&doctor3)->currPNum--;
			}
		}
		if (time3 > 1200 && flag3 == 0) {
			flag3 = 1;
			printf("%d시각의 대기자수는 %d", time3, (&doctor3)->currPNum);
		}
		if (time3 > 1500 && flag33 == 0) {
			flag33 = 1;
			printf("%d시각의 대기자수는 %d", time3, (&doctor3)->currPNum);
		}
		i3++;
		time3 += randomPatient();
		enqueue(&doctor3, i3,time3+randomCure());
		(&doctor3)->currPNum++;
		(&doctor3)->pNum++;
		(&doctor3)->cureTime += ranC3;
	}
	printf("\n DOCTOR1의 1인 평균 대기시간 %d, 총 진료시간 %d\n", (&doctor1)->cureTime / (&doctor1)->pNum, (&doctor1)->cureTime);
	printf("\n DOCTOR2의 1인 평균 대기시간 %d, 총 진료시간 %d\n", (&doctor2)->cureTime / (&doctor2)->pNum, (&doctor1)->cureTime);
	printf("\n DOCTOR3의 1인 평균 대기시간 %d, 총 진료시간 %d\n", (&doctor3)->cureTime / (&doctor3)->pNum, (&doctor1)->cureTime);
	
}
void initQueue(queue * pq) {
	pq->front = 0;
	pq->rear = 0;
	pq->pNum = 0;
	pq->cureTime = 0;
	pq->currPNum = 0;
}
int randomPatient() {
	srand(time(NULL));
	return (rand() % 25) + 5;
}
int randomCure() {
	srand(time(NULL));
	return (rand() % 20) + 10;
}
void enqueue(queue* pq, int data, int cT) {
	pq->rear = (pq->rear + 1) % 10;
	pq->pInfo[pq->rear][0] = data;
	pq->pInfo[pq->rear][1] = cT;
}
int dequeue(queue * pq) {
	pq->front = (pq->front + 1) % 10;
	return pq->pInfo[pq->front];
}