#include <cstdlib> // for exit()
#include <iostream>
#include <fstream>
#include <iomanip>
 
int main()
{
    using namespace std;
    ofstream outf("mesh1.dat", ios::app);
    if (!outf)
    {
        cerr << "mesh.dat could not be opened for writing!" << endl;
        exit(1);
    }
    outf<<"density = 2800"<<endl;
    outf<<"specificHeat = 795"<<endl;
    outf<<"thickness = 1"<<endl;
    outf<<"thermalConductivity = 143"<<endl;
    outf<<"time = 10000"<<endl;
    outf<<"cfl = 0.5"<<endl;
    int hori=31; int verti=31;
    outf <<"nElem = "<<(hori-1)*(verti-1)*2<< endl; 
    int count = 0;
    int j = 1;
    for(int i=1;i<=((hori-1)*(verti-1));i++){
        //outf<<"j ="<<j<<endl;
        count = count + 1;
        outf <<"5e"<<" "<<count<<" "<< j<<" "<<j+1<<" "<<j+hori<<endl;
        count = count + 1;
        outf <<"5e"<<" "<<count<<" "<< j+1<<" "<<j+hori+1<<" "<<j+hori<<endl;
       if((i%(hori-1))==0) j=j+2;
       else j=j+1; }   
    int nPoin = hori*verti;
    outf <<"nPoin = "<<nPoin<< endl;
   double deltax = 0.05,deltay = 0.05;
  // outf<<setprecision(17);
    for(int i=0;i<nPoin;i++){
        outf <<"Poi"<<" "<< i+1<<" "<<(i%hori)*deltax<<" "<<(i/hori)*deltay<<endl;
    }
    outf<<"nMark = 4"<<endl;
    outf<<"Marker_Tag_ 1 = Bottom"<<endl;
    outf<<"nBottom = "<<hori-1<<endl;
   // outf<<"Bottom 3e"<<" "<<1<<" "<<2<<" ConsT "<<350<<" "<<600<<endl;
    for(int i=0;i<hori-1;i++) outf<<"Bottom 3e"<<" "<<i+1<<" "<<i+2<<" ConsT "<<60<<" "<<60<<endl;
   // outf<<"Bottom 3e"<<" "<<hori-2+1<<" "<<hori-2+2<<" ConsT "<<600<<" "<<350<<endl;
    
    outf<<"Marker_Tag_ 2 = Right"<<endl;
    outf<<"nRight = "<<verti-1<<endl;
    for(int i=0;i<verti-1;i++) outf<<"Right 3e"<<" "<<hori*(i+1)<<" "<<hori*(i+2)<<" ConsT "<<10<<" "<<10<<endl;
    
    outf<<"Marker_Tag_ 3 = Top"<<endl;
    outf<<"nTop = "<<hori-1<<endl;
    for(int i=0;i<hori-1;i++) outf<<"Top 3e"<<" "<<(verti*hori)-i<<" "<<(verti*hori)-i-1<<" ConsT "<<10<<" "<<10<<endl;

    outf<<"Marker_Tag_ 4 = Left"<<endl;
    outf<<"nLeft = "<<verti-1<<endl;
    for(int i=0;i<verti-1;i++) outf<<"Left 3e"<<" "<<(hori*(i+1))+1<<" "<<(hori*(i))+1<<" ConsT "<<10<<" "<<10<<endl;
       
    return 0;	
}