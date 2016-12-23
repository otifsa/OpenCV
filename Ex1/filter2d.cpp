#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

// take image from web cam 
void cap(){
 	Mat frame;
    VideoCapture cap(0);
   
    if(!cap.isOpened())
      cout<<"No Camera Detected"<<endl;
    else{
        cap >> frame;
        imwrite("img.jpg",frame);
        }
}

// this function apply a filter to image src with a kernel and return the result
Mat fil(Mat src,int kernel_size)
{
    Mat dst,kernel;
	//Inialise the kernel 
    kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);
 
    // Apply filter
    filter2D(src, dst, -1 , kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    return dst;
}
 
int main ( int argc, char** argv )
{
    Mat src,dst3,dst5,dst9,dst11;
    cap();
    // Load an image
    src = imread( "img.jpg" );
    if( !src.data )  { return -1; }
 	// apply a filter with kenel 3*3
    dst3=fil(src,3);
	// apply a filter with kenel 5*5
	dst5=fil(src,5);
	// apply a filter with kenel 9*9
	dst9=fil(src,9);
    // apply a filter with kenel 11*11
	dst11=fil(src,11);
// show the result of deffrents kernels
imshow( "filter2D 3*3 ", dst3 );
imshow( "filter2D 5*5 ", dst5 );
imshow( "filter2D 9*9 ", dst9 );
imshow( "filter2D 11*11 ", dst11 );

//note the result images as diffrents with kernel size 5*5 and 11*11 
//because each pixel of result image calcluate with this kernel 
//the greater size of kernel the information decreased 
    waitKey(0);
    return 0;
}
