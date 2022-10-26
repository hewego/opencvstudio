#pragma once

#include "../ExternalControl/Opencv34/include/opencv2/core.hpp"
#include "../ExternalControl/Opencv34/include/opencv2/imgcodecs.hpp"
#include "../ExternalControl/Opencv34/include/opencv2/highgui.hpp"
#include "../ExternalControl/Opencv34/include/opencv2/imgproc.hpp"

using namespace cv;

#if _DEBUG
#pragma comment(lib, "../ExternalControl/Opencv34/opencv_world3416d.lib")
#else
#pragma comment(lib, "../ExternalControl/Opencv34/opencv_world3416.lib")
#endif