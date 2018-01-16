#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Circle.h"

using namespace std;

string getUserInput(string s)
	{
		cout<<"File name to process: ";
		cin>>s;	
		return s;	
	}
void dumpArrayChunk(string A[], int fst, int lst)
   {
      cout<<"Number of Circles: "<<A[fst]<<endl;
      for (int i=fst+1;i<=lst;i++)
         {
			 cout<<"circle: ";
			stringstream ss;
			string tok;
			ss<<A[i];
			int j=1;
			ss>>tok;
			while (ss)
			{
				if (j==1)
				{cout<<"("<<tok;}
				else if (j==2)
				{cout<<","<<tok<<")";}
				else
				{cout<<" - "<<tok<<endl;}
				j++;
				ss>>tok;
			}
           
         }
      cout<<endl;
   }

void dumpArray(string A[], int n)
   {
      dumpArrayChunk(A,0,n-1);
   }
int main(int argc, char *argv[])
{
	
	string s;
	ifstream infile;
	string a=getUserInput("File name to process: ");
	infile.open(a.c_str());
	int n=0;
	double totArea=0;
	double x;
	double y;
	double r=0;
	string A[500];
	getline(infile,s);
	while (infile and n<500)
	{
		
		A[n]=s;
		n++;
		getline(infile,s);
	}
	infile.close();
	
	for (int i=1;i<n;i++)
	{
		stringstream ss;
		string tok;
		ss<<A[i];
		int j=1;
		ss>>tok;
			while(ss)
			{
				
				if (j==1)
				{x=atoi(tok.c_str());}
				else if (j==2)
				{y=atoi(tok.c_str());}
				else if (j==3)
				{r=atoi(tok.c_str());}
				j++;
				ss>>tok;
			 }
		 cout<<y<<endl;
		
		Circle a(x,y,r);
		totArea=totArea+a.calcArea();
		
		
				
			
		
	}
		dumpArray(A,n);
		cout<<"Total Area: "<<totArea<<endl;
		
}

