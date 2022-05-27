# Multi-Camera Streamer
This repo is a proposal for a software module that collects live sensor data from seven [Realsense D455](https://www.intelrealsense.com/depth-camera-d455/) cameras and stores this data in a single buffer that can be queried by perception algorithms, where frames in the buffer are ordered by exposure time.

Based on the type of application scenario that these cameras are being used in, users may require data to be streamed in a synchronous or asynchronous mode. For example, in a VR application, to capture the 3D scene around the user, live recording of camera streams in a synchronous fashion is required. The cameras may also need to be positioned in an inward facing manner with the user being the subject of interest at the center, so that all surface volumes of the objects around the user, in the scene can be captured.

To understand more about the hardware specifications of the Realsense D455 cameras and how to connect them in a multi-cam fashion, refer to this [documentation](https://dev.intelrealsense.com/docs/multiple-depth-cameras-configuration).

This repo, inspired by the [Intel Realsense SDK 2.0](https://github.com/IntelRealSense/librealsense), provides a high level API for streaming live data from seven D455 cameras.

## Design of software Module
The D455 cameras stream three types of data - RGB, Depth and IMU. Each of the seven cameras will have their internal time clock which are ideally built with the same crystal and are individual (i.e. they do not synchronize with any camera's clock). The CPU of the host machine, to which the cameras are connected, has a clock internally that is not in sync with the clocks of any of the cameras. To stream live data from all the cameras, the following design of a software module is proposed.

This software module consists of a pipeline, frame manager and synchronizer.

### Pipeline
Pipeline is an abstract class consisting of methods to perform the following. This class allows to establish a connection with a camera and obtain streaming data form the camera sensor.

1. Keep a record of camera config: For each camera, the config parameters such as device id, frame rate, exposure time, etc. are mentioned in a `yaml` file that can be used by this class to refer to a particular camera before streaming data.

2. Configure and establish connections with camera: Once the camera config is known, establish a connection with that particular camera and perform hand-shake.

3. Start camera stream: Create a channel to stream data from the camera sensor.

4. Poll data streams: Wait for camera streams to appear on streaming channel.

5. Stop camera stream: Close camera stream and disconnect camera connection.

### Frame Manager
As the name implies, this module is designed to handle and manage frames from each camera. As we have seven cameras streaming data at different timestamps, we make use of a `frame_queue` which is a `queue` data structure, to store frames particular to each camera.  To avoid conflicts of shared resources, threading architechture is used. Each camera streams data to the frame_queue which is executed in a separate thread. This means we have seven threads for seven cameras to stream data onto seven queues. Now all these seven queues are stored in a `queue_vector` which is a vector container that is sorted upon each update in any of the queues so that the first queues in the vector corresponds to the camera with least exposure time. Of course, the data coming into the queues is also ordered by least exposure time because queues follow a FIFO principle.

Each frame from each camera will have a frame number and time stamp that can be queried. The time stamp attached to the frame is based on the host machine's clock and not the camera's clock (i.e. the time at which the frame was received on the CPU).

### Synchronizer
This module aids in creating composite frames that are synchronized. For live streaming applications, it is important for all the camera streams to be synchronized. Now synchronization of data can be done based on time or the data header stamp (i.e. frame number or data id). 

