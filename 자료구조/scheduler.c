#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct schedule {
	char startT[5];
	char endT[5];
	char date[5];
	char schName[30];
	struct sch * next;
}sch;
typedef struct scheduleList {
	sch * head;
	sch * tail;
}schList;

void UI();
void initSchList(schList * plist);
void addSchedule(schList * plist, char* d, char* sT, char* eT, char * sN);
void deleteSchedule(schList * plist, char * sN);
void checkSchedule_name(schList * plist, char * sN);
void checkSchedule_time(schList * plist, char* d, char* time);
void checkAllSchedule(schList * plist);

int main() {
	schList * sList = (schList*)malloc(sizeof(schList));
	int cmd, tf = 1;
	char d[5], sT[5], eT[5], T[5], sN[30];
	initSchList(sList);
	while (tf) {
		system("cls");
		UI();
		printf("\t COMMAND >> ");
		scanf("%d", &cmd);
		switch (cmd) {
		case 1: {
			printf("\t Please insert date, start time, end time, name >> \n");
			printf("\t Ex) 0922 1230 1600 Birthday \n");
			printf("\t ");
			scanf("%s %s %s %s", &d, &sT, &eT, &sN);
			addSchedule(sList, d, sT, eT, sN);
		}; break;
		case 2: {
			printf("\t Please insert the name of schedule >> \n");
			printf("\t ");
			scanf("%s", &sN);
			deleteSchedule(sList, sN);
		}; break;
		case 3: {
			printf("\t Please insert the name of schedule >> \n");
			printf("\t ");
			scanf("%s", &sN);
			checkSchedule_name(sList, sN);
		}; break;
		case 4: {
			printf("\t Please insert the date , time of schedule >> \n");
			printf("\t ");
			scanf("%s %s", &d, &T);
			checkSchedule_time(sList, d, T);
		}; break;
		case 5: checkAllSchedule(sList); break;
		default: printf("\t Invalid command. Try again.\n\t "); break;
		}
		printf("\t ");
		system("pause");
	}
	
}
void UI() {
	printf("\n\t--------------------------------------\n");
	printf("\t               SCHEDULER\n\n");
	printf("\t    PLEASE SELECT MENU...\n\n");
	printf("\t    1. Add Schedule\n");
	printf("\t    2. Delete Schedule\n");
	printf("\t    3. Check Schedule by Name\n");
	printf("\t    4. Check Schedule by Time\n");
	printf("\t    5. Check Every Schedule\n");
	printf("\t--------------------------------------\n"); 
}
void initSchList(schList * plist) {
	plist->head = (sch*)malloc(sizeof(sch));
	plist->head->next = NULL;
}
void addSchedule(schList * plist, char* d, char* sT, char* eT, char * sN) {
	sch * newSch = (sch*)malloc(sizeof(sch));
	sch * curr = plist->head->next;
	sch * tmp = NULL;
	sch * tmp1 = NULL;
	
	strcpy(newSch->date,d);
	strcpy(newSch->startT,sT);
	strcpy(newSch->endT , eT);
	strcpy(newSch->schName, sN);

	if (curr == NULL) {
		newSch->next = plist->head->next;
		plist->head->next = newSch;
		newSch->next = NULL;
	}
	else {
		if (atoi(curr->date) > atoi(d)) {
			newSch->next = plist->head->next;
			plist->head->next = newSch;
			return;
		}
		else if (atoi(curr->date) < atoi(d)) {
				while (1) {
					tmp = curr;
					curr = curr->next;
					if (curr == NULL || atoi(curr->date) >= atoi(d))break;
				}
				curr = tmp;
		}
		if (curr->next != NULL) {
			tmp = curr->next;
			if (atoi(tmp->date) == atoi(d)) {
				if (atoi(curr->endT) < atoi(sT)) {
					while (1) {
						tmp = curr;
						curr = curr->next;
						if (curr == NULL || atoi(curr->date) > atoi(d)) break;
						if (atoi(curr->endT) >= atoi(sT)) break;
					}
					curr = tmp;
				}
			}
		}
		newSch->next = curr->next;
		curr->next = newSch;
		
	}
}
void deleteSchedule(schList * plist, char * sN) {
	sch * curr = plist->head->next;
	if (curr == NULL) {
		printf("\t There is no schedule.\n");
		return;
	}
	if (curr->next == NULL) {
		plist->head->next = NULL;
		free(curr);
		printf("\t Deleted.\n");
		return;
	}
	while (strcmp(curr->schName, sN)) {
		sch * tmp = curr->next;
		if (strcmp(tmp->schName, sN) == 0) break;
		curr = curr->next;
	}
	sch * tmp = curr->next;
	curr->next = tmp->next;
	free(tmp);
	printf("\t Deleted.\n");
}
void checkSchedule_name(schList * plist, char * sN) {
	sch * curr = plist->head->next;
	int flag = 0;
	if (curr == NULL) {
		printf("\t There is no schedule.\n");
		return;
	}
	if (strcmp(curr->schName, sN) == 0) flag = 1;
	while (strcmp(curr->schName, sN)) {
		curr = curr->next;
		if (strcmp(curr->schName, sN) == 0)flag = 1;
		if (curr->next == NULL) break;
	
	}
	if (flag == 0) {
		printf("\t The schedule %s does not exist.\n",sN);
		return;
	}
	printf("\t Date:%s Start:%s End:%s Name:%s\n", curr->date, curr->startT, curr->endT, curr->schName);
}
void checkSchedule_time(schList * plist, char* d, char* time) {
	sch * curr = plist->head->next;
	if (curr == NULL) {
		printf("\t There is no schedule.\n");
		return;
	}
	if (atoi(curr->date) < atoi(d)) {
		while (1) {
			curr = curr->next;
			if (curr == NULL || atoi(curr->date) >= atoi(d))break;
		}
	}
	while (1) {
		if (atoi(curr->startT) <= atoi(time) && atoi(curr->endT) >= atoi(time)) break;
		else curr = curr->next;
	}
	printf("\t Date:%s Start:%s End:%s Name:%s\n", curr->date, curr->startT, curr->endT, curr->schName);
}
void checkAllSchedule(schList * plist) {
	sch * curr = plist->head->next;
	if (curr == NULL) {
		printf("\t There is no schedule.\n");
		return;
	}
	while (curr->next != NULL) {
		printf("\t Date:%s Start:%s End:%s Name:%s\n", curr->date, curr->startT, curr->endT, curr->schName);
		curr = curr->next;
	}
	printf("\t Date:%s Start:%s End:%s Name:%s\n", curr->date, curr->startT, curr->endT, curr->schName);
}
