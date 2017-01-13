#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
using namespace cv;

  string cap[15] = {"cap01.bmp", "cap02.bmp", "cap03.bmp", "cap04.bmp", "cap05.bmp" ,"cap06.bmp", "cap07.bmp", "cap08.bmp", "cap09.bmp", "cap10.bmp", "cap11.bmp", "cap12.bmp", "cap13.bmp", "cap14.bmp", "cap15.bmp"};

  string pixel[15] = {"pixel01.txt", "pixel02.txt", "pixel03.txt", "pixel04.txt", "pixel05.txt", "pixel06.txt", "pixel07.txt", "pixel08.txt", "pixel09.txt", "pixel10.txt", "pixel11.txt", "pixel12.txt", "pixel13.txt", "pixel14.txt", "pixel15.txt"};

  string world[15] = {"world01.txt", "world02.txt", "world03.txt", "world04.txt", "world05.txt", "world06.txt", "world07.txt", "world08.txt", "world09.txt", "world10.txt", "world11.txt", "world12.txt", "world13.txt", "world14.txt", "world15.txt"};

  string proj[15] = {"proj01.bmp", "proj02.bmp", "proj03.bmp", "proj04.bmp", "proj05.bmp", "proj06.bmp", "proj07.bmp", "proj08.bmp", "proj09.bmp", "proj10.bmp", "proj11.bmp", "proj12.bmp", "proj13.bmp", "proj14.bmp", "proj15.bmp"};

  vector<Point2f> Read2DPoints(const string& filename);
  vector<Point3f> Read3DPoints(const string& filename);
  void drawCross(int x, int y, Mat& image);

int main(){

    int nPics = 15;
    vector< vector <Point2f> > imagePoints;
    vector< vector <Point3f> > objectPoints;
    Mat image;

    for(int i = 0; i < nPics; i++ ){
       vector<Point2f> inputImagePoints = Read2DPoints(pixel[i]);
       vector<Point3f> inputObjectPoints = Read3DPoints(world[i]);

       imagePoints.push_back(inputImagePoints);
       objectPoints.push_back(inputObjectPoints);
    }

    image = imread(cap[0]);
    Mat cameraMatrix;
    Mat distCoeffs;
    vector<Mat> rvecs;
    vector<Mat> tvecs;
    float avgError = 0;

    calibrateCamera(objectPoints, imagePoints, image.size(), cameraMatrix, distCoeffs, rvecs, tvecs);
    
    cout <<"Camera Matrix:"<<endl<<cameraMatrix<<endl<<endl;
    cout <<"Distance Coefficients:"<<endl<<distCoeffs<<endl<<endl;

    for(int i = 0; i < rvecs.size(); i++){
    cout << "Rotation Vector for "<<i<<endl<<rvecs[i]<<endl<<endl;
    cout << "Translation Vector for "<<i<<endl<<tvecs[i]<<endl<<endl;
    }

    for(int i = 0; i < nPics; i++){
       Mat image = imread(cap[i]);
       vector<Point2f> projPoints;
       float error = 0;

       projectPoints(Mat(objectPoints[i]), rvecs[i], tvecs[i], cameraMatrix, distCoeffs, projPoints);

       for(int j = 0; j < objectPoints[i].size(); j++){
       error += sqrt( pow( (imagePoints[i][j].x - projPoints[j].x),2) + pow( (imagePoints[i][j].y - projPoints[j].y),2));
       drawCross(projPoints[j].x, projPoints[j].y,image);
       }
       avgError += error / objectPoints[i].size();
       imwrite(proj[i],image);
    }

    avgError = avgError / nPics;
    cout << endl <<"Average Error:  "<< avgError << endl;
    return 0;
}

vector<Point2f> Read2DPoints(const string& filename){

   ifstream fin(filename.c_str());

   if(fin == NULL){cout << "Cannot Open File:  " << filename << endl;}

   float x,y;
   vector<Point2f> points;

   fin >> x >> y;
   while(fin.good()){
      points.push_back(Point2f(x,y));
      fin >> x >> y;
   }

return points;
}

vector<Point3f> Read3DPoints(const string& filename){

   ifstream fin(filename.c_str());

   if(fin == NULL){cout << "Cannot Open File:  " << filename << endl;}

   float x,y;
   vector<Point3f> points;

   fin >> x >> y;
   while(fin.good()){
      points.push_back(Point3f(x,y,0));
      fin >> x >> y;
   }

return points;
}

void drawCross(int x, int y, Mat& image){
int len = 5;
Vec3b color;
    for(int i = -len; i < len; i++){
    color = image.at<Vec3b>(Point(x - i,y));
    color[0] = 0;
    color[1] = 0;
    color[2] = 255;
    image.at<Vec3b>(Point(x - i,y)) = color;

    color = image.at<Vec3b>(Point(x,y - i));
    color[0] = 0;
    color[1] = 0;
    color[2] = 255;
    image.at<Vec3b>(Point(x,y - i)) = color;
    }
}
