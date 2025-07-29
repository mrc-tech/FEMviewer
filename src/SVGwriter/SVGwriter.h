#ifndef MRC_SVG
#define MRC_SVG

#include <fstream>
#include <vector>
#include <string>

char buf[1024]; // buffer per gestire le stringhe


class SVGwriter
{
	public:
		SVGwriter();
		
		void addCirc(double cx, double cy, double r);
		void addLine(double x1, double y1, double x2, double y2);
		void addRect(double x1, double y1, double x2, double y2);
		
		void write_file(std::string fName);
		
	private:
		std::vector<std::string> lines; // lines of the SVG file
		double x_min, x_max, y_min, y_max; // per calcolare viewBox
};


// --------------------------------------------------------------------------------------------------------


SVGwriter::SVGwriter()
{
	
}


void SVGwriter::write_file(std::string fName)
{
	std::ofstream file(fName);
	
	double p = 0.05;
	
	double w = x_max-x_min;
	double h = y_max-y_min;
	double d = sqrt(w*w + h*h);
	double D = p * d;
	
	file << "<svg ";
	file << "viewBox=\"" << x_min-D << " " << y_min-D << " " << w + 2*D << " " << h + 2*D << "\"";
	file << " xmlns=\"http://www.w3.org/2000/svg\">" << std::endl; // header finale standard
	for(auto x : lines) file << x << std::endl;
	file << "</svg>";
	
	file.close();
}



void SVGwriter::addCirc(double cx, double cy, double r)
{
//	std::string str = "";
//	str = "<circle " + "cx=\"" + std::to_string(cx) + "\" " + "cy=\"" + std::to_string(cy) + "\" " + "r=\"" + std::to_string(r) + "\"/>"
//	sprintf(buf,"<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\"/>", cx,cy, r);
	sprintf(buf,"<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf%%\"/>", cx,cy, r); // raggio percentuale (percentuale della diagonale del viewBox?)
	lines.push_back(buf);
	// aggiorna i bordi:
	x_min = std::min(cx, x_min); x_max = std::max(cx, x_max);
	y_min = std::min(cy, y_min); y_max = std::max(cy, y_max);
}

void SVGwriter::addLine(double x1, double y1, double x2, double y2)
{
	sprintf(buf,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"1%%\"/>", x1,y1, x2,y2); // stroke-width percentuale rispetto alla diagonale del viewBox
	lines.push_back(buf);
	// aggiorna i bordi:
	x_min = std::min(x1, x_min); x_min = std::min(x2, x_min); x_max = std::max(x1, x_max); x_max = std::max(x2, x_max);
	y_min = std::min(y1, y_min); y_min = std::min(y2, y_min); y_max = std::max(y1, y_max); y_max = std::max(y2, y_max);
}

void SVGwriter::addRect(double x1, double y1, double x2, double y2)
{
	// IN SVG CI STA UN COMANDO RECT!!!!!
	addLine(x1,y1, x2,y1);
	addLine(x2,y1, x2,y2);
	addLine(x2,y2, x1,y2);
	addLine(x1,y2, x1,y1);
}



#endif // MRC_SVG
