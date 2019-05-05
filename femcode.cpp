//#include <cstdlib> 
//#include <iostream>
//#include <fstream>
#include <bits/stdc++.h> 
using namespace std;
#include "mesh.hpp"
int main()
{   
    Mesh mesh1;
    mesh1.readMesh();
    mesh1.prepareElements();
    mesh1.solVe();

    
	return 0;
}