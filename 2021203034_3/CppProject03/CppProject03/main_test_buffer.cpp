#include "HW3.h"


int menuMain()
{
	cout << "<<< TEST BUFFER >>>" << endl;
	cout << "1. Vertex Buffer" << endl;
	cout << "2. Face Buffer" << endl;
	cout << "3. Exit" << endl;
	cout << endl;

	int option = -1;
	do
	{
		cout << "Choose an option (1-3): ";
		cin >> option;
	} while (option < 1 || option > 3);

	cout << endl;

	return option;
}

int menuVertexBuffer()
{
	cout << "[[ VERTEX BUFFER ]]" << endl;
	cout << "1. Print All Vertices" << endl;
	cout << "2. Add Vertex" << endl;
	cout << "3. Add Random Vertices" << endl;
	cout << "4. Return" << endl;
	cout << endl;

	int option = -1;
	do
	{
		cout << "Choose an option (1-4): ";
		cin >> option;
	} while (option < 1 || option > 4);

	cout << endl;

	return option;
}

int menuFaceBuffer()
{
	cout << "[[ FACE BUFFER ]]" << endl;
	cout << "1. Print All Faces" << endl;
	cout << "2. Add Face" << endl;
	cout << "3. Add Random Faces" << endl;
	cout << "4. Return" << endl;
	cout << endl;

	int option = -1;
	do
	{
		cout << "Choose an option (1-4): ";
		cin >> option;
	} while (option < 1 || option > 4);

	cout << endl;

	return option;
}

void printAllVertices(const VertexBuffer& vertex_buffer)
{
	int n = vertex_buffer.size();
	
	cout << "(*) Print vertices..." << endl;
	cout << "# of vertices = " << n << endl << endl;
	
	for (int i=0; i < n; i++)
	{
		Vertex v = vertex_buffer[i];
		cout << "[" << i << "]: (" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
	}
	cout << endl;
}

void addVertex(VertexBuffer& vertex_buffer)
{
	float x, y, z;
	cout << "Input the position of a new vertex: ";
	cin >> x >> y >> z;
	cout << endl;

	vertex_buffer.addVertex(x, y, z);
}

void addRandomVertices(VertexBuffer& vertex_buffer)
{
	unsigned int n;
	cout << "Input the number of new vertices: ";
	cin >> n;
	cout << endl;

	float range = 100.0f;

	for (unsigned int i = 0; i < n; i++)
	{
		float x = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
		float y = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
		float z = (float)rand() / (float)RAND_MAX * range * 2.0f - range;

		vertex_buffer.addVertex(x, y, z);
	}
}

void printAllFaces(const FaceBuffer& face_buffer)
{
	int n = face_buffer.size();

	cout << "(*) Print faces..." << endl;
	cout << "# of faces = " << n << endl << endl;

	for (int i = 0; i < n; i++)
	{
		Face f = face_buffer[i];
		cout << "[" << i << "]: (" << f.i << ", " << f.j << ", " << f.k << ")" << endl;
	}
	cout << endl;
}

void addFace(FaceBuffer& face_buffer)
{
	int i, j, k;
	cout << "Input the indices of a new face: ";
	cin >> i >> j >> k;
	cout << endl;

	face_buffer.addFace(i, j, k);
}

void addRandomFaces(FaceBuffer& face_buffer)
{
	unsigned int n;
	cout << "Input the number of new faces: ";
	cin >> n;
	cout << endl;

	int range = 100;

	for (unsigned int f = 0; f < n; f++)
	{
		int i = rand() % range;
		int j = rand() % range;
		int k = rand() % range;

		face_buffer.addFace(i, j, k);
	}
}

VertexBuffer manageVertexBuffer(VertexBuffer vertex_buffer)
{
	while (true)
	{
		int list_option = menuVertexBuffer();

		switch (list_option) {
		case 1:
			printAllVertices(vertex_buffer);
			break;

		case 2:
			addVertex(vertex_buffer);
			break;

		case 3:
			addRandomVertices(vertex_buffer);
			break;

		case 4:
			return vertex_buffer;
		}
	}
}

FaceBuffer manageFaceBuffer(FaceBuffer face_buffer)
{
	while (true)
	{
		int list_option = menuFaceBuffer();

		switch (list_option) {
		case 1:
			printAllFaces(face_buffer);
			break;

		case 2:
			addFace(face_buffer);
			break;

		case 3:
			addRandomFaces(face_buffer);
			break;

		case 4:
			return face_buffer;
		}
	}
}

int main()
{
	VertexBuffer vertex_buffer;
	FaceBuffer face_buffer;

	while (true)
	{
		int main_option = menuMain();

		switch (main_option) {
		case 1:
			vertex_buffer = manageVertexBuffer(vertex_buffer);
			break;

		case 2:
			face_buffer = manageFaceBuffer(face_buffer);
			break;

		case 3:
			return 0;
		}
	}
}