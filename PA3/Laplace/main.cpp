#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;
#include <sstream>
#include "Image.cpp"
#include "Gauss_masks.cpp"
#include "DGauss_masks.cpp"
#include "Harris.cpp"
int dLevels = 17, gLevels = 18, Hthresh  = 1500;
float SIGMA  = 1.5f;
float K  = 1.2f;
int Widths[2] = {850,800};
int Heights[2] = {680,640};
Image harrisLaplace(Image &orig, Mat&, string fName, float sigma, float k);
void drawCircle(Image &tar, Mat&,  int x0, int y0, int r);

int main(int argv,char* argc[]){
int i, h = Heights[0] , w = Widths[0];
char c = argc[1][0];
i = int(c) - 48;

        if(i >= 4){h = Heights[1]; w = Widths[1];};
    
	    Image input(w,h), HL(w,h);
        Mat bmp(h,w, CV_8UC3, Scalar(0,0,255));
        ostringstream srtream;
        srtream <<"img"<<i<<".pgm";
        string filename = srtream.str();

	    input.readImage(filename);
        input.convert(input,bmp);
        HL = harrisLaplace(input, bmp, filename, SIGMA, K);
        input.overlay2(HL,bmp,255);
       
        ostringstream sstream;
        sstream << filename << "_final";
        string finame = sstream.str();
        input.writeImage(finame);
        imwrite("Test.bmp",bmp);
	return 0;
}

Image harrisLaplace(Image& orig, Mat& matr, string fName, float sigma, float k)
{
    int h = orig.height, w = orig.width;
	Image gauss_ss[gLevels];
	Image dog_ss[dLevels];
	Image harris_ss[dLevels];
	float* mask;
	int i, j;
	Image scale(w,h);
	Image Final(w,h);

    for(int i= 0; i < gLevels;i++){
    gauss_ss[i].allocate(w,h);
    if(i != gLevels - 1){
    dog_ss[i].allocate(w,h);
    harris_ss[i].allocate(w,h);
    }
    }

	for(i = 0; i < gLevels; i++) {
		cout << "Gaussian Level: " << i << endl;
        mask = new float[int(sigma * pow(k, i) * 5)];
		Gauss(sigma * pow(k, i), sigma * pow(k, i) * 5,mask);
		gauss_ss[i] = orig.horMask(mask,sigma * pow(k, i) * 5,orig);
		gauss_ss[i] = gauss_ss[i].verMask(mask,sigma * pow(k, i) * 5,gauss_ss[i]);
	}

	for(i = 0; i < dLevels; i++) {
		cout << "DoG Level: " << i << endl;
		dog_ss[i] = gauss_ss[i] - gauss_ss[i+1];
	}

	for(i = 0; i < dLevels; i++) {
		cout << "Harris Interest Level: " << i << endl;
		harris_ss[i] = harrisDetector(orig, 0.06f, 0.7f, sigma * pow(k, i));

        ostringstream sstream;
        sstream << fName << "_har-guass" << i;
        string finame = sstream.str();
      
		harris_ss[i].writeImage(finame);
        
		harris_ss[i] = harris_ss[i].nonMax(3);
		harris_ss[i] = harris_ss[i].nonMin(3);
		harris_ss[i].thresh(Hthresh);

        ostringstream srtream;
        srtream << fName << "_NonMax" << i;
        string f1name = srtream.str();

		harris_ss[i].writeImage(f1name);
	}

	cout << "Suppressing" << endl;
	float max, min;
	int maxx, maxy, maxz, minx, miny, minz;
	int cx, cy, cz;
	for(int level = 0; level < dLevels; level++){
	   for(int j = 0; j < h; j++){
	      for(int i = 0; i < w; i++){
		  max = -100000000000;
		  min = 1000000000000;
		    for(int z = -1; z < 2; z++){
		       for(int y = -1; y < 2; y++){
		          for(int x = -1; x < 2; x++){
			      cx = i + x;
			      cy = j + y;
			      cz = level + z;
			        if(cx < 0 || cx >= w ||cy < 0 || cy >= h || cz < 0 || cz >= dLevels) {
				    continue;
			        }
			        if( dog_ss[cz].data[cy][cx] < min ) {
				    min = dog_ss[cz].data[cy][cx];
				    minx = cx;
				    miny = cy;
				    minz = cz;
			        } 
                    else if( dog_ss[cz].data[cy][cx] > max ) {
				    max = dog_ss[cz].data[cy][cx];
				    maxx = cx;
				    maxy = cy;
				    maxz = cz;
			        }
		    }}}
		if((maxx == i && maxy == j && maxz == level) || (minx == i && miny == j && minz == level) ) {
	       if(Final.data[j][i] < harris_ss[level].data[j][i] && dog_ss[level].data[j][i] < 118.f || dog_ss[level].data[j][i] > 138.f) {
		   Final.data[j][i] = harris_ss[level].data[j][i];
		   scale.data[j][i] = level;
		   }
	    }
	}}}
	float cirSigma;
	Image Copy(Final);
    int count = 0;
	for(int x = 0; x < h; x++){
	   for(int y = 0; y < w; y++)
	   {
		  if(Copy.data[x][y] != 0.f) {
           count++;
		   cirSigma = sigma * pow(k, scale.data[x][y]);
	       Final.drawCross(matr,y, x, 255); 
           drawCircle(Final,matr,y,x,2 * cirSigma);
		  }
	   }
    }
    cout << "Number of Points: " << count << endl;
    ostringstream srtream;
    srtream << fName << "_har-lac";
    string f1name = srtream.str();
	Final.writeImage(f1name);
	return Final;
}

void drawCircle(Image &tar, Mat& mat, int x0, int y0, int r){
int x, y;
Vec3b red;
red[0] =0; red[1] = 0; red[2] = 255;

	for(int i = -r; i <= r; i++)
	{
		x = x0 + i;
		if(x >= 0 && x < tar.width)
		{
			y = int( sqrt(r*r - (x-x0)*(x-x0) ) + y0 );
			if(y >= 0 && y < tar.height){
				tar.data[y][x] = 255.f;
                mat.at<Vec3b>(Point(x,y)) = red;
            }
			y = int( -sqrt(r*r - (x-x0)*(x-x0) ) + y0 );
			if(y >= 0 && y < tar.height){
				tar.data[y][x] = 255.f;
                mat.at<Vec3b>(Point(x,y)) = red;
            }
		}
		y = y0 + i;
		if(y >= 0 && y < tar.height){
			x = int( sqrt(r*r - (y-y0)*(y-y0) ) + x0 );
			if (x >= 0 && x < tar.width){
				tar.data[y][x] = 255.f;
                mat.at<Vec3b>(Point(x,y)) = red;
            }
			x = int( -sqrt(r*r - (y-y0)*(y-y0) ) + x0 );
			if (x >= 0 && x < tar.height){
				tar.data[y][x] = 255.f;
                mat.at<Vec3b>(Point(x,y)) = red;
            }
		}
	}  
}
