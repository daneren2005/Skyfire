/*
	This file is part of Skyfire.

    Skyfire is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Skyfire is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Skyfire.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _DATE_H
#define	_DATE_H

#include "Time.h"
#include "CString.h"

class Date
{
public:
	Date();
	Date(const time_t& value);
	Date(int year, int month, int day);
	Date(int year, int month, int day, int hour, int minute, int second);
	Date(const Date& orig);

	int getSecond() const;
	int getMinute() const;
	int getHour() const;
	int getDay() const;
	int getWeekDay() const;
	int getYearDay() const;
	int getMonth() const;
	int getDaysInMonth() const;
	int getYear() const;
	int getTimeZone() const;
	// TODO
	String getTimeZoneIdentifier() const;
	bool isLeapYear() const;

	void setSecond(int second);
	void setMinute(int minute);
	void setHour(int hour);
	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);
	void convertTimeZone(int timeZone);

	void addTime(int hour, int minute, int second);
	void addTime(int day, int hour, int minute, int second);

	String toString(String format = "%l %m %D %Y %h:%i:%s %A GMT%E") const;

	Date& operator=(const Date& rhs);
	Date operator+(const Time& rhs);
	Date& operator+=(const Time& rhs);
	// TODO: Get exact Time not average days per month/year
	// year = static 365, month = static 30 days
	Time operator-(const Date& rhs);
	Date operator-(const Time& rhs);
	Date& operator-=(const Time& rhs);
	bool operator==(const Date& rhs) const;
	bool operator!=(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
	bool operator<=(const Date& rhs) const;
	bool operator>(const Date& rhs) const;
	bool operator>=(const Date& rhs) const;

	static Date now();
	static int getSystemTimeZone();
private:
	String leadingZero(int value) const;
	String addSuffix(int num) const;

	String getLowerAMPM() const;
	String getUpperAMPM() const;

	String getShortDay() const;
	String getFullDay() const;
	String getShortMonth() const;
	String getFullMonth() const;

	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;
	int timeZone;
};

/*

%s:	Seconds with leading zeros							00-59
%S:	Seconds without leading zeros						0-59
%i:	minutes with leading zeros							00-59
%I:	minutes without leading zeros						0-59
%g:	hour in 12-hour without leading zeros		1-12
%G:	hour in 24-hour without leading zeros		0-23
%h: hour in 12-hour with leading zeros			01-12
%H:	hour in 24-hour with leading zeros			00-23
%a:	lowercase AM or PM											am/pm
%A: uppercase AM or PM											AM/PM

%d:	day of month with leading zeros					01-31
%D:	day of month without leading zeros			1-31
%l:	abbreviated textual day of week					Mon-Sun
%L:	full textual day of week								Monday-Sunday
%f:	day of week with suffix									1st-7th
%F:	day of month with suffix								1st,2nd,3rd-31st
%z:	number day of the week									1-7
%Z: number day of the year									0-365

%m:	abbreviated textual month								Jan-Dec
%M:	full textual month											January-December
%n:	number month with leading zeros					01-12
%N:	number month without leading zeros			1-12
%t:	number of days in a month								28-31
%y:	short year number												89,04,11
%Y:	full year number												1989,2004,2011

%e:	timezone identifier											GMT,UTC,PST...
%E:	hour difference from GMT								0,1,2...

*/

#endif
