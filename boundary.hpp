class BoundLineElement{
	int firstindex,secondindex;
	double temperature1,temperature2,length,x1,y1,x2,y2,boundaryMatrix[2][1],ConvecCoeff,boundaryConvecMatrix[2][2],ConvTemp,heatFlux;
	string bctype;

public:
	BoundLineElement(int x, int y, string BCtype ,double Temperature1,double Temperature2)
	{
		firstindex = x; secondindex = y; temperature1 = Temperature1; temperature2 = Temperature2; bctype = BCtype;
 //cout<<"bou element is created with firstindex "<<firstindex<<" secondindex "<<secondindex<<" tem1 "<<temperature1<<" tem2 "<<temperature2<<" bctype "<<bctype<<endl;
	if(BCtype == "ConsT") 
		{boundaryMatrix[0][0]=0;boundaryMatrix[1][0]=0;
          for(int i=0;i<2;i++) for(int j=0;j<2;j++) boundaryConvecMatrix[i][j]=0;
		}
	
	}
	BoundLineElement(int xX,int yY, double ConvCoeff, double ConTemp,string BCtypE)
   {
   	 firstindex = xX; secondindex = yY; ConvecCoeff=ConvCoeff; ConvTemp=ConTemp; bctype = BCtypE;
     
   }
   BoundLineElement(int xX,int yY, string BCtype, double heatFlu)
   {
firstindex = xX; secondindex = yY; bctype = BCtype; heatFlux=heatFlu;
   }
  
  void setBouElemCoordinates(double X1,double Y1,double X2,double Y2){
     x1=X1;y1=Y1;x2=X2;y2=Y2;
   }
   void setLengthAndProperties(){
length = sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
if(bctype == "Convec") 
	{	boundaryConvecMatrix[0][0]= (ConvecCoeff*length/3);
		boundaryConvecMatrix[0][1]= (ConvecCoeff*length/6);
		boundaryConvecMatrix[1][0]= (ConvecCoeff*length/6);
		boundaryConvecMatrix[1][1]= (ConvecCoeff*length/3);

		boundaryMatrix[0][0]=(ConvecCoeff*ConvTemp*length*0.5);boundaryMatrix[1][0]=(ConvecCoeff*ConvTemp*length*0.5);}
if(bctype == "HFlux"){
       boundaryMatrix[0][0]=(heatFlux*length*0.5);boundaryMatrix[1][0]=(heatFlux*length*0.5);
       for(int i=0;i<2;i++) for(int j=0;j<2;j++) boundaryConvecMatrix[i][j]=0;
} 

   }
	int GetFirstIndex(){return firstindex;}
	int GetSecondIndex(){return secondindex;}
	double GetboundaryMatrix(int x,int y){return boundaryMatrix[x][y];}
	double GetboundaryConvecMatrix(int x,int y){return boundaryConvecMatrix[x][y];}
	double GetTemperature1(){return temperature1;}
	double GetTemperature2(){return temperature2;}
	string GetBoundaryType(){return bctype;}
	

};
