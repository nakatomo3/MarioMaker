#pragma once
#include "LogWriter.h"
#include <math.h>
#include "main.h"
class Vector3 {
public:

	//x,y,z¬•ª‚ğ0‚É‚·‚é‰Šú‰»
	Vector3() {
		x, y, z = 0;
	}

	//x,y¬•ª‚ğw’è‚·‚é‰Šú‰»
	Vector3(float X, float Y) {
		x = X;
		y = Y;
		z = 0;
	}

	//x,y,z¬•ª‚ğw’è‚·‚é‰Šú‰»
	Vector3(float X, float Y, float Z) {
		x = X;
		y = Y;
		z = Z;
	}

	Vector3(D3DXVECTOR3 vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	//-------------------------operator-----------------------

	//‘«‚µZ
	Vector3 operator+(Vector3 vector) {
		return Vector3(x + vector.x, y + vector.y, z + vector.z);
	};
	Vector3 operator+=(Vector3 vector) {
		x += vector.x;
		y += vector.y;
		z += vector.z;
		return Vector3(x, y, z);
	};

	//ˆø‚«Z
	Vector3 operator-(Vector3 vector) {
		return Vector3(x - vector.x, y - vector.y, z - vector.z);
	};
	Vector3 operator-=(Vector3 vector) {
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		return Vector3(x, y, z);
	};

	//Š|‚¯Z
	Vector3 operator* (float value) {
		return Vector3(x * value, y * value, z * value);
	};
	Vector3 operator*= (float value) {
		x *= value;
		y *= value;
		z *= value;
		return Vector3(x, y, z);
	}
	Vector3 operator*=(Vector3 vector) {
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		return Vector3(x, y, z);
	};

	//Š„‚èZ
	Vector3 operator/ (float value) {
		return Vector3(x / value, y / value, z / value);
	};
	Vector3 operator/=(Vector3 vector) {
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;
		return Vector3(x, y, z);
	};

#pragma region D3DXVECTOR‚Æ‚ÌŒvZ

	//‘«‚µZ
	Vector3 operator+(D3DXVECTOR3 vector) {
		return Vector3(x + vector.x, y + vector.y, z + vector.z);
	};
	Vector3 operator+=(D3DXVECTOR3 vector) {
		x += vector.x;
		y += vector.y;
		z += vector.z;
		return Vector3(x, y, z);
	};

	//ˆø‚«Z
	Vector3 operator-(D3DXVECTOR3 vector) {
		return Vector3(x - vector.x, y - vector.y, z - vector.z);
	};
	Vector3 operator-=(D3DXVECTOR3 vector) {
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		return Vector3(x, y, z);
	};

	//Š|‚¯Z
	Vector3 operator*=(D3DXVECTOR3 vector) {
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		return Vector3(x, y, z);
	};

	//Š„‚èZ
	Vector3 operator/=(D3DXVECTOR3 vector) {
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;
		return Vector3(x, y, z);
	};
#pragma endregion

	//“àÏ
	float operator*(Vector3 vector) {
		return x * vector.x + y * vector.y + z * vector.z;
	}

	//ŠOÏ
	Vector3 operator^(Vector3 vector) {
		return Vector3(
			y*vector.z - z * vector.y,
			z*vector.x - x * vector.z,
			x*vector.y - y * vector.x
		);
	}

	bool operator==(Vector3 vector) {
		if (x == vector.x && y == vector.y && z == vector.z) {
			return true;
		}
		return false;
	}

	bool operator!=(Vector3 vector) {
		if (x == vector.x && y == vector.y && z == vector.z) {
			return false;
		}
		return true;
	}


	//’·‚³‚ğ•Ô‚·ŠÖ”
	float Magnitude() {
		return sqrt(x * x + y * y + z * z);
	}

	//’PˆÊƒxƒNƒgƒ‹‚ğ•Ô‚·ŠÖ”
	Vector3 UnitVector() {
		return Vector3(x / Magnitude(), y / Magnitude(), z / Magnitude());
	}

	void Set(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	float GetX() {
		return x;
	}

	float GetY() {
		return y;
	}

	float GetZ() {
		return z;
	}

	D3DXVECTOR3 ConvertD3DVECTOR3() {
		return D3DXVECTOR3(x, y, z);
	}

	static D3DXVECTOR3 ConvertD3DVECTOR3(Vector3 vec) {
		return D3DXVECTOR3(vec.x, vec.y, vec.z);
	}

	void Destroy() {
		delete this;
	}
	~Vector3() {}

	static Vector3 Right() {
		return Vector3(1, 0, 0);
	}

	static Vector3 Left() {
		return Vector3(-1, 0, 0);
	}

	static Vector3 Up() {
		return Vector3(0, 1, 0);
	}

	static Vector3 Down() {
		return Vector3(0, -1, 0);
	}

	static Vector3 Forward() {
		return Vector3(0, 0, 1);
	}

	static Vector3 Back() {
		return Vector3(0, 0, -1);
	}

	static Vector3 One() {
		return Vector3(1, 1, 1);
	}

	static Vector3 Zero() {
		return Vector3(0, 0, 0);
	}

private:
	float x, y, z;

};