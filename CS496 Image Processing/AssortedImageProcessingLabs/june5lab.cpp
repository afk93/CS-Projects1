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
      string imagefilename = "ocean.tif";
      if (!file_exists(imagefilename))
         errorMsg("Can't find conehead.jpg",true);
      else
         cout<<"Here we go...close the image to terminate the program"<<endl;
         
      CImg<float> image(imagefilename.c_str());
      CImg<float> workimage=image;
      
      float lum=0;
      float k=1;
      float p=3;
      float val=0;
      float cx=image.width()/2;
      float cy=image.height()/2;
      float maxdist=sqrt(pow((image.width()-cx),2)+pow((image.height()-cy),2));
      for (int x=0;x<image.width();x++)
      {
		  for (int y=0;y<image.height();y++)
		  {
			  float dist=sqrt(pow((x-cx),2)+pow((y-cy),2));
			  val=k*(pow((dist/maxdist),p));
			  lum=(.2126*image(x,y,0) + .7152*image(x,y,1) + .0722*image(x,y,2));
			  workimage(x,y,0)=image(x,y,0)*((val+lum)/lum);
		  }
	  }
      CImgDisplay disp(workimage,"doug");
      while (!disp.is_closed()) 
         {
            disp.wait();
		}
	}
      
      
      
      
      
