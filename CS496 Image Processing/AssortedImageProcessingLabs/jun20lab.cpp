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
      string imagefilename = "boxworld.tif";
      if (!file_exists(imagefilename))
         errorMsg("Can't find image",true);
      else
         cout<<"Here we go...close the img to terminate the program"<<endl;
         
      CImg<float> img(imagefilename.c_str());
      CImg<float> workimg(img.width(),img.height(),1,3,0);
       
        
	  
	     
      img.RGBtoHSL();
	  workimg.RGBtoHSL();
	  for (int x=1;x<img.width()-1;x++)
		 { 
			 for (int y=1;y<img.height()-1;y++)
			 {
					int ker[3][3]={5-3,-3,5,0,-3,5,-3,-3};
					int work[3][3];
					 img(0,y,2)=img(1,y,2);
					 img(x,0,2)=img(x,1,2);
					 float dd[8];	
					 for (int i=0;i<8;i++)
					 {
						dd[i]=ker[0][0]*img(x-1,y-1,2)+ker[0][1]*img(x,y-1,2)+ker[0][2]*img(x+1,y-1,2)+ker[1][0]*img(x-1,y,2)+ker[1][1]*img(x,y,2)+ker[1][2]*img(x+1,y,2)+ker[2][0]*img(x-1,y+1,2)+ker[2][1]*img(x,y+1,2)+ker[2][2]*img(x+1,y+1,2);
						
						work[0][0]=ker[1][0];
						work[0][1]=ker[0][0];
						work[0][2]=ker[0][1];
						work[1][2]=ker[0][2];
						work[2][2]=ker[1][2];
						work[2][1]=ker[2][2];
						work[2][0]=ker[2][1];
						work[1][0]=ker[2][0];
						for(int m=0;m<3;m++)
						{
							for (int n=0;n<3;n++)
							{
								ker[m][n]=work[m][n];
							}
						}	
								
					 }
					 
					 float max=dd[0];
					 for (int i=1;i<8;i++)
					 {
						 if(dd[i]>dd[i-1])
						 {
							 max=dd[i];
						 }
					 }
				
					workimg(x,y,2)=max/9;	
				 
			 }
		 }
		 img.HSLtoRGB();
		 workimg.HSLtoRGB();
    
      
     
      
      
      
     
    
	  CImgDisplay dispworkimg(workimg,"new image");
	  CImgDisplay dispimg(img,"image");
      while (!dispworkimg.is_closed()) 
         {
            dispworkimg.wait();
         } 
         
     
	 }
			  
      
