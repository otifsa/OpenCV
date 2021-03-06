#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;
int det(double a,double b,double c,double d)
{return (a*d-b*c);}

Point2f intersection(Point2f o1, Point2f p1, Point2f o2, Point2f p2)
{
    Point2f R;
    float cross=det(det(o1.x,1,p1.x,1),det(o1.y,1,p1.y,1),det(o2.x,1,p2.x,1),det(o2.y,1,p2.y,1));
    if (abs(cross)==0)
        return Point2f(0,0);

  R.x=det(det(o1.x,o1.y,p1.x,p1.y),det(o1.x,1,p1.x,1),det(o2.x,o2.y,p2.x,p2.y),det(o2.x,1,p2.x,1) )/cross;   
  R.y=det(det(o1.x,o1.y,p1.x,p1.y),det(o1.y,1,p1.y,1),det(o2.x,o2.y,p2.x,p2.y),det(o2.y,1,p2.y,1) )/cross; 

 return R;}




int main(){
      Mat src,dst;
	 int compteur=0;
      src=imread("check.pgm");
	  imshow("image",src);
	  Canny( src, dst, 20, 50, 3);
	  imshow("edge",dst);
	vector<Vec2f> lines;
    HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );

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
		circle(src,r,3, (0,255,255), -1);
		compteur++;
		  }
}
imshow("point", src);
cout<<"nomber of intersect point is: "<<compteur<<endl;
	
waitKey(0);

return 0;
			}
