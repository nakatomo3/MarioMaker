#pragma once
#include <math.h>
class Vector2 {
public:

	//x,y������0�ɂ��鏉����
	Vector2() {
		x, y = 0;
	}

	//x,y�������w�肷�鏉����
	Vector2(float X,float Y) {
		x = X;
		y = Y;
	}

	float GetX() {
		return x;
	}
	float GetY() {
		return y;
	}


	//-------------------------operator-----------------------

	//�����Z
	Vector2 operator+(Vector2 vector) {
		return Vector2(x + vector.x, y + vector.y);
	};
	Vector2 operator+=(Vector2 vector) {
		x += vector.x;
		y += vector.y;
		return Vector2(x, y);
	};


	//�����Z
	Vector2 operator-(Vector2 vector) {
		return Vector2(x - vector.x, y - vector.y);
	};
	Vector2 operator-=(Vector2 vector) {
		x -= vector.x;
		y -= vector.y;
		return Vector2(x, y);
	};

	//�|���Z
	Vector2 operator*(float value) {
		return Vector2(x * value, y * value);
	}
	Vector2 operator*=(float value) {
		x *= value;
		y *= value;
		return Vector2(x, y);
	}


	//����
	float operator*(Vector2 vector) {
		return x * vector.x + y * vector.y;
	}

	//�O��
	float operator^(Vector2 vector) {
		return float(x*vector.y-y*vector.x);
	}

	//����Z
	Vector2 operator/(float num) {
		return Vector2(x / num, y / num);
	}
	Vector2 operator/=(float value) {
		x /= value;
		y /= value;
		return Vector2(x, y);
	}

	bool operator==(Vector2 vector) {
		if (x == vector.x && y == vector.y) {
			return true;
		}
		return false;
	}

	bool operator!=(Vector2 vector) {
		if (x == vector.x && y == vector.y) {
			return false;
		}
		return true;
	}

	//������Ԃ��֐�
	float Magnitude() {
		return (float)sqrt(x * x + y * y);
	}

	//�P�ʃx�N�g����Ԃ��֐�
	Vector2 UnitVector() {
		return Vector2(x / Magnitude(), y / Magnitude());
	}

	void Destroy() {
		delete this;
	}
	~Vector2() {

	}

private:

	float x, y;

};