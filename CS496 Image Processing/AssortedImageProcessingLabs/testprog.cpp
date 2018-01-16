// testprog.cpp
// test program to see if you've got ImageMagick and CImg.h where they belong

// adjust this #include to point to your CImg.h
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
      string imagefilename = "conehead.jpg";
      if (!file_exists(imagefilename))
         errorMsg("Can't find conehead.jpg",true);
      else
         cout<<"Here we go...close the image to terminate the program"<<endl;
         
      CImg<unsigned char> image(imagefilename.c_str());
      CImg<unsigned char> imageR(image.width(),image.height(),1,3,0);
      CImg<unsigned char> imageG(image.width(),image.height(),1,3,0);
      CImg<unsigned char> imageB(image.width(),image.height(),1,3,0);
      /*for (int x=0;x<image.width();x++)
      {
		  for (int y=0;y<image.height(); y++)
		  {
			  imageR(x,y,0)=image(x,y,0);
		  }
	  } 
	for (int x=0;x<image.width();x++)
      {
		  for (int y=0;y<image.height(); y++)
		  {
			  imageG(x,y,1)=image(x,y,0);
		  }
	  } 
      CImgDisplay dispR(imageR,"Red");
      CImgDisplay dispG(imageG,"Green");
      while (!dispG.is_closed()) 
         {
            dispG.wait();
         } */
      int RHist[256]={0};
      int BHist[256]={0};
      int GHist[256]={0};
      int BrHist[1024]={0};
      int LumHist[1024]={0};
      int r=0;
      int b=0;
      int g=0;
      float bright=0;
      float lum=0;
      
      for (int x=0;x<image.width();x++)
      {
		  for (int y=0;y<image.height(); y++)
		  {
			  r=image(x,y,0);
			  RHist[r]++;
		  }
	  } 
	 for (int i=0;i<256;i++)
	 {
		 cout<<RHist[i]<<endl;
	 }
	 cout<<"blueuuuuuu"<<endl;
	  ofstream outfile("redfile.csv");
	  for  (int i=0;i<256;i++)
	  {outfile<<RHist[i]<<endl;}
	  
      
      ///////////////////////////////////////////////////
      for (int x=0;x<image.width();x++)
      {
		  for (int y=0;y<image.height(); y++)
		  {
			  b=image(x,y,2);
			  BHist[b]++;
		  }
	  } 
	  for (int i=0;i<256;i++)
	 {
		 
		 cout<<BHist[i]<<endl;
	 }
	  ofstream outfileB("bluefile.csv");
	  for  (int i=0;i<256;i++)
	  {outfileB<<BHist[i]<<endl;}
	  
	  ///////////////////////////////////////////
	  
	   for (int x=0;x<image.width();x++)
      {
		  for (int y=0;y<image.height(); y++)
		  {
			  g=image(x,y,1);
			  GHist[g]++;
		  }
	  } 
	  for (int i=0;i<256;i++)
	 {
		 cout<<GHist[i]<<endl;
	 }
	  ofstream outfileG("greenfile.csv");
	  for  (int i=0;i<256;i++)
	  {outfileG<<GHist[i]<<endl;}
	  outfile.close();
	  outfileB.close();
	  outfileG.close();
	  ///////////////////////////////////////////////////////
	  
	    for (int x=0;x<image.width();x++)
      {
		  for (int y=0;y<image.height(); y++)
		  {
			  bright=(image(x,y,0) + image(x,y,1) + image(x,y,2))/3.0;
			  int index=(bright*1024)/255;
			  BrHist[index]++;
		  }
	  } 
	  
	  ofstream outfileBr("brightfile.csv");
	  for  (int i=0;i<1024;i++)
	  {outfileBr<<BrHist[i]<<endl;}
	  outfileBr.close();
	  /////////////////////////////////////////
	  
	   for (int x=0;x<image.width();x++)
      {
		  for (int y=0;y<image.height(); y++)
		  {
			  lum=(.2126*image(x,y,0) + .7152*image(x,y,1) + .0722*image(x,y,2));
			  int index=(lum*1024)/255;
			  LumHist[index]++;
		  }
	  } 
	  
	  ofstream outfileLum("Luminancefile.csv");
	  for  (int i=0;i<1024;i++)
	  {outfileLum<<LumHist[i]<<endl;}
	  outfileLum.close();
	  
   }
