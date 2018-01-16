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
         
      CImg<unsigned char> img(imagefilename.c_str());
      CImg<unsigned char> workimg(img.width(),img.height(),1,3,0);
       
      
     
		  for (int x=1;x<img.width()-1;x++)
		 { 
			 for (int y=1;y<img.height()-1;y++)
			 {
				 for (int i=0;i<3;i++)
				 {
					 img(0,y,i)=img(1,y,i);
					 img(x,0,i)=img(x,1,i);
					 
					 float wtAVG=(-1)*img(x-1,y-1,i)+(-1)*img(x,y-1,i)+(-1)*img(x+1,y-1,i)+(-1)*img(x-1,y,i)+30.0*img(x,y,i)+(-1)*img(x+1,y,i)+(-1)*img(x-1,y+1,i)+(-1)*img(x,y+1,i)+(-1)*img(x+1,y+1,i);
					 workimg(x,y,i)=wtAVG/22.0;
					
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
			  
      
