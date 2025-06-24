#ifndef MRC_SVG
#define MRC_SVG

#include <fstream>
#include <vector>
#include <string>

char buf[256]; // buffer per gestire le stringhe


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
};


// --------------------------------------------------------------------------------------------------------


SVGwriter::SVGwriter()
{
	
}


void SVGwriter::write_file(std::string fName)
{
	std::ofstream file(fName);
	
	// INSERIRE ANCHE LE DIMENSIONI TOTALI DELL'IMMAGINE?????!!!!!!!!!!
	file << "<svg xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
	for(auto x : lines) file << x << std::endl;
	file << "</svg>";
	
	file.close();
}



void SVGwriter::addCirc(double cx, double cy, double r)
{
//	std::string str = "";
//	str = "<circle " + "cx=\"" + std::to_string(cx) + "\" " + "cy=\"" + std::to_string(cy) + "\" " + "r=\"" + std::to_string(r) + "\"/>"
	sprintf(buf,"<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\"/>", cx,cy, r);
	lines.push_back(buf);
}

void SVGwriter::addLine(double x1, double y1, double x2, double y2)
{
	sprintf(buf,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\"/>", x1,y1, x2,y2);
	lines.push_back(buf);
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
