#include "algorithms/priority/priority_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the priority algorithm.
*/

PRIORITYScheduler::PRIORITYScheduler(int slice)
{
    if (slice != -1)
    {
        throw("PRIORITY must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> PRIORITYScheduler::get_next_thread()
{
    if (!priorityQueue.empty())
    {
        std::shared_ptr<Thread> selectedThread = priorityQueue.top();

        // Create a scheduling decision for the selected thread
        auto decision = std::make_shared<SchedulingDecision>();
        decision->thread = selectedThread;

        int before[4];
        for (int i = 0; i < 4; ++i)
        {
            before[i] = myArray[i];
        }
        myArray[decision->thread->priority] -= 1;

        decision->explanation = fmt::format("[S: {} I: {} N: {} B: {}] -> [S: {} I: {} N: {} B: {}]. Will run to completion of burst.", before[0],before[1],before[2],before[3],myArray[0],myArray[1],myArray[2],myArray[3]);
        // Remove the selected thread from the ready queue
        priorityQueue.pop();

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

void PRIORITYScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread)
{
    // TODO: implement me!
    priorityQueue.push(thread->priority, thread);
    myArray[thread->priority] += 1;
}

size_t PRIORITYScheduler::size() const
{
    // TODO: Implement me!!
    return priorityQueue.size();
}
