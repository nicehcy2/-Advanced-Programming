#pragma once

#include <vector>
#include <string>

#include "Window.h"
#include "Graph.h"

struct Vertex
{
	Vertex() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f } {}
	Vertex(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
	float operator[](int n) {
		switch (n) {
		case 0: return x;
		case 1:	return y;
		case 2: return z;
		default: return 0.0f;
		}
	}

	float x;
	float y;
	float z;
};

struct Face
{
	Face() : i{ -1 }, j{ -1 }, k{ -1 } {}
	Face(int i, int j, int k) : i{ i }, j{ j }, k{ k } {}
	int operator[](int n) {
		switch (n) {
		case 0:	return i;
		case 1:	return j;
		case 2:	return k;
		default: return -1;
		}
	}

	int i;
	int j;
	int k;
};

class VertexBuffer
{
public:
	VertexBuffer();
	explicit VertexBuffer(int size);

	VertexBuffer(const VertexBuffer& vb);
	VertexBuffer(VertexBuffer&& vb);

	~VertexBuffer();

	VertexBuffer& operator=(const VertexBuffer& vb);
	VertexBuffer& operator=(VertexBuffer&& vb);

	Vertex& operator[](int n) { return buffer[n]; }
	const Vertex& operator[](int n) const { return buffer[n]; }

	int size() const { return sz; }
	int capacity() const { return space; }

	void resize(int new_size);
	void reserve(int new_capacity);

	void clear();
	void addVertex(float x, float y, float z);

private:
	int sz = 0;
	int space = 0;
	Vertex* buffer = nullptr;
};

class FaceBuffer
{
public:
	FaceBuffer();
	explicit FaceBuffer(int size);

	FaceBuffer(const FaceBuffer& fb);
	FaceBuffer(FaceBuffer&& fb);

	~FaceBuffer();

	FaceBuffer& operator=(const FaceBuffer& fb);
	FaceBuffer& operator=(FaceBuffer&& fb);

	Face& operator[](int n) { return buffer[n]; }
	const Face& operator[](int n) const { return buffer[n]; }

	int size() const { return sz; }
	int capacity() const { return space; }

	void resize(int new_size);
	void reserve(int new_capacity);

	void clear();
	void addFace(int i, int j, int k);

private:
	int sz = 0;
	int space = 0;
	Face* buffer = nullptr;
};

class Vector4;

class Vector3
{
public:
	Vector3();
	Vector3(const Vector4& v);
	Vector3(float x, float y, float z);
	Vector3(float v[3]);

	float& operator[](int n) { return v[n]; }
	const float& operator[](int n) const { return v[n]; }

	float x() const { return v[0]; }
	float y() const { return v[1]; }
	float z() const { return v[2]; }

private:
	float v[3];
};

class Vector4
{
public:
	Vector4();
	Vector4(const Vector3& v);
	Vector4(float x, float y, float z, float w);
	Vector4(float v[4]);

	float& operator[](int n) { return v[n]; }
	const float& operator[](int n) const { return v[n]; }

	float x() const { return v[0]; }
	float y() const { return v[1]; }
	float z() const { return v[2]; }
	float w() const { return v[3]; }

private:
	float v[4];
};

class Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4(	float _00, float _01, float _02, float _03,
				float _10, float _11, float _12, float _13,
				float _20, float _21, float _22, float _23,
				float _30, float _31, float _32, float _33);
	Matrix4x4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);
	Matrix4x4(float m[16]);

	Vector4& operator[](int m) { return rows[m]; }
	const Vector4& operator[](int m) const { return rows[m]; }

private:
	Vector4 rows[4];
};

std::ostream& operator<<(std::ostream& os, const Vector3& v);
Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(float k, const Vector3& v);
Vector3 operator*(const Vector3& v, float k);
Vector3 operator/(const Vector3& v, float k);
Vector3 operator^(const Vector3& v1, const Vector3& v2);	// cross
float operator%(const Vector3& v1, const Vector3& v2);		// dot

std::ostream& operator<<(std::ostream& os, const Vector4& v);
Vector4 operator+(const Vector4& v1, const Vector4& v2);
Vector4 operator-(const Vector4& v1, const Vector4& v2);
Vector4 operator*(float k, const Vector4& v);
Vector4 operator*(const Vector4& v, float k);
Vector4 operator/(const Vector4& v, float k);
float operator%(const Vector4& v1, const Vector4& v2);		// dot

std::ostream& operator<<(std::ostream& os, const Matrix4x4& m);
Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);
Vector4 operator*(const Matrix4x4& m, const Vector4& v);

float norm(const Vector3& v);
float norm(const Vector4& v);

Vector3 normalize(const Vector3& v);
Vector4 normalize(const Vector4& v);

Vector3 vector3_from_vertex(const Vertex& vertex);
Vector4 vector4_from_vertex(const Vertex& vertex);

Matrix4x4 matrix_identity();
Matrix4x4 matrix_translation(float tx, float ty, float tz);
Matrix4x4 matrix_rotation(const Vector3& axis, float angle);
Matrix4x4 matrix_perspective(float fovy, float aspect_ratio, float z_near, float z_far);
Matrix4x4 matrix_lookat(const Vector3& eye, const Vector3& at, const Vector3& up);

extern const float PI;
float degree_from_radian(float rad);
float radian_from_degree(float deg);
