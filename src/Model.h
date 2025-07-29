/*
	Classe che immagazzina in memoria i parametri del modello OpenSEES
*/
#ifndef MRC_OPENSEES_MODEL
#define MRC_OPENSEES_MODEL

#include <vector>


// ########################### NODE ###########################

class Node 
{
	public:
		Node(unsigned int ID, double x, double y, double z);
		Node(double x, double y, double z) : Node(0, x,y,z) {};
		Node(double x, double y) : Node(0, x,y,0) {};
		Node() : Node (0, 0,0,0) {};
//		Node(const Node& rhs) {	ID=rhs.getID(); x=rhs.getX(); y=rhs.getY(); z=rhs.getZ(); }; //copy constructor
		
//		Node& operator=(const Node& rhs);
		
		inline unsigned int getID() const{ return ID; }
		inline double getX() const{ return x; }
		inline double getY() const{ return y; }
		inline double getZ() const{ return z; }
		
		inline void setNode(double x,double y,double z){ this->x=x; this->y=y; this->z=z; }
		
	private:
		unsigned int ID; //il TAG di OpenSEES
		double x, y, z; //coordinate del nodo
};

Node::Node(unsigned int ID, double x, double y, double z)
{
	this->ID = ID;
	this->x = x;
	this->y = y;
	this->z = z;
}


// ########################### ELEMENT ###########################

class Element
{
	public:
		Element(unsigned int ID_i,unsigned int ID_j) : n1(ID_i), n2(ID_j), tipo("") {}
		Element(unsigned int ID_i,unsigned int ID_j,std::string type) : n1(ID_i), n2(ID_j), tipo(type) {}
		
		inline unsigned int iNode(){ return n1; }
		inline unsigned int jNode(){ return n2; }
		
		inline std::string getType(){ return tipo; }
		
	private:
		unsigned int n1, n2; //ID dei nodi di inizio e fine elemento (n1: nodo iniziale; n2: nodo finale)
		std::string tipo; //tiplogia di elemento (ad esempio "Two_NodeLink", "ElasticBeamColumn" etc.)
};



// ########################### MODEL ###########################


class Model
{
	public:
		Model();
		
		inline void addNode(unsigned int ID,double x,double y,double z){ nod.push_back(Node(ID,x,y,z)); }
		inline void addElem(unsigned int ID_i,unsigned int ID_j){ ele.push_back(Element(ID_i,ID_j)); }
		inline void addElem(unsigned int ID_i,unsigned int ID_j,std::string type){ ele.push_back(Element(ID_i,ID_j,type)); }
		
		inline int nNode(){ return nod.size(); }
		inline int nElem(){ return ele.size(); }
		
		inline Node    getNode(int id){ return nod[id]; } // segue la numerzione del vettore locale
		inline Element getElem(int id){ return ele[id]; } // segue la numerzione del vettore locale
		
		Node    getNodeMod(int tagID); // segue la numerzione del modello
//		Element getElemMod(lnt tagID); // segue la numerzione del modello
		
		inline void setNode(int id, double x,double y,double z){ nod[id].setNode(x,y,z); }
		void setNodeMod(int tagID, double x,double y,double z); // usa i tagID del modello
		
	private:
		std::vector<Node>    nod;
		std::vector<Element> ele;
		
};




// ########################### DEFINIZIONI ###########################

Model::Model()
{
	
}


Node Model::getNodeMod(int tagID)
{
	for(int i=0;i<nod.size();i++){
		if(nod[i].getID() == tagID){
			return nod[i];
		}
	}
}


void Model::setNodeMod(int tagID, double x,double y,double z)
{
	for(int i=0;i<nod.size();i++){
		if(nod[i].getID() == tagID){
			nod[i].setNode(x,y,z);
			return;
		}
	}
}





#endif
