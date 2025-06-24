#ifndef MRC_FEM_VIEWER
#define MRC_FEM_VIEWER

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

#include "Model.h"
#include "SVGwriter/SVGwriter.h"
#include "utils/string_utils.h"

#define PI 3.141592653589793


Node project_ortho(Node, double,double, double);
Node project_ortho(Node, double,double);
Node rotate(Node ,double,double,double);
Model loadModel(string fName);
Model loadDisplacements(Model m, string fName, double mul, int j);


struct opzioni{
	int img_width; // dimensione immagine in orizzontale
	int img_height; // dimensione immagine in verticale
	int zoom; // ingrandimento dell'immagine
	int x_shift; // spostamento in x dell'origine
	int y_shift; // spostamento in y dell'origine
	double alpha; // assonometria: 
	double theta; // assonometria: 
	double scale; // scala degli spostamenti
};


int main(int argc, char **argv)
{
	char buf[256];
	
	
	if(argc > 1){
		sprintf(buf, "tcl2model %s > model.dat", argv[1]);
		system(buf);
	}
	
	// definizione modello:
	Model mod;
	mod = loadModel("model.dat");
	
	
	// DEVE CARICARE LE IMPOSTAZIONI DA UN FILE INI ESTERNO (se non esiste lo crea).........................
//	struct opzioni op;
//	op.img_width  = 800;
//	op.img_height = 600;
//	op.alpha = 30;
//	op.theta = 30;
//	op.zoom = 30;
//	op.x_shift = 150;
//	op.y_shift = 150;
//	op.scale = 100000;
	
//	TCHAR win_buf[1000];
//	GetPrivateProfileString(NULL, TEXT("scale"), TEXT("1.0"), win_buf, sizeof(win_buf) / sizeof(win_buf[0]), TEXT(".\\plotModel3D.ini"));
//		cout << win_buf << endl;
////	GetPrivateProfileString(TEXT("database"), TEXT("server"), TEXT("127.0.0.1"), dbserver, sizeof(dbserver) / sizeof(dbserver[0]), TEXT(".\\plotModel3D.ini"));
	
	struct opzioni op;
	op.img_width  = 800;
	op.img_height = 600;
	op.alpha = 30;
	op.theta = 30;
	op.zoom = 20;
	op.x_shift = 0;
	op.y_shift = 150;
	op.scale = 200;
	
//	// load an ini file
//	ini::IniFile myIni;
//	myIni.load("plotModel3D.ini"); // RICHIEDE PER FORZA LE SEZIONI!!!!
//	
//	op.img_width = myIni["opzioni"]["img_width"].as<int>();
//	op.img_height = myIni["opzioni"]["img_height"].as<int>();
//	op.x_shift = myIni["opzioni"]["x_shift"].as<int>();
//	op.y_shift = myIni["opzioni"]["y_shift"].as<int>();
//	op.zoom = myIni["opzioni"]["zoom"].as<int>();
//	op.scale = myIni["opzioni"]["scale"].as<double>();
//	op.alpha = myIni["opzioni"]["alpha"].as<double>();
//	op.theta = myIni["opzioni"]["theta"].as<double>();
	

	
	double alpha = op.alpha;
	double theta = op.theta;
	
//	Image img(op.img_width,op.img_height);
	
	int mul = op.zoom;
//	int xoff = img.width()/2+op.x_shift;
//	int yoff = img.height()/2+op.y_shift;
	
//	int FPS = 50; // Frames Per Seconds target per il video da creare
	double Dt = 0.01; // timestep in cui e` discretizzato l-output del modello
//	int skip_istant = (int)(1./(Dt*FPS)); // numero di istanti da skippare per arrivare al FPS target
	
	ifstream in_stream("output/Node_disp.out");
	int Ndata = std::count_if(std::istreambuf_iterator<char>{in_stream}, {}, [](char c) { return c == '\n'; }); // conta il numero di righe nel file... (metodo efficiente MA SBAGLIATO!!?)
	in_stream.close();
	
	
int frame = 1;
for(int i=0; i<Ndata; i++){ // NUMERO DI RIGHE DEL FILE DI OUPTUT (quanti istanti temporali ho)
	
	printf("\r %d/%d   ", i,Ndata);
	
//	if(i % skip_istant != 0) continue; // skippa i frames
	
//	img.clear();
	
	// disegna il modello indeformato:
//	img.penColor(100,100,100);
	for(int i=0; i<mod.nElem(); i++){
		Node n1 = project_ortho(mod.getNodeMod(mod.getElem(i).iNode()), alpha,theta);
		Node n2 = project_ortho(mod.getNodeMod(mod.getElem(i).jNode()), alpha,theta);
		
//		DrawLine(img, n1.getX(),n1.getY(), n2.getX(),n2.getY(), mul,xoff,yoff);
	}
	
	// disegna il modello deformato:
	Model mod_def = loadDisplacements(mod, "output/Node_disp.out", op.scale, i+1); // carica gli spostamenti
//	img.penColor(255,255,255);
	for(int i=0; i<mod.nElem(); i++){
		Node n1 = project_ortho(mod_def.getNodeMod(mod_def.getElem(i).iNode()), alpha,theta);
		Node n2 = project_ortho(mod_def.getNodeMod(mod_def.getElem(i).jNode()), alpha,theta);
		
//		DrawLine(img, n1.getX(),n1.getY(), n2.getX(),n2.getY(), mul,xoff,yoff);
		if(mod_def.getElem(i).getType() == "str"){ // disegna i nodi degli elementi strutturali
//			img.circ((int)(n1.getX()*mul)+xoff, -(int)(n1.getY()*mul)+yoff, 3);
//			img.circ((int)(n2.getX()*mul)+xoff, -(int)(n2.getY()*mul)+yoff, 3);
		}
	}
	
	
	
	// disegna gli assi:
//	Node zero, temp;
//	zero = project_ortho(Node(0,0,0), alpha,theta);
//	temp = project_ortho(Node(1,0,0), alpha,theta); img.penColor(255,0,0);
//	DrawLine(img, zero.getX(),zero.getY(), temp.getX(),temp.getY(), mul,xoff,yoff);
//	DrawText(img, temp.getX(),temp.getY(), "x", mul,xoff,yoff);
//	temp = project_ortho(Node(0,1,0), alpha,theta); img.penColor(0,255,0);
//	DrawLine(img, zero.getX(),zero.getY(), temp.getX(),temp.getY(), mul,xoff,yoff);
//	DrawText(img, temp.getX(),temp.getY(), "y", mul,xoff,yoff);
//	temp = project_ortho(Node(0,0,1), alpha,theta); img.penColor(0,0,255);
//	DrawLine(img, zero.getX(),zero.getY(), temp.getX(),temp.getY(), mul,xoff,yoff);
//	DrawText(img, temp.getX(),temp.getY(), "z", mul,xoff,yoff);
	
	/*
	img.penColor(150,150,150);
	sprintf(buf,"alpha = %3.1f\ntheta = %3.1f", alpha,theta);
	img.text(10,img.height()-30,buf,IBM_EGA_8x14);
	sprintf(buf,"(mul=%d; xoff=%d; yoff=%d)", mul,xoff,yoff);
	img.text(img.width()-8*strlen(buf)-10,img.height()-15,buf,IBM_EGA_8x14);
	*/
	
	sprintf(buf, "output/frames/frame%d.bmp", frame++);
//	img.save_bmp(buf);
	
	
}

	
	
	return 0;
}

// ------------------------------------------------------------------------------------------------------


Node project_ortho(Node node, double alpha, double theta, double scale)
{
	double a = alpha *PI/180;
	double t = theta *PI/180;
	
	Node temp = rotate(rotate(rotate(node, -PI/2,0,0), 0,-a,0), t,0,0); // ruota la visuale
	
	double x = (1/scale) * temp.getX();
	double y = (1/scale) * temp.getY();
	
	return Node(x,y);
}

Node project_ortho(Node node, double alpha, double theta)
{
	return project_ortho(node, alpha,theta, 1);
}


Node rotate(Node node, double rx, double ry, double rz)
{
	double x = (cos(ry)*cos(rz)) * node.getX() + (sin(rx)*sin(ry)*cos(rz)-cos(rx)*sin(rz)) * node.getY() + (cos(rx)*sin(ry)*cos(rz)+sin(rx)*sin(rz)) * node.getZ();
	double y = (cos(ry)*sin(rz)) * node.getX() + (sin(rx)*sin(ry)*sin(rz)+cos(rx)*cos(rz)) * node.getY() + (cos(rx)*sin(ry)*sin(rz)-sin(rx)*cos(rz)) * node.getZ();
	double z = (-sin(ry)) * node.getX() + (sin(rx)*cos(ry)) * node.getY() + (cos(rx)*cos(ry)) * node.getZ();
	
	return Node(x,y,z);
}


//void DrawLine(Image &img, double x1,double y1,double x2,double y2, int mul,int xoff,int yoff) {
//	img.line((int)(x1*mul)+xoff, -(int)(y1*mul)+yoff, (int)(x2*mul)+xoff, -(int)(y2*mul)+yoff);
//}
//
//void DrawText(Image &img, double x,double y, string str, int mul,int xoff,int yoff) {
//	img.text((int)(x*mul)+xoff, -(int)(y*mul)+yoff, str, IBM_EGA_8x14);
//}



Model loadModel(string fName)
{
	Model mod;
	ifstream file(fName);
	string str;
	vector<int> ID;
	vector<double> x, y, z;
	
	while(getline(file, str)){
		vector<string> strvec = splitTokens(deleteMultipleSpace(str), ' ');
		if(strvec.size() == 0) continue; // salta le righe vuote
		if(strvec[0] == "Node" && strvec.size() >= 5){
			ID.push_back(atoi(strvec[1].c_str()));
			 x.push_back(atof(strvec[2].c_str()));
			 y.push_back(atof(strvec[3].c_str()));
			 z.push_back(atof(strvec[4].c_str()));
		}
		if(strvec[0] == "Line" && strvec.size() >= 3){
			int n1 = atoi(strvec[1].c_str());
			int n2 = atoi(strvec[2].c_str());
			if(strvec.size() == 3) mod.addElem(n1, n2);
			else                   mod.addElem(n1, n2, strvec[3]);
		}
	}
	file.close();
	
	// carica i nodi in ordine crescente di ID (per fare scopa con il recorder OpenSees che salva in ordine crescente di ID):
//	auto p = sort_permutation(ID, [](double const& a, double const& b){ a < b; }); // crea la permutazione facendo il sorting del vettore "ID"
//	ID = apply_permutation(ID, p); // applica la permutazione a "ID"
//	x  = apply_permutation(x,  p); // applica la permutazione a "x"
//	y  = apply_permutation(y,  p); // applica la permutazione a "y"
//	z  = apply_permutation(z,  p); // applica la permutazione a "z"

	// Create an index vector:
	std::vector<size_t> idx(ID.size());
	for (size_t i=0; i<idx.size(); ++i) idx[i] = i;
    
	// Sort indices based on values in vector 'ID':
	std::sort(idx.begin(), idx.end(), [&ID](size_t i1, size_t i2) {
		return ID[i1] < ID[i2];
	});
	
	// aggiunge i nodi ordinati nel modello:
	for(size_t i : idx) mod.addNode(ID[i], x[i],y[i],z[i]);
	
	return mod;
}


Model loadDisplacements(Model m, string fName, double mul, int j)
{
	// modifica il modello "m" aggiungendo gli spostamenti dal file "fName" nella riga "j" scalati di "mul"
	// il file degli spostamenti deve avere una riga per ogni istante temporale
	// e per ogni colonna lo spostamento in x, y e z di ogni nodo del modello (la prima colonna e` il tempo)
	// ordinati in ordine crescente nello stesso ordine di definizione nel modello "m" (DA PROBLEMI SE NON DEFINISCO NODI CON ID CRESCENTE!!)
	// ordinati in ordine crescente di ID (come esce dal recorder) [loadModel assicura che gli ID sono crescenti]
	Model res;
	string str;
	ifstream file(fName);
	
	for(int i=0; i<j; i++) getline(file, str);
	file.close();
	
	vector<string> strvec = splitTokens(str,' ');
	if(strvec.size() != m.nNode()*3+1) cout << "ERRORE!: lettura file output: " << endl;
	
	for(int i=0; i<m.nNode(); i++){
		unsigned ID = m.getNode(i).getID();
		double x = m.getNode(i).getX() + mul*atof(strvec[i*3+1].c_str()); // il primo (la colonna 0) e` il tempo
		double y = m.getNode(i).getY() + mul*atof(strvec[i*3+2].c_str());
		double z = m.getNode(i).getZ() + mul*atof(strvec[i*3+3].c_str());
		res.addNode(ID, x,y,z);
	}
	
	for(int i=0; i<m.nElem(); i++){
		res.addElem(m.getElem(i).iNode(), m.getElem(i).jNode(), "str");
	}
	
	
	return res;
}



#endif // MRC_FEM_VIEWER
