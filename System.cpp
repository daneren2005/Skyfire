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

#include "System.h"
#include <stdio.h>
#include <string.h>
#include "Console.h"

System sys = System();

System::System()
{
	uint eax, ebx, ecx, edx;

	eax = 0;
	cpuid(eax, ebx, ecx, edx);
	
	char* buff = new char[13];
	memcpy(buff, &ebx, 4);
	memcpy(buff + 4, &edx, 4);
	memcpy(buff + 8, &ecx, 4);
	buff[12] = 0x0;
	processor.vendor = buff;
	delete[] buff;

	eax = 1;
	cpuid(eax, ebx, ecx, edx);

	processor.hyperthread = edx & (1 << 28);
	processor.hypervisor = ecx & (1 << 31);

	processor.sse = edx & (1 << 25);
	processor.sse2 = edx & (1 << 26);
	processor.sse3 = ecx & (1 << 0);
	processor.ssse3 = ecx & (1 << 9);
	processor.sse4_1 = ecx & (1 << 19);
	processor.sse4_2 = ecx & (1 << 20);
	processor.aes = ecx & (1 << 25);
	processor.avx = ecx & (1 << 28);
	processor.rdrand = ecx & (1 << 30);
	
	processor.threads = (ebx >> 16) & 0xff;
	
	eax = 0x80000001;
	cpuid(eax, ebx, ecx, edx);
	processor.x64 = edx & (1 << 29);
	
	buff = new char[48];
	eax = 0x80000002;
	cpuid(eax, ebx, ecx, edx);
	memcpy(buff + 0, &eax, 4);
	memcpy(buff + 4, &ebx, 4);
	memcpy(buff + 8, &ecx, 4);
	memcpy(buff + 12, &edx, 4);
	eax = 0x80000003;
	cpuid(eax, ebx, ecx, edx);
	memcpy(buff + 16, &eax, 4);
	memcpy(buff + 20, &ebx, 4);
	memcpy(buff + 24, &ecx, 4);
	memcpy(buff + 28, &edx, 4);
	eax = 0x80000004;
	cpuid(eax, ebx, ecx, edx);
	memcpy(buff + 32, &eax, 4);
	memcpy(buff + 36, &ebx, 4);
	memcpy(buff + 40, &ecx, 4);
	memcpy(buff + 44, &edx, 4);
	processor.name = buff;
	delete[] buff;
	
	eax = 0x80000008;
	cpuid(eax, ebx, ecx, edx);
	processor.cores = (ecx & 0xff) + 1; 
}

void System::cpuid(uint& eax, uint& ebx, uint& ecx, uint& edx)
{
	__asm volatile
    ("mov %%ebx, %%edi;"
     "cpuid;"
     "mov %%ebx, %%esi;"
     "mov %%edi, %%ebx;"
     :"+a" (eax), "=S" (ebx), "=c" (ecx), "=d" (edx)
     : :"edi");
}
