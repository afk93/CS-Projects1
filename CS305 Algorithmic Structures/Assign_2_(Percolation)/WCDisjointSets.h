// WCDisjointSets.h
// simple class for disjoint sets of integers in a range
// union without rank
// find with path compression

#include <iostream>
using namespace std;

class WCDisjointSets
   {
      public:
            WCDisjointSets();
            WCDisjointSets(int);
            ~WCDisjointSets();
            WCDisjointSets(const WCDisjointSets&);

            WCDisjointSets & operator=(const WCDisjointSets&);

            int Find(int);
            void Union(int,int);

            int getDistinctSetCount();

            void dumpSets();
            void dumpSets(string);
            void showSet(int);
            void showSet(string,int);
            void showDistinctSets();
            void showDistinctSets(string);



      private:
            int *a;                    // the data (ints)
            int *rank;
            int arraysize;             // size of the array
            int n;                     // items
            int distinctsets;          // distinct sets
   };

// default constructor
WCDisjointSets::WCDisjointSets()
   {
      n = 0;
      arraysize = 0;
      a = NULL;
      rank=NULL;
      distinctsets = 0;
   }

// construct with universe size nn
WCDisjointSets::WCDisjointSets(int nn)
   {
      n = nn*nn;
      arraysize = n;
      a = new int[arraysize];
      for (int i=0;i<n;i++)
         {
            a[i] = i;                        // each is its own leader
         }
      rank = new int[arraysize];
      for (int i=0;i<n;i++)
         {
            rank[i] = 0;                    
         }
      distinctsets = n;
   }

// destructor
WCDisjointSets::~WCDisjointSets()
   {
      delete [] a;
   }

// copy constructor
WCDisjointSets::WCDisjointSets(const WCDisjointSets &other)
   {
      arraysize = other.arraysize;
      n = other.n;
      a = new int[arraysize];
      for (int i=0;i<n;i++)
         a[i] = other.a[i];
      distinctsets = other.distinctsets;
   }


// debugging tool
void WCDisjointSets::dumpSets()
   {
      int j=0;
      for (int i=0;i<n;i++)
         {
            cout<<i<<": ";
            j=i;
            while (a[j]!=j)
               j = a[j];
            cout<<j<<endl;
         }
   }

// debugging tool
void WCDisjointSets::dumpSets(string msg)
   {
      cout<<msg<<endl;
      dumpSets();
   }


// debugging tool
void WCDisjointSets::showSet(int x)
   {
      int leader;
      leader = Find(x);
      cout<<"Set for "<<x<<" has leader: "<<leader<<" - contains: ";
      for (int i=0;i<n;i++)
         {
            if (Find(i)==leader)
               cout<<i<<" ";
         }
      cout<<endl;
   }

// debugging tool
void WCDisjointSets::showSet(string msg,int x)
   {
      cout<<msg<<endl;
      showSet(x);
   }

void WCDisjointSets::showDistinctSets()
   {
      bool *got;
      got = new bool[n];
      for (int i=0;i<n;i++)
         got[i] = false;

      int leader = -1;
      for (int i=0;i<n;i++)
         {
            leader = Find(i);
            if (!got[leader])
               {
                  for (int j=0;j<n;j++)
                     {
                        if (Find(j)==leader)
                           {
                              got[j] = true;
                              cout<<j<<" ";
                           }
                     }
                  cout<<endl;
               }
         }
   }


void WCDisjointSets::showDistinctSets(string msg)
   {
      cout<<msg<<endl;
      showDistinctSets();
   }

int WCDisjointSets::getDistinctSetCount()
   {
      return distinctsets;
   }


//======================================================================

// add this function's code
int WCDisjointSets::Find(int x)
   {
	   if(x!=a[x])
	   a[x]=Find(a[x]);
	   
	   return a[x];
   }

//  Add this function's code
void WCDisjointSets::Union(int x, int y)
   {
	  int X=Find(x);
	  int Y=Find(y);
	  
	  if (rank[X]>rank[Y])
	  {
	   distinctsets--;
	   a[Y]=X;
	  }
	  else if (rank[X]<rank[Y])
	  {
	   distinctsets--;
	   a[X]=Y;
	  }
	  else
	  {
		  distinctsets --;
		  a[X]=Y;
		  rank[Y]++;
	  }
	  

	   
   }


// assignment operator overload
WCDisjointSets & WCDisjointSets::operator=(const WCDisjointSets &rhs)
   {
      if (this == &rhs)      // watch for self-asst
         return *this;
      
       arraysize=rhs.arraysize;
       n=rhs.n;  
          
       if (a!=NULL)
       {
		   delete [] a;
	   }
	   
       a = new int[arraysize]; 
       
	   
      for (int i=0;i<n;i++)
         {
            a[i] = rhs.a[i];
         }
         
       distinctsets=rhs.distinctsets;


      return *this;
   }




//======================================================================
