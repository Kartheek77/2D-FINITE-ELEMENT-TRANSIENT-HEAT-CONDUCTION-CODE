#pragma once
#include <bits/stdc++.h> 
class Solver{
	TriElement **EleSolver=NULL;Node **PoiSolver=NULL;BoundLineElement ***BouSolver=NULL;
	double **assembledCapacitanceMatrix, **assembledConductionMatrix;
	double* assembledRHSMatrix;
	int nPoin,nElem,nMark, *NoOfEachMarkers,numberOfSteps,numberOfConsT,*non_consTindex,*consTindex;
    double density,specificHeat,thermalConductivity,thickness,minTimeStepValue,lastTimeStep,time,cfl;
    double *solution,**equationRhsMatrix,**preConditionerMatrix,*solutiontemp,*consTvector,*solutiontemp1;
    double *reduced_solution,**reduced_preConditionerMatrix, **reduced_equationRhsMatrix, **Lmatrix,**Umatrix;
    double *forwardSubMatrix,*backwardSubMatrix;
    
	public:
	Solver(TriElement **EleSolver,
		         Node **PoiSolver,
		         BoundLineElement ***BouSolver,
		         int nPoin,
		         int nElem,
		         int nMark,
		         double density,
		         double specificHeat,
		         double thermalConductivity,
		         double thickness,
		         int *NoOfEachMarkers,
		         double time,
		         double cfl)

	{   this->EleSolver=EleSolver;
		this->PoiSolver=PoiSolver;
		this->BouSolver=BouSolver;
        this->nPoin=nPoin;
        this->nElem=nElem;
        this->nMark=nMark;
        this->density=density;
        this->specificHeat=specificHeat;
        this->thermalConductivity=thermalConductivity;
        this->thickness=thickness;
        this->NoOfEachMarkers = NoOfEachMarkers;
        this->time = time;
        this->cfl = cfl;

        numberOfConsT = 0;
        assembledCapacitanceMatrix =new double* [nPoin];
        for(int i=0;i<nPoin;i++) assembledCapacitanceMatrix[i] = new double[nPoin];
        for(int i=0;i<nPoin;i++) for(int j=0;j<nPoin;j++) assembledCapacitanceMatrix[i][j]=0;	
        assembledConductionMatrix = new double* [nPoin];
        for(int i=0;i<nPoin;i++) assembledConductionMatrix[i] = new double[nPoin];
        for(int i=0;i<nPoin;i++) for(int j=0;j<nPoin;j++) assembledConductionMatrix[i][j]=0;	
        assembledRHSMatrix = new double[nPoin];
        for(int i=0;i<nPoin;i++)  assembledRHSMatrix[i] = 0;

	//	cout<<"first index of 18th element is "<<EleSolver[18]->GetFirstIndex()<<
	//" and its x,y coordinate is given by "<<PoiSolver[EleSolver[18]->GetFirstIndex()]->GetXcord()<<" , "<<PoiSolver[EleSolver[18]->GetFirstIndex()]->GetYcord()<<endl;
		cout<<"hurray solver class is created"<<endl;
	}

	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void assemble(){
	//	cout<<"EleSolver[1]->GetConductionMatrix(0,0) "<<EleSolver[1]->GetConductionMatrix(0,0)<<endl;
		
 for(int i=1;i<=nElem;i++) {
assembledConductionMatrix[(EleSolver[i]->GetFirstIndex())-1][(EleSolver[i]->GetFirstIndex())-1] += EleSolver[i]->GetConductionMatrix(0,0);
assembledConductionMatrix[(EleSolver[i]->GetFirstIndex())-1][(EleSolver[i]->GetSecondIndex())-1] += EleSolver[i]->GetConductionMatrix(0,1);
assembledConductionMatrix[(EleSolver[i]->GetFirstIndex())-1][(EleSolver[i]->GetThirdIndex())-1] += EleSolver[i]->GetConductionMatrix(0,2);

assembledConductionMatrix[(EleSolver[i]->GetSecondIndex())-1][(EleSolver[i]->GetFirstIndex())-1] += EleSolver[i]->GetConductionMatrix(1,0);
assembledConductionMatrix[(EleSolver[i]->GetSecondIndex())-1][(EleSolver[i]->GetSecondIndex())-1] += EleSolver[i]->GetConductionMatrix(1,1);
assembledConductionMatrix[(EleSolver[i]->GetSecondIndex())-1][(EleSolver[i]->GetThirdIndex())-1] += EleSolver[i]->GetConductionMatrix(1,2);

assembledConductionMatrix[(EleSolver[i]->GetThirdIndex())-1][(EleSolver[i]->GetFirstIndex())-1] += EleSolver[i]->GetConductionMatrix(2,0);
assembledConductionMatrix[(EleSolver[i]->GetThirdIndex())-1][(EleSolver[i]->GetSecondIndex())-1] += EleSolver[i]->GetConductionMatrix(2,1);
assembledConductionMatrix[(EleSolver[i]->GetThirdIndex())-1][(EleSolver[i]->GetThirdIndex())-1] += EleSolver[i]->GetConductionMatrix(2,2);

    }

for(int i=1;i<=nElem;i++) {
assembledCapacitanceMatrix[(EleSolver[i]->GetFirstIndex())-1][(EleSolver[i]->GetFirstIndex())-1] += EleSolver[i]->GetCapacitanceMatrix(0,0);
assembledCapacitanceMatrix[(EleSolver[i]->GetFirstIndex())-1][(EleSolver[i]->GetSecondIndex())-1] += EleSolver[i]->GetCapacitanceMatrix(0,1);
assembledCapacitanceMatrix[(EleSolver[i]->GetFirstIndex())-1][(EleSolver[i]->GetThirdIndex())-1] += EleSolver[i]->GetCapacitanceMatrix(0,2);

assembledCapacitanceMatrix[(EleSolver[i]->GetSecondIndex())-1][(EleSolver[i]->GetFirstIndex())-1] += EleSolver[i]->GetCapacitanceMatrix(1,0);
assembledCapacitanceMatrix[(EleSolver[i]->GetSecondIndex())-1][(EleSolver[i]->GetSecondIndex())-1] += EleSolver[i]->GetCapacitanceMatrix(1,1);
assembledCapacitanceMatrix[(EleSolver[i]->GetSecondIndex())-1][(EleSolver[i]->GetThirdIndex())-1] += EleSolver[i]->GetCapacitanceMatrix(1,2);

assembledCapacitanceMatrix[(EleSolver[i]->GetThirdIndex())-1][(EleSolver[i]->GetFirstIndex())-1] += EleSolver[i]->GetCapacitanceMatrix(2,0);
assembledCapacitanceMatrix[(EleSolver[i]->GetThirdIndex())-1][(EleSolver[i]->GetSecondIndex())-1] += EleSolver[i]->GetCapacitanceMatrix(2,1);
assembledCapacitanceMatrix[(EleSolver[i]->GetThirdIndex())-1][(EleSolver[i]->GetThirdIndex())-1] += EleSolver[i]->GetCapacitanceMatrix(2,2);

    }
for(int i=0;i<nMark;i++){
	for(int j=0;j<NoOfEachMarkers[i];j++){
		assembledRHSMatrix[(BouSolver[i][j]->GetFirstIndex())-1] += BouSolver[i][j]->GetboundaryMatrix(0,0);
		assembledRHSMatrix[(BouSolver[i][j]->GetSecondIndex())-1] += BouSolver[i][j]->GetboundaryMatrix(1,0);
		if((BouSolver[i][j]->GetBoundaryType())=="ConsT") numberOfConsT += 1;
assembledConductionMatrix[(BouSolver[i][j]->GetFirstIndex())-1][(BouSolver[i][j]->GetFirstIndex())-1] += BouSolver[i][j]->GetboundaryConvecMatrix(0,0);
assembledConductionMatrix[(BouSolver[i][j]->GetFirstIndex())-1][(BouSolver[i][j]->GetSecondIndex())-1] += BouSolver[i][j]->GetboundaryConvecMatrix(0,1);
assembledConductionMatrix[(BouSolver[i][j]->GetSecondIndex())-1][(BouSolver[i][j]->GetFirstIndex())-1] += BouSolver[i][j]->GetboundaryConvecMatrix(1,0);
assembledConductionMatrix[(BouSolver[i][j]->GetSecondIndex())-1][(BouSolver[i][j]->GetSecondIndex())-1] += BouSolver[i][j]->GetboundaryConvecMatrix(1,1);
	}
}
/*cout<<" assembledCapacitanceMatrix "<<endl;
for(int i=0;i<nPoin;i++) {for(int j=0;j<nPoin;j++) cout<<assembledCapacitanceMatrix[i][j]<<" "; cout<<endl;}
cout<<" assembledConductionMatrix "<<endl;
for(int i=0;i<nPoin;i++) {for(int j=0;j<nPoin;j++) cout<<assembledConductionMatrix[i][j]<<" "; cout<<endl;} */

	}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void SetMinTimeStepValue(){
//time step for Crank-Nicolson Method
    minTimeStepValue = 0; double tempForSwap,firstElementTimeStep,x1,y1,x2,y2,x3,y3,Cx,Cy,distFromC1,distFromC2,distFromC3,characteristicLength;
   
   {
   	int i =1;
   	characteristicLength = 0;
             	 x1 = PoiSolver[EleSolver[i]->GetFirstIndex()]->GetXcord();
                 y1 = PoiSolver[EleSolver[i]->GetFirstIndex()]->GetYcord();
                 x2 = PoiSolver[EleSolver[i]->GetSecondIndex()]->GetXcord();
                 y2 = PoiSolver[EleSolver[i]->GetSecondIndex()]->GetYcord();
                 x3 = PoiSolver[EleSolver[i]->GetThirdIndex()]->GetXcord();
                 y3 = PoiSolver[EleSolver[i]->GetThirdIndex()]->GetYcord(); 
                 Cx=(x1+x2+x3)/3; Cy=(y1+y2+y3)/3;
                 distFromC1 = (((Cx-x1)*(Cx-x1))+((Cy-y1)*(Cx-y1)));
                 distFromC2 = (((Cx-x2)*(Cx-x2))+((Cy-y2)*(Cx-y2)));
                 distFromC3 = (((Cx-x3)*(Cx-x3))+((Cy-y3)*(Cx-y3)));
    if(distFromC1 > distFromC2){if(distFromC1 > distFromC3) characteristicLength = distFromC1; else characteristicLength = distFromC3;}
    else{if(distFromC2 > distFromC3) characteristicLength = distFromC2; else characteristicLength = distFromC3;}
    minTimeStepValue = characteristicLength;
}

  	for(int i=2;i<=nElem;i++){
             	characteristicLength = 0;
             	 x1 = PoiSolver[EleSolver[i]->GetFirstIndex()]->GetXcord();
                 y1 = PoiSolver[EleSolver[i]->GetFirstIndex()]->GetYcord();
                 x2 = PoiSolver[EleSolver[i]->GetSecondIndex()]->GetXcord();
                 y2 = PoiSolver[EleSolver[i]->GetSecondIndex()]->GetYcord();
                 x3 = PoiSolver[EleSolver[i]->GetThirdIndex()]->GetXcord();
                 y3 = PoiSolver[EleSolver[i]->GetThirdIndex()]->GetYcord(); 
                 Cx=(x1+x2+x3)/3; Cy=(y1+y2+y3)/3;
                 distFromC1 = (((Cx-x1)*(Cx-x1))+((Cy-y1)*(Cx-y1)));
                 distFromC2 = (((Cx-x2)*(Cx-x2))+((Cy-y2)*(Cx-y2)));
                 distFromC3 = (((Cx-x3)*(Cx-x3))+((Cy-y3)*(Cx-y3)));
    if(distFromC1 > distFromC2){if(distFromC1 > distFromC3) characteristicLength = distFromC1; else characteristicLength = distFromC3;}
    else{if(distFromC2 > distFromC3) characteristicLength = distFromC2; else characteristicLength = distFromC3;}
     
     if(minTimeStepValue > characteristicLength) minTimeStepValue = characteristicLength;
  	}
 //cout<<"minTimeStepValue before is "<<minTimeStepValue<<endl;
  	
  	minTimeStepValue /= (6*thermalConductivity/(density*specificHeat));

  	minTimeStepValue *= cfl ;

  	cout<<"minTimeStepValue after is "<<minTimeStepValue<<endl;
  	  }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Correction(){

   for(int i=0;i<nMark;i++)
	for(int j=0;j<NoOfEachMarkers[i];j++)
	{
		if((BouSolver[i][j]->GetBoundaryType()) == "ConsT"){
				PoiSolver[(BouSolver[i][j]->GetFirstIndex())]->setAsBouNode();
				PoiSolver[(BouSolver[i][j]->GetSecondIndex())]->setAsBouNode();
		}}


	for(int i=0;i<nMark;i++)
	for(int j=0;j<NoOfEachMarkers[i];j++)
	{
if((BouSolver[i][j]->GetBoundaryType()) == "Convec"){
	if((PoiSolver[(BouSolver[i][j]->GetFirstIndex())]->getNodeType())!="ConsT") PoiSolver[(BouSolver[i][j]->GetFirstIndex())]->setAsCovecNode();
	if((PoiSolver[(BouSolver[i][j]->GetSecondIndex())]->getNodeType())!="ConsT") PoiSolver[(BouSolver[i][j]->GetSecondIndex())]->setAsCovecNode();
		}
		if((BouSolver[i][j]->GetBoundaryType()) == "HFlux"){
 if((PoiSolver[(BouSolver[i][j]->GetFirstIndex())]->getNodeType())!="ConsT") PoiSolver[(BouSolver[i][j]->GetFirstIndex())]->setAsHfluxNode();
 if((PoiSolver[(BouSolver[i][j]->GetSecondIndex())]->getNodeType())!="ConsT") PoiSolver[(BouSolver[i][j]->GetSecondIndex())]->setAsHfluxNode();
		}

	}
numberOfConsT = 0;
for(int i=0;i<nPoin;i++) {
     if((PoiSolver[i+1]->getNodeType())=="ConsT"){numberOfConsT+=1;}}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

  void Initialize()
  {  solution = new double[nPoin];
  	 solutiontemp = new double[nPoin];
  	 solutiontemp1 = new double[nPoin];
  	for(int i=0;i<nPoin;i++) {solution[i] = 0;solutiontemp[i] = 0;solutiontemp1[i] = 0;}

  	 equationRhsMatrix = new double*[nPoin];
  	for(int i=0;i<nPoin;i++) equationRhsMatrix[i] = new double[nPoin];
  	for(int i=0;i<nPoin;i++) for(int j=0;j<nPoin;j++)  equationRhsMatrix[i][j] = 0;	
  		preConditionerMatrix = new double* [nPoin];
  	for(int i=0;i<nPoin;i++) preConditionerMatrix[i] = new double[nPoin];
  	for(int i=0;i<nPoin;i++) for(int j=0;j<nPoin;j++)  preConditionerMatrix[i][j] = 0;
    
    reduced_solution = new double[(nPoin-numberOfConsT)];
  	for(int i=0;i<(nPoin-numberOfConsT);i++) reduced_solution[i] = 0;
   
    reduced_equationRhsMatrix = new double*[(nPoin-numberOfConsT)];
  	for(int i=0;i<(nPoin-numberOfConsT);i++) reduced_equationRhsMatrix[i] = new double[nPoin-numberOfConsT];
    for(int i=0;i<(nPoin-numberOfConsT);i++) for(int j=0;j<(nPoin-numberOfConsT);j++)  reduced_equationRhsMatrix[i][j] = 0;	

  	reduced_preConditionerMatrix = new double* [nPoin-numberOfConsT];
  	for(int i=0;i<(nPoin-numberOfConsT);i++) reduced_preConditionerMatrix[i] = new double[nPoin-numberOfConsT];
  	for(int i=0;i<(nPoin-numberOfConsT);i++) for(int j=0;j<(nPoin-numberOfConsT);j++)  reduced_preConditionerMatrix[i][j] = 0;

    forwardSubMatrix = new double[(nPoin-numberOfConsT)];
	backwardSubMatrix = new double[(nPoin-numberOfConsT)];
	non_consTindex = new int[(nPoin-numberOfConsT)];
	consTindex = new int[numberOfConsT];
	consTvector = new double[numberOfConsT];
    for(int i=0;i<(nPoin-numberOfConsT);i++){forwardSubMatrix[i]=0;backwardSubMatrix[i]=0;}

  	Lmatrix = new double* [nPoin-numberOfConsT];
    Umatrix = new double* [nPoin-numberOfConsT];
  	for(int i=0;i<(nPoin-numberOfConsT);i++) 
  		{Lmatrix[i] = new double[nPoin-numberOfConsT];
  		 Umatrix[i] = new double[nPoin-numberOfConsT];	
  		}
  	for(int i=0;i<(nPoin-numberOfConsT);i++) for(int j=0;j<(nPoin-numberOfConsT);j++) 
  		{ Lmatrix[i][j] = 0; Umatrix[i][j] = 0;}




  	for(int i=0;i<nMark;i++)
	for(int j=0;j<NoOfEachMarkers[i];j++)
	{
		if((BouSolver[i][j]->GetBoundaryType()) == "ConsT"){
				solution[(BouSolver[i][j]->GetFirstIndex())-1] = BouSolver[i][j]->GetTemperature1();
				solution[(BouSolver[i][j]->GetSecondIndex())-1] = BouSolver[i][j]->GetTemperature2();
			//	PoiSolver[(BouSolver[i][j]->GetFirstIndex())]->setAsBouNode();
			//	PoiSolver[(BouSolver[i][j]->GetSecondIndex())]->setAsBouNode();
		}
		

	}

/*for(int i=0;i<nMark;i++)
	for(int j=0;j<NoOfEachMarkers[i];j++)
	{
if((BouSolver[i][j]->GetBoundaryType()) == "Convec"){
	if((PoiSolver[(BouSolver[i][j]->GetFirstIndex())]->getNodeType())!="ConsT") PoiSolver[(BouSolver[i][j]->GetFirstIndex())]->setAsCovecNode();
	if((PoiSolver[(BouSolver[i][j]->GetSecondIndex())]->getNodeType())!="ConsT") PoiSolver[(BouSolver[i][j]->GetSecondIndex())]->setAsCovecNode();
		}
		if((BouSolver[i][j]->GetBoundaryType()) == "HFlux"){
 if((PoiSolver[(BouSolver[i][j]->GetFirstIndex())]->getNodeType())!="ConsT") PoiSolver[(BouSolver[i][j]->GetFirstIndex())]->setAsHfluxNode();
 if((PoiSolver[(BouSolver[i][j]->GetSecondIndex())]->getNodeType())!="ConsT") PoiSolver[(BouSolver[i][j]->GetSecondIndex())]->setAsHfluxNode();
		}

	}   */



/*	cout<< "initial solution "<<endl;
	for(int i=0;i<nPoin;i++) cout<<"initial solution at index "<<i+1<<" is "<<solution[i]<<endl;
	cout<< "end of initial solution "<<endl;  */
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void Iterate()
  { double temp1 = time/minTimeStepValue;
  	double temp2 = floor(time/minTimeStepValue);
  	double theta = 0.5;
  	lastTimeStep = 0;
  	if((temp1-temp2)>0) { numberOfSteps = temp2 + 1; lastTimeStep = time - (temp2*minTimeStepValue); }
  	else { numberOfSteps = temp2 ;}
  	cout<<temp1<<endl;
  	cout<<temp2<<endl;
  	cout<<" minTimeStepValue "<<minTimeStepValue<<endl;
  	cout << "numberOfSteps" << numberOfSteps<<endl;
  	cout << "lastTimeStep "  << lastTimeStep <<endl;
    
 //  cout<<" solution before multiplying "<<endl;
//for(int i=0;i<(nPoin);i++) cout<< solution[i]<<endl;

  int tempCount = 0;
  for(int i=0;i<nPoin;i++) {
     if((PoiSolver[i+1]->getNodeType())=="ConsT"){
  	consTvector[tempCount]=solution[i];
tempCount +=1;
}

}

 //cout<<" consTvector "<<endl;
//for(int i=0;i<tempCount;i++) cout<< consTvector[i]<<endl;

  	for(int i=0;i<nPoin;i++) for(int j=0;j<nPoin;j++){        
  preConditionerMatrix[i][j] = (((theta)*assembledConductionMatrix[i][j])+((1/minTimeStepValue)*assembledCapacitanceMatrix[i][j]));}

  	for(int i=0;i<nPoin;i++) for(int j=0;j<nPoin;j++){        
 equationRhsMatrix[i][j] = (((-1)*(1-theta)*assembledConductionMatrix[i][j])+((1/minTimeStepValue)*assembledCapacitanceMatrix[i][j]));}
double sum1 = 0;
  for(int i=0;i<nPoin;i++){ sum1 = 0; for(int k=0;k<nPoin;k++) {sum1 += (equationRhsMatrix[i][k]*solution[k]);} solutiontemp[i]=sum1;}
  for(int i=0;i<nPoin;i++) solution[i]=solutiontemp[i];	
 // 	cout<<"i was here"<<endl;
  for(int i=0;i<nPoin;i++) solution[i]+=assembledRHSMatrix[i];
 // cout<<"i was here"<<endl;
/*cout<<" after multiplying solution "<<endl;
for(int i=0;i<(nPoin);i++) cout<< solution[i]<<endl;

 	cout<<"preConditionerMatrix"<<endl;
for(int i=0;i<(nPoin);i++) 
{for(int j=0;j<(nPoin);j++) cout<<preConditionerMatrix[i][j]<<" "; cout<<endl;}
cout<<" equationRhsMatrix"<<endl;
for(int i=0;i<(nPoin);i++) 
{for(int j=0;j<(nPoin);j++) cout<<equationRhsMatrix[i][j]<<" "; cout<<endl;}  */

  int rowCount = 0;
  for(int i=0;i<nPoin;i++) {
     int columnCount = 0;
     if((PoiSolver[i+1]->getNodeType())!="ConsT"){
  	for(int j=0;j<nPoin;j++){
  		if((PoiSolver[j+1]->getNodeType())!="ConsT"){
  	reduced_preConditionerMatrix[rowCount][columnCount] = preConditionerMatrix[i][j];
  	reduced_equationRhsMatrix[rowCount][columnCount] =  equationRhsMatrix[i][j];
  	columnCount +=1;
  } }
rowCount +=1;
}

}
//cout<<"i was here"<<endl;
  rowCount = 0;
  for(int i=0;i<nPoin;i++) {
     if((PoiSolver[i+1]->getNodeType())!="ConsT"){
  	reduced_solution[rowCount]=solution[i];
rowCount +=1;
}

}

//cout<<" reduced_solution "<<endl;
//for(int i=0;i<(nPoin-numberOfConsT);i++) cout<<reduced_solution[i]<<endl;


int count1=0,count2=0;
for(int i=0;i<nPoin;i++) {
     if((PoiSolver[i+1]->getNodeType())=="ConsT") {consTindex[count1] = i;count1+=1;}
     else {non_consTindex[count2]=i;count2+=1;}	
      }
for(int i=0;i<(numberOfConsT);i++){
	for(int j=0;j<(nPoin-numberOfConsT);j++){
		reduced_solution[j] -= preConditionerMatrix[non_consTindex[j]][consTindex[i]]*consTvector[i];
	}

}


//cout<<" reduced_solution after subtraction"<<endl;
//for(int i=0;i<(nPoin-numberOfConsT);i++) cout<< reduced_solution[i]<<endl;


  //LU DECOMPOSITION OF REDUCED PRECONDITIONER MATRIX
  
for(int i=0;i<(nPoin-numberOfConsT);i++) for(int j=0;j<(nPoin-numberOfConsT);j++)
	{if(i==j) Lmatrix[i][j]=1; Umatrix[i][j]=reduced_preConditionerMatrix[i][j];} 
/*cout<<"reduced_preConditionerMatrix"<<endl;
for(int i=0;i<(nPoin-numberOfConsT);i++) 
{for(int j=0;j<(nPoin-numberOfConsT);j++) cout<<reduced_preConditionerMatrix[i][j]<<" "; cout<<endl;} */

//cout<<"reduced_equationRhsMatrix"<<endl;
//for(int i=0;i<(nPoin-numberOfConsT);i++) 
	//{for(int j=0;j<(nPoin-numberOfConsT);j++) cout<<reduced_equationRhsMatrix[i][j]<<" "; cout<<endl;}

//for(int i=0;i<(nPoin-numberOfConsT);i++)
double tempHere = 0;
for(int k=0;k<(nPoin-numberOfConsT);k++)
	for(int i=k+1;i<(nPoin-numberOfConsT);i++){

	                      tempHere = (Umatrix[i][k]/Umatrix[k][k]);
		for(int j=k;j<(nPoin-numberOfConsT);j++){

				Umatrix[i][j] = Umatrix[i][j] - (tempHere)*Umatrix[k][j];
				
		}  
       Lmatrix[i][k] = tempHere;
	}
/*cout<<"upper triangular matrix"<<endl;
for(int i=0;i<(nPoin-numberOfConsT);i++) 
{for(int j=0;j<(nPoin-numberOfConsT);j++) cout<<Umatrix[i][j]<<" "; cout<<endl;}
cout<<"lower triangular matrix"<<endl;
for(int i=0;i<(nPoin-numberOfConsT);i++) 
{for(int j=0;j<(nPoin-numberOfConsT);j++) cout<<Lmatrix[i][j]<<" "; cout<<endl;}
cout<<"multiplication of lower and upper triangular matrix"<<endl; */
 /*for(int i=0;i<(nPoin-numberOfConsT);i++) {
 	
 	for(int j=0;j<(nPoin-numberOfConsT);j++){
 		double tempodele = 0;
 		for(int k=0;k<(nPoin-numberOfConsT);k++){
            tempodele += Lmatrix[i][k]*Umatrix[k][j];
 		}
    //  cout<<tempodele<<" ";

 	}
//cout<<endl;
 	}  */

 //cout<<" reduced_solution before the looping "<<endl;
//for(int i=0;i<(nPoin-numberOfConsT);i++) cout<< reduced_solution[i]<<endl;


  //foward substitution for every timestep in loop
 //backward substitution for every timestep in loop
//cout<<"reduced_solution "<<endl;
//for(int i=0;i<(nPoin-numberOfConsT);i++) cout<< reduced_solution[i]<<endl;
ofstream outf1("solution.dat", ios::app); 
//ofstream outf2("paroutput.vtk", ios::app); 	
outf1.precision(6);
string prefix = "solution_";
string ext(".vtk");
int countOutput = 0;
for (int i1=0;i1<numberOfSteps;i1++) 
  	{    
  		//cout<<"reduced_solution at beginning of step "<<i1+1<<endl;
//for(int j=0;j<(nPoin-numberOfConsT);j++) cout<<reduced_solution[j]<<endl;

  		for(int i=0;i<(nPoin-numberOfConsT);i++){forwardSubMatrix[i] = 0;backwardSubMatrix[i]=0;}
  		 //forward substitution
  		forwardSubMatrix[0]=reduced_solution[0];  
  		double sum2=0;   
       for(int i=1;i<(nPoin-numberOfConsT);i++){
       	sum2=0;
       	for(int j=0;j<i;j++){
       		sum2 += Lmatrix[i][j]*forwardSubMatrix[j];
       	}
       	forwardSubMatrix[i]=reduced_solution[i]-sum2;
       }
     //  cout<<"forwardSubMatrix in step "<<i1+1<<endl;
     // for(int i=0;i<(nPoin-numberOfConsT);i++) cout<< forwardSubMatrix[i]<<endl;
       //backward substitution
backwardSubMatrix[(nPoin-numberOfConsT)-1] = forwardSubMatrix[(nPoin-numberOfConsT)-1]/Umatrix[(nPoin-numberOfConsT)-1][(nPoin-numberOfConsT)-1];

if((nPoin-numberOfConsT)>1)
for(int i=((nPoin-numberOfConsT)-2);i>=0;i--){
      double sum = 0;
      for(int j=i+1;j<(nPoin-numberOfConsT);j++){
      	sum += Umatrix[i][j]*backwardSubMatrix[j];
      }
      backwardSubMatrix[i]= ((forwardSubMatrix[i]-sum)/Umatrix[i][i]);
}  
//for(int i=0;i<nPoin;i++) solution[i]=0;
//cout<<"backwardSubMatrix in step "<<i1+1<<endl;
//for(int i=0;i<(nPoin-numberOfConsT);i++) cout<<backwardSubMatrix[i]<<endl;
count1=0;count2=0;
for(int i=0;i<nPoin;i++) {
     if((PoiSolver[i+1]->getNodeType())=="ConsT") {solution[i]=consTvector[count1];count1+=1;}
     else {solution[i]=backwardSubMatrix[count2];count2+=1;}	
      }

 
//outf1<<"Solution at time step "<<i1+1<<endl;
//for(int i=0;i<(nPoin);i++){
//outf1<<PoiSolver[i+1]->GetIndex()<<" "<<PoiSolver[i+1]->GetXcord()<<" "<<PoiSolver[i+1]->GetYcord()<<" "<<solution[i]<<endl;
//}

if((i1%10)==0){
stringstream ss;
        ss << prefix << std::setfill('0') << std::setw(4) << countOutput << ext;
string temp;
ss >> temp;

ofstream outf2(ss.str().c_str());
        if ( !outf2 )
        {
            std::cerr << "Error: failed to create file " << ss.str() << '\n';
            break;
        }



     outf2<<"# vtk DataFile Version 3.0"<<endl;
     outf2<<"vtk output"<<endl;
     outf2<<"ASCII"<<endl;
     outf2<<"DATASET UNSTRUCTURED_GRID"<<endl;
     outf2<<"POINTS "<<nPoin<<" double"<<endl;
     for(int i=0;i<(nPoin);i++){
	 outf2<<PoiSolver[i+1]->GetXcord()<<" "<<PoiSolver[i+1]->GetYcord()<<" "<<"0 ";
	 }
	 outf2<<endl;
	 outf2<<"CELLS "<<nElem<<" "<<nElem*4<<endl;
	 for(int i=1;i<=nElem;i++) outf2<<"3 "<<((EleSolver[i]->GetFirstIndex())-1)<<" "<<((EleSolver[i]->GetSecondIndex())-1)<<" "<<((EleSolver[i]->GetThirdIndex())-1)<<" ";
	 outf2<<endl;
	 outf2<<"CELL_TYPES "<<nElem<<endl;
	 for(int i=1;i<=nElem;i++) outf2<<"5 ";
	 outf2<<"POINT_DATA "<<nPoin<<endl;
	 outf2<<endl;
	 outf2<<"SCALARS Temperature double 1"<<endl;
	 outf2<<"LOOKUP_TABLE default"<<endl;
	 for(int i=0;i<(nPoin);i++) outf2<<solution[i]<<" ";

 countOutput+=1;
}

 //cout<<"solution at step "<<i1+1<<endl;
//for(int i=0;i<(nPoin);i++) cout<<solution[i]<<endl;    
for(int i=0;i<(nPoin);i++) solutiontemp1[i]=0;
for(int i=0;i<(nPoin);i++)
{ double sum =0; 
for(int k=0;k<(nPoin);k++) sum += equationRhsMatrix[i][k]*solution[k]; 
	solutiontemp1[i]=sum;}

for(int i=0;i<(nPoin);i++) solution[i]=solutiontemp1[i];

for(int i=0;i<(nPoin);i++) solution[i]+=assembledRHSMatrix[i];
//cout<<"solution after multiplying with equationRhsMatrix at step "<<i1+1<<endl;
//for(int i=0;i<(nPoin);i++) cout<<solution[i]<<endl; 	
for(int i=0;i<(nPoin-numberOfConsT);i++) reduced_solution[i] = 0;
	int rowCount = 0;
  for(int i=0;i<nPoin;i++) {
     if((PoiSolver[i+1]->getNodeType())!="ConsT"){
  	reduced_solution[rowCount]=solution[i];
rowCount +=1;
}

}

for(int i=0;i<(numberOfConsT);i++){
	for(int j=0;j<(nPoin-numberOfConsT);j++){
		reduced_solution[j] -= (preConditionerMatrix[non_consTindex[j]][consTindex[i]]*consTvector[i]);
	}

}
//cout<<"reduced_solution at end of step "<<i1+1<<endl;
//for(int j=0;j<(nPoin-numberOfConsT);j++) cout<<reduced_solution[j]<<endl;
cout<<"S.No "<< i1+1 <<" "<<numberOfSteps<<endl;
//for(int i=1;i<(nPoin-numberOfConsT);i++) cout<< backwardSubMatrix[i]<<endl;


  	}
//cout<<"final solution "<<endl;
//for(int i=0;i<(nPoin-numberOfConsT);i++) cout<< backwardSubMatrix[i]<<endl;
	cout<<"numberOfConsT is "<<numberOfConsT<<endl;
    cout<<"nPoin-numberOfConsT is "<<nPoin-numberOfConsT<<endl;
 //cout<<"consTvector "<<endl;
 //for(int i=0;i<(numberOfConsT);i++) cout<< consTvector[i]<<endl;
 //cout<<"consTindex "<<endl;
 //for(int i=0;i<(numberOfConsT);i++) cout<< consTindex[i]+1<<endl;
  }	




};