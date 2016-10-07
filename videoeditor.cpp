#include "videoeditor.h"

VideoEditor::VideoEditor(SBuffer *b1, SBuffer *b2)
    :buf1(b1)
    , buf2(b2)
{
    fps1= 30;
    fps2= 50;
    first = true;
}

void VideoEditor::edit()
{

    int time1et= 1000/fps1;
    int time2et = 1000/fps2;
    int time1 = time1et;
    int time2 = time2et;


    int buf1Size = buf1->size();



    while(true)
    {
        int i,j = 0;

        i=0;
        j=0;

       buf1->lock();
       buf2->lock();

       while(i < buf1Size)
        {

            cv::Mat frame = buf1->getData()[i];
            cv::Mat fr1 = buf2->getData()[i];
            if(frame.empty()) break;
            if(fr1.empty()) break;
            mergeFrames(frame, fr1);

            cv::imshow("Display", frame);
            cv::waitKey(33);
            i++;
       }

        buf2->unlock();
        buf1->unlock();

    }
}

void VideoEditor::mergeFrames(cv::Mat &f1, cv::Mat &f2)
{
    cv::Mat  temp;
    cv::resize(f2,temp,cv::Size(400,240),0,0,cv::INTER_CUBIC);
    temp.copyTo(f1(cv::Rect(0,0,400,240)));
}


