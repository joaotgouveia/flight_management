#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"limits.h"
#include"structs.h"

/* Prototyping funtions */
void quicksort(airport aArray[MAXAIRPORTS], int iFirst, int iLast);
int partition(airport aArray[MAXAIRPORTS], int iFirst, int iLast);
void add_airplane(char* arg);
void list_all_ap();
void list_ap(char* arg);

/* Global variables */
airport airport_list[MAXAIRPORTS];
int iCurrentAirports = 0;
date today = {1, 1, 2022};

int main () {
	char arg[ARGSIZE];
	fgets(arg, sizeof(char)*ARGSIZE, stdin);
	switch (arg[0]) {
		case 'q':
			exit(0);
		case 'a':
			add_airplane(arg + ARGSTART);
		/*case 'l':
			if (strlen(arg) == 1) {
				list_all();
			}
			else {
				exit(0);
			}*/
	}
	return 0;
}

void quicksort(airport aArray[MAXAIRPORTS], int iFirst, int iLast) {
	int iPartition;
	if (iFirst < iLast) {
		iPartition = partition(aArray, iFirst, iLast);
		quicksort(aArray, iFirst, iPartition-1);
		quicksort(aArray, iPartition+1, iLast);
	}
}

int partition(airport aArray[MAXAIRPORTS], int iFirst, int iLast) {
	int i = iFirst+1, j = iLast;
	char sPivot[IDSIZEAP], sAux[IDSIZEAP];
	strcpy(sPivot, aArray[iFirst].id);
	while (i < j) {
		while (strcmp(aArray[i].id, sPivot) <= 0) {
			i++;
		}
		while (strcmp(aArray[j].id, sPivot) > 0) {
			j++;
		}
		strcpy(sAux, aArray[i].id);
		strcpy(aArray[i].id, aArray[j].id);
		strcpy(aArray[j].id, sAux);
	}
	strcpy(sAux, aArray[iFirst].id);
	strcpy(aArray[iFirst].id, aArray[j].id);
	strcpy(aArray[j].id, sAux);
	return j;
}

void add_airplane(char* arg) {
	int i, j;
	airport aNewAirport;
	for (i = 0; i < 3; i++) {
		if (isupper(arg[i]) > 0) {
			aNewAirport.id[i] = arg[i];
		}
		else {
			printf("invalid airport ID\n");
			return;
		}
	}
	if (iCurrentAirports == MAXAIRPORTS) {
		printf("too many airports\n");
		return;
	}
	aNewAirport.id[i] = '\0';
	for (i = 0; i < iCurrentAirports; i++) {
		if (strcmp(aNewAirport.id, airport_list[i].id) == 0) {
			printf("duplicate airport\n");
			return;
		}
	}
	j = 4;
	for (i = 4; arg[i] != ' '; i++) {
		aNewAirport.country[i - j] = arg[i];
	}
	aNewAirport.country[i - j] = '\0';
	j = i + 1;
	for (i++; arg[i] != '\n'; i++) {
		aNewAirport.city[i - j] = arg[i];
	}
	aNewAirport.city[i - j] = '\0';
	aNewAirport.flights = 0;
	airport_list[iCurrentAirports] = aNewAirport;
	iCurrentAirports++;
	printf("airport %s\n", aNewAirport.id);
}

void list_all_ap() {
	int i;
	quicksort(airport_list, 0, iCurrentAirports);
	for (i = 0; i < iCurrentAirports; i++) {
		printf("%s %s %s %d", airport_list[i].id, airport_list[i].city, airport_list[i].country, airport_list[i].flights);
	}
}

void list_ap(char* arg) {
	
}
