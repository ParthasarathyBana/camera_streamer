#pragma once

#include <map>

namespace frame_manager
{
    // define types of stream data
    enum stream_type
    {
        rgb_stream = 10,
        depth_stream = 11,
        rgbd_stream = 12,
        imu_stream = 13
    };

    class frame_holder
    {
        public:
            unsigned int frame_number;
            float timestamp;

        private:
            std::map<frame_holder*, float> m_current_frame;        
    };
}