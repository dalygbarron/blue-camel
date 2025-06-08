#include "Job.hh"

Job::List::List(unsigned int nThreads) {
    if (nThreads == 0) nThreads = std::thread::hardware_concurrency();
    for (int i = 0; i < nThreads; i++) {
        threads.emplace_back(std::thread([this] {
            while (!this->timeToDie) {
                Job *job;
                if (this->jobs.try_dequeue(job)) {
                    if (job->execute(job->params)) this->enqueue(job, job->params);
                }
            }
        }));
    }
}

Job::List::~List() {
    timeToDie = true;
    for (std::thread& thread: threads) {
        thread.join();
    }
}


void Job::List::enqueue(Job *job, void const *params) {
    job->params = params;
    jobs.enqueue(job);
}