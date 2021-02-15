#include "MeshBuilder.h"
#include <GL\glew.h>
#include "Vertex.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#define PI 3.14159265
#define Rad PI/180
//generate a ring
Mesh* MeshBuilder::Generatering(const std::string& meshName, float lengthX, float lengthY, float lengthZ) {
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	for (int theta = 0; theta <= 360; theta += 10) {
		v.pos.Set(10 * cos(theta * (PI / 180)), 0, 10 * sin(theta * (PI / 180))); 
		v.normal.Set(0, 1, 0);
		v.color.Set(Red); 
		vertex_buffer_data.push_back(v);
		v.pos.Set(5*cos(theta*(PI/180)), 0, 5*sin(theta*(PI/180))); 
		v.color.Set(Red); 
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}
	for (int i = 0; i < 74; i++) {
		index_buffer_data.push_back(i);
	}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = 74;
	return mesh;
}
//generate a hemisphere
Mesh* MeshBuilder::Generatehemisphere(const std::string& meshName, float lengthX, float lengthY, float lengthZ) {
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	for (int phi = 0; phi <90; phi+=10) {
		for (int theta = 0; theta <= 360; theta += 10) {
			v.pos.Set(5*cos(phi*Rad)*cos(theta*Rad),5*sin(phi*Rad),5*cos(phi*Rad)*sin(theta*Rad)); v.color.Set(Purple); vertex_buffer_data.push_back(v);
			v.pos.Set(5*cos((phi+10) * Rad) * cos(theta * Rad), 5 * sin((phi+10) * Rad), 5* cos((phi+10) * Rad) * sin(theta * Rad)); v.color.Set(Blue); vertex_buffer_data.push_back(v);
		}
	}
	for (int theta = 0; theta <= 360; theta += 10) {
		v.pos.Set(0, 0, 0); v.color.Set(Purple); vertex_buffer_data.push_back(v);
		v.pos.Set(5 * cos(theta*Rad), 0, 5 * sin(theta*Rad)); v.color.Set(Purple); vertex_buffer_data.push_back(v);
	}
	for (int i = 0; i < 740; i++) {
		index_buffer_data.push_back(i);
	}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = 740;
	return mesh;
}
//generate a sphere
Mesh* MeshBuilder::Generatesphere(const std::string& meshName, float lengthX, float lengthY, float lengthZ,int name) {
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	int count = 0;
	float x = 0;
	float y = 0;
	for (int phi = -90; phi < 90; phi += 10) {
		for (int theta = 0; theta <= 360; theta += 10) {
			v.pos.Set(cos(phi * Rad) * cos(theta * Rad), sin(phi * Rad), cos(phi * Rad) * sin(theta * Rad)); 
			v.color.Set(name);
			v.normal.Set(cos(phi * Rad) * cos(theta * Rad), sin(phi * Rad), cos(phi * Rad) * sin(theta * Rad));
			x = ((cos((theta/2) * Rad))/2.8)+0.5;
			y = (sin(phi * Rad)/2)+0.5;
			v.texCoord.Set(x, y);
			
			vertex_buffer_data.push_back(v);
			count++;
			v.pos.Set(cos((phi + 10) * Rad) * cos(theta * Rad),sin((phi + 10) * Rad),cos((phi + 10) * Rad) * sin(theta * Rad)); 
			v.color.Set(name); 
			v.normal.Set(cos((phi + 10) * Rad) * cos(theta * Rad),  sin((phi + 10) * Rad), cos((phi + 10) * Rad) * sin(theta * Rad));
			x = (cos((theta/2) * Rad)/2.8)+0.5;
			y = (sin((phi + 10) * Rad) / 2)+0.5;
			v.texCoord.Set(x, y);
		
			vertex_buffer_data.push_back(v);
			count++;
		}
	}
	for (int i = 0; i < count; i++) {
		index_buffer_data.push_back(i);
	}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = count;
	return mesh;
}
//generate torus
Mesh* MeshBuilder::GenerateTorus(const std::string& meshName, unsigned numStack, unsigned numSlice, float outerR, float innerR,int color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	float degreePerStack = 360.f / numStack;
	float degreePerSlice = 360.f / numSlice;
	float x1, z1; 
	float x2, y2, z2;
	Mesh* mesh = new Mesh(meshName);
	for (unsigned stack = 0; stack < numStack + 1; stack++) {
		for (unsigned slice = 0; slice < numSlice + 1; slice++) {
			z1 = outerR * cos(stack * degreePerStack*Rad);
			x1 = outerR * sin(stack * degreePerStack*Rad);
			z2 = (outerR + innerR * cos(slice * degreePerSlice*Rad)) * cos(stack * degreePerStack*Rad);
			y2 = innerR * sin(slice * degreePerSlice*Rad);
			x2 = (outerR + innerR * cos(slice * degreePerSlice*Rad)) * sin(stack * degreePerStack*Rad);
			v.pos.Set(x2, y2, z2);
			v.color.Set(color);
			v.normal.Set(x2-x1,y2,z2-z1);
			vertex_buffer_data.push_back(v);
		}
	}
	int indexsize = 0;
	for (unsigned stack = 0; stack < numStack; stack++) {
		for (unsigned slice = 0; slice < numSlice + 1; slice++) {
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
			indexsize += 2;
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = indexsize;
	return mesh;
}
//generate a cylinder
Mesh* MeshBuilder::GenerateCylinder(const std::string& meshName, float lengthX, float lengthY, float lengthZ, int name)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	int NumStack = 1;
	float height = 4;
	float stackheight = height / NumStack;
	int index = 0;
	Mesh* mesh = new Mesh(meshName);
	for (int stack = 0; stack < NumStack; ++stack) {
		for (int theta = 0; theta <= 360; theta += 10) {
			v.pos.Set(1 * cos(theta * Rad), (-height / 2) + stack * stackheight, 1 * sin(theta * Rad));
			v.color.Set(name);
			v.normal.Set(cos(theta * Rad), 0, sin(theta * Rad));
			vertex_buffer_data.push_back(v);
			v.pos.Set(1 * cos(theta * Rad), (-height / 2) + (stack+1) * stackheight, 1 * sin(theta * Rad));
			v.color.Set(name);
			v.normal.Set(cos(theta * Rad), 0, sin(theta * Rad));
			vertex_buffer_data.push_back(v);
			index += 2;
		}
	}
	for (int theta = 0; theta <= 360; theta += 10) {
		v.pos.Set(1 * cos(theta * Rad), height/2,1 * sin(theta * Rad));
		v.color.Set(name);
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		v.pos.Set(0, height/2, 0);
		v.color.Set(name);
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		index += 2;
	}
	for (int theta = 0; theta <= 360; theta += 10) {
		v.pos.Set(0, -height/2, 0);
		v.color.Set(name);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
		v.pos.Set(1 * cos(theta * Rad), -height / 2,1 * sin(theta * Rad));
		v.color.Set(name);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
		index += 2;
	}
	for (int i = 0; i < index; i++) {
		index_buffer_data.push_back(i);
	}
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index;
	return mesh;
}
//generate a cone
Mesh* MeshBuilder::GenerateCone(const std::string& meshName, float lengthX, float lengthY, float lengthZ, int name)
{
	Vertex v;
	std::vector<Vertex>vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	float height = 2;
	int index = 0;
	Mesh* mesh = new Mesh(meshName);
	for (int theta = 0; theta <= 360; theta += 10) {
		v.pos.Set(height / height*1 * cos(theta * Rad), -height / 2, height / height *1* sin(theta * Rad));
		v.color.Set(name);
		v.normal.Set(height * (height / height * 1 * cos(theta * Rad)), 1, height * (height / height * 1 * sin(theta * Rad)));
		vertex_buffer_data.push_back(v);
		v.pos.Set(0, height / 2, 0);
		v.color.Set(name);
		v.normal.Set(height * (height / height * 1 * cos(theta * Rad)), 1, height * (height / height * 1 * sin(theta * Rad)));
		vertex_buffer_data.push_back(v);
		index += 2;
	}
	for (int theta = 0; theta <= 360; theta += 10) {
		v.pos.Set(0, -height / 2, 0);
		v.color.Set(name);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
		v.pos.Set(height / height * 1 * cos(theta * Rad), -height / 2, height / height * 1 * sin(theta * Rad));
		v.color.Set(name);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
		index += 2;
	}
	for (int i = 0; i < index; i++) {
		index_buffer_data.push_back(i);
	}
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index;
	return mesh;
}
Mesh* MeshBuilder::GenerateHalfCube(const std::string& meshName, float lengthX, float lengthY, float lengthZ, int color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	//front
	v.pos.Set(v1); v.color.Set(color); v.normal.Set(0,0,1);vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color); v.normal.Set(0,0,1);vertex_buffer_data.push_back(v);
	v.pos.Set(v2); v.color.Set(color); v.normal.Set(0,0,1);vertex_buffer_data.push_back(v);
	//Back
	v.pos.Set(v5); v.color.Set(color); v.normal.Set(0,0,-1);vertex_buffer_data.push_back(v);
	v.pos.Set(v6); v.color.Set(color); v.normal.Set(0,0,-1);vertex_buffer_data.push_back(v);
	v.pos.Set(v8); v.color.Set(color); v.normal.Set(0,0,-1);vertex_buffer_data.push_back(v);
	//top
	v.pos.Set(v5); v.color.Set(color);v.normal.Set(0,1,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v1); v.color.Set(color);v.normal.Set(0,1,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v6); v.color.Set(color);v.normal.Set(0,1,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v6); v.color.Set(color);v.normal.Set(0,1,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v1); v.color.Set(color);v.normal.Set(0,1,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v2); v.color.Set(color);v.normal.Set(0,1,0); vertex_buffer_data.push_back(v);
	//left
	v.pos.Set(v5); v.color.Set(color);v.normal.Set(-1,-1,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v8); v.color.Set(color);v.normal.Set(-1,-1,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v1); v.color.Set(color);v.normal.Set(-1,-1,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v1); v.color.Set(color);v.normal.Set(-1,-1,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v8); v.color.Set(color);v.normal.Set(-1,-1,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color);v.normal.Set(-1,-1,0); vertex_buffer_data.push_back(v);
	//right
	v.pos.Set(v8); v.color.Set(color);v.normal.Set(1,0,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v6); v.color.Set(color);v.normal.Set(1,0,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color);v.normal.Set(1,0,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color);v.normal.Set(1,0,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v6); v.color.Set(color);v.normal.Set(1,0,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v2); v.color.Set(color);v.normal.Set(1,0,0); vertex_buffer_data.push_back(v);
	for (int i = 0; i < 24; i++) {
		index_buffer_data.push_back(i);
	}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = 24;
	return mesh;
}
Mesh* MeshBuilder::GenerateOBJ(const std::string& meshName, const std::string& file_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	//Create the mesh and call glBindBuffer, glBufferData
	//Use triangle list and remember to set index size
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}
Mesh* MeshBuilder::GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	float width = 1.f / numCol;
	float height = 1.f / numRow;
	float currentwidth = 0;
	float postiionwidth = 0;
	unsigned offset = 0;
	std::ifstream file;
	std::string output = "    ";
	file.open("WidthTextFile//WidthInfo.txt");
	for (unsigned row = 0; row < numRow; ++row)
	{
		for (unsigned col = 0; col < numCol; ++col)
		{
			output = "    ";
			getline(file, output);
			currentwidth = (width/64) * stof(output);
			postiionwidth = ((1.0f / 64) * stof(output))/2;
			//Task: Add 4 vertices into vertex_buffer_data
			v.pos.Set(postiionwidth, 0.5f, 0.f);     v.normal.Set(1, 1, 1);    v.texCoord.Set(currentwidth+(width *col), -height * (row));    vertex_buffer_data.push_back(v);
			v.pos.Set(-postiionwidth, 0.5f, 0.f); v.normal.Set(-1, 1, 1);   v.texCoord.Set(width * col, -height * (row));    vertex_buffer_data.push_back(v);
			v.pos.Set(-postiionwidth, -0.5, 0.f); v.normal.Set(-1, -1, 1);   v.texCoord.Set(width * col, -height * (row + 1));    vertex_buffer_data.push_back(v);
			v.pos.Set(postiionwidth, -0.5f, 0.f); v.normal.Set(1, -1, 1);   v.texCoord.Set(currentwidth +(width*col), -height * (row + 1));    vertex_buffer_data.push_back(v);
			//Task: Add 6 indices into index_buffer_data
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
		
	}
	
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}
Mesh* MeshBuilder::GenerateOBJMTL(const std::string& meshName, const std::string& file_path, const std::string& mtl_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	std::vector<Material> materials;
	bool success = LoadOBJMTL(file_path.c_str(), mtl_path.c_str(),
		vertices, uvs, normals, materials);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data,
		vertex_buffer_data);
	Mesh* mesh = new Mesh(meshName);
	for (Material& material : materials)
		mesh->materials.push_back(material);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() *
		sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()
		* sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	return mesh;
}
Mesh* MeshBuilder::GenerateColliderBox(const std::string& meshName, double legnthx, double lengthy, double lengthz)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	//bottom
	v.pos.Set(-legnthx / 2, -lengthy / 2, -lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(-legnthx / 2, -lengthy / 2, lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(legnthx / 2, -lengthy / 2, -lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(legnthx / 2, -lengthy / 2, lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(-legnthx / 2, -lengthy / 2, -lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(legnthx / 2, -lengthy / 2, -lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(-legnthx / 2, -lengthy / 2, lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(legnthx / 2, -lengthy / 2, lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	//top
	v.pos.Set(-legnthx / 2, lengthy / 2, -lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(-legnthx / 2, lengthy / 2, lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(legnthx / 2, lengthy / 2, -lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(legnthx / 2, lengthy / 2, lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(-legnthx / 2, lengthy / 2, -lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(legnthx / 2, lengthy / 2, -lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(-legnthx / 2, lengthy / 2, lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(legnthx / 2, lengthy / 2, lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	//sides
	v.pos.Set(-legnthx / 2, lengthy / 2, -lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(-legnthx / 2, -lengthy / 2, -lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(legnthx / 2, lengthy / 2, -lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(legnthx / 2, -lengthy / 2, -lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(-legnthx / 2, lengthy / 2, lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(-legnthx / 2, -lengthy / 2, lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(legnthx / 2, lengthy / 2, lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	v.pos.Set(legnthx / 2, -lengthy / 2, lengthz / 2); v.color.Set(Red); vertex_buffer_data.push_back(v);
	Mesh* mesh = new Mesh(meshName);
	for (int i = 0; i < 24; i++) {
		index_buffer_data.push_back(i);
	}
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_LINES;
	mesh->indexSize = index_buffer_data.size();;
	return mesh;
}


//generate a circle
Mesh* MeshBuilder::GenerateCircle(const std::string& meshName, float lengthX, float lengthY, float lengthZ) {
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	for (int theta = 0; theta <= 360; theta+=10) {
		v.pos.Set(1*cos(theta*(PI/180)), 0, 1*sin(theta*(PI/180))); v.color.Set(Red); vertex_buffer_data.push_back(v);
		v.pos.Set(0, 0, 0);v.color.Set(Blue);vertex_buffer_data.push_back(v);
	}
	for (int i = 0; i < 74; i++) {
		index_buffer_data.push_back(i);
	}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = 74;
	return mesh;
}
Mesh* MeshBuilder::GenerateSemiCircle(const std::string& meshName, float lengthX, float lengthY, float lengthZ, int color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;
	for (int theta = 0; theta <= 180; theta += 10) {
		v.pos.Set(1 * cos(theta * (PI / 180)), 0, 1 * sin(theta * (PI / 180))); v.color.Set(color); vertex_buffer_data.push_back(v);
		v.pos.Set(0, 0, 0); v.color.Set(color); vertex_buffer_data.push_back(v);
	}
	for (int i = 0; i < 38; i++) {
		index_buffer_data.push_back(i);
	}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = 38;
	return mesh;
}
/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	//almost the same as GenerateQuad or GenerateCube
	v.pos.Set(-1000, 0, 0); v.color.Set(1, 0, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(1000, 0, 0); v.color.Set(1, 0, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(0, -1000, 0); v.color.Set(0, 1, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(0, 1000, 0); v.color.Set(0, 1, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -1000); v.color.Set(0, 0, 1);vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, 1000); v.color.Set(0, 0, 1);vertex_buffer_data.push_back(v);
	Mesh* mesh = new Mesh(meshName);
	for (int i = 0; i < 6; i++) {
		index_buffer_data.push_back(i);
	}
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);;
	mesh->mode = Mesh::DRAW_LINES;
	mesh->indexSize = index_buffer_data.size();;
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, float lengthX, float lengthY,int color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	v.pos.Set(v8); v.color.Set(color); v.normal.Set(0, 1, 0);v.texCoord.Set(1,1); vertex_buffer_data.push_back(v);
	v.pos.Set(v7); v.color.Set(color); v.normal.Set(0, 1, 0);v.texCoord.Set(0,1); vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color); v.normal.Set(0, 1, 0);v.texCoord.Set(1,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color); v.normal.Set(0, 1, 0);v.texCoord.Set(1,0); vertex_buffer_data.push_back(v);
	v.pos.Set(v7); v.color.Set(color); v.normal.Set(0, 1, 0);v.texCoord.Set(0,1); vertex_buffer_data.push_back(v);
	v.pos.Set(v3); v.color.Set(color); v.normal.Set(0, 1, 0);v.texCoord.Set(0,0); vertex_buffer_data.push_back(v);
	
	Mesh* mesh = new Mesh(meshName);
	for (int i = 0; i < 6; i++) {
		index_buffer_data.push_back(i);
	}
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = 6;
	return mesh;
}

Mesh* MeshBuilder::GenerateQuad2(const std::string& meshName, float lengthX, float lengthY, int color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	v.pos.Set(-0.5,0.5,0); v.color.Set(color); v.normal.Set(0, 0, 1); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5,-0.5,0); v.color.Set(color); v.normal.Set(0, 0, 1); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5,0.5,0); v.color.Set(color); v.normal.Set(0, 0, 1); v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5,0.5,0); v.color.Set(color); v.normal.Set(0, 0, 1); v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5,-0.5,0); v.color.Set(color); v.normal.Set(0, 0, 1); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5,-0.5,0); v.color.Set(color); v.normal.Set(0, 0, 1); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);

	Mesh* mesh = new Mesh(meshName);
	for (int i = 0; i < 6; i++) {
		index_buffer_data.push_back(i);
	}
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();;
	return mesh;
}

Mesh* MeshBuilder::GenerateQuadRepeat(const std::string& meshName, float lengthX, float lengthY, int color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	v.pos.Set(v8); v.color.Set(color); v.normal.Set(0, 1, 0); v.texCoord.Set(10,10); vertex_buffer_data.push_back(v);
	v.pos.Set(v7); v.color.Set(color); v.normal.Set(0, 1, 0); v.texCoord.Set(0, 10); vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color); v.normal.Set(0, 1, 0); v.texCoord.Set(10, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color); v.normal.Set(0, 1, 0); v.texCoord.Set(10, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v7); v.color.Set(color); v.normal.Set(0, 1, 0); v.texCoord.Set(0, 10); vertex_buffer_data.push_back(v);
	v.pos.Set(v3); v.color.Set(color); v.normal.Set(0, 1, 0); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);

	Mesh* mesh = new Mesh(meshName);
	for (int i = 0; i < 6; i++) {
		index_buffer_data.push_back(i);
	}
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = 6;
	return mesh;
}



/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/

Mesh* MeshBuilder::GenerateCube(const std::string &meshName, float lengthX=1, float lengthY=1, float lengthZ=1,int color=1)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	
	//front
	v.pos.Set(v1); v.color.Set(color); v.normal.Set(0, 0, 1); v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v3); v.color.Set(color); v.normal.Set(0, 0, 1); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v2); v.color.Set(color); v.normal.Set(0, 0, 1); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v2); v.color.Set(color); v.normal.Set(0, 0, 1); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v3); v.color.Set(color); v.normal.Set(0, 0, 1); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color); v.normal.Set(0, 0, 1); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);
	//Back																
	v.pos.Set(v7); v.color.Set(color);v.normal.Set(0,0,-1);    v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v5); v.color.Set(color); v.normal.Set(0, 0, -1); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v8); v.color.Set(color); v.normal.Set(0, 0, -1); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v8); v.color.Set(color); v.normal.Set(0, 0, -1); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v5); v.color.Set(color); v.normal.Set(0, 0, -1); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v6); v.color.Set(color); v.normal.Set(0, 0, -1); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);
	//top
	v.pos.Set(v5); v.color.Set(color);v.normal.Set(0,1,0); v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v1); v.color.Set(color); v.normal.Set(0, 1, 0); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v6); v.color.Set(color); v.normal.Set(0, 1, 0); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v6); v.color.Set(color); v.normal.Set(0, 1, 0); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v1); v.color.Set(color); v.normal.Set(0, 1, 0); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v2); v.color.Set(color); v.normal.Set(0, 1, 0); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);
	//bottom
	v.pos.Set(v3); v.color.Set(color);v.normal.Set(0,-1,0); v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v7); v.color.Set(color); v.normal.Set(0, -1, 0); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color); v.normal.Set(0, -1, 0); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color); v.normal.Set(0, -1, 0); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v7); v.color.Set(color); v.normal.Set(0, -1, 0); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v8); v.color.Set(color); v.normal.Set(0, -1, 0); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);
	//left
	v.pos.Set(v3); v.color.Set(color);v.normal.Set(1,0,0); v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v1); v.color.Set(color); v.normal.Set(1, 0, 0); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v7); v.color.Set(color); v.normal.Set(1, 0, 0); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v7); v.color.Set(color); v.normal.Set(1, 0, 0); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v1); v.color.Set(color); v.normal.Set(1, 0, 0); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v5); v.color.Set(color); v.normal.Set(1, 0, 0); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);
	//right
	v.pos.Set(v8); v.color.Set(color);v.normal.Set(-1,0,0); v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v6); v.color.Set(color); v.normal.Set(-1, 0, 0); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color); v.normal.Set(-1, 0, 0); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v4); v.color.Set(color); v.normal.Set(-1, 0, 0); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(v6); v.color.Set(color); v.normal.Set(-1, 0, 0); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(v2); v.color.Set(color); v.normal.Set(-1, 0, 0); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);
	for (int i = 0; i < 36; i++) {
		index_buffer_data.push_back(i);
}
	Mesh *mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()*sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = 36;
	return mesh;
}