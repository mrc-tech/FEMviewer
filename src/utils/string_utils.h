#ifndef MRC_UTILS
#define MRC_UTILS

#include <vector>
#include <string>



std::vector<std::string> splitTokens(std::string str,char c)
{
	std::vector<std::string> res;
	std::string temp;
	
	for(int i=0;i<str.length();i++)
	{
		if(str[i] == c){
			res.push_back(temp);
			temp.clear();
		} else {
			temp = temp + str[i];
		}
	}
	//aggiunge l'ultimo
	if(temp != "") res.push_back(temp);
	
	return res;
}



std::string deleteChar(std::string str, char c)
{
	// elimina un determinato carattere dalla stringa
	std::string res;
	
	for(int i=0;i<str.length();i++)	if(str[i]!=c) res.push_back(str[i]);
	
	return res;
}


std::string deleteMultipleSpace(std::string str)
{
	//elimina gli spazi consecutivi facendoli diventare uno solo
	
	bool foundSpace = false;
	std::string res;
	
	for(int i=0;i<str.length();i++){
		if(str[i]==' '){
			//ha incontrato uno spazio
			if(!foundSpace){
				foundSpace = true;
				res = res + str[i];
			}
		}else{
			foundSpace = false;
			res = res + str[i];
		}
	}
	
	return res;
}



std::string deleteMultipleChar(std::string str, char c)
{
	//elimina caratteri consecutivi facendoli diventare uno solo
	
	bool foundChar = false;
	std::string res;
	
	for(int i=0;i<str.length();i++){
		if(str[i]==c){
			//ha incontrato uno spazio
			if(!foundChar){
				foundChar = true;
				res = res + str[i];
			}
		}else{
			foundChar = false;
			res = res + str[i];
		}
	}
	
	return res;
}


std::string deleteInitialSpace(std::string str)
{
	if(str[0]==' '){
		//il primo elemento � uno spazio e non lo considera
		str.erase(0,1); //elimina 1 carattere partendo dall'indice 0
		return str;
	}else{
		//non ci sono spazi iniziali e ritorna la stringa cos� com'�
		return str;
	}
}


std::string deleteChars(std::string str, int first, int last)
{
	//elimina i caratteri iniziali e finali
	std::string res;
	
	if(str.size()-last <= first) return str; //controllo
	for(int i=first;i<str.size()-last;i++){
		res = res + str[i];
	}
	
	return res;
}



std::string changeChars(std::string str, char src, char dest)
{
	// cambia i caratteri "src" in "dest"
	for(int i=0; i<str.length(); i++) if(str[i] == src) str[i] = dest;
	return str;
}


bool contiene(std::string str, char c)
{
	// ritorna VERO se la stringa str contiene il carattere c
	for(int i=0; i<str.length(); i++) if(str[i] == c) return true;
	return false;
}





#endif
