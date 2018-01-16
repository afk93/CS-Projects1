#include "CImg.h"
#include <cstdlib>
#include  <iostream>
#include <fstream>
 
using namespace cimg_library;
using namespace std;


//---------------------- Dean utilities ------------------------------------
void errorMsg(string msg, bool term)
   {
      cout<<msg<<endl;
      if (term)
         exit(0);
   }

string getUserInput(string prompt)
   {
      cout<<prompt;
      string t="";
      getline(cin,t);
      return t;
   }

bool isIntegerString(string s)
   {
       unsigned int i=0;
       if (s[i]=='+' || s[i]=='-')
          i++;
      for (;i<s.length();i++)
         if (!isdigit(s[i]))
            return false;
      return true;
   }

int getUserInteger(string prompt)
   {
      string t = "z";
      while (!isIntegerString(t))
         {
            t = getUserInput(prompt);
         }
      return atoi(t.c_str());
   }

bool file_exists( string fileName)
{
    ifstream infile(fileName.c_str());
    return infile.good();
}
//------------------------Dean utilities ---------------------------------
 
 
 int main()
   {
      string imagefilename = "bird.tif";
      if (!file_exists(imagefilename))
         errorMsg("Can't find image",true);
      else
         cout<<"Here we go...close the img to terminate the program"<<endl;
         
      CImg<float> img(imagefilename.c_str());
      CImg<float> workimg(img.width(),img.height(),1,3,0);
       
    /*  
     int t= img.height()*img.width();
     float a[t];
     int p=0;
		  for (int x=1;x<img.width()-1;x++)
		 { 
			 for (int y=1;y<img.height()-1;y++)
			 {
				 for (int i=0;i<3;i++)
				 {
					  workimg(x,y,i)=img(x,y,i)/255;
					  a[p]=workimg(x,y,i);
					  p++;
					  
					  
				 }
			 }
		 }
      
     float max,min;
     int channel;
     for (int i=0;i<t;i++)
     {
		 if (a[i+1]>a[i])
		 { 
			 max=a[i+1];
			 channel=(i+1)%3; 
		 }
		 else
		 { min=a[i+1]; }
	 }
	 
     float lum=(max+min)/2.0;
     float sat;
     float hue;
     if (lum<.5)
     {
		 sat=(max-min)/(max+min);
	 }
	 else if (lum>.5)
	 {
		 sat=(max-min)/(2.0-max-min);
	 }
	 else 
	 {
		 sat=0;
	 }
     if (channel==0)
     {
		 hue=( 
      
     */
     for (int j=0;j<50;j++)
      {
		  for (int x=1;x<img.width()-1;x++)
		 { 
			 for (int y=1;y<img.height()-1;y++)
			 {
				 for (int i=0;i<3;i++)
				 {
					 img(0,y,i)=img(1,y,i);
					 img(x,0,i)=img(x,1,i);
					 
					 float wtAVG=4*img(x-1,y-1,i)+2*img(x,y-1,i)+1*img(x+1,y-1,i)+2*img(x-1,y,i)+4*img(x,y,i)+2*img(x+1,y,i)+1*img(x-1,y+1,i)+2*img(x,y+1,i)+1*img(x+1,y+1,i);
					 workimg(x,y,i)=wtAVG/16;
					
				 }
			 }
		 }
      }
    
	  img.RGBtoHSL();
	  workimg.RGBtoHSL();
	  for (int x=1;x<img.width()-1;x++)
		 { 
			 for (int y=1;y<img.height()-1;y++)
			 {
				 
					 img(0,y,2)=img(1,y,2);
					 img(x,0,2)=img(x,1,2);
					 
					 float wtAVG=(-1)*img(x-1,y-1,2)+(-1)*img(x,y-1,2)+(-1)*img(x+1,y-1,2)+(-1)*img(x-1,y,2)+30.0*img(x,y,2)+(-1)*img(x+1,y,2)+(-1)*img(x-1,y+1,2)+(-1)*img(x,y+1,2)+(-1)*img(x+1,y+1,2);
					 workimg(x,y,2)=wtAVG/22.0;
					 float diff=(img(x,y,2)-workimg(x,y,2)+1.0)/2.0;
					 img(x,y,2)=(1.5*img(x,y,2)+2.5*diff)/3.0;
					 
					
				 
			 }
		 }
		 img.HSLtoRGB();
    
	 // CImgDisplay dispworkimg(workimg,"new image");
	  CImgDisplay dispimg(img,"image");
      while (!dispimg.is_closed()) 
         {
            dispimg.wait();
         } 
         
     
	 }
			  
      
