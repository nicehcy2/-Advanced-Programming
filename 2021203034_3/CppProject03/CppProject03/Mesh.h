#pragma once

#include "HW3.h"

enum class Geometry
{
	NONE = -1,
	CUBE = 0,
};

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	Mesh(const Mesh& mesh);
	Mesh(Mesh&& mesh);

	Mesh& operator=(const Mesh& mesh);
	Mesh& operator=(Mesh&& mesh);

	void initialize(Geometry geom);
	void clear();

	bool load(const std::string& path);
	bool save(const std::string& path);

	void addVertex(float x, float y, float z);
	void addFace(int i, int j, int k);

	int getNumVertices();
	int getNumFaces();

	const Vertex* getVertex(int n);
	const Face* getFace(int n);

	bool setVertex(int n, float x, float y, float z);
	bool setFace(int n, int i, int j, int k);

	void setTranslation(const Vector3& trans);
	void setRotation(const Vector3& rot_axis, float rot_angle);

	Graph_lib::Lines* render(Graph_lib::Window* wnd, const Matrix4x4& mat_camera, bool is_cull_enabled = false);

private:
	VertexBuffer vertex_buffer;
	FaceBuffer face_buffer;

	Vector3 translation;
	Vector3 rotation_axis;
	float rotation_angle;
};
