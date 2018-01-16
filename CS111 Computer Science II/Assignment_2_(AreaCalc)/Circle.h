#include <iostream>
#include <cstdlib>
#include <sstream>

#ifndef CIRCLE_H
#define CIRCLE_H

using namespace std;

class Circle
	{
		public:
				Circle ();
				Circle (double,double,double);
				string toString();
				double getCenterX();
				double getCenterY();
				double getRadius();
				void setCenterX(double);
				void setCenterY(double);
				void setRadius(double);
				static int getCircleCount();
				Circle(Circle &);
				~Circle();
				double calcArea();
				
		 private:
				double x,y,r,Area;
				static int cCount;
				
			
	};
	
#endif

int Circle::cCount=0;			
Circle::Circle()
{
	x=0;
	y=0;
	r=0;
	Area=0;
	cCount++;
	
}
Circle::Circle(Circle &oth)
{
	x=oth.x;
	y=oth.y;
	r=oth.r;
	cCount++;
}
Circle::Circle(double xx, double yy, double rr)
{
	x=xx;
	y=yy;
	r=rr;
	Area=3.14159*r*r;
	cCount++;
}

Circle::~Circle()
{
	cCount--;
}
int Circle::getCircleCount()
{
	return cCount;
}

string Circle::toString()
{
	stringstream ss;
	ss<<"("<<x<<","<<y<<"), "<<r;
	return ss.str();
	
}
double Circle::getCenterX()
{
	return x;
}
double Circle::getCenterY()
{
	return y;
}
double Circle::getRadius()
{
	return r;
}
void Circle::setCenterX(double xx)
{
	x=xx;
}
void Circle::setCenterY(double yy)
{
	y=yy;
}
void Circle::setRadius(double rr)
{
	r=rr;
}
double Circle::calcArea()
{
	return Area; 
}

