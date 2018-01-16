#include <iostream>
#include <cstdlib>
#include <sstream>
#include "../CImg.h"

using namespace std;
using namespace cimg_library;

class PercVisualizer
{
	public:
			PercVisualizer();
			PercVisualizer(int,int);
			void paintCell(int,int,int);
			void displayVisualization();
			void getRectangleCoordinates(int,int,int&,int&,int&,int&);
	private:
			int xcells;
			int ycells;
			int xoff;
			int yoff;
			int cellwid;
			int cellht;
			int canvaswid;
			int canvasht;
			CImg <unsigned char> canvas;
};
PercVisualizer::PercVisualizer()
{
	xcells=0;
	ycells=0;
	xoff=0;
	yoff=0;
	cellwid=0;
	cellht=0;
	canvaswid=0;
	canvasht=0;
	
	
}

PercVisualizer::PercVisualizer(int xx, int yy)
{
	xcells=xx;
	ycells=yy;
	cellwid=5;
	cellht=5;
	xoff=10;
	yoff=10;
	canvaswid=2*xoff+xcells*cellwid;
	canvasht=2*yoff+ycells*cellht;
	CImg <unsigned char> wcanvas(canvaswid,canvasht,1,3,0);
	canvas=wcanvas;
	unsigned char mdgrey2[]={128,128,128};
	for (int i=0;i<=ycells;i++)
	{
		canvas.draw_line(xoff,yoff+i*cellht,xoff+xcells*cellwid,yoff+i*cellht,mdgrey2);
	}
	for (int i=0;i<=xcells;i++)
	{
		canvas.draw_line(xoff+i*cellwid,yoff,xoff+i*cellwid,yoff+ycells*cellht,mdgrey2);
	} 	
}

void PercVisualizer::getRectangleCoordinates(int x, int y, int &x0, int &x1, int &y0, int &y1)
{
	
	for (int i=0;i<xcells;i++)
	{
		if (x>(xoff+i*cellwid) && x<(xoff +(i+1)*cellwid))
		{
			x0=xoff+i*cellwid+1;
			x1=xoff +(i+1)*cellwid-1;
		}
	}
	for (int i=0;i<ycells;i++)
	{
		if (y>(yoff+i*cellht) && y<(yoff +(i+1)*cellht))
		{
			y0=yoff+i*cellht+1;
			y1=yoff +(i+1)*cellht-1;
		}
	}
}



void PercVisualizer::paintCell(int row, int col, int colortype)
{
	int x0,x1,y0,y1;
	unsigned char red,green,blue;
	int x=col*cellwid+xoff+1;
	int y=row*cellht+yoff+1;
	getRectangleCoordinates(x,y,x0,x1,y0,y1);
	if (colortype==0)
	{
		red=255;
		green=255;
		blue=255;
	}
	else
	{
		red=255;
		green=69;
		blue=0;
	}
	unsigned char color[]={red,green,blue};
	canvas.draw_rectangle(x0,y0,x1,y1,color,1);
}

void PercVisualizer::displayVisualization()
{
	
	CImgDisplay disp(canvas,"PERC");
	while(!disp.is_closed())
	{
		disp.wait();
	}
}
