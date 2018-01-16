#include "CImg.h"
#include <cstdlib>
#include  <iostream>
#include <fstream>
#include <cmath>
 
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
         
      CImg<float> img(imagefilename.c_str());
      CImg<float> workimg(img.width(),img.height(),1,img.spectrum(),0);
      
      
        for (int x=2;x<img.width()-2;x++)
      {
		  for (int y=2;y<img.height()-2;y++)
		  {
			  for (int i=0;i<img.spectrum();i++)
			  {
				 
				  img(1,y,i)=img(2,y,i);
				  img(x,1,i)=img(x,2,i);
				  img(0,y,i)=img(1,y,i);
				  img(x,0,i)=img(x,1,i);
				  float pixval=img(x,y,i);
				  float avg=(img(x-1,y+2,i)+img(x,y+2,i)+img(x+1,y+2,i)+img(x-2,y+1,i)+img(x-1,y+1,i)+img(x,y+1,i)+img(x+1,y+1,i)+img(x+2,y+1,i)+img(x-2,y,i)+img(x-1,y,i)+img(x,y,i)+img(x+1,y,i)+img(x+2,y,i)+img(x-2,y-1,i)+img(x-1,y-1,i)+img(x,y-1,i)+img(x+1,y-1,i)+img(x+2,y-1,i)+img(x-1,y-2,i)+img(x,y-2,i)+img(x+1,y-2,i))/21.0;
				  float ratio=avg/pixval;
				  float exp=ratio*ratio;
				  float newval=(pow((pixval/255),exp))*255.0;
				  workimg(x,y,i)=newval;
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
			  
      

      
      
      
      
      
      
