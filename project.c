#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"limits.h"
#include"structs.h"

/* Airport sorting funtions */
void quicksort_ap(int iFirst, int iLast);
int partition_ap(int iFirst, int iLast);
void swap_ap(int i, int j);
/* Airport related funtions */
void print_ap(Airport aAirport);
int find_ap(char cId[IDAP]);
/* Flight sorting funtions */
void quicksort_fl(Flight* fArray, int iFirst, int iLast, int iArrivals);
int partition_fl(Flight* fArray, int iFirst, int iLast, int iArrivals);
void swap_fl(Flight* fArray, int i, int j);
/* Flight related funtions */
void format_time_fl(char* dest, Flight f, int iArrivals);
void print_fl(Flight fFlight, int iMode);
/* Date related funtions */
void read_date(Date* dDate, char* arg);
int same_date(Date dDate1, Date dDate2);
int invalid_date(Date dDate);
void arrival_date(char sDest[5][YEAR], Flight fFlight);
/* Time related funtions */
void read_time(Time* tTime, char* arg);
int read_duration(int* iDuration, char* arg);
/* Main project functions */
void add_ap(char* arg);
void list_all_ap();
void list_ap(char* arg);
void list_all_fl();
void add_fl(char* arg);
void departures(char* cId);
void arrivals(char* cId);
void advance_date(char* arg);

/* Global variables */
Airport aAirports[MAXAIRPORTS];
Flight fFlights[MAXFLIGHTS];
int iCurrentAirports, iCurrentFlights;
Date today = {"01", "01", "2022"};

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
				add_ap(arg+ARGSTART);
				break;
			case 'l':
				if (strlen(arg) == 2) {
					list_all_ap();
				}
				else {
					list_ap(arg+ARGSTART);
				}
				break;
			case 'v':
				if (strlen(arg) == 2) {
					list_all_fl();
				}
				else {
					add_fl(arg+ARGSTART);
				}
				break;
			case 'p':
				departures(arg+ARGSTART);
				break;
			case 'c':
				arrivals(arg+ARGSTART);
				break;
			case 't':
				advance_date(arg+ARGSTART);
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
	Airport aAux;
	if (i == j) {
		return;
	}
	aAux = aAirports[i];
	aAirports[i] = aAirports[j];
	aAirports[j] = aAux;
}

void print_ap(Airport aAirport) {
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

void format_time_fl(char* dest, Flight f, int iArrivals) {
	if (iArrivals) {
		sprintf(dest, "%s%s%s%s%s", f.arrDate.year, f.arrDate.month, f.arrDate.day, f.arrTime.hours, f.arrTime.mins);
	}
	else {
		sprintf(dest, "%s%s%s%s%s", f.date.year, f.date.month, f.date.day, f.time.hours, f.time.mins);
	}
}

void copy_flights(Flight* fArray) {
	int i;
	for (i = 0; i < iCurrentFlights; i++) {
		fArray[i] = fFlights[i];
	}
}

void quicksort_fl(Flight* fArray, int iFirst, int iLast, int iArrivals) {
	int iPartition;
	if (iFirst < iLast) {
		iPartition = partition_fl(fArray, iFirst, iLast, iArrivals);
		quicksort_fl(fArray, iFirst, iPartition-1, iArrivals);
		quicksort_fl(fArray, iPartition+1, iLast, iArrivals);
	}
}

int partition_fl(Flight* fArray, int iFirst, int iLast, int iArrivals) {
	int i = iFirst, j = iLast;
	char sPivot[CATDATETIME], sAux[CATDATETIME];
	format_time_fl(sPivot, fArray[iFirst], iArrivals);
	while (i < j) {
		format_time_fl(sAux, fArray[i], iArrivals);
		while (strcmp(sAux, sPivot) <= 0 && i < iLast) {
			i++;
			format_time_fl(sAux, fArray[i], iArrivals);
		}
		format_time_fl(sAux, fArray[j], iArrivals);
		while (strcmp(sAux, sPivot) > 0) {
			j--;
			format_time_fl(sAux, fArray[j], iArrivals);
		}
		if (i < j) {
			swap_fl(fArray, i, j);
		}
	}
	swap_fl(fArray, iFirst, j);
	return j;
}

void swap_fl(Flight* fArray, int i, int j) {
	Flight fAux;
	if (i == j) {
		return;
	}
	fAux = fArray[i];
	fArray[i] = fArray[j];
	fArray[j] = fAux;
}

void print_fl(Flight fFlight, int iMode) {
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

void read_date(Date* dDate, char* arg) {
	strncpy(dDate->day, arg, 2);
	dDate->day[2] = '\0';
	strncpy(dDate->month, arg+DAY, 2);
	dDate->month[2] = '\0';
	strncpy(dDate->year, arg+DAY+MONTH, 4);
	dDate->year[4] = '\0';
}

void advance_day(int* iDate) {
	iDate[0]++;
	if (iDate[0] == 28 && iDate[1] == 2) {
		iDate[0] = 1;
		iDate[1] += 1;
	}
	else if (iDate[0] == 31 && (iDate[1] == 4 || iDate[1] == 6 || iDate[1] == 9 || iDate[1] == 11)) {
		iDate[2] = 1;
		iDate[3] += 1;
	}
	else if (iDate[0] == 32 && (iDate[1] == 1 || iDate[1] == 3 || iDate[1] == 5 || iDate[1] == 7 || iDate[1] == 8 || iDate[1] == 10)) {
		iDate[0] = 1;
		iDate[1] += 1;
	}
	else if (iDate[0] == 32 && iDate[1] == 12) {
		iDate[0] = 1;
		iDate[1] = 1;
		iDate[2] += 1;
	}
}

int same_date(Date dDate1, Date dDate2) {
	if (strcmp(dDate1.day, dDate2.day) == 0 && strcmp(dDate1.month, dDate2.month) == 0) {
		return strcmp(dDate1.year, dDate2.year) == 0;
	}
	return FALSE;
}

int invalid_date(Date dDate) {
	int iYear;
	char cToday[CATDATE], cDate[CATDATE], cFuture[CATDATE];
	/* Converting year to int for easier math */
	sprintf(cToday, "%s%s%s", today.year, today.month, today.day);
	sprintf(cDate, "%s%s%s", dDate.year, dDate.month, dDate.day);
	iYear = atoi(today.year);
	iYear++;
	sprintf(cFuture, "%d%s%s", iYear, today.month, today.day);
	return strcmp(cDate, cFuture) > 0 || strcmp(cDate, cToday) < 0;
}

void arrival_date(char sDest[5][YEAR], Flight fFlight) {
	int i, iDurMins, iDurHours;
	int iTime[5];
	/* Converting strings to int for easier math */
	iDurMins = fFlight.duration[1];
	iDurHours = fFlight.duration[0];
	iTime[0] = atoi(fFlight.time.mins);
	iTime[1] = atoi(fFlight.time.hours);
	iTime[2] = atoi(fFlight.date.day);
	iTime[3] = atoi(fFlight.date.month);
	iTime[4] = atoi(fFlight.date.year);
	/* Adding the duration and checking if the other variables need advancing */
	iTime[0] += iDurMins;
	iTime[1] += iDurHours;
	if (iTime[0] >= 60) {
		iTime[0] -= 60;
		iTime[1] += 1;
	}
	if (iTime[1] >= 24) {
		iTime[1] -= 24;
		advance_day(iTime+2);
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
	sprintf(sDest[4], "%d", iTime[4]);
}

void read_time(Time* tTime, char* arg) {
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
	cAux[i] = '\0';
	iDuration[0] = atoi(cAux);
	iOffset = i+1;
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
	Airport aNewAirport;
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
	int i, iIndexAp, iSize = strlen(arg);
	char sAux[IDAP];
	for (i = 0; i < iSize; i += IDAP) {
		strncpy(sAux, arg+i, IDAP-1);
		sAux[IDAP-1] = '\0';
		iIndexAp = find_ap(sAux);
		if (iIndexAp == NOTFOUND) {
			printf("%s: no such airport ID\n", sAux);
		}
		else {
			print_ap(aAirports[iIndexAp]);
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
	int i, iDepartureIndex, iOffset, iIdSize;
	char cCapacity[CAPACITY], sTime[5][YEAR];
	Flight fNewFlight;
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
	iIdSize = strlen(fNewFlight.id);
	if (iIdSize > IDFL || iIdSize < 3) {
		printf("invalid flight code\n");
		return;
	}
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
		printf("%s: no such airport ID\n", fNewFlight.departure);
		return;
	}
	arg += IDAP;
	strncpy(fNewFlight.arrival, arg, IDAP-1);
	fNewFlight.arrival[IDAP-1] = '\0';
	if (find_ap(fNewFlight.arrival) == NOTFOUND) {
		printf("%s: no such airport ID\n", fNewFlight.arrival);
		return;
	}
	/* Checking if there are too many flights */
	if (iCurrentFlights == MAXFLIGHTS) {
		printf("too many flights\n");
		return;
	}
	/* Checking if date is valid */
	if (invalid_date(fNewFlight.date)) {
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
	else if (fNewFlight.duration[0] == 12 && fNewFlight.duration[1] > 0) {
		printf("invalid duration\n");
		return;
	}
	arg += iOffset;
	/* Checking if capacity is valid */
	strncpy(cCapacity, arg, CAPACITY-1);
	cCapacity[CAPACITY-1] = '\0';
	fNewFlight.capacity = atoi(cCapacity);
	if(fNewFlight.capacity > 100 || fNewFlight.capacity < 10) {
		printf("invalid capacity\n");
		return;
	}
	/* Calculating and saving arrival date */
	arrival_date(sTime, fNewFlight);
	strcpy(fNewFlight.arrTime.mins, sTime[0]);
	strcpy(fNewFlight.arrTime.hours, sTime[1]);
	strcpy(fNewFlight.arrDate.day, sTime[2]);
	strcpy(fNewFlight.arrDate.month, sTime[3]);
	strcpy(fNewFlight.arrDate.year, sTime[4]);
	/* Adding one more flight to the departure counter */
	aAirports[iDepartureIndex].departures++;
	/* Adding flight to flight list */
	fFlights[iCurrentFlights] = fNewFlight;
	iCurrentFlights++;
}

void departures(char* cId) {
	int i;
	Flight fSortedFlights[MAXFLIGHTS];
	cId[3] = '\0';
	if (find_ap(cId) == NOTFOUND) {
		printf("%s: no such airport ID\n", cId);
		return;
	}
	copy_flights(fSortedFlights);
	quicksort_fl(fSortedFlights, 0, iCurrentFlights-1, FALSE);
	for (i = 0; i < iCurrentFlights; i++) {
		if (strcmp(cId, fSortedFlights[i].departure) == 0) {
			print_fl(fSortedFlights[i], 1);
		}
	}
}

void arrivals(char* cId) {
	int i;
	Flight fSortedFlights[MAXFLIGHTS];
	cId[3] = '\0';
	if (find_ap(cId) == NOTFOUND) {
		printf("%s: no such airport ID\n", cId);
		return;
	}
	copy_flights(fSortedFlights);
	quicksort_fl(fSortedFlights, 0, iCurrentFlights-1, TRUE);
	for (i = 0; i < iCurrentFlights; i++) {
		if (strcmp(cId, fSortedFlights[i].arrival) == 0) {
			print_fl(fSortedFlights[i], 2);
			printf("%s-%s-%s ", fSortedFlights[i].arrDate.day, fSortedFlights[i].arrDate.month, fSortedFlights[i].arrDate.year);
			printf("%s:%s\n", fSortedFlights[i].arrTime.hours, fSortedFlights[i].arrTime.mins);
		}
	}
}

void advance_date(char* arg) {
	Date dNewToday;
	read_date(&dNewToday, arg);
	if (invalid_date(dNewToday)) {
		printf("invalid date\n");
		return;
	}
	today = dNewToday;
	printf("%s-%s-%s\n", dNewToday.day, dNewToday.month, dNewToday.year);
}
