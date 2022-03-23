#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"limits.h"
#include"structs.h"

/* Ver quicksorte devo ter fodido aquilo tudo */
/* Ver add_fl ta todo comido pelo menos o find_ap (teste07) */
void main_loop();
void quicksort(int iFirst, int iLast);
int partition(int iFirst, int iLast);
void swap(int i, int j);
void print_ap(airport aAirport);
int find_ap(char cId[IDAP]);
void print_fl(flight fFlight);
void read_date(date dDate, char* arg);
int same_date(date dDate1, date dDate2);
void add_ap(char* arg);
void list_all_ap();
void list_ap(char* arg);
void list_all_fl();
void add_fl(char* arg);

/* Global variables */
airport aAirports[MAXAIRPORTS];
flight fFlights[MAXFLIGHTS];
int iCurrentAirports, iCurrentFlights;
date today = {"01", "01", "2022"};

int main () {
	char arg[ARGSIZE];
	fgets(arg, sizeof(char)*ARGSIZE, stdin);
	switch (arg[0]) {
		case 'q':
			exit(0);
		case 'a':
			add_ap(arg + ARGSTART);
			break;
		case 'l':
			if (strlen(arg) == 2) {
				list_all_ap();
			}
			else {
				list_ap(arg + ARGSTART);
			}
			break;
		case 'v':
			if (strlen(arg) == 2) {
				list_all_fl();
			}
			else {
				add_fl(arg + ARGSTART);
			}
			break;
	}
	main_loop();
	return 0;
}

void main_loop() {
	main();
}

void quicksort_airports(int iFirst, int iLast) {
	int iPartition;
	if (iFirst < iLast) {
		iPartition = partition(iFirst, iLast);
		quicksort_airports(iFirst, iPartition-1);
		quicksort_airports(iPartition+1, iLast);
	}
}

int partition(int iFirst, int iLast) {
	int iPivot = iFirst, i = iFirst+1, j = iLast;
	while (i < j) {
		while (strcmp(aAirports[i].id, aAirports[iPivot].id) <= 0 && i < iLast) {
			i++;
		}
		while (strcmp(aAirports[j].id, aAirports[iPivot].id) > 0 && j > iFirst) {
			j--;
		}
		if (i < j) {
			swap(i, j);
		}
	}
	swap(iFirst, j);
	return j;
}

void swap(int i, int j) {
	airport aAux;
	aAux = aAirports[i];
	aAirports[i] = aAirports[j];
	aAirports[j] = aAux;
}

void print_ap(airport aAirport) {
	printf("%s ", aAirport.id); 
	printf("%s ", aAirport.city); 
	printf("%s ", aAirport.country); 
	printf("%d\n", aAirport.departures); 
}

int find_ap(char cId[IDAP]) {
	int i;
	for (i = 0; i < iCurrentAirports; i++) {
		if (!strcmp(cId, aAirports[i].id)) {
			return TRUE;
		}
	}
	return FALSE;
}

void print_fl(flight fFlight) {
	printf("%s ", fFlight.id);
	printf("%s ", fFlight.departure);
	printf("%s ", fFlight.arrival);
	printf("%s-%s-%s ", fFlight.date.day, fFlight.date.month, fFlight.date.year);
	printf("%s\n", fFlight.time);
}

void read_date(date dDate, char* arg) {
	strncpy(dDate.day, arg, 2);
	dDate.day[3] = '\0';
	strncpy(dDate.month, arg+DAY, 2);
	dDate.month[3] = '\0';
	strncpy(dDate.year, arg+DAY+MONTH, 4);
	dDate.year[5] = '\0';
}

int same_date(date dDate1, date dDate2) {
	if (!strcmp(dDate1.day, dDate2.day) && !strcmp(dDate1.month, dDate2.month)) {
		return !strcmp(dDate1.year, dDate2.year);
	}
	return FALSE;
}

void add_ap(char* arg) {
	int i, j, iDuplicate;
	airport aNewAirport;
	for (i = 0; i < IDAP-1; i++) {
		if (isupper(arg[i])) {
			aNewAirport.id[i] = arg[i];
		}
		else {
			printf("invalid airport ID\n");
			return;
		}
	}
	aNewAirport.id[i] = '\0';
	/* Checking if there are too many airports */
	if (iCurrentAirports == MAXAIRPORTS) {
		printf("too many airports\n");
		return;
	}
	iDuplicate = find_ap(aNewAirport.id);
	if (iDuplicate) {
		printf("duplicate airport\n");	
		return;
	}
	j = 4;
	for (i = 4; arg[i] != ' ' && arg[i] != '\t'; i++) {
		aNewAirport.country[i-j] = arg[i];
	}
	aNewAirport.country[i-j] = '\0';
	j = i + 1;
	for (i++; arg[i] != '\n'; i++) {
		aNewAirport.city[i-j] = arg[i];
	}
	aNewAirport.city[i-j] = '\0';
	aNewAirport.departures = 0;
	aAirports[iCurrentAirports] = aNewAirport;
	iCurrentAirports++;
	printf("airport %s\n", aNewAirport.id);
}

void list_all_ap() {
	int i;
	quicksort_airports(0, iCurrentAirports-1);
	for (i = 0; i < iCurrentAirports; i++) {
		print_ap(aAirports[i]);
	}
}

void list_ap(char* arg) {
	int i, j = 0, iExists, iSize = strlen(arg);
	char sAux[MAXAIRPORTS][IDAP];
	/* Checking if all provided IDs exist and storing them,
	 * useful to printing them later if they all exist */
	for (i = 0; i < iSize; i += 4) {
		strncpy(sAux[j], arg+i, 3);
		sAux[j][3] = '\0';
		iExists = find_ap(sAux[j]);
		if (!iExists) {
			printf("%s: no such airport ID\n", sAux[j]);
			return;
		}
		j++;
	}
	/* Printing all requested airports */
	for (i = 0; i < iCurrentAirports; i++) {
		for (j = 0; j < iCurrentAirports; j++) {
			if (!strcmp(sAux[i], aAirports[j].id)) {
				print_ap(aAirports[j]);
				break;
			}
		}
	}
}

void list_all_fl() {
	int i;
	for (i = 0; i < iCurrentFlights; i++) {
		print_fl(fFlights[i]);
	}
}

void add_fl(char* arg) {
	int i, iExists;
	flight fNewFlight;
	for (i = 0; arg[i] != ' '; i++) {
		if (isupper(arg[i]) && i < 2) {
			fNewFlight.id[i] = arg[i];
		}
		else if (isdigit(arg[i]) && i >= 2) {
			fNewFlight.id[i] = arg[i];
		}
		else {
			printf("invalid flight code\n");
			return;
		}
	}
	fNewFlight.id[i] = '\0';
	arg += i+1;
	read_date(fNewFlight.date, arg+DATESTART);
	for (i = 0; i < iCurrentAirports; i++) {
		if (!strcmp(fFlights[i].id, fNewFlight.id) && same_date(fFlights[i].date, fNewFlight.date)) {
			printf("flight already exists\n");
		}
	}
	/* Checking if both ids exist */
	strncpy(fNewFlight.departure, arg, 3);
	fNewFlight.departure[4] = '\0';
	iExists = find_ap(fNewFlight.departure);
	if (!iExists) {
		printf("%s: no such airport id\n", fNewFlight.departure);
		return;
	}
	strncpy(fNewFlight.arrival, arg, 3);
	fNewFlight.arrival[4] = '\0';
	iExists = find_ap(fNewFlight.arrival);
	if (!iExists) {
		printf("%s: no such airport id\n", fNewFlight.arrival);
		return;
	}
	/* Checking if there are too many flights */
	if (iCurrentFlights == MAXFLIGHTS) {
		printf("too many flights\n");
		return;
	}
	/* Checking if date is valid */
	fFlights[iCurrentFlights] = fNewFlight;
	iCurrentFlights++;
}
