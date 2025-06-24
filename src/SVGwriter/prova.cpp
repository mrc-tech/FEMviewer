#include <iostream>

#include "SVGwriter.h"


using namespace std;



int main()
{
	SVGwriter svg;
	
	svg.addCirc(100,100,50);
	svg.addLine(0,0, 200,200);
	svg.addLine(0,200, 200,0);
	
	svg.write_file("output.svg");
	
	return 0;
}
