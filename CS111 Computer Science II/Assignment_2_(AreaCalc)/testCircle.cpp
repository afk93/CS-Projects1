// test Circle.h

#include <iostream>
#include <cstdlib>

#include "Circle.h"

using namespace std;

void fiddle(Circle aa)
   {
      aa.setCenterX(99);
      aa.setCenterY(98);
      aa.setRadius(1);
      //cout<<"aa: "<<aa.toString()<<endl;
      cout<<"\nIn fiddle() there are "<<Circle::getCircleCount()<<" circles"<<endl;
      cout<<"      aa: "<<aa.toString()<<endl<<endl;
   }


int main(int argc, char *argv[])
   {
      Circle a(1,2,3);
      Circle b(0,0,1);

      // cout<<"a: "<<a.toString()<<endl;
      // cout<<"b: "<<b.toString()<<endl;
      cout<<"Before call fiddle() there are "<<a.getCircleCount()<<" Circles"<<endl;
      cout<<"   Here they are: "<<endl;
      cout<<"      a: "<<a.toString()<<endl;
      cout<<"      b: "<<b.toString()<<endl;
      fiddle(b);
      cout<<"After call fiddle() there are "<<Circle::getCircleCount()<<" Circles"<<endl;
      cout<<"   Here they are: "<<endl;
      cout<<"      a: "<<a.toString()<<endl;
      cout<<"      b: "<<b.toString()<<endl;
      
   }
