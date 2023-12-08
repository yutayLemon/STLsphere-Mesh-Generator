#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>

//vector operations
class cord {
public:
	float x = 0;
	float y = 0;
	float z = 0;
};
//z as up


///simple add
cord vectorOPadd(cord vec1, cord vec2) {
	cord temp;
	temp.x = vec1.x + vec2.x;
	temp.y = vec1.y + vec2.y;
	temp.z = vec1.z + vec2.z;
	return temp;
}
//simple mius
cord vectorOPmins(cord vec1, cord vec2) {
	cord temp;
	temp.x = vec1.x - vec2.x;
	temp.y = vec1.y - vec2.y;
	temp.z = vec1.z - vec2.z;
	return temp;
}


//multiply as a scaler
cord vectorOPmult(float scal, cord vec2) {
	cord temp;
	temp.x = scal * vec2.x;
	temp.y = scal * vec2.y;
	temp.z = scal * vec2.z;
	return temp;
}

//get vector len
float vectorOPlen(cord vect1) {
	return sqrt(vect1.x * vect1.x + vect1.y * vect1.y + vect1.z * vect1.z);
}

//get unit vector
cord vectorOPUnit(cord vect1) {
	return vectorOPmult(1 / vectorOPlen(vect1), vect1);
}

//display vector
void vectorOPdisply(cord vect1) {
	std::cout << "\nx:" << vect1.x << " y:" << vect1.y << " z:" << vect1.z << "\n";
}



//crossproduct generates othorgonal vector perpendiculer to the other 2
cord vectorOPCrossProd(cord vect1, cord vect2) {
	cord temp;
	temp.x = vect1.y * vect2.z - vect1.z * vect2.y;
	temp.y = vect1.z * vect2.x - vect1.x * vect2.z;
	temp.z = vect1.x * vect2.y - vect1.y * vect2.x;

	return temp;
}


//get normal vector in stl triangle vect1,2 vector from middle to outer sides
cord STLNormal(cord vect1, cord vect2, cord Mid) {
	cord tempVect1;
	cord tempVect2;
	tempVect1 = vectorOPmins(vect1, Mid);
	tempVect2 = vectorOPmins(vect2, Mid);
	return vectorOPUnit(vectorOPCrossProd(tempVect1, tempVect2));

}
/*
std::ofstream MyfileO("perlinNoiseSTL.stl");
void LogTriangle(cord vect1, cord vect2, cord vect3, cord normal) {
	MyfileO << std::scientific << std::setprecision(6) << "facet normal " << normal.x << " " << normal.y << " " << normal.z;
	MyfileO << std::scientific << std::setprecision(6) << "\nouter loop\nvertex " << vect1.x << " " << vect1.y << " " << vect1.z << "\n";
	MyfileO << std::scientific << std::setprecision(6) << "vertex " << vect2.x << " " << vect2.y << " " << vect2.z << "\n";
	MyfileO << std::scientific << std::setprecision(6) << "vertex " << vect3.x << " " << vect3.y << " " << vect3.z << "\n";
	MyfileO << std::scientific << std::setprecision(6) << "endloop\nendfacet\n";


	//log the triangle STL

}
*/

void STDLogTriangle(cord vect1, cord vect2, cord vect3, cord normal) {
	std::cout << std::scientific << std::setprecision(6) << "facet normal " << normal.x << " " << normal.y << " " << normal.z;
	std::cout << std::scientific << std::setprecision(6) << "\nouter loop\nvertex " << vect1.x << " " << vect1.y << " " << vect1.z << "\n";
	std::cout << std::scientific << std::setprecision(6) << "vertex " << vect2.x << " " << vect2.y << " " << vect2.z << "\n";
	std::cout << std::scientific << std::setprecision(6) << "vertex " << vect3.x << " " << vect3.y << " " << vect3.z << "\n";
	std::cout << std::scientific << std::setprecision(6) << "endloop\nendfacet\n";
	//log the triangle STL

}





