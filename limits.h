/* Airport related values */
#define MAXAIRPORTS 40
#define IDAP 4
#define COUNTRY 30
#define CITY 50
/* Flight related values */
#define MAXFLIGHTS 30000
#define IDFL 7
#define CAPACITY 4
/* Time and date related values */
#define HOURS 3
#define MINS 3
#define TIME 6
#define DAY 3
#define MONTH 3
#define YEAR 5
#define DATE 11
#define DATESTART IDAP*2
#define CATDATETIME DATE-3+TIME-1
#define CATDATE DATE-2
/* Arg related values */
#define ARGSIZE MAXAIRPORTS*(IDAP+1)+3
#define ARGSTART 2
/* Boolean values */
#define TRUE 1
#define FALSE 0
#define NOTFOUND -1
/* Data structures */
#define TUPLE 2
