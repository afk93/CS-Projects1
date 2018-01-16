#include <iostream>
#include "WCDisjointSets.h"
#include "PercVisualizer.h"

using namespace std;

class Percolation
   {
      public:
            Percolation();
            Percolation(int);
            ~Percolation();
            
            bool isValidPosition(int,int);
            void open(int,int);
            bool isOpen(int,int);
            bool pathToTop(int,int);
            bool percolates();
            void showPercolationVisualization();
            void showFinalVisualization();
            
     
     
      private:
			int **a;
			int n;
			WCDisjointSets *djs;
            PercVisualizer *pv;          
   };

Percolation::Percolation()
{
	n=5;
	a=NULL;
	djs=NULL;
}

Percolation::Percolation(int nn)
{
	n=nn;
	a=new int*[n];
	for (int i=0;i<n;i++)
         {
            a[i] = new int[n];
            for (int j=0;j<n;j++)
               a[i][j] = -1;
         }
    djs=new WCDisjointSets(n);
         
}

Percolation::~Percolation()
{
	delete [] a;
}

bool Percolation::isValidPosition(int r, int c)
   {
	   
	   if (r<0)
	   {return false;}
	   else if (r>=n)
	   {return false;}
	   else if (c<0)
	   {return false;}
	   else if (c>=n)
	   {return false;}
	   else
	   return true;
	   
   }


void Percolation::open(int row, int col)
{
	
		a[row][col]=1;
		if (isValidPosition(row-1,col) && isOpen(row-1,col))
			djs->Union(row*n+col,(row-1)*n+col);	
		if (isValidPosition(row,col+1) && isOpen(row,col+1))
			djs->Union(row*n+col,row*n+(col+1));
		if (isValidPosition(row+1,col) && isOpen(row+1,col))
			djs->Union(row*n+col,(row+1)*n+col);
		if (isValidPosition(row,col-1) && isOpen(row,col-1))
			djs->Union(row*n+col,row*n+(col-1));
			
	
}

bool Percolation::isOpen(int row, int col)
{
	if (a[row][col]<0)
	{
		return false;
	}
	else
		return true;
}

bool Percolation::pathToTop(int row, int col)
{

	int xb=djs->Find(row*n+col);
	for(int i=0;i<n;i++)
	{
		int yb=djs->Find(i);
		if (xb==yb)
			return true;
			
	}
	return false;
}

bool Percolation::percolates()
{
	
	for (int i=0;i<n;i++)
	{
		if (pathToTop(n-1,i))
			return true;
			
	}
	
	return false;
}
	
void Percolation::showPercolationVisualization()
{
	pv = new PercVisualizer(n,n);
	for (int i=0;i<n;i++)
         {
            for (int j=0;j<n;j++)
            {
				if(a[i][j]>0)
				{
					pv->paintCell(i,j,0);
				}
			}
		}
	pv->displayVisualization();
}
	
void Percolation::showFinalVisualization()
{
	pv = new PercVisualizer(n,n);
	for (int i=0;i<n;i++)
         {
            for (int j=0;j<n;j++)
            {
				if(a[i][j]>0)
				{
					pv->paintCell(i,j,0);
				}
			}
		}
	for (int i=0;i<n;i++)
	{
		if (pathToTop(n-1,i))
		{
			int m=n*(n-1)+i;
			int xb=djs->Find(m);
			for (int d=0;d<(n*n);d++)
			{
				int yb=djs->Find(d);
				if(xb==yb)
				{
					pv->paintCell(d/n,d%n,1);
				}
			}
		}
	}
		
	
	pv->displayVisualization();
}
		
	
	
	
