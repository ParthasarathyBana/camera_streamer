#pragma once

#include "pipeline.h"
#include "frame_manager.h"

// function to synchronize frames based on frame number
void frame_manager::sync_frameid(frame_manager::queue_vector qv, const int frame_number);

// function to synchronize frames based on frame timestamp
void frame_manager::sync_timestamp(frame_manager::queue_vector qv, float timestamp);
