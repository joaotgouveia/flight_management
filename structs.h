/* Defining structs */
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
