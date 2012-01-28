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

#ifndef _THREAD_MANAGER_H
#define	_THREAD_MANAGER_H

#include "Function.h"
#include "List.h"
#include "GenericType.h"
// #include "Buffer.h"
#include "Lock.h"
#include "Condition.h"
#include "Types.h"
#include "Array.h"
#include "Queue.h"

class ThreadManager
{
public:
	ThreadManager();
	virtual ~ThreadManager();

	void addJob(const Function<void, GenericType>& job, GenericType arg);
	void addBulkJob(const Function<void, GenericType>& job, Array<GenericType> args);
	void waitTillDone();
	
	void setWorkers(ulong workers);
	ulong getWorkers();
private:
	struct Job
	{
		Function<void, GenericType> job;
		GenericType arg;
	};
	struct Worker
	{
		ThreadManager* manager;
		pthread_t thread;
		bool running;
	};

	List<Worker*> workers;
	Queue<Job*> jobs;

	static void* workerFunction(void* arg);
	static void deleteWorker(GenericType arg);

	// Don't allow use of
	ThreadManager(ThreadManager& orig);
	ThreadManager& operator=(ThreadManager& rhs);
};

#endif
