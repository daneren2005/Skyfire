/* 
 * File:   conversion.h
 * Author: scott
 *
 * Created on November 22, 2010, 10:39 AM
 */

#ifndef _CONVERSION_H
#define	_CONVERSION_H

#include <iostream>
#include <sstream>

float atof(std::string string)
{
	std::stringstream ss;
	ss << string;
	float value;
	ss >> value;
	return value;
}

#endif	/* _CONVERSION_H */

