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

#include "Date.h"
#include <time.h>

#include <iostream>
using namespace std;

Date::Date()
{
	// Get current date/time
	time_t rawValue;
	time(&rawValue);

	struct tm* date = localtime(&rawValue);
	this->second = date->tm_sec;
	this->minute = date->tm_min;
	this->hour = date->tm_hour;
	this->day = date->tm_mday;
	this->month = date->tm_mon + 1;
	this->year = date->tm_year + 1900;
	this->timeZone = getSystemTimeZone();
}
Date::Date(const time_t& value)
{
	struct tm* date = localtime(&value);
	this->second = date->tm_sec;
	this->minute = date->tm_min;
	this->hour = date->tm_hour;
	this->day = date->tm_mday;
	this->month = date->tm_mon + 1;
	this->year = date->tm_year + 1900;
	this->timeZone = getSystemTimeZone();
}
Date::Date(int year, int month, int day)
{
	this->second = 0;
	this->minute = 0;
	this->hour = 0;
	this->day = day;
	this->month = month;
	this->year = year;
	this->timeZone = getSystemTimeZone();
}
Date::Date(int year, int month, int day, int hour, int minute, int second)
{
	this->second = second;
	this->minute = minute;
	this->hour = hour;
	this->day = day;
	this->month = month;
	this->year = year;
	this->timeZone = getSystemTimeZone();
}
Date::Date(const Date& orig)
{
	this->second = orig.second;
	this->minute = orig.minute;
	this->hour = orig.hour;
	this->day = orig.day;
	this->month = orig.month;
	this->year = orig.year;
	this->timeZone = orig.timeZone;
}

int Date::getSecond() const
{
	return second;
}
int Date::getMinute() const
{
	return minute;
}
int Date::getHour() const
{
	return hour;
}
int Date::getDay() const
{
	return day;
}
int Date::getWeekDay() const
{
	// Get what day of week a doomsday is
	int doom = 2 + year + (year / 4) - (year / 100) + (year / 400);

	// Get closest doomsday of the month
	bool leap = isLeapYear();
	int date = 0;
	switch(month)
	{
		case 1:
			if(leap)
				date = 11;
			else
				date = 10;
			break;
		case 2:
			if(leap)
				date = 29;
			else
				date = 28;
			break;
		case 3:
			date = 7;
			break;
		case 4:
			date = 4;
			break;
		case 5:
			date = 9;
			break;
		case 6:
			date = 6;
			break;
		case 7:
			date = 11;
			break;
		case 8:
			date = 8;
			break;
		case 9:
			date = 5;
			break;
		case 10:
			date = 10;
			break;
		case 11:
			date = 7;
			break;
		case 12:
			date = 12;
			break;
		default:
			break;
	}

	// Get how many weekdays between date and doomsday
	int diff = (day - date) % 7;
	// Get the weekday that day is
	int dayOfWeek = (doom + diff) % 7;
	return (dayOfWeek == 0) ? 7 : dayOfWeek;
}
int Date::getYearDay() const
{
	int total = 0;
	switch(month)
	{
		case 2:
			total += 31;
			break;
		case 3:
			total += 59;
			break;
		case 4:
			total += 90;
			break;
		case 5:
			total += 120;
			break;
		case 6:
			total += 151;
			break;
		case 7:
			total += 181;
			break;
		case 8:
			total += 212;
			break;
		case 9:
			total += 243;
			break;
		case 10:
			total += 273;
			break;
		case 11:
			total += 304;
			break;
		case 12:
			total += 334;
			break;
		default:
			break;
	}

	if(isLeapYear())
		total++;

	total += day;
	return total - 1;
}
int Date::getMonth() const
{
	return month;
}
int Date::getDaysInMonth() const
{
	switch(month)
	{
		case 1:
			return 31;
			break;
		case 2:
			if(isLeapYear())
				return 29;
			else
				return 28;
			break;
		case 3:
			return 31;
			break;
		case 4:
			return 30;
			break;
		case 5:
			return 31;
			break;
		case 6:
			return 30;
			break;
		case 7:
			return 31;
			break;
		case 8:
			return 31;
			break;
		case 9:
			return 30;
			break;
		case 10:
			return 31;
			break;
		case 11:
			return 30;
			break;
		case 12:
			return 31;
			break;
		default:
			return 31;
			break;
	}
}
int Date::getYear() const
{
	return year;
}
int Date::getTimeZone() const
{
	return timeZone;
}
bool Date::isLeapYear() const
{
	return (year % 4 == 0) ? ((year % 100 == 0) ? ((year % 400 == 0) ? true : false) : true) : false;
}

void Date::setSecond(int second)
{
	this->second = second;
}
void Date::setMinute(int minute)
{
	this->minute = minute;
}
void Date::setHour(int hour)
{
	this->hour = hour;
}
void Date::setDay(int day)
{
	this->day = day;
}
void Date::setMonth(int month)
{
	this->month = month;
}
void Date::setYear(int year)
{
	this->year = year;
}
void Date::convertTimeZone(int timeZone)
{
	int diff = timeZone - this->timeZone;
	this->timeZone = timeZone;
	this->hour += diff;
	this->day += hour / 24;
	this->hour = hour % 24;

	if(this->hour < 0)
	{
		this->hour = 24 + this->hour;
		this->day--;

		if(this->day <= 0)
		{
			this->month--;
			if(this->month <= 0)
			{
				this->year--;
				this->month = 12;
			}
			this->day = getDaysInMonth();
		}
	}
	else
	{
		int daysInMonth = getDaysInMonth();
		while(this->day > daysInMonth)
		{
			this->month++;
			this->day = this->day - daysInMonth;
			daysInMonth = getDaysInMonth();
		}
	
		this->year += this->month / 12;
		this->month = this->month % 12;
	}
}

void Date::addTime(int hour, int minute, int second)
{
	this->second += second;
	if(this->second < 0)
	{
		this->minute -= this->second / -60 + minute + 1;
		this->second = 60 + this->second % 60; 
	}
	else
	{
		this->minute += this->second / 60 + minute;
		this->second = this->second % 60;
	}

	if(this->minute < 0)
	{
		this->hour -= this->minute / -60 + hour + 1;
		this->minute = 60 + this->minute % 60;
	}
	else
	{
		this->hour += this->minute / 60 + hour;
		this->minute = this->minute % 60;
	}

	if(this->hour < 0)
	{
		this->day -= this->hour / -24 + 1;
		this->hour = 24 + this->hour % 24;
	}
	else
	{
		this->day += this->hour / 24;
		this->hour = this->hour % 24;
	}

	if(this->day <= 0)
	{
		while(this->day <= 0)
		{
			this->day = this->day + getDaysInMonth();
			this->month--;
		}
	}
	else
	{
		int daysInMonth = getDaysInMonth();
		while(this->day > daysInMonth)
		{
			this->month++;
			this->day = this->day - daysInMonth;
			daysInMonth = getDaysInMonth();
		}
	}

	if(this->month <= 0)
	{
		this->year -= this->month / -12 + 1;
		this->month = 12 + this->month % 12;
	}
	else
	{
		this->year += this->month / 12;
		this->month = this->month % 12;
	}
}
void Date::addTime(int day, int hour, int minute, int second)
{
	this->second += second;
	if(this->second < 0)
	{
		this->minute -= this->second / -60 + minute + 1;
		this->second = 60 + this->second % 60; 
	}
	else
	{
		this->minute += this->second / 60 + minute;
		this->second = this->second % 60;
	}

	if(this->minute < 0)
	{
		this->hour -= this->minute / -60 + hour + 1;
		this->minute = 60 + this->minute % 60;
	}
	else
	{
		this->hour += this->minute / 60 + hour;
		this->minute = this->minute % 60;
	}

	if(this->hour < 0)
	{
		this->day -= this->hour / -24 + 1;
		this->hour = 24 + this->hour % 24;
	}
	else
	{
		this->day += this->hour / 24 + day;
		this->hour = this->hour % 24;
	}

	if(this->day <= 0)
	{
		while(this->day <= 0)
		{
			this->day = this->day + getDaysInMonth();
			this->month--;
		}
	}
	else
	{
		int daysInMonth = getDaysInMonth();
		while(this->day > daysInMonth)
		{
			this->month++;
			this->day = this->day - daysInMonth;
			daysInMonth = getDaysInMonth();
		}
	}

	if(this->month <= 0)
	{
		this->year -= this->month / -12 + 1;
		this->month = 12 + this->month % 12;
	}
	else
	{
		this->year += this->month / 12;
		this->month = this->month % 12;
	}
}

String Date::toString(String format) const
{
	for(long i = 0; i < format.length(); i++)
	{
		if(format[i] == '%')
		{
			switch(format[i + 1])
			{
				case 's':
					format = format.replace(i, 2, leadingZero(second));
					break;
				case 'S':
					format = format.replace(i, 2, String(second));
					break;
				case 'i':
					format = format.replace(i, 2, leadingZero(minute));
					break;
				case 'I':
					format = format.replace(i, 2, String(minute));
					break;
				case 'g':
					format = format.replace(i, 2, String(hour % 12));
					break;
				case 'G':
					format = format.replace(i, 2, String(hour));
					break;
				case 'h':
					format = format.replace(i, 2, leadingZero(hour % 12));
					break;
				case 'H':
					format = format.replace(i, 2, leadingZero(hour));
					break;
				case 'a':
					format = format.replace(i, 2, getLowerAMPM());
					break;
				case 'A':
					format = format.replace(i, 2, getUpperAMPM());
					break;
				case 'd':
					format = format.replace(i, 2, leadingZero(day));
					break;
				case 'D':
					format = format.replace(i, 2, String(day));
					break;
				case 'l':
					format = format.replace(i, 2, getShortDay());
					break;
				case 'L':
					format = format.replace(i, 2, getFullDay());
					break;
				case 'f':
					format = format.replace(i, 2, addSuffix(getWeekDay()));
					break;
				case 'F':
					format = format.replace(i, 2, addSuffix(getYearDay()));
					break;
				case 'z':
					format = format.replace(i, 2, String(getWeekDay()));
					break;
				case 'Z':
					format = format.replace(i, 2, String(getYearDay()));
					break;
				case 'm':
					format = format.replace(i, 2, getShortMonth());
					break;
				case 'M':
					format = format.replace(i, 2, getFullMonth());
					break;
				case 'n':
					format = format.replace(i, 2, leadingZero(month));
					break;
				case 'N':
					format = format.replace(i, 2, String(month));
					break;
				case 't':
					format = format.replace(i, 2, String(getDaysInMonth()));
					break;
				case 'y':
					format = format.replace(i, 2, String(year % 1000));
					break;
				case 'Y':
					format = format.replace(i, 2, String(year));
					break;
				case 'e':
					// TODO
					break;
				case 'E':
					if(timeZone >= 0)
						format = format.replace(i, 2, String("+") + String(timeZone));
					else
						format = format.replace(i, 2, String(timeZone));
					break;
				default:
					break;
			}
		}
	}

	return format;
}

Date& Date::operator=(const Date& rhs)
{
	this->second = rhs.second;
	this->minute = rhs.minute;
	this->hour = rhs.hour;
	this->day = rhs.day;
	this->month = rhs.month;
	this->year = rhs.year;
	return *this;
}
Date Date::operator+(const Time& rhs)
{
	Date date(*this);
	date.addTime(rhs.getDays(), rhs.getHours() % 24, rhs.getMinutes() % 60, rhs.getSeconds() % 60);

	return date;
}
Date& Date::operator+=(const Time& rhs)
{
	this->addTime(rhs.getDays(), rhs.getHours() % 24, rhs.getMinutes() % 60, rhs.getSeconds() % 60);
	return *this;
}
Time Date::operator-(const Date& rhs)
{
	return (this->year - rhs.year) * (long)31536000 + (this->month - rhs.month) * (long)2592000 + (this->day - rhs.day) * (long)86400 + (this->hour - rhs.hour) * (long)3600 + (this->minute - rhs.minute) * (long)60 + (this->second - rhs.second);
}
Date Date::operator-(const Time& rhs)
{
	Date date(*this);
	date.addTime(-rhs.getDays(), -rhs.getHours() % 24, -rhs.getMinutes() % 60, -rhs.getSeconds() % 60);

	return date;
}
Date& Date::operator-=(const Time& rhs)
{
	this->addTime(-rhs.getDays(), -rhs.getHours() % 24, -rhs.getMinutes() % 60, -rhs.getSeconds() % 60);
	return *this;
}
bool Date::operator==(const Date& rhs) const
{
	return (this->second == rhs.second) && (this->minute == rhs.minute) 
		&& (this->hour == rhs.hour) && (this->day == rhs.day)
		&& (this->month == rhs.month) && (this->year == rhs.year);
}
bool Date::operator!=(const Date& rhs) const
{
	return (this->second != rhs.second) || (this->minute != rhs.minute) 
		|| (this->hour != rhs.hour) || (this->day != rhs.day)
		|| (this->month != rhs.month) || (this->year != rhs.year);
}
bool Date::operator<(const Date& rhs) const
{
	long timeDiff = (this->second + this->minute * 60 + this->hour * 3600)
		- (rhs.second + rhs.minute * 60 + rhs.hour * 3600);
	long dayDiff = (this->day + this->month * 35 + this->year * 370)
		- (rhs.day + rhs.month * 35 + rhs.year * 370);

	if(dayDiff < 0)
		return true;
	else if(dayDiff > 0)
		return false;
	else
		return timeDiff < 0;
}
bool Date::operator<=(const Date& rhs) const
{
	long timeDiff = (this->second + this->minute * 60 + this->hour * 3600)
		- (rhs.second + rhs.minute * 60 + rhs.hour * 3600);
	long dayDiff = (this->day + this->month * 35 + this->year * 370)
		- (rhs.day + rhs.month * 35 + rhs.year * 370);

	if(dayDiff < 0)
		return true;
	else if(dayDiff > 0)
		return false;
	else
		return timeDiff <= 0;
}
bool Date::operator>(const Date& rhs) const
{
	long timeDiff = (this->second + this->minute * 60 + this->hour * 3600)
		- (rhs.second + rhs.minute * 60 + rhs.hour * 3600);
	long dayDiff = (this->day + this->month * 35 + this->year * 370)
		- (rhs.day + rhs.month * 35 + rhs.year * 370);

	if(dayDiff > 0)
		return true;
	else if(dayDiff < 0)
		return false;
	else
		return timeDiff > 0;
}
bool Date::operator>=(const Date& rhs) const
{
	long timeDiff = (this->second + this->minute * 60 + this->hour * 3600)
		- (rhs.second + rhs.minute * 60 + rhs.hour * 3600);
	long dayDiff = (this->day + this->month * 35 + this->year * 370)
		- (rhs.day + rhs.month * 35 + rhs.year * 370);

	if(dayDiff > 0)
		return true;
	else if(dayDiff < 0)
		return false;
	else
		return timeDiff >= 0;
}

Date Date::now()
{
	return Date();
}
int Date::getSystemTimeZone()
{
	time_t t = time(0x0);
	struct tm* gmt = gmtime(&t);
	time_t t2 = mktime(gmt);

	return (t - t2) / 3600; 
}

String Date::leadingZero(int value) const
{
	if(value < 10)
		return String("0") + String(value);
	else
		return String(value);
}

String Date::addSuffix(int num) const
{
	String suffix;
	switch(num % 10)
	{
		case 0:
			suffix = "th";
			break;
		case 1:
			suffix = "st";
			break;
		case 2:
			suffix = "nd";
			break;
		case 3:
			suffix = "rd";
			break;
		case 4:
			suffix = "th";
			break;
		case 5:
			suffix = "th";
			break;
		case 6:
			suffix = "th";
			break;
		case 7:
			suffix = "th";
			break;
		case 8:
			suffix = "th";
			break;
		case 9:
			suffix = "th";
			break;
	}

	return String(num) + suffix;
}

String Date::getLowerAMPM() const
{
	return (hour < 12) ? "am" : "pm";
}
String Date::getUpperAMPM() const
{
	return (hour < 12) ? "AM" : "PM";
}

String Date::getShortDay() const
{
	switch(getWeekDay())
	{
		case 1:
			return "Mon";
			break;
		case 2:
			return "Tue";
			break;
		case 3:
			return "Wed";
			break;
		case 4:
			return "Thu";
			break;
		case 5:
			return "Fri";
			break;
		case 6:
			return "Sat";
			break;
		case 7:
			return "Sun";
			break;
		default:
			return "NaN";
			break;
	}
}
String Date::getFullDay() const
{
	switch(getWeekDay())
	{
		case 1:
			return "Monday";
			break;
		case 2:
			return "Tuesday";
			break;
		case 3:
			return "Wednesday";
			break;
		case 4:
			return "Thursday";
			break;
		case 5:
			return "Friday";
			break;
		case 6:
			return "Saturday";
			break;
		case 7:
			return "Sunday";
			break;
		default:
			return "NaN";
			break;
	}
}
String Date::getShortMonth() const
{
	switch(month)
	{
		case 1:
			return "Jan";
			break;
		case 2:
			return "Feb";
			break;
		case 3:
			return "Mar";
			break;
		case 4:
			return "Apr";
			break;
		case 5:
			return "May";
			break;
		case 6:
			return "Jun";
			break;
		case 7:
			return "Jul";
			break;
		case 8:
			return "Aug";
			break;
		case 9:
			return "Sep";
			break;
		case 10:
			return "Oct";
			break;
		case 11:
			return "Nov";
			break;
		case 12:
			return "Dec";
			break;
		default:
			return "NaN";
			break;
	}
}
String Date::getFullMonth() const
{
	switch(month)
	{
		case 1:
			return "January";
			break;
		case 2:
			return "February";
			break;
		case 3:
			return "March";
			break;
		case 4:
			return "April";
			break;
		case 5:
			return "May";
			break;
		case 6:
			return "June";
			break;
		case 7:
			return "July";
			break;
		case 8:
			return "August";
			break;
		case 9:
			return "September";
			break;
		case 10:
			return "October";
			break;
		case 11:
			return "November";
			break;
		case 12:
			return "December";
			break;
		default:
			return "NaN";
			break;
	}
}
