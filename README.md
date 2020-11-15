### Finite Element Solver for Transient Heat Conduction
- In this work a fully Object Oriented Finite Element Solver is developed for solving 2D Transient Heat Conduction Problems.
- Solver is written in C++.
- Code can handle unstructured 2d triangular meshes of arbitrary geometries with different types of boundary conditions. (Constant Temperature, Heat Flux, Convection).
- [Project Report](https://github.com/Kartheek77/2D-FINITE-ELEMENT-TRANSIENT-HEAT-CONDUCTION-CODE-/blob/master/Final%20Report%20ME%20F366_Laboratory%20Project_Karnati_Venkata_Kartheek_2014A4TS0260H.pdf)
- [Results](https://github.com/Kartheek77/2D-FINITE-ELEMENT-TRANSIENT-HEAT-CONDUCTION-CODE-/blob/master/Results%26Conclusions.pdf)
- Code is tested on structured triangular grid with 1800 triangular elements.
![alt text](https://github.com/Kartheek77/2D-FINITE-ELEMENT-TRANSIENT-HEAT-CONDUCTION-CODE-/blob/master/ImagesforFemProject/sgftm.PNG)
- Different boundary conditions are applied to test the code
    1. `Botton Const Temp 60, Right-Top-Left Const Temp 10`
    ![alt text](https://github.com/Kartheek77/2D-FINITE-ELEMENT-TRANSIENT-HEAT-CONDUCTION-CODE-/blob/master/ImagesforFemProject/case1.PNG)
    2. `Bottom Const Temp 60, Right Convection External Temperature 100, Top Insulation, Left Constant Temperature 10`
    ![alt text](https://github.com/Kartheek77/2D-FINITE-ELEMENT-TRANSIENT-HEAT-CONDUCTION-CODE-/blob/master/ImagesforFemProject/case2.PNG)
    3. `Bottom Const Temp 60, Right Convection External Tempearture 100, Top Insulation, Left Insulation`
    ![alt text](https://github.com/Kartheek77/2D-FINITE-ELEMENT-TRANSIENT-HEAT-CONDUCTION-CODE-/blob/master/ImagesforFemProject/case3.PNG)
    4. `Bottom Insulation, Right Convection External Temperature 100, Top Insulation, Left Constant Temperature 60`
    ![alt text](https://github.com/Kartheek77/2D-FINITE-ELEMENT-TRANSIENT-HEAT-CONDUCTION-CODE-/blob/master/ImagesforFemProject/case4.PNG)

