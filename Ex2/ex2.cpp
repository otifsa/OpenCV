#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

main()
{
	Mat src,dst,dst1,dst2;
	//load image from computer
	src = imread( "img.jpg");
	//inialise data for kernel
	float data[9] = {1,2,1,2,4,2,1,2,1};
	float data1[3]={1,2,1};
	float data2[3]={1,2,1};
	//inialise the kernel with data array
	Mat kernel =Mat(3,3, CV_32F,data)/(float)16;
	Mat kernel1 =Mat(1,3, CV_32F,data1)/(float)4;
	Mat kernel2 =Mat(3,1, CV_32F,data2)/(float)4;
	// apply the filter 
	filter2D(src, dst, -1 , kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
	// apply separable filter
	filter2D(src, dst1, -1 , kernel1, Point( -1, -1 ), 0, BORDER_DEFAULT );
	filter2D(dst1, dst2, -1 , kernel2, Point( -1, -1 ), 0, BORDER_DEFAULT );
	//show result of tow methods (normal filter and separable filter)
    	imshow( "src", src );
	imshow( "filter", dst);
	imshow( "filter sep", dst2);
	
	
waitKey(0);
}
