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
      string imagefilename = getUserInput("Enter Image File: ");
      if (!file_exists(imagefilename))
         errorMsg("Can't find image",true);
      else
         cout<<"Here we go...close the img to terminate the program"<<endl;
      float scale=2.0;  
      CImg<float> img(imagefilename.c_str());
      CImg<float> workimg(scale*img.width(),scale*img.height(),1,img.spectrum(),0);

	  int fx,fy,fxm1,fxp1,fxp2,fym1,fyp1,fyp2;
	  float origx,origy,dx,dy,f0,f1,f2,f3,fy0,fy1,fy2,fy3,a,b,c,d;
	  
      for (int x=0;x<scale*img.width();x++)
      {
		  for (int y=0;y<scale*img.height();y++)
		  {
			  for (int i=0;i<img.spectrum();i++)
			  {
				
				  origx=x/scale;
				  origy=y/scale;
				  fx=(int)origx;
				  fy=(int)origy;
				  dx=origx-fx;
				  dy=origy-fy;
				  if (fx-1<0)
				  {
					  fxm1=0;
				  }
				  else
				  {fxm1=fx-1;}
				  if ( fx+1>=img.width()-1)
				  {
					  fxp1=img.width()-1;
				  }
				  else
				  {fxp1=fx+1;}
				  if ( fx+2>=img.width()-1)
				  {
					  fxp2=img.width()-1;
				  }
				  else
				  {fxp2=fx+2;}
				  if (fy-1<0)
				  {
					  fym1=0;
				  }
				  else
				  {fym1=fy-1;}
				  if ( fy+1>=img.height()-1)
				  {
					  fyp1=img.height()-1;
				  }
				  else
				  {fyp1=fy+1;}
				  if ( fy+2>=img.height()-1)
				  {
					  fyp2=img.height()-1;
				  }
				  else
				  {fyp2=fy+2;}
				  
				  f0=img(fxm1,fym1,i);
				  f1=img(fx,fym1,i);
				  f2=img(fxp1,fym1,i);
				  f3=img(fxp2,fym1,i);
				  a=-.5*f0+1.5*f1-1.5*f2+.5*f3;
				  b=f0-2.5*f1+2*f2-.5*f3;
				  c=-.5*f0+.5*f3;
				  d=f1;
				  fy0=a*pow(dx,3)+b*pow(dx,2)+c*dx+d;
				  
				  f0=img(fxm1,fy,i);
				  f1=img(fx,fy,i);
				  f2=img(fxp1,fy,i);
				  f3=img(fxp2,fy,i);
				  a=-.5*f0+1.5*f1-1.5*f2+.5*f3;
				  b=f0-2.5*f1+2*f2-.5*f3;
				  c=-.5*f0+.5*f3;
				  d=f1;
				  fy1=a*pow(dx,3)+b*pow(dx,2)+c*dx+d;
				  
				  f0=img(fxm1,fyp1,i);
				  f1=img(fx,fyp1,i);
				  f2=img(fxp1,fyp1,i);
				  f3=img(fxp2,fyp1,i);
				  a=-.5*f0+1.5*f1-1.5*f2+.5*f3;
				  b=f0-2.5*f1+2*f2-.5*f3;
				  c=-.5*f0+.5*f3;
				  d=f1;
				  fy2=a*pow(dx,3)+b*pow(dx,2)+c*dx+d;
				  
				  f0=img(fxm1,fyp2,i);
				  f1=img(fx,fyp2,i);
				  f2=img(fxp1,fyp2,i);
				  f3=img(fxp2,fyp2,i);
				  a=-.5*f0+1.5*f1-1.5*f2+.5*f3;
				  b=f0-2.5*f1+2*f2-.5*f3;
				  c=-.5*f0+.5*f3;
				  d=f1;
				  fy3=a*pow(dx,3)+b*pow(dx,2)+c*dx+d;
				  
				  a=-.5*fy0+1.5*fy1-1.5*fy2+.5*fy3;
				  b=fy0-2.5*fy1+2*fy2-.5*fy3;
				  c=-.5*fy0+.5*fy3;
				  d=fy1;
				  workimg(x,y,i)=a*pow(dy,3)+b*pow(dy,2)+c*dy+d;
				
			  }
		  }
	  }
			 
	  CImgDisplay dispworkimg(workimg,"new image");
	  CImgDisplay dispimg(img,"image");
      while (!dispworkimg.is_closed()) 
         {
            dispworkimg.wait();
         } 
         
     
	 }  
      
      
