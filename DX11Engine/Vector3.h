#pragma once
#include "LogWriter.h"
#include <math.h>
#include "main.h"
class Vector3 {
public:

	//x,y,z成分を0にする初期化
	Vector3() {
		x, y, z = 0;
	}

	//x,y成分を指定する初期化
	Vector3(float X, float Y) {
		x = X;
		y = Y;
		z = 0;
	}

	//x,y,z成分を指定する初期化
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

	//足し算
	Vector3 operator+(Vector3 vector) {
		return Vector3(x + vector.x, y + vector.y, z + vector.z);
	};
	Vector3 operator+=(Vector3 vector) {
		x += vector.x;
		y += vector.y;
		z += vector.z;
		return Vector3(x, y, z);
	};

	//引き算
	Vector3 operator-(Vector3 vector) {
		return Vector3(x - vector.x, y - vector.y, z - vector.z);
	};
	Vector3 operator-=(Vector3 vector) {
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		return Vector3(x, y, z);
	};

	//掛け算
	Vector3 operator* (float value) {
		return Vector3(x * value, y * value, z * value);
	};
	Vector3 operator*=(Vector3 vector) {
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		return Vector3(x, y, z);
	};

	//割り算
	Vector3 operator/ (float value) {
		return Vector3(x / value, y / value, z / value);
	};
	Vector3 operator/=(Vector3 vector) {
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;
		return Vector3(x, y, z);
	};

#pragma region D3DXVECTORとの計算

	//足し算
	Vector3 operator+(D3DXVECTOR3 vector) {
		return Vector3(x + vector.x, y + vector.y, z + vector.z);
	};
	Vector3 operator+=(D3DXVECTOR3 vector) {
		x += vector.x;
		y += vector.y;
		z += vector.z;
		return Vector3(x, y, z);
	};

	//引き算
	Vector3 operator-(D3DXVECTOR3 vector) {
		return Vector3(x - vector.x, y - vector.y, z - vector.z);
	};
	Vector3 operator-=(D3DXVECTOR3 vector) {
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		return Vector3(x, y, z);
	};

	//掛け算
	Vector3 operator*=(D3DXVECTOR3 vector) {
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		return Vector3(x, y, z);
	};

	//割り算
	Vector3 operator/=(D3DXVECTOR3 vector) {
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;
		return Vector3(x, y, z);
	};
#pragma endregion

	//内積
	float operator*(Vector3 vector) {
		return x * vector.x + y * vector.y + z * vector.z;
	}

	//外積
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


	//長さを返す関数
	float Magnitude() {
		return sqrt(x * x + y * y + z * z);
	}

	//単位ベクトルを返す関数
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