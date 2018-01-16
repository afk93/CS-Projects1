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
         
      CImg<float> img(imagefilename.c_str());
      CImg<float> workimg(2*img.width(),2*img.height(),1,img.spectrum(),0);
      
      for (int x=0;x<img.width();x++)
      {
		  for (int y=0;y<img.height();y++)
		  {
			  for (int i=0;i<img.spectrum();i++)
			  {
				   
				  float I1=img(x,y,i)/2+img(x+1,y,i)/2;
				  float I2=img(x,y+1,i)/2+img(x+1,y+1,i)/2;
				  float P=I1/2+I2/2;
				  workimg(2*x,2*y,i)=img(x,y,i);
				  workimg(2*x+1,2*y,i)=I1;
				  workimg(2*x,2*y+1,i)=img(x,y,i)/2+img(x,y+1,i)/2;
				  workimg(2*x+1,2*y+1,i)=P;
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
      
      
