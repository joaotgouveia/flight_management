/* Defining structs */
typedef struct {
	char day[DAY];
	char month[MONTH];
	char year[YEAR];
} date;

typedef struct {
	char hours[HOURS];
	char mins[MINS];
} time;

typedef struct {
	char id[IDAP];
	char country[COUNTRY];
	char city[CITY];
	int departures;
} airport;

typedef struct {
	char id[IDFL];
	char departure[IDAP];
	char arrival[IDAP];
	date date;
	time time;
	time duration;
	int capacity;
} flight;
