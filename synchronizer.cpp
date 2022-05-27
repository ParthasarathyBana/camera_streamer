// Synchronize frames retrieved from multiple cameras.
#include <frame_manager.h>
#include <vector>
#include <mutex>
#include <chrono>

// synchronize frames based on frame number
void frame_manager::sync_frameid(queue_vector qv, const int frame_number)
{
    // collect sync frames from each queue in the queue_vector
    for (auto q : qv)
    {
        auto const current_queue = q;
        std::vector<frame_manager::frame> frames_synced; 
        while (!current_queue.empty())
        {
            std::lock_guard<std::mutex> lock(_mutex);
            for (auto s = current_queue.begin(); s!=current_queue.end(); s++)
            {
                if (s->get_frameid()!=frame_number)
                {
                    return;
                }
                frames_synced.push_back(s);
            }  
        }
    }
}

// synchronize frames based on timestamp
void frame_manager::sync_timestamp(queue_vector qv, float timestamp)
{
    for (auto q : qv)
    {
        auto const current_queue = q;
        std::vector<frame_manager::frame> frames_synced;
        while (!current_queue.empty())
        {
            std::lock_guard<std::mutex> lock(_mutex);
            for (auto s = frame_queue.begin(); s!= frame_queue.end(); s++)
            {
                if (s->get_timestamp()!=std::chrono::system_clock::now())
                {
                    return;
                }
                frames_synced.push_back(s);
            }
        }
    }
}