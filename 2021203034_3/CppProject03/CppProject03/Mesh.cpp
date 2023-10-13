#include "Mesh.h"

Mesh::Mesh()
	: translation(0, 0, 0), rotation_axis(1, 0, 0), rotation_angle(0)
{
}

Mesh::~Mesh()
{
}

Mesh::Mesh(const Mesh& mesh)
	: vertex_buffer(mesh.vertex_buffer), face_buffer(mesh.face_buffer),
	translation(mesh.translation), rotation_axis(mesh.rotation_axis), rotation_angle(mesh.rotation_angle)
{
}

Mesh::Mesh(Mesh&& mesh)
	: vertex_buffer(std::move(mesh.vertex_buffer)), face_buffer(std::move(mesh.face_buffer)),
	translation(std::move(mesh.translation)), rotation_axis(std::move(mesh.rotation_axis)), rotation_angle(std::move(mesh.rotation_angle))
{
}

Mesh& Mesh::operator=(const Mesh& mesh)
{
	vertex_buffer = mesh.vertex_buffer;
	face_buffer = mesh.face_buffer;
	translation = mesh.translation;
	rotation_axis = mesh.rotation_axis;
	rotation_angle = mesh.rotation_angle;

	return *this;
}

Mesh& Mesh::operator=(Mesh&& mesh)
{
	vertex_buffer = std::move(mesh.vertex_buffer);
	face_buffer = std::move(mesh.face_buffer);
	translation = std::move(mesh.translation);
	rotation_axis = std::move(mesh.rotation_axis);
	rotation_angle = std::move(mesh.rotation_angle);

	return *this;
}

void Mesh::addVertex(float x, float y, float z)
{
	vertex_buffer.addVertex(x, y, z);
}

void Mesh::addFace(int i, int j, int k)
{
	face_buffer.addFace(i, j, k);
}

int Mesh::getNumVertices()
{
	return vertex_buffer.size();
}

int Mesh::getNumFaces()
{
	return face_buffer.size();
}

const Vertex* Mesh::getVertex(int n)
{
	if (n >= 0 && n < getNumVertices())
	{
		return &vertex_buffer[n];
	}
	else
	{
		return nullptr;
	}
}

const Face* Mesh::getFace(int n)
{
	if (n >= 0 && n < getNumFaces())
	{
		return &face_buffer[n];
	}
	else
	{
		return nullptr;
	}
}

bool Mesh::setVertex(int n, float x, float y, float z)
{
	if (n >= 0 && n < getNumVertices())
	{
		vertex_buffer[n] = Vertex(x, y, z);
		return true;
	}
	else
	{
		return false;
	}
}

bool Mesh::setFace(int n, int i, int j, int k)
{
	if (n >= 0 && n < getNumFaces())
	{
		face_buffer[n] = Face(i, j, k);
		return true;
	}
	else
	{
		return false;
	}
}

void Mesh::clear()
{
	vertex_buffer.clear();
	face_buffer.clear();
}

void Mesh::initialize(Geometry geom)
{
	clear();

	float s = 0.5f;

	switch (geom) {
	case Geometry::CUBE:
		addVertex(-s, +s, +s);
		addVertex(+s, +s, +s);
		addVertex(+s, -s, +s);
		addVertex(-s, -s, +s);
		addVertex(+s, +s, -s);
		addVertex(-s, +s, -s);
		addVertex(-s, -s, -s);
		addVertex(+s, -s, -s);

		addFace(0, 2, 1);
		addFace(2, 0, 3);
		addFace(1, 7, 4);
		addFace(7, 1, 2);
		addFace(4, 6, 5);
		addFace(6, 4, 7);
		addFace(5, 3, 0);
		addFace(3, 5, 6);
		addFace(5, 1, 4);
		addFace(1, 5, 0);
		addFace(3, 7, 2);
		addFace(7, 3, 6);
		break;
	}

}

bool Mesh::load(const std::string& path)
{
	vertex_buffer.clear();
	face_buffer.clear();

	std::ifstream is(path.c_str());
	if (!is.is_open())
	{
		return false;
	}

	int num_vertices = 0;
	int num_faces = 0;

	is >> num_vertices;
	is >> num_faces;

	for (int v = 0; v < num_vertices; v++)
	{
		float x, y, z;
		is >> x >> y >> z;
		vertex_buffer.addVertex(x, y, z);
	}

	for (int f = 0; f < num_faces; f++)
	{
		int v1, v2, v3;
		is >> v1 >> v2 >> v3;
		face_buffer.addFace(v1 - 1, v2 - 1, v3 - 1);
	}

	return true;
}

bool Mesh::save(const std::string& path)
{
	std::ofstream os(path.c_str());
	if (!os.is_open())
	{
		return false;
	}

	int num_vertices = vertex_buffer.size();
	int num_faces = face_buffer.size();

	os << num_vertices << endl;
	os << num_faces << endl;

	for (int v = 0; v < num_vertices; v++)
	{
		Vertex vertex = vertex_buffer[v];
		os << vertex.x << "\t" << vertex.y << "\t" << vertex.z << endl;
	}
	os << endl;

	for (int f = 0; f < num_faces; f++)
	{
		Face face = face_buffer[f];
		os << face.i << "\t" << face.j << "\t" << face.k << endl;
	}

	return true;
}

void Mesh::setTranslation(const Vector3& trans)
{
	translation = trans;
}

void Mesh::setRotation(const Vector3& rot_axis, float rot_angle)
{
	rotation_axis = rot_axis;
	rotation_angle = rot_angle;
}

Graph_lib::Lines* Mesh::render(Graph_lib::Window* wnd, const Matrix4x4& mat_camera, bool is_culling_enabled/*=false*/)
{
	float width = (float)wnd->x_max();
	float height = (float)wnd->y_max();

	float hw = width / 2.0f;
	float hh = height / 2.0f;

	Matrix4x4 mat_trans = matrix_translation(translation.x(), translation.y(), translation.z());
	Matrix4x4 mat_rot = matrix_rotation(rotation_axis, rotation_angle);
	Matrix4x4 mat_modelview = mat_camera * mat_trans * mat_rot;

	Graph_lib::Lines* lines = new Graph_lib::Lines();

	for (int i = 0; i < face_buffer.size(); i++)
	{
		Face& face = face_buffer[i];

		Vertex& v_i = vertex_buffer[face.i];
		Vertex& v_j = vertex_buffer[face.j];
		Vertex& v_k = vertex_buffer[face.k];

		Vector4 vec4_i = vector4_from_vertex(v_i);
		Vector4 vec4_j = vector4_from_vertex(v_j);
		Vector4 vec4_k = vector4_from_vertex(v_k);

		Vector3 vec3_i(mat_modelview * vec4_i);
		Vector3 vec3_j(mat_modelview * vec4_j);
		Vector3 vec3_k(mat_modelview * vec4_k);

		Vector3 vec3_n = (vec3_j - vec3_i) ^ (vec3_k - vec3_i);
		float dot = vec3_n % Vector3(0, 0, -1);

		if (!is_culling_enabled || is_culling_enabled && dot < 0.0f)
		{
			Graph_lib::Point p_i((int)(vec3_i.x() * hw + hw), (int)(height - vec3_i.y() * hh - hh));
			Graph_lib::Point p_j((int)(vec3_j.x() * hw + hw), (int)(height - vec3_j.y() * hh - hh));
			Graph_lib::Point p_k((int)(vec3_k.x() * hw + hw), (int)(height - vec3_k.y() * hh - hh));

			lines->add(p_i, p_j);
			lines->add(p_j, p_k);
			lines->add(p_k, p_i);
		}
	}
	wnd->attach(*lines);

	return lines;
}


