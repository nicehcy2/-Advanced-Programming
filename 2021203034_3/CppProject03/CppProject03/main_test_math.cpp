#include "HW3.h"

int menuMain()
{
	cout << "<<< TEST MATH >>>" << endl;
	cout << "1. Vector3" << endl;
	cout << "2. Vector4" << endl;
	cout << "3. Matrix4x4" << endl;
	cout << "4. Exit" << endl;
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

int menuVector3()
{
	cout << "[[ VECTOR3 ]]" << endl;
	cout << "1. Addition" << endl;
	cout << "2. Scalar Multiplication" << endl;
	cout << "3. Dot Product" << endl;
	cout << "4. Cross Product" << endl;
	cout << "5. Return" << endl;
	cout << endl;

	int option = -1;
	do
	{
		cout << "Choose an option (1-5): ";
		cin >> option;
	} while (option < 1 || option > 5);

	cout << endl;

	return option;
}

int menuVector4()
{
	cout << "[[ VECTOR4 ]]" << endl;
	cout << "1. Addition" << endl;
	cout << "2. Scalar Multiplication" << endl;
	cout << "3. Dot Product" << endl;
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

int menuMatrix4x4()
{
	cout << "[[ MATRIX4X4 ]]" << endl;
	cout << "1. Addition" << endl;
	cout << "2. Multiplication" << endl;
	cout << "3. Return" << endl;
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

Vector3 vec3_Select()
{
	float range = 1.0f;

	Vector3 vec3_list[4];
	for (int i = 0; i < 4; i++)
	{
		float x = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
		float y = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
		float z = (float)rand() / (float)RAND_MAX * range * 2.0f - range;

		vec3_list[i] = Vector3(x, y, z);
		cout << "[" << i << "]: " << vec3_list[i] << endl;
	}

	while (true)
	{
		cout << "Choose a vector: ";

		int n;
		cin >> n;

		if (n >= 0 && n < 4)
		{
			cout << endl;
			return vec3_list[n];
		}
	}

	return Vector3(0, 0, 0);
}

Vector4 vec4_Select()
{
	float range = 1.0f;

	Vector4 vec4_list[4];
	for (int i = 0; i < 4; i++)
	{
		float x = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
		float y = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
		float z = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
		float w = (float)rand() / (float)RAND_MAX * range * 2.0f - range;

		vec4_list[i] = Vector4(x, y, z, w);
		cout << "[" << i << "]: " << vec4_list[i] << endl;
	}

	while (true)
	{
		cout << "Choose a vector: ";

		int n;
		cin >> n;

		if (n >= 0 && n < 4)
		{
			cout << endl;
			return vec4_list[n];
		}
	}

	return Vector3(0, 0, 0);
}

Matrix4x4 mat4x4_Select()
{
	Matrix4x4 mat4x4_list[4];
	for (int i = 0; i < 4; i++)
	{
		int dice = rand() % 2;

		switch (dice) 
		{
			case 0:
			{
				float range = 1.0f;
				float tx = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
				float ty = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
				float tz = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
				mat4x4_list[i] = matrix_translation(tx, ty, tz);
			}
			break;

			case 1:
			{
				float range = 1.0f;
				float ax = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
				float ay = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
				float az = (float)rand() / (float)RAND_MAX * range * 2.0f - range;
				float angle = (float)rand() / (float)RAND_MAX * 2.0f * PI;

				Vector3 axis(ax, ay, az);
				axis = normalize(axis);
				
				mat4x4_list[i] = matrix_rotation(axis, angle);
			}
			break;
		}

		cout << "[" << i << "]: " << mat4x4_list[i] << endl;
	}

	while (true)
	{
		cout << "Choose a vector: ";

		int n;
		cin >> n;

		if (n >= 0 && n < 4)
		{
			cout << endl;
			return mat4x4_list[n];
		}
	}
}

void vec3_Add()
{
	Vector3 v1 = vec3_Select();
	Vector3 v2 = vec3_Select();
	Vector3 v = v1 + v2;

	cout << v1 << " + " << v2 << " = " << v << endl;
	cout << endl;
}

void vec3_Mul()
{
	float k;
	cout << "Input a scalar value: ";
	cin >> k;
	cout << endl;

	Vector3 v = vec3_Select();
	Vector3 u = k * v;

	cout << k << " * " << v << " = " << u << endl;
	cout << endl;
}

void vec3_Dot()
{
	Vector3 v1 = vec3_Select();
	Vector3 v2 = vec3_Select();
	float d = v1 % v2;

	cout << v1 << " % " << v2 << " = " << d << endl;
	cout << endl;
}

void vec3_Cross()
{
	Vector3 v1 = vec3_Select();
	Vector3 v2 = vec3_Select();
	Vector3 v = v1 ^ v2;

	cout << v1 << " ^ " << v2 << " = " << v << endl;
	cout << endl;
}

void vec4_Add()
{
	Vector4 v1 = vec4_Select();
	Vector4 v2 = vec4_Select();
	Vector4 v = v1 + v2;

	cout << v1 << " + " << v2 << " = " << v << endl;
	cout << endl;
}

void vec4_Mul()
{
	float k;
	cout << "Input a scalar value: ";
	cin >> k;
	cout << endl;

	Vector4 v = vec4_Select();
	Vector4 u = k * v;

	cout << k << " * " << v << " = " << u << endl;
	cout << endl;
}

void vec4_Dot()
{
	Vector4 v1 = vec3_Select();
	Vector4 v2 = vec3_Select();
	float d = v1 % v2;

	cout << v1 << " % " << v2 << " = " << d << endl;
	cout << endl;
}

void mat4x4_Add()
{
	Matrix4x4 m1 = mat4x4_Select();
	Matrix4x4 m2 = mat4x4_Select();
	Matrix4x4 m = m1 + m2;

	cout << m1 << " + " << endl;
	cout << m2 << " = " << endl;
	cout << m << endl;
	cout << endl;
}

void mat4x4_Mul()
{
	Matrix4x4 m1 = mat4x4_Select();
	Matrix4x4 m2 = mat4x4_Select();
	Matrix4x4 m = m1 * m2;

	cout << m1 << " * " << endl;
	cout << m2 << " = " << endl;
	cout << m << endl;
	cout << endl;
}

void testVector3()
{
	while (true)
	{
		int list_option = menuVector3();

		switch (list_option) {
		case 1:
			vec3_Add();
			break;

		case 2:
			vec3_Mul();
			break;

		case 3:
			vec3_Dot();
			break;

		case 4:
			vec3_Cross();
			break;

		case 5:
			return;
		}
	}
}

void testVector4()
{
	while (true)
	{
		int list_option = menuVector4();

		switch (list_option) {
		case 1:
			vec4_Add();
			break;

		case 2:
			vec4_Mul();
			break;

		case 3:
			vec4_Dot();
			break;

		case 4:
			return;
		}
	}
}

void testMatrix4x4()
{
	while (true)
	{
		int list_option = menuMatrix4x4();

		switch (list_option) {
		case 1:
			mat4x4_Add();
			break;

		case 2:
			mat4x4_Mul();
			break;

		case 3:
			return;
		}
	}
}

int main()
{
	while (true)
	{
		int main_option = menuMain();

		switch (main_option) {
		case 1:
			testVector3();
			break;

		case 2:
			testVector4();
			break;

		case 3:
			testMatrix4x4();
			break;

		case 4:
			return 0;
		}
	}
}
