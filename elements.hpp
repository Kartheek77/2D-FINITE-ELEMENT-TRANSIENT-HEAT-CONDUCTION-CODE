#pragma once
#include "nodes.hpp"
class TriElement
{
   int eleNumber,firstindex,secondindex,thirdindex;
   double Area,x1,x2,x3,y1,y2,y3,conductionMatrix[3][3],capacitanceMatrix[3][3],bMatrix[2][3],TransbMatrix[3][2];
   Node *node1,*node2,*node3;
   double density,specificHeat,thickness,thermalConductivity;
public:
	TriElement(int eleNum,int x, int y,int z)
	{
		eleNumber = eleNum; firstindex = x; secondindex = y; thirdindex = z;
	//	cout<<" element number "<<eleNumber<<"is created with firstindex "<<firstindex<<" secondindex "<<secondindex<<" thirdindex "<<thirdindex<<endl;   
	}
	int GetFirstIndex(){return firstindex;}
	int GetSecondIndex(){return secondindex;}
	int GetThirdIndex(){return thirdindex;}
	
      
    void setElementCordinates(double X1, double Y1, double X2, double Y2, double X3, double Y3){
      x1=X1;x2=X2;x3=X3;
      y1=Y1;y2=Y2;y3=Y3;             
	}
	void setArea(){
      Area = 0.5*((x1*(y2-y3))-(y1*(x2-x3))+((x2*y3-x3*y2)));
     // cout<< "element number "<<eleNumber<<" with "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<x3<<" "<<y3<<" with area "<<Area<<endl;  
	}
	void setConstants(double x,double y,double z,double p)
	{
		density= x; specificHeat= y; thickness= z; thermalConductivity=p;
	}  
	void setElementMatrices(){
     for(int i=0;i<3;i++) for(int j=0;j<3;j++) {conductionMatrix[i][j] = 0;capacitanceMatrix[i][j] = 0;}
     for(int i=0;i<2;i++) for(int j=0;j<3;j++)  {bMatrix[i][j]=0;TransbMatrix[j][i]=0;}	
     bMatrix[0][0] = y2-y3;  bMatrix[0][1] = y3-y1;  bMatrix[0][2] = y1-y2;
    bMatrix[1][0] = x3-x2;  bMatrix[1][1] = x1-x3;   bMatrix[1][2] = x2-x1;
   // double bMatrix[2][3]= {{y2-y3,y3-y1,y1-y2},{x3-x2,x1-x3,x2-x1}};
   // double TransbMatrix[3][2];
     for(int i=0;i<2;i++) for(int j=0;j<3;j++) 
     {bMatrix[i][j]*=(0.5/Area); }
 for(int i=0;i<3;i++) for(int j=0;j<2;j++) 
       {TransbMatrix[i][j] = bMatrix[j][i]; }
     for(int i=0;i<3;i++) for(int j=0;j<3;j++) for(int k=0;k<2;k++) conductionMatrix[i][j]+=(TransbMatrix[i][k]*bMatrix[k][j]);
     for(int i=0;i<3;i++) for(int j=0;j<3;j++) conductionMatrix[i][j]*=(Area*thermalConductivity*thickness);
     for(int i=0;i<3;i++) for(int j=0;j<3;j++) {if(i==j) capacitanceMatrix[i][j]=2; else capacitanceMatrix[i][j]=1;}
     for(int i=0;i<3;i++) for(int j=0;j<3;j++) capacitanceMatrix[i][j]*= (density*specificHeat*thickness*Area/12);
     //	cout<<"conductionMatrix[0][0] of eleNumber "<<eleNumber<<" is "<<conductionMatrix[0][0]<<endl;
	}

    double GetConductionMatrix(int temp1,int temp2){return conductionMatrix[temp1][temp2];}
	double GetCapacitanceMatrix(int temp1,int temp2){return capacitanceMatrix[temp1][temp2];}
    void roughwork(){
    /*	cout<<"The bMatrix of "<<eleNumber<<" is "<<endl;
    	for(int i=0;i<2;i++) {for(int j=0;j<3;j++) cout<<bMatrix[i][j]<<" "; cout<<endl;}
    	cout<<"The TransbMatrix of "<<eleNumber<<" is "<<endl; 
        for(int i=0;i<3;i++) {for(int j=0;j<2;j++) cout<<TransbMatrix[i][j]<<" "; cout<<endl;}*/
        cout<<"capacitanceMatrix of element "<<eleNumber<<endl; 
        for(int i=0;i<3;i++) {for(int j=0;j<3;j++) cout<<conductionMatrix[i][j]<<" ";cout<<endl;}
     
    }


};