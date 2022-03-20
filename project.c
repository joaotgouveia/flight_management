#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"limits.h"
#include"structs.h"

/* Prototyping funtions */
void main_loop();
void quicksort(airport aArray[MAXAIRPORTS], int iFirst, int iLast);
int partition(airport aArray[MAXAIRPORTS], int iFirst, int iLast);
void add_airplane(char* arg);
void list_all_ap();
void list_ap(char* arg);

/* Global variables */
airport aAirports[MAXAIRPORTS];
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
			break;
		case 'l':
			if (strlen(arg) == 2) {
				list_all_ap();
			}
			else {
				list_ap(arg + ARGSTART);
			}
			break;
	}
	main_loop();
	return 0;
}

void main_loop() {
	main();
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
		if (strcmp(aNewAirport.id, aAirports[i].id) == 0) {
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
	aAirports[iCurrentAirports] = aNewAirport;
	iCurrentAirports++;
	printf("airport %s\n", aNewAirport.id);
}

void list_all_ap() {
	int i;
	quicksort(aAirports, 0, iCurrentAirports-1);
	for (i = 0; i < iCurrentAirports; i++) {
		printf("%s %s %s %d\n", aAirports[i].id, aAirports[i].city, aAirports[i].country, aAirports[i].flights);
	}
}

void list_ap(char* arg) {
	int i, j, k = 0, iExists, iSize = strlen(arg);
	char sAux[MAXAIRPORTS][IDSIZEAP];
	/* Checking if all provided IDs exist and storing them,
	 * useful to printing them later if they all exist*/
	for (i = 0; i < iSize; i = i+4) {
		iExists = FALSE;
		for (j = 0; j < 3; j++) {
			sAux[k][j] = arg[i + j];
		}
		sAux[k][j] = '\0';
		for (j = 0; j < iCurrentAirports; j++) {
			if (strcmp(sAux[k], aAirports[j].id) == 0) {
				iExists = TRUE;
				break;
			}
		}
		if (iExists == FALSE) {
			printf("%s: no such airport ID\n", sAux[k]);
			return;
		}
		k++;
	}
	/* Printing all requested airports */
	for (i = 0; i < iCurrentAirports; i++) {
		for (j = 0; j < iCurrentAirports; j++) {
			if (strcmp(sAux[i], aAirports[j].id) == 0) {
				printf("%s %s %s %d\n", aAirports[i].id, aAirports[i].city, aAirports[i].country, aAirports[i].flights);
				break;
			}
		}
	}
}
