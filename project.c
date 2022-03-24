#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"limits.h"
#include"structs.h"

void quicksort_ap(int iFirst, int iLast);
int partition_ap(int iFirst, int iLast);
void swap_ap(int i, int j);
void print_ap(airport aAirport);
int find_ap(char cId[IDAP]);
void format_time_fl(char* dest, flight f);
void quicksort_fl(flight* fArray, int iFirst, int iLast);
int partition_fl(flight* fArray, int iFirst, int iLast);
void swap_fl(flight* fArray, int i, int j);
void print_fl(flight fFlight, int iMode);
void read_date(date* dDate, char* arg);
int same_date(date dDate1, date dDate2);
int valid_date(date dDate);
void arrival_date(char sDest[4][DAY], char sYear[YEAR], flight fFlight);
void read_time(time* tTime, char* arg);
int read_duration(int* iDuration, char* arg);
void add_ap(char* arg);
void list_all_ap();
void list_ap(char* arg);
void list_all_fl();
void add_fl(char* arg);
void departures(char* cId);
void arrivals(char* cId);
void advance_date(char* arg);

/* Global variables */
airport aAirports[MAXAIRPORTS];
flight fFlights[MAXFLIGHTS];
int iCurrentAirports, iCurrentFlights;
date today = {"01", "01", "2022"};

int main () {
	int iExit = FALSE;
	char arg[ARGSIZE];
	while (iExit == FALSE) {
		fgets(arg, sizeof(char)*ARGSIZE, stdin);
		switch (arg[0]) {
			case 'q':
				iExit = TRUE;
				break;
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
			case 'p':
				departures(arg + ARGSTART);
				break;
			case 'c':
				arrivals(arg + ARGSTART);
				break;
			case 't':
				advance_date(arg + ARGSTART);
				break;
		}
	}
	return 0;
}

void quicksort_ap(int iFirst, int iLast) {
	int iPartition;
	if (iFirst < iLast) {
		iPartition = partition_ap(iFirst, iLast);
		quicksort_ap(iFirst, iPartition-1);
		quicksort_ap(iPartition+1, iLast);
	}
}

int partition_ap(int iFirst, int iLast) {
	int iPivot = iFirst, i = iFirst, j = iLast;
	while (i < j) {
		while (strcmp(aAirports[i].id, aAirports[iPivot].id) <= 0 && i < iLast) {
			i++;
		}
		while (strcmp(aAirports[j].id, aAirports[iPivot].id) > 0) {
			j--;
		}
		if (i < j) {
			swap_ap(i, j);
		}
	}
	swap_ap(iPivot, j);
	return j;
}

void swap_ap(int i, int j) {
	airport aAux;
	if (i == j) {
		return;
	}
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
		if (strcmp(cId, aAirports[i].id) == 0) {
			return i;
		}
	}
	return NOTFOUND;
}

void format_time_fl(char* dest, flight f) {
	sprintf(dest, "%s%s%s%s%s", f.date.year, f.date.month, f.date.day, f.time.hours, f.time.mins);
}

void copy_flights(flight* fArray) {
	int i;
	for (i = 0; i < iCurrentFlights; i++) {
		fArray[i] = fFlights[i];
	}
}

void quicksort_fl(flight* fArray, int iFirst, int iLast) {
	int iPartition;
	if (iFirst < iLast) {
		iPartition = partition_fl(fArray, iFirst, iLast);
		quicksort_fl(fArray, iFirst, iPartition-1);
		quicksort_fl(fArray, iPartition+1, iLast);
	}
}

int partition_fl(flight* fArray, int iFirst, int iLast) {
	int i = iFirst, j = iLast;
	char sPivot[CATDATETIME], sAux[CATDATETIME];
	format_time_fl(sPivot, fArray[iFirst]);
	while (i < j) {
		format_time_fl(sAux, fArray[i]);
		while (strcmp(sAux, sPivot) <= 0 && i < iLast) {
			i++;
			format_time_fl(sAux, fArray[i]);
		}
		format_time_fl(sAux, fArray[j]);
		while (strcmp(sAux, sPivot) > 0) {
			j--;
			format_time_fl(sAux, fArray[j]);
		}
		if (i < j) {
			swap_fl(fArray, i, j);
		}
	}
	swap_fl(fArray, iFirst, j);
	return j;
}

void swap_fl(flight* fArray, int i, int j) {
	flight fAux;
	if (i == j) {
		return;
	}
	fAux = fArray[i];
	fArray[i] = fArray[j];
	fArray[j] = fAux;
}

void print_fl(flight fFlight, int iMode) {
	printf("%s ", fFlight.id);
	if (iMode != 1) {
		printf("%s ", fFlight.departure);
	}
	if (iMode != 2) {
		printf("%s ", fFlight.arrival);
		printf("%s-%s-%s ", fFlight.date.day, fFlight.date.month, fFlight.date.year);
		printf("%s:%s\n", fFlight.time.hours, fFlight.time.mins);
	}
}

void read_date(date* dDate, char* arg) {
	strncpy(dDate->day, arg, 2);
	dDate->day[2] = '\0';
	strncpy(dDate->month, arg+DAY, 2);
	dDate->month[2] = '\0';
	strncpy(dDate->year, arg+DAY+MONTH, 4);
	dDate->year[4] = '\0';
}

int same_date(date dDate1, date dDate2) {
	if (strcmp(dDate1.day, dDate2.day) == 0 && strcmp(dDate1.month, dDate2.month) == 0) {
		return strcmp(dDate1.year, dDate2.year) == 0;
	}
	return FALSE;
}

int valid_date(date dDate) {
	if (strcmp(dDate.month, today.month) < 0) {
		return strcmp(dDate.year, today.year) == 1;
	}
	if (strcmp(dDate.month, today.month) == 0 && strcmp(dDate.day, today.day) < 0) {
		return strcmp(dDate.year, today.year) == 1;
	}
	return strcmp(dDate.year, today.year) == 0;
}

void arrival_date(char sDest[4][DAY], char sYear[YEAR], flight fFlight) {
	int i, iDurMins, iDurHours, iYear;
	int iTime[4];
	/* Converting strings to int for easier math */
	iDurMins = fFlight.duration[1];
	iDurHours = fFlight.duration[0];
	iTime[0] = atoi(fFlight.time.mins);
	iTime[1] = atoi(fFlight.time.hours);
	iTime[2] = atoi(fFlight.date.day);
	iTime[3] = atoi(fFlight.date.month);
	iYear = atoi(fFlight.date.year);
	/* Adding the duration and checking if the other variables need advancing */
	iTime[0] += iDurMins;
	iTime[1] += iDurHours;
	if (iTime[0] >= 60) {
		iTime[0] -= 60;
		iTime[1] += 1;
	}
	if (iTime[1] >= 24) {
		iTime[1] -= 24;
		iTime[2] += 1;
	}
	if (iTime[2] == 28 && iTime[3] == 2) {
		iTime[2] = 1;
		iTime[3] += 1;
	}
	else if (iTime[2] == 31 && (iTime[3] == 4 || iTime[3] == 6 || iTime[3] == 9 || iTime[3] == 11)) {
		iTime[2] = 1;
		iTime[3] += 1;
	}
	else if (iTime[2] == 32 && (iTime[3] == 1 || iTime[3] == 3 || iTime[3] == 5 || iTime[3] == 7 || iTime[3] == 8 || iTime[3] == 10)) {
		iTime[2] = 1;
		iTime[3] += 1;
	}
	else if (iTime[2] == 32 && iTime[3] == 12) {
		iTime[2] = 1;
		iTime[3] = 1;
		iYear += 1;
	}
	/* Converting back to string and formatting all elements except year */
	for (i = 0; i < 4; i++) {
		sprintf(sDest[i], "%d", iTime[i]);
		if (strlen(sDest[i]) == 1) {
			sDest[i][1] = sDest[i][0];
			sDest[i][0] = '0';
			sDest[i][2] = '\0';
		}
	}
	/* Year is converted seperately, since it doesn't need formatting */
	sprintf(sYear, "%d", iYear);
}

void read_time(time* tTime, char* arg) {
	strncpy(tTime->hours, arg, HOURS-1);
	tTime->hours[HOURS-1] = '\0';
	strncpy(tTime->mins, arg+HOURS, MINS-1);
	tTime->mins[MINS-1] = '\0';
}

int read_duration(int* iDuration, char* arg) {
	char cAux[MINS];
	int i, iOffset;
	for (i = 0; arg[i] != ':'; i++) {
		cAux[i] = arg[i];
	}
	iOffset = i+1;
	cAux[MINS-1] = '\0';
	iDuration[0] = atoi(cAux);
	for (i = 0; arg[i+iOffset] != ' '; i++) {
		cAux[i] = arg[i+iOffset];
	}
	cAux[MINS-1] = '\0';
	iDuration[1] = atoi(cAux);
	iOffset +=i+1;
	return iOffset;
}

void add_ap(char* arg) {
	int i;
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
	if (find_ap(aNewAirport.id) != NOTFOUND) {
		printf("duplicate airport\n");	
		return;
	}
	arg += IDAP;
	for (i = 0; arg[i] != ' ' && arg[i] != '\t'; i++) {
		aNewAirport.country[i] = arg[i];
	}
	aNewAirport.country[i] = '\0';
	arg += i+1;
	for (i = 0; arg[i] != '\n'; i++) {
		aNewAirport.city[i] = arg[i];
	}
	aNewAirport.city[i] = '\0';
	aNewAirport.departures = 0;
	aAirports[iCurrentAirports] = aNewAirport;
	iCurrentAirports++;
	printf("airport %s\n", aNewAirport.id);
}

void list_all_ap() {
	int i;
	quicksort_ap(0, iCurrentAirports - 1);
	for (i = 0; i < iCurrentAirports; i++) {
		print_ap(aAirports[i]);
	}
}

void list_ap(char* arg) {
	int i, j, iSize = strlen(arg);
	char sAux[IDAP];
	/* Checking if all provided IDs exist and storing them,
	 * useful to printing them later if they all exist */
	for (i = 0; i < iSize; i += IDAP) {
		strncpy(sAux, arg+i, IDAP-1);
		sAux[IDAP-1] = '\0';
		if (find_ap(sAux) == NOTFOUND) {
			printf("%s: no such airport ID\n", sAux);
		}
		else {
			for (j = 0; j < iCurrentAirports; j++) {
				if (strcmp(sAux, aAirports[j].id) == 0) {
					print_ap(aAirports[j]);
					break;
				}
			}
		}
	}
}

void list_all_fl() {
	int i;
	for (i = 0; i < iCurrentFlights; i++) {
		print_fl(fFlights[i], 0);
	}
}

void add_fl(char* arg) {
	int i, iDepartureIndex, iOffset;
	char cCapacity[CAPACITY];
	flight fNewFlight;
	for (i = 0; arg[i] != ' ' && arg[i] != '\t'; i++) {
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
	read_date(&fNewFlight.date, arg+DATESTART);
	for (i = 0; i < iCurrentAirports; i++) {
		if (strcmp(fFlights[i].id, fNewFlight.id) == 0 && same_date(fFlights[i].date, fNewFlight.date)) {
			printf("flight already exists\n");
			return;
		}
	}
	/* Checking if both ids exist */
	strncpy(fNewFlight.departure, arg, IDAP-1);
	fNewFlight.departure[IDAP-1] = '\0';
	iDepartureIndex = find_ap(fNewFlight.departure);
	if (iDepartureIndex == NOTFOUND) {
		printf("%s: no such airport id\n", fNewFlight.departure);
		return;
	}
	arg += IDAP;
	strncpy(fNewFlight.arrival, arg, IDAP-1);
	fNewFlight.arrival[IDAP-1] = '\0';
	if (find_ap(fNewFlight.arrival) == NOTFOUND) {
		printf("%s: no such airport id\n", fNewFlight.arrival);
		return;
	}
	/* Checking if there are too many flights */
	if (iCurrentFlights == MAXFLIGHTS) {
		printf("too many flights\n");
		return;
	}
	/* Checking if date is valid */
	if (!valid_date(fNewFlight.date)) {
		printf("invalid date\n");
		return;
	}
	arg += IDAP+DATE;
	/* Checking if duration is valid */
	read_time(&fNewFlight.time, arg);
	arg += TIME;
	iOffset = read_duration(fNewFlight.duration, arg);
	if(fNewFlight.duration[0] > 12) {
		printf("invalid duration\n");
		return;
	}
	arg += iOffset;
	/* Checking if capacity is valid */
	strncpy(cCapacity, arg, CAPACITY-1);
	cCapacity[CAPACITY-1] = '\0';
	fNewFlight.capacity = atoi(cCapacity);
	if(fNewFlight.capacity >= 100 || fNewFlight.capacity <= 10) {
		printf("invalid capacity\n");
		return;
	}
	/* Adding one more flight to the departure counter */
	aAirports[iDepartureIndex].departures++;
	/* Adding flight to flight list */
	fFlights[iCurrentFlights] = fNewFlight;
	iCurrentFlights++;
}

void departures(char* cId) {
	int i;
	flight fSortedFlights[MAXFLIGHTS];
	cId[3] = '\0';
	if (find_ap(cId) == NOTFOUND) {
		printf("%s: no such airport ID\n", cId);
		return;
	}
	copy_flights(fSortedFlights);
	quicksort_fl(fSortedFlights, 0, iCurrentFlights-1);
	for (i = 0; i < iCurrentFlights; i++) {
		if (strcmp(cId, fSortedFlights[i].departure) == 0) {
			print_fl(fSortedFlights[i], 1);
		}
	}
}

void arrivals(char* cId) {
	int i;
	char sTime[4][DAY], sYear[YEAR];
	flight fSortedFlights[MAXFLIGHTS];
	cId[3] = '\0';
	if (find_ap(cId) == NOTFOUND) {
		printf("%s: no such airport ID\n", cId);
		return;
	}
	copy_flights(fSortedFlights);
	quicksort_fl(fSortedFlights, 0, iCurrentFlights-1);
	for (i = 0; i < iCurrentFlights; i++) {
		if (strcmp(cId, fSortedFlights[i].arrival) == 0) {
			arrival_date(sTime, sYear, fSortedFlights[i]);
			print_fl(fSortedFlights[i], 2);
			printf("%s-%s-%s ", sTime[2], sTime[3], sYear);
			printf("%s:%s\n", sTime[1], sTime[0]);
		}
	}
}

void advance_date(char* arg) {
	date dNewToday;
	read_date(&dNewToday, arg);
	if (!valid_date(dNewToday)) {
		printf("invalid date\n");
		return;
	}
	today = dNewToday;
	printf("%s-%s-%s\n", dNewToday.day, dNewToday.month, dNewToday.year);
}
