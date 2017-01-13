#ifndef IMAGE_H
#define IMAGE_H

class Image{
   public:
   Image(int w, int h);
   Image(const Image&);
   void readImage(string);
   void writeImage(string);

   Image overlay(const Image&,int);
   Image verMask(float* mask, int mSize, const Image&);
   Image horMask(float* mask, int mSize, const Image&);
   Image nonMax(int size);
   void thresh(float th);
   void normalize();
   void mult(const Image&);
   void getData(int**&);
   void setData(int**);

   Image operator+(const Image&);
   Image operator-(const Image&);
   Image operator*(const Image&);

   int** data;
   int height, width;
};

#endif
