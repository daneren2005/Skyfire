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

#include "Time.h"

Time::Time()
{
	this->seconds = 0;
}
Time::Time(long seconds)
{
	this->seconds = seconds;
}
Time::Time(long minutes, long seconds)
{
	this->seconds = minutes * 60 + seconds;
}
Time::Time(long hours, long minutes, long seconds)
{
	this->seconds = hours * 3600 + minutes * 60 + seconds;
}

long Time::getSeconds() const
{
	return seconds;
}
long Time::getMinutes() const
{
	return seconds / 60;
}
long Time::getHours() const
{
	return seconds / 3600;
}
long Time::getDays() const
{
	return seconds / 86400;
}
long Time::getYears() const
{
	return seconds / 31536000;
}

void Time::setSeconds(long seconds)
{
	this->seconds = seconds;
}
void Time::setMinutes(long minutes)
{
	this->seconds = minutes * 60 + this->seconds % 60;
}
void Time::setHours(long hours)
{
	this->seconds = hours * 3600 + this->seconds % 3600;
}
void Time::setTime(long hours, long minutes, long seconds)
{
	this->seconds = seconds + minutes * 60 + hours * 3600;
}

void Time::addSeconds(long seconds)
{
	this->seconds += seconds;
}
void Time::addMinutes(long minutes)
{
	this->seconds += minutes * 60;
}
void Time::addHours(long hours)
{
	this->seconds += hours * 3600;
}
void Time::addTime(long hours, long minutes, long seconds)
{
	this->seconds += seconds + minutes * 60 + hours * 3600;
}

String Time::toString(String format) const
{
	for(long i = 0; i < format.length(); i++)
	{
		if(format[i] == '%')
		{
			switch(format[i + 1])
			{
				case 's':
					format = format.replace(i, 2, leadingZero(seconds % 60));
					break;
				case 'S':
					format = format.replace(i, 2, absolute(seconds % 60));
					break;
				case 't':
					format = format.replace(i, 2, absolute(seconds));
					break;
				case 'm':
					format = format.replace(i, 2, leadingZero(getMinutes() % 60));
					break;
				case 'M':
					format = format.replace(i, 2, absolute(getMinutes() % 60));
					break;
				case 'n':
					format = format.replace(i, 2, absolute(getMinutes()));
					break;
				case 'g':
					format = format.replace(i, 2, absolute(getHours() % 12));
					break;
				case 'G':
					format = format.replace(i, 2, absolute(getHours() % 24));
					break;
				case 'h':
					format = format.replace(i, 2, leadingZero(getHours() % 12));
					break;
				case 'H':
					format = format.replace(i, 2, leadingZero(getHours() % 24));
					break;
				case 'i':
					format = format.replace(i, 2, absolute(getHours()));
					break;
				case 'd':
					format = format.replace(i, 2, absolute(getDays()));
					break;
				case 'y':
					format = format.replace(i, 2, absolute(getYears() % 60));
					break;
				case '-':
					if(seconds < 0)
					{
						format = format.replace(i, 2, "-");
					}
					else
					{
						format = format.replace(i, 2, "");
						i--;
					}
					break;
				case '+':
					if(seconds < 0)
						format = format.replace(i, 2, "-");
					else
						format = format.replace(i, 2, "+");
					break;
			}
		}
	}

	return format;
}

Time& Time::operator=(const Time& rhs)
{
	this->seconds = rhs.seconds;
	return *this;
}
Time Time::operator+(const Time& rhs) const
{
	return Time(this->seconds + rhs.seconds);
}
Time& Time::operator+=(const Time& rhs)
{
	this->seconds += rhs.seconds;
	return *this;
}
Time Time::operator-(const Time& rhs) const
{
	return Time(this->seconds - rhs.seconds);
}
Time& Time::operator-=(const Time& rhs)
{
	this->seconds -= rhs.seconds;
	return *this;
}
bool Time::operator==(const Time& rhs) const
{
	return this->seconds == rhs.seconds;
}
bool Time::operator!=(const Time& rhs) const
{
	return this->seconds != rhs.seconds;
}
bool Time::operator<(const Time& rhs) const
{
	return this->seconds < rhs.seconds;
}
bool Time::operator<=(const Time& rhs) const
{
	return this->seconds <= rhs.seconds;
}
bool Time::operator>(const Time& rhs) const
{
	return this->seconds > rhs.seconds; 
}
bool Time::operator>=(const Time& rhs) const
{
	return this->seconds >= rhs.seconds;
}
Time::operator long() const
{
	return this->seconds;
}

String Time::absolute(int value) const
{
	if(value < 0)
		return String(-value);
	else
		return String(value);
}
String Time::leadingZero(int value) const
{
	if(value < -9)
		return String(-value);
	else if(value < 0)
		return String("0") + String(-value);
	else if(value < 10)
		return String("0") + String(value);
	else
		return String(value);
}

