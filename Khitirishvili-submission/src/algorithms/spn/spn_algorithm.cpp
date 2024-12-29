#include "algorithms/spn/spn_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"


/*
    Here is where you should define the logic for the SPN algorithm.
*/

SPNScheduler::SPNScheduler(int slice) {
    if (slice != -1) {
        throw("SPN must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> SPNScheduler::get_next_thread()
{
    // TODO: implement me!
    if (!sizeQueue.empty())
    {
        std::shared_ptr<Thread> selectedThread = sizeQueue.top();

        // Create a scheduling decision for the selected thread
        auto decision = std::make_shared<SchedulingDecision>();
        decision->thread = selectedThread;
        decision->explanation = fmt::format("Selected from {} threads. Will run to completion of burst.", sizeQueue.size());

        // Remove the selected thread from the ready queue
        sizeQueue.pop();

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

void SPNScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    //TODO: Implement me!
    sizeQueue.push(thread->bursts.front()->length, thread);
}

size_t SPNScheduler::size() const {
    //TODo: Implement me
    return sizeQueue.size();
}