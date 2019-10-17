### Overview
This is a repo based on GoSDK4 / GoSDK5 for data Acquisition of Gocator 3X00 series sensor.

### Dependencies
The original package has been tested with the following dependencies:
* Ubuntu 14.04
* CMake + gcc
* [ROS Indigo](http://wiki.ros.org/indigo/Installation/Ubuntu)
* [Point Cloud Library v1.7](http://www.pointclouds.org/) (shipped with ROS Indigo)
* GoSDK library Version 4.2(propietary library from manufacturer LMI Technologies)

This package has also been tested with the following dependencies:
* Ubuntu 18.04
* CMake + gcc
* [ROS Melodic](http://wiki.ros.org/melodic/Installation/Ubuntu)
* [Point Cloud Library v1.8](http://www.pointclouds.org/) (seems shipped with Ubuntu18.04)
* GoSDK library Version 5.2(propietary library from manufacturer LMI Technologies)


### Build the GoSdk
#### extract source and put it to path `~`.
for GoSdk5.x:
extract `14400-5.2.19.71_SOFTWARE_GO_SDK.zip` and copy folder `GO_SDK`, which is inside the extracted folder to path `~/`
for GoSdk4.x:
extract `14400-4.2.5.17_SOFTWARE_GO_SDK.zip` and copy folder `GO_SDK`, which is inside the extracted folder to path `~/`

#### Switch from different build types.
To switch Build Type between "Debug" and "Release", you need to adjust three files in total.
```
/home/ziqi/GO_SDK/Platform/kApi/kApi-Linux_X64.mk
/GO_SDK/Gocator/GoSdk/GoSdk-Linux_X64.mk
/GO_SDK/Gocator/GoSdk/GoSdkExample-Linux_X64.mk
```

find following block in these three files, and change it to "Debug" or "Release", then the generated libs with be generated and put to the corresponding folders.
```
ifndef config
	config := Release
endif
```
Note: the CMakeLists.txt is already adjusted so that it can link to LIBS in different folders according to different build types in CMakeLists.txt.
