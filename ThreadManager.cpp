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

#include "ThreadManager.h"

ThreadManager::ThreadManager()
{
	this->setWorkers(1);
}
ThreadManager::ThreadManager(ThreadManager& orig)
{
	// TODO: needs new set of workers + copied jobs
	this->workers = orig.workers;
	this->jobs = orig.jobs;
}
ThreadManager::~ThreadManager()
{
	// Empty out job queue
	while(jobs.size() > 0)
	{
		jobs.remove();
	}
	
	// Tell each Worker its done
	for(List<Worker*>::Iterator it = workers.begin(); !it; it++)
	{
		it.value()->running = false;
	}
	
	// Add a null job to each thread so they stop waiting and end
	for(ulong i = 0; i < workers.size(); i++)
	{
		Job* job = new Job;
		job->job = ThreadManager::deleteWorker;
		job->arg = 1;
		jobs.insert(job);
	}
	
	// TODO: Spinlock = bad
	// Wait until no more worker threads waiting for work
	while(jobs.waitingThreads() > 0) {}
}

void ThreadManager::addJob(const Function<void, GenericType>& job, GenericType arg)
{
	Job* newJob = new Job;
	newJob->job = job;
	newJob->arg = arg;

	jobs.insert(newJob);
}
void ThreadManager::addBulkJob(const Function<void, GenericType>& job, Array<GenericType> args)
{
	for(ulong i = 0; i < args.size(); i++)
	{
		Job* newJob = new Job;
		newJob->job = job;
		// newJob->arg = args[i];
	
		jobs.insert(newJob);
	}
}
void ThreadManager::waitTillDone()
{
	jobs.waitTillEmpty();
	// TODO: Spinlock = bad
	while(jobs.waitingThreads() < workers.size()) {}
}

void ThreadManager::setWorkers(ulong workers)
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
ulong ThreadManager::getWorkers()
{
	return workers.size();
}

void* ThreadManager::workerFunction(void* arg)
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

void ThreadManager::deleteWorker(GenericType arg)
{
	
}

ThreadManager& ThreadManager::operator=(ThreadManager& rhs)
{
	this->workers = rhs.workers;
	this->jobs = rhs.jobs;
}
