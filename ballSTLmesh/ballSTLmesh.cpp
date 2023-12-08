
#include "MeshCreationLib.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
const long double M_PI = 3.141592653589793238462643383279502884L /* pi */;


std::ofstream MyfileO("STL.stl");
void LogTriangle(cord vect1, cord vect2, cord vect3, cord normal) {
	MyfileO << std::scientific << std::setprecision(6) << "facet normal " << normal.x << " " << normal.y << " " << normal.z;
	MyfileO << std::scientific << std::setprecision(6) << "\nouter loop\nvertex " << vect1.x << " " << vect1.y << " " << vect1.z << "\n";
	MyfileO << std::scientific << std::setprecision(6) << "vertex " << vect2.x << " " << vect2.y << " " << vect2.z << "\n";
	MyfileO << std::scientific << std::setprecision(6) << "vertex " << vect3.x << " " << vect3.y << " " << vect3.z << "\n";
	MyfileO << std::scientific << std::setprecision(6) << "endloop\nendfacet\n";


	//log the triangle STL

}
//tunning parms
float r = 5;
const int pointsPerSlice = 41;//alwase even//make shour that is in the form (2n+2)
//tunning parms


//initalise grid
//height of poins on each side minus the top and bottom (eg 10, so 3) where index 0 is the second layer
//width points horozontal then plus one to connect
cord GridVert[(pointsPerSlice/2)-1][pointsPerSlice+1];

void GenGridBall(float rad,int PPS) {
	//theta is height
	//start from 0 as grid starts from 0 end at pps/2 - 2 because it is the length of the height
	for (int theta = 0; theta < (PPS/2)-1; theta++) {//total angle / PPS)

		//epsilon is the verticle
		//start from 0
		//make full revolution so PPS + 1
		for (int epsil = 0; epsil < PPS+1; epsil++) {
			cord tempBall;

			//sin cos tan 3d
			//theta verticle from pos z axis
			//epsilon from pos x?<-need to cheak(horozontal)

			//pluss one as grid index 0 is second layer(index1)
			    tempBall.x = rad * std::sin((theta+1)*((2* M_PI)/PPS)) * cos(epsil* ((2 * M_PI) / PPS)) + rad;
				tempBall.z = rad * std::cos((theta+1)* ((2 * M_PI) / PPS)) + rad;
				tempBall.y = rad * std::sin((theta+1)* ((2 * M_PI) / PPS)) * std::sin(epsil*((2* M_PI)/PPS)) + rad;


				GridVert[theta][epsil] = tempBall;
		}
	}
}
void Gentop(cord topVect) {
	for (int ep = 0; ep < pointsPerSlice; ep++) {
		LogTriangle(GridVert[0][ep], GridVert[0][ep + 1], topVect, STLNormal(GridVert[0][ep], GridVert[0][ep + 1], topVect));
	}
}

void Genbottom(cord bottomVect) {
	for (int ep = 0; ep < pointsPerSlice; ep++) {
		LogTriangle(GridVert[pointsPerSlice/2-2][ep],bottomVect, GridVert[pointsPerSlice/2-2][ep + 1], STLNormal(GridVert[pointsPerSlice/2-2][ep], bottomVect,GridVert[pointsPerSlice/2-2][ep + 1]));
	}
}

void GenMeshMiddle() {
	//start from 0 as indexed
	//and befor full as alwase maintain top coner
	for (int i = 0; i < (pointsPerSlice/2)-1-1; i++) {//first is wird
	//start from 1 and make full rotation
		std::cout << "layer :" << i + 1 << "\n";
		for (int l = 1; l < pointsPerSlice + 1; l++) {


			LogTriangle(GridVert[i][l - 1], GridVert[i + 1][l - 1], GridVert[i + 1][l], STLNormal(GridVert[i][l - 1], GridVert[i + 1][l - 1], GridVert[i + 1][l]));
			LogTriangle(GridVert[i][l], GridVert[i][l - 1], GridVert[i + 1][l], STLNormal(GridVert[i][l], GridVert[i][l - 1], GridVert[i + 1][l - 1]));


		}
	}
}
int main() {
	cord top;
	top.z = r * 1 + r;
	top.x = r;
	top.y = r;

	cord bottom;
	bottom.z = 0;
	bottom.x = r;
	bottom.y = r;
	MyfileO << "solid ci\n";
	GenGridBall(r, pointsPerSlice);
	Gentop(top);
	GenMeshMiddle();
	Genbottom(bottom);
	MyfileO << "endsolid ci";
}