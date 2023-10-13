#pragma once

#include "HW3.h"
#include "Mesh.h"

struct Camera
{
	Vector3 eye;
	Vector3 at;
	Vector3 up;

	float fovy;
	float aspect_ratio;
	float z_near;
	float z_far;
};

class Scene
{
public:
	Scene(Graph_lib::Window* wnd);
	virtual ~Scene();

	void render();
	void clear();

	Mesh* addMesh(Geometry geom);
	Mesh* addMesh(const std::string& path);
	Mesh* getMesh(int i);
	void removeAllMeshes();

	void setLookAt(const Vector3& eye, const Vector3& at, const Vector3& up);
	void setPerspective(float fovy, float aspect_ratio, float z_near, float z_far);

	inline void enableCulling() { is_culling_enabled = true; }
	inline void disableCulling() { is_culling_enabled = false; }
	inline void toggleCulling() { is_culling_enabled = !is_culling_enabled; }

private:
	Graph_lib::Window* window;
	Camera camera;

	std::vector<Mesh*> mesh_list;
	std::vector<Graph_lib::Lines*> rendered_lines;

	bool is_culling_enabled = false;
};
