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

#ifndef _TIME_H_
#define	_TIME_H_

#include "CString.h"
#include "Types.h"

class Time
{
public:
	Time();
	Time(long seconds);
	Time(long minutes, long seconds);
	Time(long hours, long minutes, long seconds);

	long getSeconds() const;
	long getMinutes() const;
	long getHours() const;
	long getDays() const;
	// 365, no accounting for leap year
	long getYears() const;

	// Sets without affecting anything below it
	// ex: 0 days, 5 minutes before, 1 day 5 minutes after setting 1 day
	void setSeconds(long seconds);
	void setMinutes(long minutes);
	void setHours(long hours);
	void setTime(long hours, long minutes, long seconds);

	void addSeconds(long seconds);
	void addMinutes(long minutes);
	void addHours(long hours);
	void addTime(long hours, long minutes, long seconds);

	String toString(String format = "%-%h:%m:%s") const;

	Time& operator=(const Time& rhs);
	Time operator+(const Time& rhs) const;
	Time& operator+=(const Time& rhs);
	Time operator-(const Time& rhs) const;
	Time& operator-=(const Time& rhs);
	bool operator==(const Time& rhs) const;
	bool operator!=(const Time& rhs) const;
	bool operator<(const Time& rhs) const;
	bool operator<=(const Time& rhs) const;
	bool operator>(const Time& rhs) const;
	bool operator>=(const Time& rhs) const;
	operator long() const;
private:
	String absolute(int value) const;
	String leadingZero(int value) const;

	long seconds;
};

/*

%s:	seconds % 60 with leading zeros							00-59
%S:	seconds % 60 without leading zeros					0-59
%t: total seconds without leading zeros
%m:	minutes % 60 with leading zeros (2 digits)	00-59
%M:	minutes % 60 without leading zeros					0-59
%n: total minutes without leading zeros
%g:	hours % 12 without leading zeros						1-12
%G:	hours % 24 without leading zeros						0-23
%h:	hours % 12 with leading zeros								01-12
%H:	hours % 24 with leading zeros								00-23
%i: total hours without leading zeros
%d:	total days without leading zeros
%y:	total year without leading zeros
%-: minus sign only if time is negative					'-',''
%+: + or - depending on negativity of time			'-','+'

*/

#endif
