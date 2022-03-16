#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* Airport related values */
#define MAXAIRPORTS 40
#define IDSIZEAP 3
#define COUNTRYSIZE 30
#define CITYSIZE 50
/* Flight related values */
#define MAXFLIGHTS 30000
#define IDSIZEFL 6
/* Time and date related values */
#define TIMESIZE 5
#define DATESIZE 10

/* Prototyping structs */
struct airport;
struct flight;

int main () {
	
	return 0;
}

struct airport {
	char cId[IDSIZEAP];
	char cCountry[COUNTRYSIZE];
	char cCity[CITYSIZE];
};

struct flight {
	char cId[IDSIZEFL];
	struct airport aDeparture;
	struct airport aArrival;
	int iDuration;
	int iMaxPassengers;

};

