//Alex Keeler


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

CImg<float> drawswatch (CImg<float> image)
{
	
	float color[3]={128,60,98};
    float x1=0,y1=0,x2=0,y2=0;
    CImg<float> workimage=image;
	
	bool drawing=false; 
	
	CImgDisplay disp(workimage,"picture");
  
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
				disp.close();
			}
			
			disp.display(workimage);
			
			
         }
         
         float w=(x2-x1);
         float h=(y2-y1);
         
         CImg<float> newimage(w,h,1,3,0);
         for (int x=x1;x<x2;x++)
			{
				
				for (int y=y1;y<y2;y++)
				{
					int u=x-x1;
					int v=y-y1;
					newimage(u,v,0)=workimage(x,y,0);
					newimage(u,v,1)=workimage(x,y,1);
					newimage(u,v,2)=workimage(x,y,2);
					
				}
				
			}
			CImgDisplay dispA(newimage,"A");
			while (!dispA.is_closed()) 
         {
            dispA.wait();
         }
         return newimage;
       
        
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
     CImg<float> Rswatch;
     CImg<float> Gswatch;
     CImg<float> Bswatch;
     float red[3]={0};
     float green[3]={0};
     float blue[3]={0};
     
      for (int i=0; i<3; i++)
      {
		  if (i==0)
		  {
			  cout<<"Select red swatch"<<endl;
			 Rswatch=drawswatch(image);
		  }
		  if (i==1)
		  {
			  cout<<"Select green swatch"<<endl;
			 Gswatch=drawswatch(image);
		  }
		  if (i==2)
		  {
			  cout<<"Select blue swatch"<<endl;
			  Bswatch=drawswatch(image);
		  }
	  }
	  
	  
	  
	  for (int x=0; x<Rswatch.width(); x++)
	  {
		  for (int y=0; y<Rswatch.height(); y++)
		  {
			  float av=((Rswatch(x,y,0)+Rswatch(x,y,1)+Rswatch(x,y,2))/3.0);
			  int index=av/255;
			  red[index]++;
		  }
	  }
	  
	  for (int x=0; x<Gswatch.width(); x++)
	  {
		  for (int y=0; y<Gswatch.height(); y++)
		  {
			  float av=((Gswatch(x,y,0)+Gswatch(x,y,1)+Gswatch(x,y,2))/3.0);
			  int index=av/255;
			  green[index]++;
		  }
	  }
	  
	  for (int x=0; x<Bswatch.width(); x++)
	  {
		  for (int y=0; y<Bswatch.height(); y++)
		  {
			  float av=((Bswatch(x,y,0)+Bswatch(x,y,1)+Bswatch(x,y,2))/3.0);
			  cout<<av<<endl;
			  int index=av/255;
			  blue[index]++;
		  }
	  }
	
	 
     int MT[3][3]={0};
     MT[0][0]=red[0];
     MT[0][1]=green[0];
     MT[0][2]=blue[0];
     MT[1][0]=red[1];
     MT[1][1]=green[1];
     MT[1][2]=blue[1];
     MT[2][0]=red[2];
     MT[2][1]=green[2];
     MT[2][2]=blue[2];
     
     int Inv [3][3]={0};
     Inv[0][0]=MT[1][1]*MT[2][2]-MT[1][2]*MT[2][1];
     Inv[0][1]=-(MT[1][0]*MT[2][2]-MT[1][2]*MT[2][0]);
     Inv[0][2]=MT[1][0]*MT[2][1]-MT[1][1]*MT[2][0];
     Inv[1][0]=-(MT[0][1]*MT[2][2]-MT[0][2]*MT[2][1]);
     Inv[1][1]=MT[0][0]*MT[2][2]-MT[0][2]*MT[2][0];
     Inv[1][2]=-(MT[0][0]*MT[2][1]-MT[0][1]*MT[2][0]);
     Inv[2][0]=MT[0][1]*MT[1][2]-MT[0][2]*MT[1][1];
     Inv[2][1]=-(MT[0][0]*MT[1][2]-MT[0][2]*MT[1][0]);
     Inv[2][2]=MT[0][0]*MT[1][1]-MT[0][1]*MT[1][0];
     
     CImg<float> endimage(image.width(),image.height(),1,3,0);
     
      
	  
	    ///////////////////////////////////////////////////////
	  
	    for (int x=0;x<image.width();x++)
      {
		  for (int y=0;y<image.height(); y++)
		  {
			 endimage(x,y,0)=(Inv[0][0]*image(x,y,0)+Inv[0][1]*image(x,y,1)+Inv[0][2]*image(x,y,2));
			 endimage(x,y,1)=(Inv[1][0]*image(x,y,0)+Inv[1][1]*image(x,y,1)+Inv[1][2]*image(x,y,2));
			 endimage(x,y,2)=(Inv[2][0]*image(x,y,0)+Inv[2][1]*image(x,y,1)+Inv[2][2]*image(x,y,2));
		  }
	  } 
	  
	 CImgDisplay enddisp(endimage,"A");
      while (!enddisp.is_closed()) 
         {
            enddisp.wait();
         }
	   
	   
	   
  
     
     
				 
       
         
       
      
      
 } 
      
      
      
