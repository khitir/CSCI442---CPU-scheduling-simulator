#include "algorithms/rr/rr_algorithm.hpp"
#include "utilities/logger/logger.hpp" 

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"


/*
    Here is where you should define the logic for the round robin algorithm.
*/

RRScheduler::RRScheduler(int slice) { 

    if (slice == -1) {
        time_slice = 3;
    }else{
        time_slice = slice;

    }

}

std::shared_ptr<SchedulingDecision> RRScheduler::get_next_thread() {


    SchedulingDecision decision;
    if (RRQueue.empty()) {
        decision.thread = nullptr;
        decision.explanation = "No threads available for scheduling.";
    }
    else{
        decision.thread = RRQueue.front();
        decision.time_slice = time_slice;
        decision.explanation = "Selected from " + std::to_string(RRQueue.size()) + " threads. Will run for at most " + std::to_string(time_slice) + " ticks.";

        RRQueue.pop();

    }

    return std::make_shared<SchedulingDecision>(decision);
}

void RRScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {

    //TODO Implement Me
    RRQueue.push(thread);
}

size_t RRScheduler::size() const {
    return RRQueue.size();
}