//Marco Rivas

#include <iostream>
#include <string.h>
#include <sstream>
#include "ReadImage.cpp"
#include "WriteImage.cpp"
#include "Gauss_masks.cpp"
#include "myFuncts.cpp"
using namespace std;

void GuassianSmoothing();
void EdgeDetection();
void GaussianPyramid();

int main(){

  char c = 't';
  for(int i = 0; i < 25; i++)
    cout << endl;
  cout << "Computer Vision PA1" << endl << "created by: Marco Rivas" << endl << endl;

  do{
   cout << "Main Menu" << endl << endl;
   cout << "<1> Gaussian Smoothing" << endl
        << "<2> Edge Detection" << endl
        << "<3> Gaussion Pyramid" << endl <<
           "<q> To Quit" << endl << endl << endl
        << "Enter Selection: ";
   cin >> c;

     switch(c){
        case 'q':
        case 'Q':
          break;
        case '1':
          GuassianSmoothing();
          break;
        case '2':
          EdgeDetection();
          break;
        case '3':
          GaussianPyramid();
          break;

        default:
          break;
     }

  for(int i = 0; i < 25; i++)
    cout << endl;
   } while(c != 'q');

return 0;
}

void GuassianSmoothing(){
int sigArray[3] = {1,5,11};
int sigma = 1;
float* mask;
float* rect = new float[128];
int** image;
char c = 'r';
int M,N,Q;
   readRect(rect);
   ReadImage("lenna.pgm",image,M,N,Q);

      do{
      cout << "Gaussian Smoothing Main Menu" << endl << endl << endl
           << "<a>" << endl << "<b>" << endl << "<c>" << endl << "<d>" << endl << "<q> To return to Main Menu" << endl
           << "Enter Selection: ";
      cin >> c;
       
         switch(c){

           case 'a':{
                      for(int i = 0; i < 3; i++){
                          sigma = sigArray[i];
                          mask = new float[5 * sigma];
                          Gauss (sigma,(sigma * 5), mask);
                          float* rect21 = new float[128];
                          rowConv(rect,mask,rect21, 128,(sigma * 5));
                          
                          ostringstream sstream;
                          sstream << "Rect_128_Sigma" << sigma << ".txt";
                          string fname = sstream.str();
                          writeRect(rect21, fname);
                          delete mask; delete rect21;
                       }
             break;
           }

           case 'b':{
               sigma = 5;
               int size = sigma * 5;
               mask = new float[size];
               Gauss (sigma,size, mask);
               float* rectA = new float[128];
               float* rectB = new float[128];
               float* rectC = new float[128];
               rowConv(rect,mask,rectA,128,size);
               rowConv(rectA,mask,rectB,128,size);
               writeRect(rectB, "Rect_128_I1.txt");
               float* newMask;
               maskConv(mask,newMask, size);
               rowConv(rect,newMask,rectC,128,size);
               writeRect(rectC, "Rect_128_I2.txt");
               delete mask; delete rectA; delete rectB; delete rectC; delete newMask;
             break;
           }
  
            case 'c':{
                      for(int i = 0; i < 3; i++){
                         sigma = sigArray[i];
                         int** newImg;
                         float** mask2D;
                         Gauss2 (sigma,(sigma * 5), mask2D);
                         TwoDGauss(image,mask2D,newImg,M,(sigma * 5)); 
                         ostringstream sstream;
                         sstream << "2DlennaSigma" << sigma << ".pgm";
                         string fname = sstream.str();
                         WriteImage(fname,newImg,M,N,Q);
                         delete[] newImg; delete[] mask2D;
                       }
                break;
            }
           
             case 'd':{
                       for(int i = 0; i < 3; i++){
                         sigma = sigArray[i];
                         int** newImg;
                         float* mask = new float[sigma * 5];
                         Gauss (sigma,(sigma * 5), mask);
                         OneDGauss(image,mask,newImg,M,(sigma * 5)); 
                         ostringstream sstream;
                         sstream << "1DlennaSigma" << sigma << ".pgm";
                         string fname = sstream.str();
                         WriteImage(fname,newImg,M,N,Q);
                         delete[] newImg; delete mask;
                       }
                break;

             }
              
         }

  for(int i = 0; i < 25; i++)
    cout << endl;
      }while(c != 'q');
}

void GaussianPyramid(){
int level, steps;
int** image;
int M,N,Q;
ReadImage("lenna.pgm",image,M,N,Q);

     cout << "Guassian Pyramid Main Menu" << endl << endl<<
             "Enter Number of Levels: ";
     cin >> level;
     cout << "Enter Number of Steps: ";
     cin >> steps;

     pyramid(image,M,0,steps,level,Q);


  for(int i = 0; i < 25; i++)
    cout << endl;
}

void EdgeDetection(){
  int threshV;
  int M,N,Q;
  int O,P,R;
  float** xMask,**yMask;
  edgeMasks(xMask,yMask);
  int** lenImage,** sfImage;
  int** newLen,** newSF;
  int** lenX,** sfX;
  int** lenY,** sfY;
  int** mgLen,** mgSF;
  int** smthLen,** smthSF;
  int** thrLen, ** thrSF;
  float* mask = new float[5];

Gauss (1,5, mask);
ReadImage("lenna.pgm", lenImage, M, N, Q);
ReadImage("sf.pgm", sfImage, O, P, R);

     cout << endl << endl <<"Edge Detection Main Menu" << endl << endl
          << "Enter threshold: ";
     cin >> threshV;

            OneDGauss(lenImage,mask, smthLen, M, 5); 
            OneDGauss(sfImage,mask,smthSF,O,5);
            TwoDGauss(smthLen,xMask,lenX,M,3);
            TwoDGauss(smthSF,xMask,sfX,O,3);
            WriteImage("Lenna_Ix.pgm",lenX,M,N,Q);
            WriteImage("sf_Ix.pgm",sfX,O,P,R);
            TwoDGauss(smthLen,yMask,lenY,M,3);
            TwoDGauss(smthSF,yMask,sfY,M,3);
            delete smthLen; delete smthSF;

            WriteImage("Lenna_Iy.pgm",lenY,M,N,Q);
            WriteImage("sf_Iy.pgm",sfY,O,P,R);
            dir(lenX, lenY, newLen, M);
            dir(sfX, sfY, newSF, M);

            WriteImage("Lenna_Dir.pgm",newLen,M,N,Q);
            WriteImage("sf_Dir.pgm",newSF,O,P,R);
            delete[] newLen; delete[] newSF;

            magn(lenX, lenY, mgLen, M);
            magn(sfX, sfY, mgSF, M);

            WriteImage("Lenna_Mag.pgm",mgLen,M,N,Q);
            WriteImage("sf_Mag.pgm",mgSF,O,P,R);

            thresh(mgLen, thrLen, M,threshV);
            thresh(mgSF, thrSF, P,threshV);
            WriteImage("Lenna_Thresh.pgm",thrLen,M,N,Q);
            WriteImage("sf_Thresh.pgm",thrSF,O,P,R);

            delete[] mgLen; delete[] mgSF; delete[] lenY; delete[] lenX;
       

  for(int i = 0; i < 25; i++)
    cout << endl;
}


