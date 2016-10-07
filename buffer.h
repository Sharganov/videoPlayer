#pragma once

#include <vector>
#include <iostream>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>

using namespace std;

template<class T>
class SArray
{

public:

    SArray(int size)
        : mSize(size)
    {

        mutex =  new boost::interprocess::interprocess_mutex();
        mData = new T[mSize];
        wPose = 0;
        rPose = 0;
    }

    ~SArray() { delete [] mData; }


    T & operator [](int i){

        return mData[i];
    }

    unsigned size(){return mSize; }

    T  * data() {return mData;}

    boost::interprocess::interprocess_mutex *mutex;

private:

    T *mData;
    int mSize;
    int wPose;
    int rPose;

};


class Buffer
{
private:
    int mSize;

    int index_of_read;

    int index_of_write;

    SArray<cv::Mat> *data1;

    SArray<cv::Mat> *data2;

    // if true isReady to write in data1, ready to read from data2
    bool first;

    boost::interprocess::interprocess_semaphore* Free;

    boost::interprocess::interprocess_semaphore* Used;

public:

    Buffer(int size);

    ~Buffer();

    cv::Mat *write();

    cv::Mat* read();

    unsigned size();

    //can be locked for reading (1) or writing (0)
    void lock(int mode);

    void unlock(int mode);
};

class NBuffer
{

public:

    NBuffer(unsigned int size);

    void write(cv::Mat frame);

    cv::Mat read();

    unsigned size();

private:

    SArray<cv::Mat> *data1;

    SArray<cv::Mat> *data2;

    unsigned wPose;

    unsigned rPose;

    unsigned mSize;

    bool first;
};



class SBuffer
{

public:

    SBuffer(unsigned int);

    cv::Mat read();

    void write(cv::Mat);

    cv::Mat *getData();

    void lock();

    void unlock();

    unsigned size();

private:

    cv::Mat *data;

    boost::interprocess::interprocess_mutex mutex;

    unsigned mSize;
};
