void TwoDGauss(int** img, float** mask, int**& newImg, int rSize, int mSize){
int i,j,x,z,a,b;
float val;

  newImg = new int*[rSize];
  for(i = 0; i < rSize; i++)
   newImg[i] = new int[rSize];
   
   
  for(i = 0; i < rSize; i++){
     for(j = 0; j < rSize; j++){
         for(x = -(mSize/2), val = 0,a = 0; a < mSize; a++,x++){
             if((x + i >= 0) && (x + i) < rSize){
                 for(z = -(mSize/2),b = 0; b < mSize; b++,z++){
                    if( (z + j) >= 0 && (z + j) < rSize){
                     val += img[i+x][j+z] * mask[a][b];
                    }
                 }
             }
         }
      newImg[i][j] = val;
     }
  }

}

void OneDGauss(int** img, float* mask, int**&newImg, int rSize, int mSize){
int i, j, z,a,b;
float val;

  newImg = new int*[rSize];
  int** tempImg = new int*[rSize];
  for(i = 0; i < rSize; i++){
   newImg[i] = new int[rSize];
   tempImg[i] = new int[rSize];
  }
   for(a = 0; a < rSize; a++){
      for(i = 0; i < rSize; i++){
         for(j = 0, val = 0,z = -(mSize/2); j < mSize;j++,z++){
            if((i + z) < rSize && (i + z >= 0)){
              val += mask[j] * img[i+z][a];
            }
         }
    tempImg[i][a] = val;
       }
   }
   for(a = 0; a < rSize; a++){
      for(i = 0; i < rSize; i++){
         for(j = 0, val = 0,z = -(mSize/2); j < mSize;j++,z++){
            if((i + z) < rSize && (i + z >= 0)){
              val += mask[j] * tempImg[a][i+z];
            }
         }
    newImg[a][i] = val;
       }
   }
}

void magn(int** ximg, int** yimg, int**& magImg, int rSize){

    magImg = new int*[rSize];
    for(int i = 0; i < rSize; i++)
      magImg[i] = new int[rSize];   
    for(int i = 0; i < rSize; i++){
       for(int j = 0; j < rSize; j++){
         magImg[i][j] = abs(ximg[i][j]) + abs(yimg[i][j]);
       }
    }
}

void thresh(int** magimg, int**& newImg, int rSize, int thresh){

    newImg = new int*[rSize];
    for(int i = 0; i < rSize; i++)
      newImg[i] = new int[rSize];
   
    for(int i = 0; i < rSize; i++){
       for(int j = 0; j < rSize; j++){
         if(magimg[i][j] >= thresh){
         newImg[i][j] = 100;
         }
         else{
         newImg[i][j] = 0;
         }
       }
    }
}

void dir(int** ximg, int** yimg, int**& dirImg, int rSize){

   dirImg = new int*[rSize];
   for(int i = 0;i < rSize; i++)
     dirImg[i] = new int[rSize];
   
    for(int i = 0; i < rSize; i++){
       for(int j = 0; j < rSize; j++){
         dirImg[i][j] = atan2(yimg[i][j],ximg[i][j]);
       }
    }

}

void rowConv(float rect[], float mask[], float*& newR, int rSize,int mSize){
int i, j, z;
float val;
newR = new float[rSize];

   for(i = 0; i < rSize; i++){
     for(j = 0, val = 0,z = -(mSize/2); j < mSize;j++,z++){
       if((i + z) < rSize && (i + z >= 0)){
       val += mask[j] * rect[i+z];
       }
     }
    newR[i] = val;
   }
}

void maskConv(float* Orig, float*& newM, int& size){
  int temp = size,i,j;
  size = 2 * size - 1;
  newM = new float[size];
  float* tempM = new float[size];
  for(i = 0; i < size; i++){
   newM[i] = 0;
   tempM[i] = 0;
  }
  for(i = temp / 2,j = 0; j < temp; i++,j++){
   newM[i] = Orig[j];
   tempM[i] = Orig[j];
  }
  rowConv(tempM, Orig, newM, size, temp);
}

void writeRect(float rect[], string file){
  ofstream fout(file.c_str());

  for(int i = 0; i < 128; i++)
   fout << rect[i] << endl;
}

void readRect(float rect[]){
  ifstream fin("Rect_128.txt");

  int i = 0;
  while (fin.good())
   fin >> rect[i++];

  fin.close();
  
}

void edgeMasks(float**& x, float**& y){

  x = new float*[3];
  y = new float*[3];

  for(int i = 0; i < 3; i++){
   x[i] = new float[3];
   y[i] = new float[3];
  }

  x[0][0] = -1; x[0][1] = 0; x[0][2] = 1;
  x[1][0] = -2; x[1][1] = 0; x[1][2] = 2;
  x[2][0] = -1; x[2][1] = 0; x[2][2] = 1;

  y[0][0] = -1; y[0][1] = -2; y[0][2] = -1;
  y[1][0] = 0; y[1][1] = 0; y[1][2] = 0;
  y[2][0] = 1; y[2][1] = 2; y[2][2] = 1;
}

void pyramid(int** image,int imgSize, int level, int step,int check,int Q){
int z = step, newSize = 0, j = 0;
int ** smoothedImg, ** newImg;
float* mask = new float[5];

Gauss (1, 5, mask);
OneDGauss(image, mask, smoothedImg, imgSize,5);

  for(j = 0; j < step; j++,z--){
     double n =  1 / float(z);
     newSize = imgSize / pow(2,n);
     newImg = new int*[newSize];
     for(int a = 0; a < newSize; a++)
       newImg[a] = new int[newSize];

         for(int b = 0; b < newSize; b++)
            for(int c = 0; c < newSize; c++)
              newImg[b][c] = smoothedImg[int(b*pow(2,n))][int(c*pow(2,n))];
        
  ostringstream sstream;
  sstream << "lenna" << level << j + 1 << ".pgm";
  string fname = sstream.str();
  WriteImage(fname,newImg,newSize,newSize,Q);
     if(j != step -1)
      delete newImg;
  }
  check--;
  level++;

  if(check != 0){
   pyramid(newImg,newSize,level++,step,check,Q);
  }


}
