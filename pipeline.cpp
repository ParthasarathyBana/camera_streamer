#include <frame_manager.h>
#include <pipeline.h>

// function to connect camera and start stream
std::shared_ptr<camera_streamer> start()
{
    start_camera(device_id);
    start_stream(camera_id);
}


// function to stop camera stream and disconnect camera device
void stop(float camera_id, float device_id)
{
    stop_stream(camera_id);
    disconnect(device_id);
}

// function to wait for frames to appear on stream
void wait_for_frames()
{
    return;
}