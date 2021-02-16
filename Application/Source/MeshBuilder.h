#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "LoadOBJ.h"
/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, float lengthX, float lengthY,int color);
	static Mesh* GenerateQuad2(const std::string& meshName, float lengthX, float lengthY, int color);
	static Mesh* GenerateQuadRepeat(const std::string& meshName, float lengthX, float lengthY, int color);
	static Mesh* GenerateCube(const std::string &meshName, float lengthX, float lengthY, float lengthZ,int color);
	static Mesh* GenerateCubeT(const std::string& meshName, float lengthX, float lengthY, float lengthZ, float texStart, float texEnd, Color col);
	static Mesh* GenerateCircle(const std::string& meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateSemiCircle(const std::string& meshName, float lengthX, float lengthY, float lengthZ,int color);
	static Mesh* Generatering(const std::string& meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* Generatehemisphere(const std::string& meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* Generatesphere(const std::string& meshName, float lengthX, float lengthY, float lengthZ,int name);
	static Mesh* GenerateTorus(const std::string& meshName, unsigned numStack, unsigned numSlice, float outerR, float innerR,int color);
	static Mesh* GenerateCylinder(const std::string& meshName, float lengthX, float lengthY, float lengthZ, int name);
	static Mesh* GenerateCone(const std::string& meshName, float lengthX, float lengthY, float lengthZ, int name);
	static Mesh* GenerateHalfCube(const std::string& meshName, float lengthX, float lengthY, float lengthZ, int color);
	static Mesh* GenerateOBJ(const std::string& meshName, const std::string& file_path);
	static Mesh* GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol);
	static Mesh* GenerateOBJMTL(const std::string& meshName, const std::string& file_path, const std::string& mtl_path);
	static Mesh* GenerateColliderBox(const std::string& meshName, double legnthx,double lengthy,double lengthz);
};

#endif