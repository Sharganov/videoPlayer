#include "videoreader.h"

VideoReader::VideoReader(string file, SBuffer *buffer)
    : mFile(file)
    , mBuffer(buffer)
{
    first = true;
    vc.open(file);
}

VideoReader::~VideoReader()
{
    //delete mBuffer;
}

void VideoReader::read()
{
    int frameCount = vc.get(CV_CAP_PROP_FRAME_COUNT);

    while(frameCount > 0)
    {
       mBuffer->lock();
        for(int i = 0; i < mBuffer->size(); i++)
        {
            vc.read(mBuffer->getData()[i]);
            frameCount--;
            if(frameCount == -1) break;
        }
        mBuffer->unlock();
    }
   }
