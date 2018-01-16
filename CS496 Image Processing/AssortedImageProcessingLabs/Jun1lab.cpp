#include "CImg.h"
#include <cstdlib>
#include  <iostream>
#include <fstream>
 
using namespace cimg_library;
using namespace std;

/////////////////////////////////////////////

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
/////////////////////////////////////////////////

int main()
{
	string imagefilename = "sandpaint.tif";
      if (!file_exists(imagefilename))
         errorMsg("Can't find image",true);
      else
         cout<<"Here we go...close the image to terminate the program"<<endl;
         
      CImg<float> image(imagefilename.c_str());
      CImg<float> imageA(image.width(),image.height(),1,3,0);
     
      
	  
	    ///////////////////////////////////////////////////////
	  
	    for (int x=0;x<image.width();x++)
      {
		  for (int y=0;y<image.height(); y++)
		  {
			 imageA(x,y,0)=(2.254*image(x,y,0)+(-.27)*image(x,y,1)+(-.574)*image(x,y,2));
			 imageA(x,y,1)=((-.339)*image(x,y,0)+1.658*image(x,y,1)+(-.459)*image(x,y,2));
			 imageA(x,y,2)=((-.283)*image(x,y,0)+(-.533)*image(x,y,1)+1.926*image(x,y,2));
		  }
	  } 
	  
	 CImgDisplay dispA(imageA,"A");
      while (!dispA.is_closed()) 
         {
            dispA.wait();
         }
	   
	   
	   
   } 
	  
	 
	  /////////////////////////////////////////
