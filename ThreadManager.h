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

template <class Param>
class ThreadManagerBase
{
public:
	ThreadManagerBase();
	virtual ~ThreadManagerBase();

	void addJob(const Function<void, Param>& job, Param arg);
	void addBulkJob(const Function<void, Param>& job, Array<Param> args);
	void waitTillDone();
	
	void setWorkers(ulong workers);
	ulong getWorkers();
private:
	struct Job
	{
		Function<void, Param> job;
		Param arg;
	};
	struct Worker
	{
		ThreadManagerBase* manager;
		pthread_t thread;
		bool running;
	};

	List<Worker*> workers;
	Queue<Job*> jobs;

	static void* workerFunction(void* arg);
	static void deleteWorker(Param arg);

	// Don't allow use of
	ThreadManagerBase(ThreadManagerBase& orig);
	ThreadManagerBase& operator=(ThreadManagerBase& rhs);
};

typedef ThreadManagerBase<GenericType> ThreadManager;

template <class Param>
ThreadManagerBase<Param>::ThreadManagerBase()
{
	this->setWorkers(1);
}
template <class Param>
ThreadManagerBase<Param>::ThreadManagerBase(ThreadManagerBase& orig)
{
	// TODO: needs new set of workers + copied jobs
	this->workers = orig.workers;
	this->jobs = orig.jobs;
}
template <class Param>
ThreadManagerBase<Param>::~ThreadManagerBase()
{
	// Empty out job queue
	while(jobs.size() > 0)
	{
		jobs.remove();
	}
	
	// Tell each Worker its done
	for(typename List<Worker*>::Iterator it = workers.begin(); !it; it++)
	{
		it.value()->running = false;
	}
	
	// Add a null job to each thread so they stop waiting and end
	for(ulong i = 0; i < workers.size(); i++)
	{
		Job* job = new Job;
		job->job = ThreadManagerBase<Param>::deleteWorker;
		job->arg = Param();
		jobs.insert(job);
	}
	
	// TODO: Spinlock = bad
	// Wait until no more worker threads waiting for work
	while(jobs.waitingThreads() > 0) {}
}

template <class Param>
void ThreadManagerBase<Param>::addJob(const Function<void, Param>& job, Param arg)
{
	Job* newJob = new Job;
	newJob->job = job;
	newJob->arg = arg;

	jobs.insert(newJob);
}
template <class Param>
void ThreadManagerBase<Param>::addBulkJob(const Function<void, Param>& job, Array<Param> args)
{
	for(ulong i = 0; i < args.size(); i++)
	{
		Job* newJob = new Job;
		newJob->job = job;
		// newJob->arg = args[i];
	
		jobs.insert(newJob);
	}
}
template <class Param>
void ThreadManagerBase<Param>::waitTillDone()
{
	jobs.waitTillEmpty();
	// TODO: Spinlock = bad
	while(jobs.waitingThreads() < workers.size()) {}
}

template <class Param>
void ThreadManagerBase<Param>::setWorkers(ulong workers)
{
	// Increase number of workers
	while(workers > this->workers.size())
	{
		Worker* worker = new Worker;
		worker->running = true;
		worker->manager = this;
		pthread_create(&worker->thread, 0x0, workerFunction, (void*)worker);
		this->workers.pushBack(worker);
	}
	// Decrease number of workers
	while(workers < this->workers.size())
	{
		Worker* worker = this->workers.popBack();
		worker->running = false;
	}
}
template <class Param>
ulong ThreadManagerBase<Param>::getWorkers()
{
	return workers.size();
}

template <class Param>
void* ThreadManagerBase<Param>::workerFunction(void* arg)
{
	Worker* worker = (Worker*)arg;

	while(worker->running)
	{
		Job* job = worker->manager->jobs.removeWait();
		job->job(job->arg);
		delete job;
	}

	delete worker;
	return 0x0;
}

template <class Param>
void ThreadManagerBase<Param>::deleteWorker(Param)
{
	
}

template <class Param>
ThreadManagerBase<Param>& ThreadManagerBase<Param>::operator=(ThreadManagerBase& rhs)
{
	this->workers = rhs.workers;
	this->jobs = rhs.jobs;
}

#endif
