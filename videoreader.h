#pragma once

#include "buffer.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <string>
#include <vector>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <thread>


class VideoReader
{

public:

    VideoReader(string file, SBuffer *buffer);

    ~VideoReader();

    void read();

    void test();

private:

    string mFile;
    cv::VideoCapture vc;
    bool first;
    SBuffer *mBuffer;
};

