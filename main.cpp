#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <chrono>
#include <thread>


#include "buffer.h"
#include "videoreader.h"
#include "videoeditor.h"

using namespace std;



int main()
{

    SBuffer *buf = new SBuffer(30);
    string str = "/home/sharganov/Videos/Webcam/1.webm";
    VideoReader reader(str,buf);
    std::thread q1(&VideoReader::read, reader);


    SBuffer *buf2 = new SBuffer(30);
    VideoReader reader1("/home/sharganov/Videos/Webcam/2.webm", buf2);
    std::thread q(&VideoReader::read, reader1);


    VideoEditor editor(buf, buf2);
    editor.edit();

    q1.join();
    q.join();

    cout << "  Hello World!" << endl;
    return 0;
}

