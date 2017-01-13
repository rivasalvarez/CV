#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;
#include <string.h>
#include "Image.cpp"
#include "Gauss_masks.cpp"
#include "DGauss_masks.cpp"

float SIGMA = 1.5, LAMBDA = 0.7, ALPHA = 0.06;
int MASK_S = SIGMA * 5;
string fNames[3] = {"Test1.pgm","Test2.pgm","Test3.pgm"};
string bmpNames[3] = {"Test1.bmp","Test2.bmp","Test3.bmp"};
int Heights[3] = {257,571,571};
int Widths[3] = {256,618,602};
int Over[3] = {125,255,255};

int main(){
float mask[MASK_S], dmask[int(SIGMA*LAMBDA*5)];
Gauss(SIGMA,MASK_S,mask);
DGauss(SIGMA*LAMBDA,SIGMA*LAMBDA*5,dmask);

for(int z = 0; z < 3; z++){
int w = Widths[z], h = Heights[z];

Image image(w,h),Ix(w,h),Iy(w,h),Ixx(w,h),Iyy(w,h),Ixy(w,h),Raw(w,h);
image.readImage(fNames[z]);

   Ix = image.horMask(dmask, SIGMA*LAMBDA*5,image);
   Iy = image.verMask(dmask,SIGMA*LAMBDA*5,image);

   Ixx = (Ix * Ix);
   Ixx =Ixx.horMask(mask,MASK_S,Ixx);
   Ixx =Ixx.verMask(mask,MASK_S,Ixx);

   Iyy = (Iy * Iy);
   Iyy = Iyy.horMask(mask,MASK_S,Iyy);
   Iyy = Iyy.verMask(mask,MASK_S,Iyy);

   Ixy = (Ix * Iy);
   Ixy = Ixy.horMask(mask,MASK_S,Ixy);
   Ixy = Ixy.verMask(mask,MASK_S,Ixy);

   float det,trace, cornerMax = -(3.402823e+38f);
   for(int i = 0;i < h; i++){
      for(int j = 0;j < w; j++){
       det = (Ixx.data[i][j] * Iyy.data[i][j]) - (Ixy.data[i][j] * Ixy.data[i][j]);
       trace = Ixx.data[i][j] + Iyy.data[i][j];
       Raw.data[i][j] = det - (ALPHA * trace * trace);
       if(Raw.data[i][j] > cornerMax){cornerMax = Raw.data[i][j];}
      }

   }
   cout << cornerMax<< endl;

   Mat bmp(Raw.height,Raw.width, CV_8UC3, Scalar(0,0,255));

   ostringstream sstring;
   sstring << fNames[z] <<"_Raw";
   string temp = sstring.str();

   Raw.writeImage(temp);
   sstring.str("");
   Raw.thresh((cornerMax * .01));

   sstring << fNames[z] << "_thresh";
   temp = sstring.str();
   Raw.writeImage(temp);
   sstring.str("");
   Raw.nonMax(3);
    
   sstring << fNames[z] << "_loc-max";
   temp = sstring.str();
   Raw.writeImage(temp);
   sstring.str("");

   sstring << fNames[z] << "_final";
   temp = sstring.str();
   Image Final(image);
   Final.convert(Final,bmp);
   Final.overlay(Raw,Over[z],bmp);
   Final.writeImage(temp);
   imwrite(bmpNames[z],bmp);
}
return 0;
}
