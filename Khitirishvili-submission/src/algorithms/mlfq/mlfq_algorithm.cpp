
#include <cassert>
#include <stdexcept>
#include <string>
#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"
#include "algorithms/mlfq/mlfq_algorithm.hpp"
MLFQScheduler::MLFQScheduler(int slice)
{
    if (slice != -1)
    {
        throw std::runtime_error("MLFQ does NOT take a customizable time slice");
    }
}

std::shared_ptr<SchedulingDecision> MLFQScheduler::get_next_thread()
{

    SchedulingDecision next_in_queue;
    std::string priorityStr = "";
    for (int i = 0; i < 10; i++)
    {
        if (!(myQueue[i].empty()))
        {
            next_in_queue.thread = myQueue[i].top();
            next_in_queue.thread->start = next_in_queue.thread->service_time;
            // next_in_queue.thread->acc = 0;
            int ftime_slice = pow(2, i);
            this->time_slice = ftime_slice;
            if (next_in_queue.thread->priority == SYSTEM)
            {
                priorityStr = "SYSTEM";
            }
            else if (next_in_queue.thread->priority == INTERACTIVE)
            {
                priorityStr = "INTERACTIVE";
            }
            else if (next_in_queue.thread->priority == NORMAL)
            {
                priorityStr = "NORMAL";
            }
            else if (next_in_queue.thread->priority == BATCH)
            {
                priorityStr = "BATCH";
            }
            next_in_queue.explanation = "Selected from queue " + std::to_string(i) + " (priority = " + priorityStr + ", runtime = " + std::to_string(next_in_queue.thread->acc) + "). Will run for at most " + std::to_string(ftime_slice) + " ticks.";
            myQueue[i].pop();

            next_in_queue.thread->acc += std::min(ftime_slice, next_in_queue.thread->get_next_burst(CPU)->length);

            return std::make_shared<SchedulingDecision>(next_in_queue);
        }
    }
    next_in_queue.thread = nullptr;
    next_in_queue.explanation = "No threads available for scheduling.";
    return std::make_shared<SchedulingDecision>(next_in_queue);
}

void MLFQScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread)
{

    //thread->acc += (thread->service_time - thread->start);
    // thread->acc += (thread.getnextburst(CPU).length() - thread->start);
    int currTimeSlice = pow(2, thread->queN);
    // slice = currTimeSlice;
    if (thread->queN == -1)
    {
        thread->queN = 0;
    }
    else if (thread->acc >= currTimeSlice || thread->acc == 0)
    {
        thread->queN++;
        if (thread->queN == 10)
        {
            thread->queN = 9;
        }
        thread->acc = 0;
    }

    myQueue[thread->queN].push(thread->priority, thread);
}

size_t MLFQScheduler::size() const
{

    size_t queueSize = 0;
    for (int i = 0; i < 10; i++)
    {
        queueSize += myQueue[i].size();
    }
    return queueSize;
}
