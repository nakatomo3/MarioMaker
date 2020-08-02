#pragma once
#include <math.h>
class Vector2 {
public:

	//x,y¬•ª‚ğ0‚É‚·‚é‰Šú‰»
	Vector2() {
		x, y = 0;
	}

	//x,y¬•ª‚ğw’è‚·‚é‰Šú‰»
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

	//‘«‚µZ
	Vector2 operator+(Vector2 vector) {
		return Vector2(x + vector.x, y + vector.y);
	};
	Vector2 operator+=(Vector2 vector) {
		x += vector.x;
		y += vector.y;
		return Vector2(x, y);
	};


	//ˆø‚«Z
	Vector2 operator-(Vector2 vector) {
		return Vector2(x - vector.x, y - vector.y);
	};
	Vector2 operator-=(Vector2 vector) {
		x -= vector.x;
		y -= vector.y;
		return Vector2(x, y);
	};

	//Š|‚¯Z
	Vector2 operator*(float value) {
		return Vector2(x * value, y * value);
	}
	Vector2 operator*=(float value) {
		x *= value;
		y *= value;
		return Vector2(x, y);
	}


	//“àÏ
	float operator*(Vector2 vector) {
		return x * vector.x + y * vector.y;
	}

	//ŠOÏ
	float operator^(Vector2 vector) {
		return float(x*vector.y-y*vector.x);
	}

	//Š„‚èZ
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

	//’·‚³‚ğ•Ô‚·ŠÖ”
	float Magnitude() {
		return (float)sqrt(x * x + y * y);
	}

	//’PˆÊƒxƒNƒgƒ‹‚ğ•Ô‚·ŠÖ”
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