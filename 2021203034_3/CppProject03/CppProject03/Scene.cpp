#include "Scene.h"

Scene::Scene(Graph_lib::Window* wnd)
	: window(wnd)
{
}

Scene::~Scene()
{
	clear();
	removeAllMeshes();
}

void Scene::render()
{
	clear();

	Matrix4x4 mat_view = matrix_lookat(camera.eye, camera.at, camera.up);
	Matrix4x4 mat_proj = matrix_perspective(camera.fovy, camera.aspect_ratio, camera.z_near, camera.z_far);
	Matrix4x4 mat_camera = mat_proj * mat_view;

	for (int i = 0; i < (int)mesh_list.size(); i++)
	{
		Mesh* mesh = mesh_list[i];
		Graph_lib::Lines* lines = mesh->render(window, mat_camera, is_culling_enabled);
		rendered_lines.push_back(lines);
	}
}

void Scene::clear()
{
	for (int i = 0; i < (int)rendered_lines.size(); i++)
	{
		Graph_lib::Lines* lines = rendered_lines[i];
		window->detach(*lines);
		delete lines;
	}
	rendered_lines.clear();
}

Mesh* Scene::addMesh(Geometry geom)
{
	Mesh* mesh = new Mesh();
	mesh->initialize(geom);
	mesh_list.push_back(mesh);

	return mesh;
}

Mesh* Scene::addMesh(const std::string& path)
{
	Mesh* mesh = new Mesh();

	bool is_loaded = mesh->load(path);
	if (!is_loaded)
	{
		delete mesh;
		mesh = nullptr;
	}
	else
	{
		mesh_list.push_back(mesh);
	}

	return mesh;
}

Mesh* Scene::getMesh(int i)
{
	if (i >= 0 && i < (int)mesh_list.size())
	{
		return mesh_list[i];
	}
	else
	{
		return nullptr;
	}
}

void Scene::removeAllMeshes()
{
	for (int i = 0; i < (int)mesh_list.size(); i++)
	{
		delete mesh_list[i];
	}
	mesh_list.clear();
}

void Scene::setLookAt(const Vector3& eye, const Vector3& at, const Vector3& up)
{
	camera.eye = eye;
	camera.at = at;
	camera.up = up;
}

void Scene::setPerspective(float fovy, float aspect_ratio, float z_near, float z_far)
{
	camera.fovy = fovy;
	camera.aspect_ratio = aspect_ratio;
	camera.z_near = z_near;
	camera.z_far = z_far;
}
