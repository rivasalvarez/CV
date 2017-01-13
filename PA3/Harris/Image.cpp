#ifndef IMAGE_CPP
#define IMAGE_CPP
#include "Image.h"

Image::Image(int w, int h){
  width = w;
  height = h;
 
  data = new int*[h];
  for(int i = 0; i < h; i++)
  data[i] = new int[w];
}
///////////////////////////////////////////////////////////////////////
Image::Image(const Image &RHS){
width = RHS.width; height = RHS.height;
   data = new int*[height];
   for(int i = 0; i < height; i++)
     data[i] = new int[width];
 

   for(int i = 0; i < height; i++){
     for(int j = 0; j < width; j++){
     data[i][j] = RHS.data[i][j];
     }
   }
}

void Image::readImage(string fname){
 int i, j,M,N,Q;
 unsigned char *image;
 char header [100], *ptr;
 ifstream ifp(fname.c_str());

 if (!ifp) {
   cout << "Can't read image: " << fname << endl;
   exit(1);
 }


 ifp.getline(header,100,'\n');
 if ( (header[0]!=80) ||    /* 'P' */
      (header[1]!=53) ) {   /* '5' */
      cout << "Image " << fname << " is not PGM" << endl;
      exit(1);
 }

 ifp.getline(header,100,'\n');
 while(header[0]=='#')
   ifp.getline(header,100,'\n');

 M=strtol(header,&ptr,0);
 N=atoi(ptr);

 ifp.getline(header,100,'\n');

 Q=strtol(header,&ptr,0);
 image = (unsigned char *) new unsigned char [M*N];

 ifp.read( reinterpret_cast<char *>(image), (M*N)*sizeof(unsigned char));

 if (ifp.fail()) {
   cout << "Image " << fname << " has wrong size" << endl;
   exit(1);
 }

 ifp.close();

 //
 // Convert the unsigned characters to integers
 //
 for(i=0; i<N; i++)
   for(j=0; j<M; j++)
     (data)[i][j]=(int)image[i*M+j];

}
//////////////////////////////////////////////////////////////////////   
void Image::writeImage(string fname){

 int i, j,M=width, N = height, Q = 255;
 unsigned char *cimage;
 ofstream ofp(fname.c_str());
 cimage = (unsigned char *) new unsigned char [M*N];

 // convert the integer values to unsigned char

 for(i=0; i<N; i++)
   for(j=0; j<M; j++)
     cimage[i*M+j]=(unsigned char)data[i][j];


 if (!ofp) {
   cout << "Can't open file: " << fname << endl;
   exit(1);
 }

 ofp << "P5" << endl;
 ofp << M << " " << N << endl;
 ofp << Q << endl;

 ofp.write( reinterpret_cast<char *>(cimage), (M*N)*sizeof(unsigned char));

 if (ofp.fail()) {
   cout << "Can't write image " << fname << endl;
   exit(0);
 }

 ofp.close();
}
/////////////////////////////////////////////////////////////////////// 
Image Image::verMask(float* mask,int mSize,const Image& RHS){
int i,j,z,a,b;
float val;
Image temp(width,height);

   for(a = 0; a < width; a++){
      for(i = 0; i < height; i++){
         for(j = 0, val = 0,z = -(mSize/2); j < mSize;j++,z++){
            if((i + z) < height && (i + z >= 0)){
              val += mask[j] * RHS.data[i+z][a];
            }
         }
    temp.data[i][a] = val;
       }
   }
return temp;
}

Image Image::horMask(float* mask,int mSize, const Image& RHS){
	Image temp(width,height);
	int i,j,z,a,b;
	float val;

   for(a = 0; a < height; a++){
      for(i = 0; i < width; i++){
         for(j = 0, val = 0,z = -(mSize/2); j < mSize;j++,z++){
            if((i + z) < width && (i + z >= 0)){
              val += mask[j] * RHS.data[a][i+z];
            }
         }
     temp.data[a][i] = val;
       }
   }

	return temp;
}
void Image::normalize(){
 int min, max = data[0][0];
 min = max;
   for(int i = 0; i < height; i++){
     for(int j = 0; j < width; j++){
        if(data[i][j] < min){min = data[i][j];}
     }
   }

   for(int i = 0; i < height; i++){
     for(int j = 0; j < width; j++){
        data[i][j] -= min;
     }
   }

   for(int i = 0; i < height; i++){
     for(int j = 0; j < width; j++){
        data[i][j] *=-(255.f / min) ;
     }
   }
}

Image Image::operator-(const Image&RHS){
Image temp(width,height);
    for(int i = 0;i < height; i++){
       for(int j = 0;j < width; j++){
         temp.data[i][j] = data[i][j] - RHS.data[i][j];
       }
    }
return temp;
}

Image Image::operator+(const Image&RHS){
Image temp(width,height);
    for(int i = 0;i < height; i++){
       for(int j = 0;j < width; j++){
         temp.data[i][j] = data[i][j] + RHS.data[i][j];
       }
    }
return temp;
}
  
Image Image::operator*(const Image&RHS){
Image temp(width,height);
    for(int i = 0;i < height; i++){
       for(int j = 0;j < width; j++){
         temp.data[i][j] = data[i][j] * RHS.data[i][j];
       }
    }
return temp;
}

void Image::thresh(float th){
   for(int i = 0;i < height;i++){
       for(int j = 0;j < width; j++){
         if(data[i][j] < th){data[i][j] = 0;}
       }
   }
}
   
Image Image::nonMax(int window_size){

	Image ret(*this);
	int i, j, start, end;
	float max_val;
	bool keep;


	for (int y = 0; y < height; y++)
	for (int x = 0; x < width; x++) {
		max_val = 0;
		start = -(window_size / 2);
		end = 1 - start;
		for (j = start; j < end; j++)
		for (i = start; i < end; i++) {
			if ( (j+y >= 0) && (j+y < height) && (x+i > 0) && (x+i < width) &&(data[j+y][i+x] > max_val) ) {
				max_val = data[j+y][i+x];
				keep = (i==0 && j==0);
			}
		}
		if (!keep && (j+y >= 0) && (j+y < height) && (x+i > 0) && (x+i < width) ) {
			data[y][x] = 0.f;
		}
	}
	return ret;
}

Image Image::overlay(const Image &RHS, int val, Mat& mat){
Vec3b red;

red[0] = 0; red[1] = 0; red[2] = 255;

    for(int i = 0;i < height;i++){
       for(int j = 0;j< width; j++){
          if(RHS.data[i][j] != 0){
             data[i][j] = val; 
             mat.at<Vec3b>(Point(j,i)) = red;
             for(int z = 1 ; z < 3; z++){
                if(i+z < height){ data[i+z][j] = val; mat.at<Vec3b>(Point(j,i+z)) = red;}
                if(i-z >= 0){ data[i-z][j] = val; mat.at<Vec3b>(Point(j,i-z)) = red;}
                if(j+z < width){ data[i][j+z] = val; mat.at<Vec3b>(Point(j+z,i)) = red;}
                if(j-z >= 0){ data[i][j-z] = val; mat.at<Vec3b>(Point(j-z,i)) = red;}
             }
          }
       }
    }
}

void Image::convert(const Image &RHS, Mat& mat){
Vec3b color;

    for(int i = 0; i < height; i++){
    	for(int j = 0; j < width; j++){
	    color[0] = color[1] = color[2] = RHS.data[i][j];
	    mat.at<Vec3b>(Point(j,i)) = color;
	}
    }

}

void Image::getData(int**& RHS){
   for(int i = 0; i< height; i++){
     for(int j = 0; j < width; j++){
      RHS[i][j] = data[i][j];
     } 
   }
}

void Image::setData(int** RHS){
   for(int i = 0; i< height; i++){
     for(int j = 0; j < width; j++){
      data[i][j] = RHS[i][j];
     }
   }
}
#endif
