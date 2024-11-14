# Intel-Realsense-Recording-on-Raspberry-Pi-4
Simple C++ Program for recording the data from the Intel Realsense Camera D455 attached to a Raspberry Pi 4. The reason for making this program was for use in a project. During the build process of librealsense2 [here](@Dependencies), the built on tools such as ```rs-record``` did not function properly. As there was a need to record without a gui, ```realsense-viewer`` was not a viable option despite it working.


## Device Requirements
- Raspberry Pi4 running on Bookworm
- IntelRealSense D455
- USB3.0 cable (Required for D455 to function properly)

## Dependencies
- librealsense2 (Installed using [this script](https://github.com/IntelRealSense/librealsense/blob/master/doc/installation_raspbian.md))


## Installation
1. Clone the repository
2. Build using ```g++ -o record_only record_only.cpp -lrealsense2 -lGL -lGLU -lglfw -ldl -lpthread```
3. If required, use ```chmod +x ./record_only ``` for permissions to run the built program.

## Usage

```./record_only --seconds=t --output=/path/to/bag/file.bag```
Takes 2 arguments
1. ```--seconds=t```, where t is the number of seconds to record for
2. ```--output=/path/to/bag/file.bag```, where you provide the absolute path where your recording will be saved

## Possibile Updates
I am extremely new to C++ at the time of making of this source code. In future when I find myself with free time and feel more proficient, I intend to feature ```make``` and ```cmake``` for the ease of building of future projects.


