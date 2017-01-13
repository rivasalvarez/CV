Image harrisDetector(Image &src, float ALPHA, float LAMBDA, float SIGMA){
int MASK_S = 5 * SIGMA;
float mask[MASK_S], dmask[int(SIGMA*LAMBDA*5)];
Gauss(SIGMA,MASK_S,mask);
DGauss(SIGMA*LAMBDA,SIGMA*LAMBDA*5,dmask);
int w = src.width, h = src.height;

Image image(src),Ix(w,h),Iy(w,h),Ixx(w,h),Iyy(w,h),Ixy(w,h),Raw(w,h);

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

   //ostringstream sstring;
   //sstring << fNames[z] <<"_Raw";
   //string temp = sstring.str();

   //Raw.writeImage(temp);
   //sstring.str("");
   Raw.thresh((cornerMax * .01));

   //sstring << fNames[z] << "_nonMax";
   //temp = sstring.str();
   Raw.nonMax(3);
   //Raw.writeImage(temp);
   //sstring.str("");

   //sstring << fNames[z] << "_final";
   //temp = sstring.str();
   //Image Final(image);
   //Final.overlay(Raw,Over[z]);
   //Final.writeImage(temp);

return Raw;
}
