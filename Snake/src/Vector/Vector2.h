#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

#define Rad_to_Degress(x) (x * 57.2957795)
#define Degress_to_Rad(x) (x * 0.01745329)

const double pi = 3.14159265359;

typedef enum {
	rad,
	degrees
}Angle_units;

class Vector2
{
	double x, y;
public:
	Vector2();
	Vector2(double x, double y);
	Vector2(const Vector2 &v) { x = v.x; y = v.y; }
	void setX(double x);
	void setY(double y);
	double getX();
	double getY();
	double getNorm();
	void normalize();
	void rotate(float angle, Angle_units units);
	friend std::ostream &operator<<(std::ostream &out, const Vector2 &v);
	friend Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
	friend Vector2 operator+(const Vector2 &v, double a);
	friend Vector2 operator+(double a, const Vector2 &v);
	friend Vector2 operator-(const Vector2 &v1, const Vector2 &v2);
	friend Vector2 operator-(const Vector2 &v, double a);
	friend Vector2 operator-(double a, const Vector2 &v);
	friend double operator*(const Vector2 &v1, const Vector2 &v2);
	friend Vector2 operator*(const Vector2 &v, double a);
	friend Vector2 operator*(double a, const Vector2 &v);
	friend double getArg(Vector2 &v1, Vector2 &v2, Angle_units units);
	Vector2 &operator=(const Vector2 &v);
	bool operator==(const Vector2 &v);
};

#endif // VECTOR2_H


