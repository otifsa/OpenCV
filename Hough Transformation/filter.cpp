#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

Point2f intersection(Point2f o1, Point2f p1, Point2f o2, Point2f p2)
{
    Point2f x = o2 - o1;
    Point2f d1 = p1 - o1;
    Point2f d2 = p2 - o2;
	Point2f r;
    float cross = d1.x*d2.y-d1.y*d2.x;
    if (abs(cross) < 1e-8)
        return Point2f(0,0);

    double t1 = (x.x * d2.y - x.y * d2.x)/cross;
    r = o1 + d1 * t1;
    return r;
}


int main(){
      Mat src,dst;
	 int compteur=0;
      src=imread("check.jpg");
	  imshow("image",src);
	  Canny( src, dst, 50, 150, 3);
	  imshow("edge",dst);
	vector<Vec2f> lines;
    HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 );

for( int i = 0; i < lines.size(); i++ )
    {   
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( src, pt1, pt2, Scalar(0,0,255), 0, 0);
    }

    imshow("lines", src);

for(int i=0;i<lines.size();i++){
		float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
		Point2f r;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
		for(int j=i+1;j<lines.size();j++)
		  { float rho1 = lines[j][0], theta1 = lines[j][1];
		    Point pt11, pt21;
		    double a1 = cos(theta1), b1 = sin(theta1);
		    double x01 = a1*rho1, y01 = b1*rho1;
		    pt11.x = cvRound(x01 + 1000*(-b1));
		    pt11.y = cvRound(y01 + 1000*(a1));
		    pt21.x = cvRound(x01 - 1000*(-b1));
		    pt21.y = cvRound(y01 - 1000*(a1));
        r=intersection(pt1,pt2,pt11,pt21);
		if(r.x!=0 &&r.y!=0)
		circle(src,r,10, (0,255,255), -1);
		compteur++;
		  }
}
imshow("point", src);
cout<<"nomber of intersect point is: "<<compteur<<endl;
	
waitKey(0);

return 0;
			}
