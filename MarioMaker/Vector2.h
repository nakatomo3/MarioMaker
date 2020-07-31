#pragma once
#include <math.h>
class Vector2 {
public:

	//x,y成分を0にする初期化
	Vector2() {
		x, y = 0;
	}

	//x,y成分を指定する初期化
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

	//足し算
	Vector2 operator+(Vector2 vector) {
		return Vector2(x + vector.x, y + vector.y);
	};
	Vector2 operator+=(Vector2 vector) {
		x += vector.x;
		y += vector.y;
		return Vector2(x, y);
	};


	//引き算
	Vector2 operator-(Vector2 vector) {
		return Vector2(x - vector.x, y - vector.y);
	};
	Vector2 operator-=(Vector2 vector) {
		x -= vector.x;
		y -= vector.y;
		return Vector2(x, y);
	};

	//掛け算
	Vector2 operator*(float value) {
		return Vector2(x * value, y * value);
	}
	Vector2 operator*=(float value) {
		x *= value;
		y *= value;
		return Vector2(x, y);
	}


	//内積
	float operator*(Vector2 vector) {
		return x * vector.x + y * vector.y;
	}

	//外積
	float operator^(Vector2 vector) {
		return float(x*vector.y-y*vector.x);
	}

	//割り算
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

	//長さを返す関数
	float Magnitude() {
		return (float)sqrt(x * x + y * y);
	}

	//単位ベクトルを返す関数
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