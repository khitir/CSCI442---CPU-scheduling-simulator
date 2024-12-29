#include "algorithms/fcfs/fcfs_algorithm.hpp"
#include "utilities/logger/logger.hpp" 
#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"
#include "utilities/stable_priority_queue/stable_priority_queue.hpp" // or this ???
/*
    Here is where you should define the logic for the FCFS algorithm.
*/

FCFSScheduler::FCFSScheduler(int slice)
{
    if (slice != -1)
    {
        throw("FCFS must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> FCFSScheduler::get_next_thread()
{
    // TODO: implement me!
    if (!readyQueue.empty())
    {
        // Get the first thread in the ready queue (FCFS)
        std::shared_ptr<Thread> selectedThread = readyQueue.top();

        // Create a scheduling decision for the selected thread
        auto decision = std::make_shared<SchedulingDecision>();
        decision->thread = selectedThread;
        decision->explanation = fmt::format("Selected from {} threads. Will run to completion of burst.", readyQueue.size());

        // Remove the selected thread from the ready queue
        readyQueue.pop();

        return decision;
    }

    else
    {
        // No threads available for scheduling
        auto decision = std::make_shared<SchedulingDecision>();
        decision->explanation = "No threads available for scheduling.";
        decision->thread = nullptr;

        return decision;
    }
}

void FCFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread)
{
    // TODO: implement me!
    readyQueue.push(0, thread);
}

size_t FCFSScheduler::size() const
{
    // TODO: implement me!
    return readyQueue.size();
}
