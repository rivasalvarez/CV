#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "ReadImage.cpp"
#include "WriteImage.cpp"
using namespace std;

int M,N,Q,I; 
                    //Left eye,Right eye,Nose,Mouth
int Storage[20][8] ={{55,26,50,63,71,45,89,45},
                      {45,31,43,74,68,65,86,57},
                      {49,24,45,62,75,46,91,45},
                      {45,16,43,57,65,28,85,32},
                      {45,34,44,76,65,69,85,30},
                      {47,15,45,52,66,27,85,30},
                      {46,24,43,61,59,43,81,44},
                      {46,28,44,65,67,50,85,50},
                      {37,31,36,67,47,53,73,52},
                      {52,35,50,74,78,64,93,52},
                      {53,24,55,59,68,39,89,38},
                      {52,35,53,68,69,55,87,52},
                      {51,20,54,56,67,33,87,33},
                      {53,32,53,66,71,50,88,49},
                      {54,38,52,73,68,60,88,57},
                      {51,16,54,50,68,26,88,27},
                      {53,29,53,61,71,46,89,44},
                      {52,23,54,58,67,34,88,35},
                      {53,33,55,68,70,51,89,48},
                      {55,46,53,76,69,70,88,67} };

                         // Orignial file, new file
 string filenames[20][2]= {{"S1.1.pgm","s1.1.pgm"},
                           {"S1.2.pgm","s1.2.pgm"},
                           {"S1.3.pgm","s1.3.pgm"},
                           {"S1.4.pgm","s1.4.pgm"},
                           {"S1.5.pgm","s1.5.pgm"},
                           {"S1.6.pgm","s1.6.pgm"},
                           {"S1.7.pgm","s1.7.pgm"},
                           {"S1.8.pgm","s1.8.pgm"},
                           {"S1.9.pgm","s1.9.pgm"},
                           {"S1.10.pgm","s1.10.pgm"},
                           {"S2.1.pgm","s2.1.pgm"},
                           {"S2.2.pgm","s2.2.pgm"},
                           {"S2.3.pgm","s2.3.pgm"},
                           {"S2.4.pgm","s2.4.pgm"},
                           {"S2.5.pgm","s2.5.pgm"},
                           {"S2.6.pgm","s2.6.pgm"},
                           {"S2.7.pgm","s2.7.pgm"},
                           {"S2.8.pgm","s2.8.pgm"},
                           {"S2.9.pgm","s2.9.pgm"},
                           {"S2.10.pgm","s2.10.pgm"}};

extern "C" void solve_system(int, int, float**, float*, float*); 
void affine(int**,int**,float**,float*);

int main(int argc, char* argv[])
{
 int i;
 int m=4, n=4;
 float **a, *x, *b, **A,*B;
 int** img,** newImg;
 B = new float[3];
 A = new float* [3];
 for(i = 0; i<3; i++)
   A[i] = new float[3];
 a = new float* [m+1];
 for(i=0; i<m+1; i++)
   a[i] = new float [n+1];
 x = new float [n+1];
 b = new float [m+1];

    //Loop for every image
    for(I = 0; I < 20; I++){
       ReadImage(filenames[I][0],img,M,N,Q);
       //Set up matrix a for the picture
       a[1][1] = Storage[I][0];  a[1][2] = Storage[I][1];a[1][3] = 1;a[1][4] = 0;
       a[2][1] = Storage[I][2];  a[2][2] = Storage[I][3];a[2][3] = 1;a[2][4] = 0;
       a[3][1] = Storage[I][4];  a[3][2] = Storage[I][5];a[3][3] = 1;a[3][4] = 0;
       a[4][1] = Storage[I][6];  a[4][2] = Storage[I][7];a[4][3] = 1;a[4][4] = 0;

       // set up b
       b[1] = 10; b[2] = 10; b[3] = 24;b[4] = 35; 
       solve_system(m,n,a,x,b);
       // get first three values
       A[1][1] = x[1]; A[1][2] = x[2];
       B[1] = x[3];

       // set up b for second equation
       b[1] = 10; b[2] = 30; b[3] = 20;b[4] = 20; 
       solve_system(m,n,a,x,b);
       // get the remaining three values
       A[2][1] = x[1]; A[2][2] = x[2];
       B[2] = x[3];
   
       // display the caluclated matrix A and B
       cout << filenames[I][0] << endl << endl << "A                        B" << endl;
       cout << A[1][1] << "   " << A[1][2] << "      " << B[1] << endl;
       cout << A[2][1] << "   " << A[2][2] << "      " << B[2] << endl << endl;
       // transform the image
       affine(img,newImg,A,B);
     }
}

void affine(int** img,int** newImg,float** A,float* B){
float x[3];
float b[3];
newImg = new int*[48];
for(int i = 0; i< 48; i++)
newImg[i] = new int[40];

    // for every pixel in the new image reverse map
    for(int i = 0; i < 48; i++){
       for(int j = 0; j < 40; j++){
        // take b to other side of the equal sign
        b[1] = i - B[1];
        b[2] = j - B[2];
        // solve for x
        solve_system(2,2,A,x,b);
        // get the orginal location for the new image
        if(int(x[1]) > 111) x[1] =111;
        newImg[i][j] = img[int(x[1])][int(x[2])];
       }
    }
   // write the image
   WriteImage(filenames[I][1],newImg,40,48,255);
}

