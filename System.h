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

#ifndef _SYSTEM_H__
#define	_SYSTEM_H__

#include "CString.h"
#include "Types.h"

class System
{
public:
	System();

	struct Processor
	{
		// Physical Processor Details
		String vendor;
		String name;
		uint cores;
		uint threads;
		// uint clock;
	
		// Virtual Processor Details 
		bool x64;
		bool hyperthread;
		bool hypervisor;
	
		// Processor Extensions
		bool sse;
		bool sse2;
		bool sse3;
		bool ssse3;
		bool sse4_1;
		bool sse4_2;
		bool aes;
		bool avx;
		bool rdrand;
	} processor;
private:
	void cpuid(uint& eax, uint& ebx, uint& ecx, uint& edx);
};

extern System sys;

#endif
