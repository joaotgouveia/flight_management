/* Defining structs */
typedef struct date{
	char day[DAY];
	char month[MONTH];
	char year[YEAR];
} date;

typedef struct airport {
	char id[IDAP];
	char country[COUNTRY];
	char city[CITY];
	int departures;
} airport;

typedef struct flight {
	char id[IDFL];
	char departure[IDAP];
	char arrival[IDAP];
	date date;
	char time[TIME];
	int duration;
	int maxPassengers;
} flight;
