#include "Job.hh"
#include <concurrentqueue.h>
#include <thread>

static moodycamel::ConcurrentQueue<Job *> jobs;
static std::vector<std::thread> threads;
static bool endWork;

void Job::work() {
    while (!endWork) {
        Job *job;
        if (jobs.try_dequeue(job)) {
            job->execute(job->params);
            job->iterations++;
        }
    }
}

void Job::enqueue(void const *params) {
    this->params = params;
    jobs.enqueue(this);
}

unsigned int Job::getIterations() const {
    return iterations;
}

void Job::start() {
    endWork = false;
    const uint32_t num_threads = std::thread::hardware_concurrency();
    for (uint32_t ii = 0; ii < num_threads; ++ii) {
        threads.emplace_back(std::thread(&work));
    }
}

void Job::stop() {
    endWork = true;
    while (jobs.size_approx() != 0) {}
    for (std::thread& thread: threads) {
        thread.join();
    }
    threads.clear();
}