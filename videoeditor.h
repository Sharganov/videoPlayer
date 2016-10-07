#pragma once

#include <vector>
#include <string>
#include <videoreader.h>
#include <boost/thread.hpp>


using namespace std;

class VideoEditor
{
public:
    VideoEditor(SBuffer *b1, SBuffer *b2);

    void edit();

    void mergeFrames(cv::Mat &f1, cv::Mat &f2);

private:
    bool first;

    int fps1;

    int fps2;

    SBuffer *buf1;

    SBuffer *buf2;
};
