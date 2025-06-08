#pragma once

#include <thread>
#include <concurrentqueue.h>

/**
 * A job that can be carried out by a thread in a thread pool.
 */
class Job {
    public:
        /**
        * A big beautiful list of jobs.
        */
        class List {
            private:
                moodycamel::ConcurrentQueue<Job *> jobs;
                std::vector<std::thread> threads;
                bool timeToDie = false;

            public:
                /**
                * Creates the job list with however many threads you like, with 0
                * meaning just figure it out yourself.
                * @param nThreads is the number of threads to use.
                */
                List(unsigned int nThreads);

                /**
                * Grabs all the threads and gets a jonestown type situation going.
                */
                ~List();

                /**
                * Enqueues a job and records some params to give it at run time.
                * @param job is the job to enqueue.
                * @param params is the params to give it.
                */
                void enqueue(Job *job, void const *params);

                friend class Job;
        };
        
    private:
        void const *params;

        /**
         * This is where the actual job execution logic goes.
         * @param params is a void pointer to whatever you passed to enqueue
         *        job.
         * @return true iff you wanna immediately add this job back to the queue
         *         after it finishes.
         */
        virtual bool execute(void const *params) = 0;
};