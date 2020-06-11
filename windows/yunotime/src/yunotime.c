#include <yuno.h>
#include <windows.h>
#include <stdbool.h>

/*
*/

#define MINUTE_SECONDS (60)
#define HOUR_SECONDS (60 * 60)
#define DAY_SECONDS (24 * 60 * 60)
#define YEAR_SECONDS (DAY_SECONDS * 365)
#define LEAP_YEAR_SECONDS (DAY_SECONDS * (365 + 1))

/*
*/

#define JANUARY_DAY_SECONDS (31 * DAY_SECONDS) 
#define FEBRUARY_DAY_SECONDS (28 * DAY_SECONDS)  
#define LEAP_FEBRUARY_DAY_SECONDS ((28 + 1) * DAY_SECONDS)
#define MARCH_DAY_SECONDS (31 * DAY_SECONDS) 
#define APRIL_DAY_SECONDS (30 * DAY_SECONDS) 
#define MAY_DAY_SECONDS (31 * DAY_SECONDS) 
#define JUNE_DAY_SECONDS (30 * DAY_SECONDS) 
#define JULY_DAY_SECONDS (31 * DAY_SECONDS) 
#define AUGUST_DAY_SECONDS (31 * DAY_SECONDS) 
#define SEPTEMBER_DAY_SECONDS (30 * DAY_SECONDS) 
#define OCTOBER_DAY_SECONDS (31 * DAY_SECONDS) 
#define NOVEMBER_DAY_SECONDS (30 * DAY_SECONDS) 
#define DECEMBER_DAY_SECONDS (31 * DAY_SECONDS) 

/*
*/

static bool leap_yearp (int year){
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

/*
*/

static yunoseconds count_seconds (int year, int month, int day, int hours, int minutes, int seconds){
	yunoseconds totalseconds = 0;
	for (int y = 1970; y < year; y++){
		totalseconds += leap_yearp(y) ? LEAP_YEAR_SECONDS: YEAR_SECONDS;
	}
	for (int m = 1; m < month; m++){
		switch (m){
			case 1: totalseconds += JANUARY_DAY_SECONDS; break;
			case 2: totalseconds += leap_yearp(year) ? LEAP_FEBRUARY_DAY_SECONDS: FEBRUARY_DAY_SECONDS; break;
			case 3: totalseconds += MARCH_DAY_SECONDS; break;
			case 4: totalseconds += APRIL_DAY_SECONDS; break;
			case 5: totalseconds += MAY_DAY_SECONDS; break;
			case 6: totalseconds += JUNE_DAY_SECONDS; break;
			case 7: totalseconds += JULY_DAY_SECONDS; break;
			case 8: totalseconds += AUGUST_DAY_SECONDS; break;
			case 9: totalseconds += SEPTEMBER_DAY_SECONDS; break;
			case 10: totalseconds += OCTOBER_DAY_SECONDS; break;
			case 11: totalseconds += NOVEMBER_DAY_SECONDS; break;
			case 12: totalseconds += DECEMBER_DAY_SECONDS; break;
			default: break;
		}
	}
	totalseconds += (day -1) * DAY_SECONDS;
	totalseconds += hours * HOUR_SECONDS;
	totalseconds += minutes * MINUTE_SECONDS;
	totalseconds += seconds;
	return totalseconds;
}

int __stdcall yunotime (yunoseconds *secondsp){
	reset_yunoerror();
	SYSTEMTIME systemtime;
	GetSystemTime(&systemtime);
	yunoseconds totalseconds = count_seconds(
		systemtime.wYear,
		systemtime.wMonth,
		systemtime.wDay,
		systemtime.wHour,
		systemtime.wMinute,
		systemtime.wSecond
	);
	*secondsp = totalseconds;
	return 0;
}
