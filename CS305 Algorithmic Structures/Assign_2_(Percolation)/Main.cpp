#include <iostream>
#include "Percolation.h"
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

string getUserInput(string prompt)
   {
      string t="";
      cout<<prompt;
      getline(cin,t);
      return t;
   }

void errorMsg(string msg, bool term)
   {
      cout<<msg<<endl;
      if (term)
         exit(0);
   }
   
bool isDigitString(string s)
   {
      if (!isdigit(s[0]) && s[0]!='+' && s[0]!='-')
         return false;
      for (unsigned int i=1;i<s.length();i++)
         if (!isdigit(s[i]))
            return false;
      return true;
   }
   

int getUserInteger(string prompt)
   {
      string t="billybob";

      while (!isDigitString(t))
         {
            t = getUserInput(prompt);
         }
      return atoi(t.c_str());
   }

////////////////////////////////////////////////////////////////////

int main()
{
	srand(time(NULL));
	int trials = getUserInteger("Number of Trials: ");
	int n = getUserInteger("N: ");
	string show = getUserInput("Show final percolating grids? (y/n): ");
	double sumx=0;
	double a[trials];
	for(int t=0;t<trials;t++)
	{
		double count=0;
		Percolation perc(n);
		while(!perc.percolates())
		{
			int x=(rand()%(n*n-1));
			int r=x/n;
			int c=x%n;
			if (!perc.isOpen(r,c))
			{perc.open(r,c);
			count=count+1;
			}
			
		}
		sumx += count/(n*n);
		a[t]=count/(n*n);
		
		cout<<"Trial: "<<t<<" N: "<<n<<" open count: "<<count<<" ratio: "<<count/(n*n)<<endl;
		
		
			if(show[0]=='y' or show[0]=='Y')
			perc.showFinalVisualization();
		
	}
	double smean=sumx/trials;
	double offsets=0;
	for(int t=0;t<trials;t++)
	{
		offsets=offsets+(a[t]-smean)*(a[t]-smean);
	}
	double svar=offsets/(trials-1);
	
	cout<<"p*: "<<smean<<endl;
	cout<<"calculated interval for p*: ["<<smean-1.96*sqrt(svar/trials)<<","<<smean+1.96*sqrt(svar/trials)<<"]"<<endl;
}

		
		
	
	
