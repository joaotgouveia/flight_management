#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/* Airport related values */
#define MAXAIRPORTS 40
#define IDSIZEAP 4
#define COUNTRYSIZE 31
#define CITYSIZE 51
/* Flight related values */
#define MAXFLIGHTS 30000
#define IDSIZEFL 7
/* Time and date related values */
#define TIMESIZE 6
#define DATESIZE 11
/* Arg related values */
#define ARGSIZE MAXAIRPORTS*(IDSIZEAP+1)+3
#define ARGSTART 2

/* Prototyping functions */
void add_airplane(char* arg);

/* Declaring structs */
typedef struct date{
	int day;
	int month;
	int year;
} date;

typedef struct airport {
	char id[IDSIZEAP];
	char country[COUNTRYSIZE];
	char city[CITYSIZE];
	int flights;
} airport;

typedef struct flight {
	char id[IDSIZEFL];
	airport departure;
	airport arrival;
	int duration;
	int maxPassengers;
} flight;

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
		case 'l':
			if (strlen(arg) != 1) {
				list_airports(arg + ARGSTART);
			}
	}
	return 0;
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

void list_airports(char* arg)
