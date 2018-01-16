#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include "../CImg.h"

using namespace std;
using namespace cimg_library;

class SeamCarver
{
	public:
		SeamCarver();
		SeamCarver(CImg<unsigned char>);
		~SeamCarver();
		
		CImg<unsigned char>* getImage();
		void setImage(CImg<unsigned char>);
		
		int getHeight();
		int getWidth();
		CImg<unsigned char>* getEnergyImage();
		
		int *findHorizontalSeam();
		int *findVerticalSeam();
		
		void removeHorizontalSeam(int*);
		void removeVerticalSeam(int*);
	
	private:
		 void calcEnergy();
         double get_XEnergy(int, int, int);
         double get_YEnergy(int, int, int);
         double findMin(double, double, double);
		 double **energy_arr;
		 CImg<unsigned char> *img;
         bool flag;
         int h,w;
	
};

SeamCarver::SeamCarver()
{
	flag = false;
	img = NULL;
	h=0;
	w=0;
}

SeamCarver::SeamCarver(CImg<unsigned char> image)
{
	flag = true;
	img = new CImg<unsigned char> (image);
	
	h = getHeight();
	w = getWidth();
	
	energy_arr = new double *[h];

    for(int i = 0; i < h; i++)
    {
        energy_arr[i] = new double[w];
    }
}

SeamCarver::~SeamCarver()
{

	delete img;
	
	for(int i = 0; i < h; i++)
    {
        delete energy_arr[i];
    }

    delete energy_arr;
}

int SeamCarver::getHeight()
{
	if (flag)
		return img->height();
	else
		return 0;
}

int SeamCarver::getWidth()
{
	if (flag)
		return img->width();
	else
		return 0;
}

CImg<unsigned char>* SeamCarver::getImage()
{
	if (flag)
	{
		CImg<unsigned char> *tmp = new CImg<unsigned char> (*img);
		return tmp;
	}
	else
		return 0;
}

void SeamCarver::setImage(CImg<unsigned char> newimg)
{
	flag = true;
	img = new CImg<unsigned char> (*newimg);
	h=getHeight();
	w=getWidth();
	
	energy_arr = new double *[h];

    for(int i = 0; i < h; i++)
    {
        energy_arr[i] = new double[w];
    }
	
}

CImg<unsigned char>* SeamCarver::getEnergyImage()
{
    if(flag == true)
    {
        CImg<unsigned char> *energy_image = new CImg<unsigned char> (w, h, 1, 3, 0);
        int red, green, blue;

        calcEnergy();

        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                red = ((int)energy_arr[i][j] & 0xff0000) >> 16;
                green = ((int)energy_arr[i][j] & 0x00ff00) >> 8;
                blue = ((int)energy_arr[i][j] & 0x0000ff);

                (*energy_image)(j, i, 0, 0) = red;
                (*energy_image)(j, i, 0, 1) = green;
                (*energy_image)(j, i, 0, 2) = blue;
            }
        }

        return energy_image;
    }

    else
        {
            return 0;
        }
}

double SeamCarver::get_XEnergy(int row, int col, int color)
{

    double energy = 0;
    if(col > 0 && col < w - 1)
    {
        energy = (*img)(col - 1, row, 0, color) - (*img)(col + 1, row, 0, color);
    }
    else
    {
        if(col == 0)
        {
            energy = (*img)(w - 1, row, 0, color) - (*img)(col + 1, row, 0, color);
        }

        if(col == w - 1)
        {
            energy = (*img)(col - 1, row, 0, color) - (*img)(0, row, 0, color);
        }

    }
    return energy;
}

double SeamCarver::get_YEnergy(int row, int col, int color)
{
    double energy = 0;

    if(row > 0 && row < h - 1)
    {
        energy = (*img)(col, row - 1, 0, color) - (*img)(col, row + 1, 0, color);
    }

    else
    {
        if(row == 0)
        {
            energy = (*img)(col, h - 1, 0, color) - (*img)(col, row, 0, color);
        }

        if(row == h - 1)
        {
            energy = (*img)(col, row - 1, 0, color) - (*img)(col, 0, 0, color);
        }
    }

    return energy;
}

void SeamCarver::calcEnergy()
{
    double redX = 0,    redY = 0,
           greenX = 0,  greenY = 0,
           blueX = 0,   blueY = 0,
           sum = 0,     sumX = 0,
           sumY = 0;

    if(flag == true)
    {
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                    redX = get_XEnergy(i, j,0);
                    greenX = get_XEnergy(i, j, 1);
                    blueX = get_XEnergy(i, j, 2);
                    sumX = pow(redX, 2) + pow(greenX, 2) + pow(blueX, 2);

                    redY = get_YEnergy(i, j, 0);
                    greenY = get_YEnergy(i, j, 1);
                    blueY = get_YEnergy(i, j, 2);
                    sumY = pow(redY, 2) + pow(greenY, 2) + pow(blueY, 2);

                    sum = sumX + sumY;
                    energy_arr[i][j] = sqrt(sum);
            } 
        }
    }
}

double SeamCarver::findMin(double x, double y, double z)
{
    if(y < x && y < z)
            return y;

    else if(x < y && x < z)
            return x;

    else
        return z;
}


int* SeamCarver::findHorizontalSeam()
{
	if (flag == true)
	{
		double **mem_arr = new double *[h];
		for(int i = 0; i < h; i++)
		{
			mem_arr[i] = new double[w];
		}
		
		calcEnergy();
		
		for (int i=0;i<h;i++)
		{
			mem_arr[i][0] = energy_arr[i][0];
		}
		
		for (int j=1;j<w;j++)
		{
			for (int i=0;i<h;i++)
			{
				if (i==0)
				{
					mem_arr[i][j] = energy_arr[i][j] + findMin(DBL_MAX,mem_arr[i][j-1],mem_arr[i+1][j-1]);
				}
				else if(i==(h-1))
				{
					mem_arr[i][j] = energy_arr[i][j] + findMin(mem_arr[i-1][j-1],mem_arr[i][j-1],DBL_MAX);
				}
				else
				{
					mem_arr[i][j] = energy_arr[i][j] + findMin(mem_arr[i-1][j-1],mem_arr[i][j-1],mem_arr[i+1][j-1]);
				}
			}
		}
		
		double rightmin=mem_arr[0][w-1];
		int ridge=0;
		
		for (int i=1;i<h;i++)
		{
			if (mem_arr[i][w-1]<rightmin)
			{
				rightmin = mem_arr[i][w-1];
				ridge = i;
			}
		}
		int *h_seam = new int[w];
		
		h_seam[w-1]=ridge;
		
		for (int j=(w-2);j>=0;j--)
		{
			if (ridge == 0)
			{
				if (mem_arr[0][j]<mem_arr[1][j])
				{
					h_seam[j]=ridge;
				}
				else
				{
					ridge=1;
					h_seam[j]=ridge;
				}
			}
			else if (ridge == (h-1))
			{
				if (mem_arr[h-1][j]<mem_arr[h-2][j])
				{
					h_seam[j]=ridge;
				}
				else
				{
					ridge=h-2;
					h_seam[j]=ridge;
				}
			}
			else
			{
				if (mem_arr[ridge-1][j]<mem_arr[ridge][j] && mem_arr[ridge-1][j]<mem_arr[ridge+1][j])
				{
					ridge=ridge-1;
					h_seam[j]=ridge;
				}
				else if (mem_arr[ridge+1][j]<mem_arr[ridge][j] && mem_arr[ridge+1][j]<mem_arr[ridge-1][j])
				{
					ridge=ridge+1;
					h_seam[j]=ridge;
				}
				else
					h_seam[j]=ridge;
			}
			
		}
		return h_seam;
	}
	else
		return 0;
}

int* SeamCarver::findVerticalSeam()
{
	if (flag == true)
	{
		double **mem_arr = new double *[h];
		for(int i = 0; i < h; i++)
		{
			mem_arr[i] = new double[w];
		}
		
		calcEnergy();
		
		for (int j=0;j<w;j++)
		{
			mem_arr[0][j] = energy_arr[0][j];
		}
		
		for (int i=1;i<h;i++)
		{
			for (int j=0;j<w;j++)
			{
				if (j==0)
				{
					mem_arr[i][j] = energy_arr[i][j] + findMin(DBL_MAX,mem_arr[i-1][j],mem_arr[i-1][j+1]);
				}
				else if(j==(w-1))
				{
					mem_arr[i][j] = energy_arr[i][j] + findMin(DBL_MAX,mem_arr[i-1][j-1],mem_arr[i-1][j]);
				}
				else
				{
					mem_arr[i][j] = energy_arr[i][j] + findMin(mem_arr[i-1][j-1],mem_arr[i-1][j],mem_arr[i-1][j+1]);
				}
			}
		}
		
		
		double bottommin=mem_arr[h-1][0];
		int ridge=0;
		cout<<bottommin<<endl;
		for (int j=1;j<w;j++)
		{
			if (mem_arr[h-1][j]<bottommin)
			{
				bottommin = mem_arr[h-1][j];
				ridge = j;
			}
		}
		int *v_seam = new int[h];
		
		v_seam[h-1]=ridge;
		
		for (int i=(h-2);i>=0;i--)
		{
			if (ridge == 0)
			{
				if (mem_arr[i][0]<mem_arr[i][1])
				{
					v_seam[i]=ridge;
				}
				else
				{
					ridge=1;
					v_seam[i]=ridge;
				}
			}
			else if (ridge == (w-1))
			{
				if (mem_arr[i][w-1]<mem_arr[i][w-2])
				{
					v_seam[i]=ridge;
				}
				else
				{
					ridge=w-2;
					v_seam[i]=ridge;
				}
			}
			else
			{
				if (mem_arr[i][ridge-1]<mem_arr[i][ridge] && mem_arr[i][ridge-1]<mem_arr[i][ridge+1])
				{
					ridge=ridge-1;
					v_seam[i]=ridge;
				}
				else if (mem_arr[i][ridge+1]<mem_arr[i][ridge] && mem_arr[i][ridge+1]<mem_arr[i][ridge-1])
				{
					ridge=ridge+1;
					v_seam[i]=ridge;
				}
				else
					v_seam[i]=ridge;
			}
			
		}
		return v_seam;
	}
	else
		return 0;
}
		
void SeamCarver::removeHorizontalSeam(int* h_seam)
{
	if(flag)
	{
		h=h-1;
		CImg<unsigned char> *t = new CImg<unsigned char>(w,h,img->depth(),img->spectrum());
		for (int j=0;j<h;j++)
		{
			for (int i=0;i<w;i++)
			{
				if (j<h_seam[i])
				{
					(*t)(i,j,0,0) = (*img)(i,j,0,0);
					(*t)(i,j,0,1) = (*img)(i,j,0,1);
					(*t)(i,j,0,2) = (*img)(i,j,0,2);
				}
				else if (j>=h_seam[i])
				{
					(*t)(i,j,0,0) = (*img)(i,j+1,0,0);
					(*t)(i,j,0,1) = (*img)(i,j+1,0,1);
					(*t)(i,j,0,2) = (*img)(i,j+1,0,2);
				}
			}
		}
		img=t;
	}
}

void SeamCarver::removeVerticalSeam(int *v_seam)
{
	if(flag)
	{
		w=w-1;
		CImg<unsigned char> *t = new CImg<unsigned char>(w,h,img->depth(),img->spectrum());
		for (int j=0;j<h;j++)
		{
			for (int i=0;i<w;i++)
			{
				if (i<v_seam[j])
				{
					(*t)(i,j,0,0) = (*img)(i,j,0,0);
					(*t)(i,j,0,1) = (*img)(i,j,0,1);
					(*t)(i,j,0,2) = (*img)(i,j,0,2);
				}
				else if (i>=v_seam[j])
				{
					(*t)(i,j,0,0) = (*img)(i+1,j,0,0);
					(*t)(i,j,0,1) = (*img)(i+1,j,0,1);
					(*t)(i,j,0,2) = (*img)(i+1,j,0,2);
				}
			}
		}
		img=t;
		
	}
}
