#pragma once
class Node
{
	int pIndex;
	double x,y;
	string type;
public:
	Node(int index, double xCord, double yCord){
		pIndex = index; x = xCord; y = yCord;
   //   cout<<"point number "<<pIndex<<"is created with xCord "<<xCord<<" and yCord "<<yCord<<endl;
		type = "interiorNode";
	}
	double GetXcord(){ return x;}
	double GetYcord(){ return y;}
	void setAsBouNode(){ type = "ConsT";}
	void setAsCovecNode(){type = "Convec";}
	void setAsHfluxNode(){type = "HFlux";}
	string getNodeType(){return type;}
	int GetIndex(){return pIndex;}

};