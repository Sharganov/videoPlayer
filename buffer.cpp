
#include "buffer.h"

Buffer::Buffer(int size)
{
    mSize = size;
    index_of_read = 0;
    index_of_write = 0;
    data1 = new SArray<cv::Mat>(size/2);
    data2 = new SArray<cv::Mat>(size/2);

    first  =true;

    Free = new boost::interprocess::interprocess_semaphore (size);
    Used = new boost::interprocess::interprocess_semaphore (0);
}

Buffer::~Buffer()
{
    delete data1;
    delete Free;
    delete Used;
}

cv::Mat *Buffer::write()
{
    //Free->wait();
    cv::Mat *data = (first) ? (data1->data()) : (data2->data());
    first = !first;
    return data;
}


cv::Mat* Buffer::read()
{
    //Used->wait();
    //return &frameArray[index_of_read];
    return (first) ? (data2->data()) : (data1->data());
}

unsigned Buffer::size()
{
    return mSize;
}

void Buffer::lock(int mode){

    // want to write in buffer
    if(mode == 0)
    {
      if(first) {
          data1->mutex->lock();
      }
      else
      {
          data2->mutex->lock();
      }
    }
    else
    {
      if(first) {
          data2->mutex->lock();
      }
      else
      {
          data1->mutex->lock();
      }
    }
}

void Buffer::unlock(int mode)
{
    if(mode == 0)
    {
      if(!first) {
          data1->mutex->unlock();
      }
      else
      {
          data2->mutex->unlock();
      }
    }
    else
    {
      if(!first) {
          data2->mutex->unlock();
      }
      else
      {
          data1->mutex->unlock();
      }
    }
}


NBuffer::NBuffer(unsigned int size)
    :mSize(size)
{
    data1 = new SArray<cv::Mat>(mSize/2);
    data2 = new SArray<cv::Mat>(mSize/2);
    wPose = 0;
    rPose = 0;
    //array for writting
    first = true;
}

void NBuffer::write(cv::Mat frame){

    if(first)
    {
        if(wPose == 0) data1->mutex->lock();
        data1->data()[wPose] = frame;
        wPose++;
        if(wPose == mSize/2)
        {
            wPose = 0;
            first = false;
            data1->mutex->unlock();
        }
    }
    else
    {
        if(wPose == 0) data2->mutex->lock();
        data2->data()[wPose] = frame;
        wPose++;
        if(wPose == mSize/2)
        {
            wPose = 0;
            first = true;
            data2->mutex->unlock();
        }
    }
}

cv::Mat NBuffer::read()
{
    if(first)
    {
        if(rPose == 0) data2->mutex->lock();
        cv::Mat ans = data2->data()[rPose];
        rPose++;
        if(rPose == mSize/2)
        {
            rPose = 0;
            first = false;
            data2->mutex->unlock();
        }
        return ans;
    }
    else
    {
        if(rPose == 0) data1->mutex->lock();
        cv::Mat ans = data1->data()[rPose];
        rPose++;
        if(rPose == mSize/2)
        {
            rPose = 0;
            first = true;
            data1->mutex->unlock();
        }
        return ans;
    }
}

unsigned NBuffer::size()
{
    return mSize;
}

SBuffer::SBuffer(unsigned size)
    : mSize(size)
{
    data = new cv::Mat[size];
}


cv::Mat * SBuffer::getData()
{
    return data;
}
void SBuffer::lock()
{
    mutex.lock();
   // cout <<3;
}

void SBuffer::unlock()
{
    mutex.unlock();
}

unsigned SBuffer::size()
{
    return mSize;
}
