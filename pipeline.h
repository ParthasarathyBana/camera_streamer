// Ref: https://github.com/IntelRealSense/librealsense
#pragma once

#include <frame_manager.h>

namespace camera_streamer
{
    namespace pipeline
    {
        class pipeline
        {
            public:
                // function to load camara config parameters and start camera stream
                std::shared_ptr<camera_profile> start(std::shared_ptr<config> config, frame_callback_ptr callback = nullptr);
                
                // function to stop camera stream
                void stop();
                
                // function to wait and poll frames as they appear on the channel
                frame_holder wait_for_frames(float timeout_ms);

            private:
                // callback to retrieve data for asynchronous applications
                frame_callback_ptr m_async_callback;
                
                // vector to store all synchronized data
                std::vector<camera_streamer> m_synced_streams;
        };
    }
}