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
	string imagefilename = "conehead.jpg";
      if (!file_exists(imagefilename))
         errorMsg("Can't find image",true);
      else
         cout<<"Here we go...close the image to terminate the program"<<endl;
         
      CImg<float> image(imagefilename.c_str());
      CImg<float> workimage=image;
      
      float color[3]={128,60,98};
      float x1=0,y1=0,x2=0,y2=0;
      
      bool drawing=false; 
       
       CImgDisplay disp(workimage,"doug");
      while (!disp.is_closed()) 
         {
            disp.wait();
            if (disp.button())
            {
				if (drawing==false)
				{
					drawing=true;
					x1=disp.mouse_x();
					y1=disp.mouse_y();
					
				}
				else
				{
					
					x2=disp.mouse_x();
					y2=disp.mouse_y();
					workimage=image;
					workimage.draw_rectangle(x1,y1,x2,y2,color,1);
				}
			}
			else if (!disp.button() && drawing==true)
			{
				x2=disp.mouse_x();
				y2=disp.mouse_y();
				drawing=false;
			}
			
			
			
		
			disp.display(workimage);	
         }
         
         
      
      
 } 
      
      
      
