#pragma once

/**
 * A job that can be carried out by a thread in a thread pool.
 */
class Job {
    private:
        unsigned int iterations = 0;
        void const *params;

        /**
         * This is where the actual job execution logic goes.
         * @param params is a void pointer to whatever you passed to enqueue
         *        job.
         */
        virtual void execute(void const *params) = 0;

        /**
         * This is the code that all the threads are doing, we just make
         * it a private static so it can access private stuff on jobs.
         */
        static void work();

    public:
        /**
         * Adds the job to the list of jobs to do.
         * @param params is a void pointer to whatever parameters you might like
         *        to be used in the job body. You can pass null if you want, it
         *        totally depends on how execute is implemented.
         */
        void enqueue(void const *params);

        /**
         * This tells you the number of times this specific job object
         * has been completed if that information is interesting to you
         * for some reason.
         * @return the number of times this job has been completed.
         */
        unsigned int getIterations() const;

        /**
         * Start processing jobs and create threads to do it etc.
         */
        static void start();

        /**
         * Blocks until all jobs are done, then destroys all the threads.
         */
        static void stop();
};