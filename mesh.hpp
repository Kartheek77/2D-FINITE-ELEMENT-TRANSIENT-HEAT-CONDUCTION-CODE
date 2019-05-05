#pragma once
#include <bits/stdc++.h> 
#include <string> 
#include "elements.hpp"
#include "nodes.hpp"
#include "boundary.hpp"
#include "solver.hpp"
using namespace std;
class Mesh
{    TriElement **Ele;Node **Poi;BoundLineElement ***Bou;Solver *MySolver;
	int nElem,nPoin,nMark;
	double density,specificHeat,thickness,thermalConductivity,time,cfl;
	public:
		Mesh()
		{
			Ele = NULL;
			Poi = NULL;
			Bou = NULL;
		}
	//	int nElem,nPoin,nMark,density,specificHeat,thickness;
		int *NoOfEachMarkers;
		 vector <string> tokens;
		 vector <string> tokens1;
		 vector <string> tokens2;
		 vector <string> markers;
		void readMesh()
		{
			ifstream inf("mesh1.dat");
	        if (!inf)
			      {
			        cerr << "mesh.dat could not be opened for reading!" << endl;
			        exit(1);
			      }
	int countElements = 0,countPoints = 0,countMarkers=0,eleNum=0,firstIndex=0,secondIndex=0,thirdIndex=0,pIndex=0;
	double xCord=0,yCord=0;
			      
		    while (inf)
		    {
		        std::string line;
		        getline(inf, line);
              //cout << line <<endl;
									  	   
				    stringstream check1(line);     
				    string intermediate;
				    while(getline(check1, intermediate, ' '))
				    { 
				        tokens.push_back(intermediate);
				    }												    
			    if(tokens[0]=="nElem") {  
				    	nElem = 0;
			        stringstream geek(tokens[tokens.size()-1]);		    
				   geek >> nElem;
				   Ele = new TriElement*[nElem+1];
                 countElements=1;
				}
				if(tokens[0]=="5e"){
         	eleNum=0;firstIndex=0;secondIndex=0;thirdIndex=0;
         	stringstream geek1(tokens[1]);
         	geek1 >> eleNum;
         	stringstream geek2(tokens[2]);
         	geek2 >> firstIndex;
         	stringstream geek3(tokens[3]);
         	geek3 >> secondIndex;
         	stringstream geek4(tokens[4]);
         	geek4 >> thirdIndex;
				Ele[eleNum] = new TriElement(eleNum,firstIndex,secondIndex,thirdIndex);
				countElements+=1;
				   } 
					if(tokens[0]=="nPoin") {  
				    	nPoin = 0;
			        stringstream geek(tokens[tokens.size()-1]);		    
				   geek >> nPoin;
				   Poi = new Node*[nPoin+1];
				}

			if(tokens[0]=="Poi"){
         	pIndex=0;xCord=0;yCord=0;
         	stringstream geek5(tokens[1]);
         	geek5 >> pIndex;
         	stringstream geek6(tokens[2]);
         	geek6 >> xCord;
         	stringstream geek7(tokens[3]);
         	geek7 >> yCord;
				Poi[pIndex] = new Node(pIndex,xCord,yCord);
				countPoints+=1;
				   }
			if(tokens[0]=="density")
				{density=0;
					stringstream geek8(tokens[tokens.size()-1]);		    
				   geek8 >> density;}
			if(tokens[0]=="specificHeat")
				{specificHeat=0;
					stringstream geek9(tokens[tokens.size()-1]);		    
				   geek9 >> specificHeat;}
			if(tokens[0]=="thickness")
			    {thickness=0;
					stringstream geek10(tokens[tokens.size()-1]);		    
				   geek10 >> thickness;}
            
            if(tokens[0]=="thermalConductivity")
			    {thermalConductivity=0;
					stringstream geek17(tokens[tokens.size()-1]);		    
				   geek17 >> thermalConductivity;}

		    if(tokens[0]=="time")
			    {time=0;
					stringstream geek18(tokens[tokens.size()-1]);		    
				   geek18 >> time;}

			 if(tokens[0]=="cfl")
			    {cfl=0;
					stringstream geek18(tokens[tokens.size()-1]);		    
				   geek18 >> cfl;}	   
				   	


			if(tokens[0]=="nMark") {  
				    	nMark = 0;
			        stringstream geek11(tokens[tokens.size()-1]);		    
				   geek11 >> nMark;
				  Bou = new BoundLineElement**[nMark];
				  NoOfEachMarkers = new int[nMark];
				  
				}

					if((tokens[0]=="Marker_Tag_"))
                   
		    	{     markers.push_back(tokens[tokens.size()-1]);	
		    		
				}	   
                 
				 tokens.clear();   
			}

		   //inf.close();
		    cout<<"number of elements in the mesh is "<<nElem<<endl;  
		    cout<<"number of points in the mesh is "<<nPoin<<endl;
		    cout<<"specificHeat is "<<specificHeat<<endl;
		    cout<<"density is "<<density<<endl;
		    cout<<"thickness is "<<thickness<<endl;
		    cout<<"thermalConductivity is "<<thermalConductivity<<endl;
		    cout<<"number of boundary markers are "<<nMark<<endl;
		   for(int i=0;i<nMark;i++) cout<<markers[i]<<endl;
		   	//for(int i=0;i<nMark;i++) *boundaryMarkers[countMarkers+1]<<endl;
		   	int *countEachMarker;
		   countEachMarker = new int[nMark];
		   	for(int i=0;i<nMark;i++) countEachMarker[i]=0;
		   	int tempCountMarker=0;
		   	
		   	ifstream inf1("mesh1.dat");	       
            while (inf1)
		    {
		        std::string line;
		        getline(inf1, line);
		        stringstream check2(line);     
				    string intermediate;
				    while(getline(check2, intermediate, ' '))
				    { 
				        tokens1.push_back(intermediate);
				    }

				    if((countMarkers<nMark)&&(tokens1[0]==("n"+markers[countMarkers]))) { 
				    cout<<countMarkers<<endl; 
				    	cout<<"n"+markers[countMarkers]<<endl;
				    	NoOfEachMarkers[countMarkers] = 0;
			        stringstream geek(tokens1[tokens1.size()-1]);		    
				   geek >> NoOfEachMarkers[countMarkers];				  
				  Bou[countMarkers] = new BoundLineElement*[NoOfEachMarkers[countMarkers]];
				  tempCountMarker = countMarkers;
				   countMarkers+=1;
				}
				tokens1.clear();
			}


			/*	if((tokens1[0]==markers[tempCountMarker])&&(countEachMarker[tempCountMarker]<NoOfEachMarkers[tempCountMarker])){

					int tempfirstindex=0,tempsecondindex=0;
					stringstream geek13(tokens1[2]);
		         	geek13 >> tempfirstindex;
		         	stringstream geek14(tokens1[3]);
		         	geek14 >> tempsecondindex;
		         	Bou[countMarkers][countEachMarker[tempCountMarker]] = new BoundLineElement(tempfirstindex,tempsecondindex);
                    countEachMarker[tempCountMarker]+=1;
  
				}       */
				countMarkers = 0;   
				ifstream inf2("mesh1.dat");	       
            while (inf2)
		    {
		        std::string line;
		        getline(inf2, line);
		        stringstream check3(line);     
				    string intermediate;
				    while(getline(check3, intermediate, ' '))
				    { 
				        tokens2.push_back(intermediate);
				    }
				  //  if((tokens1[0]==markers[tempCountMarker])&&(countEachMarker[tempCountMarker]<NoOfEachMarkers[tempCountMarker]))

                    if(tokens2[0]==markers[countMarkers])
				    {

					int tempfirstindex=0,tempsecondindex=0; double tempTemperature1=0,tempTemperature2=0,Conveccoef=0,ConvecTemp=0,heatflux=0;
			if(tokens2[4]=="ConsT"){
					stringstream geek13(tokens2[2]);
		         	geek13 >> tempfirstindex;
		         	stringstream geek14(tokens2[3]);
		         	geek14 >> tempsecondindex;
		         	stringstream geek15(tokens2[5]);
		         	geek15 >> tempTemperature1;
		         	stringstream geek16(tokens2[6]);
		         	geek16 >> tempTemperature2;
 Bou[countMarkers][countEachMarker[countMarkers]] = new BoundLineElement(tempfirstindex,tempsecondindex,tokens2[4],tempTemperature1,tempTemperature2);}
 if(tokens2[4]=="Convec"){
 	                stringstream geek13(tokens2[2]);
		         	geek13 >> tempfirstindex;
		         	stringstream geek14(tokens2[3]);
		         	geek14 >> tempsecondindex;
		         	stringstream geek15(tokens2[5]);
		         	geek15 >> Conveccoef;
		         	stringstream geek16(tokens2[6]);
		         	geek16 >> ConvecTemp;
Bou[countMarkers][countEachMarker[countMarkers]] = new BoundLineElement(tempfirstindex,tempsecondindex,Conveccoef,ConvecTemp,tokens2[4]);
 }
if(tokens2[4]=="HFlux"){ 
					stringstream geek13(tokens2[2]);
		         	geek13 >> tempfirstindex;
		         	stringstream geek14(tokens2[3]);
		         	geek14 >> tempsecondindex;
		         	stringstream geek15(tokens2[5]);
		         	geek15 >> heatflux;
Bou[countMarkers][countEachMarker[countMarkers]] = new BoundLineElement(tempfirstindex,tempsecondindex,tokens2[4],heatflux);

}

                    countEachMarker[countMarkers]+=1;
                    if(countEachMarker[countMarkers]==NoOfEachMarkers[tempCountMarker]) countMarkers+=1;
  
				}


             tokens2.clear();
		    }     

		 for(int i=0;i<nMark;i++) cout<<"number of elements in each boundary markers are "<<NoOfEachMarkers[i]<<endl;  
        // int countEachMarker[nMark]={0};

		   
		}

       void prepareElements(){
       	for(int i=1;i<=nElem;i++)
          {
          	Ele[i]->setElementCordinates(Poi[Ele[i]->GetFirstIndex()]->GetXcord(),
          		                         Poi[Ele[i]->GetFirstIndex()]->GetYcord(),
          		                         Poi[Ele[i]->GetSecondIndex()]->GetXcord(),
          		                         Poi[Ele[i]->GetSecondIndex()]->GetYcord(),
          		                         Poi[Ele[i]->GetThirdIndex()]->GetXcord(),
          		                         Poi[Ele[i]->GetThirdIndex()]->GetYcord()  
          		                         );
          	Ele[i]->setArea();
          	Ele[i]->setConstants(density,specificHeat,thickness,thermalConductivity);
          	Ele[i]->setElementMatrices();	
          	// Ele[i]->roughwork();                                
          }

          for(int i=0;i<nMark;i++){
	for(int j=0;j<NoOfEachMarkers[i];j++){
		Bou[i][j]->setBouElemCoordinates(Poi[Bou[i][j]->GetFirstIndex()]->GetXcord(),
											   Poi[Bou[i][j]->GetFirstIndex()]->GetYcord(),
											   Poi[Bou[i][j]->GetSecondIndex()]->GetXcord(),
											   Poi[Bou[i][j]->GetSecondIndex()]->GetYcord());
		Bou[i][j]->setLengthAndProperties();
		
	}
}
         //cout<<Ele[i]->Getfirstindex( )<<endl;
         // Ele[1]->roughwork();
  // cout<<(Poi[Ele[1]->GetFirstIndex()]->GetXcord())<<" "<<(Poi[Ele[1]->GetFirstIndex()]->GetYcord())<<" "<<endl;
  // cout<<(Poi[Ele[1]->GetSecondIndex()]->GetXcord())<<" "<<(Poi[Ele[1]->GetSecondIndex()]->GetYcord())<<" "<<endl;
  // cout<<(Poi[Ele[1]->GetThirdIndex()]->GetXcord())<<" "<<(Poi[Ele[1]->GetThirdIndex()]->GetYcord())<<" "<<endl;
          		                        
         // for(int i=0;i<3;i++){ for(int j=0;j<3;j++) {cout<<Ele[1]->GetConductionMatrix(i,j)<<" ";} cout<<endl;}
       }

       void solVe(){

        MySolver = new Solver(Ele,Poi,Bou,nPoin,nElem,nMark,density,specificHeat,thermalConductivity,thickness,NoOfEachMarkers,time,cfl);
        MySolver->assemble();
        MySolver->SetMinTimeStepValue();
        MySolver->Correction();
        MySolver->Initialize();
        MySolver->Iterate();


       }

};