#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>



using namespace std;


string getUserInput(string prompt)
   {
      cout<<prompt;
      string t="";
      getline(cin,t);
      cout<<endl;
      return t;
   }
   
   
void errorMsg(string msg, bool term)
   {
      cout<<msg<<endl;
      if (term)
        exit(0);
   }
   
   
bool isItAWord(string dictionary[], int z, string s)
   {
	   for (int i=0;i<=z;i++)
	   {
		   if (dictionary[i]==s)
		   {
			   return true;
		   }
	   }
	   return false;
   }
   
   
void loadDictionary(string dictionary[], int &z, int max, string filename)
   {
	   ifstream infile;
	   infile.open(filename.c_str());
	   string s;
	   z=0;
	   infile>>s;
	   while (infile)
	   {
		   dictionary[z]=s;
		   z++;
		   infile>>s;
	   }
		infile.close();
		bool fail;
		if (z>max)
		{
			fail=true;
		
		errorMsg("File exceeds maximum word count!",fail);  
	}
	   
   }
   
   
void dimension(int &n, int &a, int l)
{
	
	n++;
	while(l%n!=0 and n<l)
	{
		n++;
	}
	
	a=l/n;
 }


void find(string d,string dict[], string &answer, int &p,int z)  
{
	string s;
	int n=0;
	stringstream dd;
	dd<<d;
	string tok;
	dd>>tok;
	while(dd)
	{
		if (isItAWord(dict,z,tok))
		{
			s=s+tok+" ";
			n++;
		}
		dd>>tok;
	}
	if (n>p)
	{
		p=n;
		answer=d;
	}
}	
int main()
{
	
	
	string s;
	ifstream myfile;
	string f=getUserInput("File name to process: ");
	myfile.open(f.c_str());
	getline(myfile,s);
	while (myfile)
	{
		string answer="";
		string dict[200000];
		int z;
		int p=0;
		
		loadDictionary(dict,z,200000,"cmuwords.txt");
		string t[10000];
		int n=1;
		int a=0;
		
		dimension(n,a,s.length());
		while (a>1)
		{
			int k=0;
			for (int j=0;j<n;j++)
			{
				for (int i=0;i<a;i++)
				{
					t[i]=t[i]+s[k];
					k++;
				}
			}
			string d;
			for (int i=0;i<a;i++)
			{
				
				d=d+t[i];
				t[i]="";
			}
			
			
			find (d,dict,answer,p,z);
			dimension(n,a,s.length());
			
		}
		cout<<answer<<endl;
		cout<<endl;
		
		getline(myfile,s);
	}
	myfile.close();
}
					
				
				
			
			
				
