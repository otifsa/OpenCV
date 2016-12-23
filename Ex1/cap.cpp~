#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;




int main(int argc, char* argv[])
{
   
    Mat frame;
    VideoCapture cap(0);
   
    if(!cap.isOpened())
      cout<<"No Camera Detected"<<endl;
    else{
        cv::namedWindow("Webcam Video");
        cap >> frame;
        imwrite("img.jpg",frame);
        }
    return 0;
}
