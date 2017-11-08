/*
 * main.cpp
 *
 *  Created on: May 15, 2017
 *      Author: rasp
 */

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>

using namespace cv;
using namespace std;
//using namespace boost;
using namespace boost::posix_time;

int findCamera();
void loopCamera();
VideoCapture stream1, stream2;
thread t1, t2;

class Video_Capture{
public:
    Video_Capture();
    ~Video_Capture();
    bool bFrontCamera, bDownCamera;
    void start_thread();
};


Video_Capture::Video_Capture()
{
    bFrontCamera = false;
    bDownCamera = false;
}

Video_Capture::~Video_Capture()
{
    t1.join();
}

int findCamera(int max)
{
    VideoCapture stream;   //0 is the id of video device.0 if you have only one camera.

    int maxTested = max;
    int i;
    for (i = maxTested; i >= 0; i--){
        VideoCapture stream(i);
        bool res = (stream.isOpened());
        cout << res <<endl;
        if (res)
        {
            cout <<"Open camera " << i <<endl;
            return i;

        }
        else
        {
            stream.release();
            cout <<"Camera " << i << " is released" <<endl;
        }
    }
    return -1;
}
void loopCamera()
{
    int frameno = 0;
    //uncondition loop
    while (true)
    {
        ptime timestamp1 = microsec_clock::local_time();
        Mat cameraFrame1, cameraFrame2;
        stream1.read(cameraFrame1);
        stream2.read(cameraFrame2);
        imshow("cam", cameraFrame1);
        imshow("cam2", cameraFrame2);
        cout << "Frame" << ++frameno << " @ " << timestamp1 << endl;
        if (waitKey(30) >= 0)
            break;
    }
}

void loopCamera2()
{
    int frameno = 0;
    //uncondition loop
    while (true)
    {
        ptime timestamp1 = microsec_clock::local_time();
        Mat cameraFrame;
        stream2.read(cameraFrame);
        imshow("cam2", cameraFrame);
        cout << "Frame" << ++frameno << " @ " << timestamp1 << endl;
        if (waitKey(30) >= 0)
            break;
    }
}

void Video_Capture::start_thread()
{
    int cam = findCamera(5);
    if(cam == -1)
    {
        cout << "cannot open camera";
        //return 0;
    }
    stream1  = VideoCapture(cam);
    int cam2 = findCamera(cam-1);
    stream2  = VideoCapture(cam2);
    t1 = thread(&loopCamera);
}

int main()
{

    Video_Capture vc;
    vc.start_thread();
    for (int i = 0; i<=10;i++)
    {
        cout << "main : " << i <<endl;
        sleep(1);
    }

    return 0;
}

