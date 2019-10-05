#include "vector2.h"
#include <cmath>

Vector2::Vector2() {
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(double x, double y) {
	this->x = x;
	this->y = y;
}

void Vector2::setX(double x) {
	this->x = x;
}

void Vector2::setY(double y) {
	this->y = y;
}

double Vector2::getX() {
	return x;
}

double Vector2::getY() {
	return y;
}

double Vector2::getNorm() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

void Vector2::normalize() {
	double norm = getNorm();
	if (norm != 0.0f) {
		x = x / norm;
		y = y / norm;
	}
}

void Vector2::rotate(float angle, Angle_units units)
{
	if (units) {
		angle = (float)Degress_to_Rad(angle);
	}
	double temp_x = x;
	double temp_y = y;
	this->x = (temp_x * cos(angle) - temp_y * sin(angle));
	this->y = (temp_x * sin(angle) + temp_y * cos(angle));
}

double getArg(Vector2 &v1, Vector2 &v2, Angle_units units)
{
	if ((v1*v2) == 0.0) {
		if (units) {
			double product_1 = v1.getY() * v2.getX();
			double product_2 = v1.getX() * v2.getY();
			if (!product_1) {
				if (product_2 > 0) {
					return Rad_to_Degress(pi / 2);
				}
				else {
					return - Rad_to_Degress(pi / 2);
				}
			}
			else {
				if (product_1 > 0) {
					return -Rad_to_Degress(pi / 2);
				}
				else {
					return Rad_to_Degress(pi / 2);
				}
			}			
		}
		else {
			if (v2.getX() > v1.getX()) {
				return (pi / 2);
			}
			else {
				return -(pi / 2);
			}
		}
	}
	else {
		if (units) {
			double result = (v1*v2) / (v1.getNorm()*v2.getNorm());
			if (result > 1)
				result = 1;
			else if (result < -1) {
				result = -1;
			}
			return Rad_to_Degress(acos(result));
		}
		else {
			double result = (v1*v2) / (v1.getNorm()*v2.getNorm());
			if (result > 1)
				result = 1;
			else if (result < -1) {
				result = -1;
			}
			return (acos(result));
		}

	}
}

Vector2 &Vector2::operator=(const Vector2 &v)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}

bool Vector2::operator==(const Vector2 & v)
{
	if (this->x == v.x && this->y == v.y) {
		return true;
	}
	else {
		return false;
	}
}

Vector2 operator+(const Vector2 &v1, const Vector2 &v2)
{
	return Vector2((v1.x + v2.x), (v1.y + v2.y));
}

Vector2 operator+(const Vector2 &v, double a)
{
	return Vector2((v.x + a), (v.y + a));
}

Vector2 operator+(double a, const Vector2 &v)
{
	return Vector2((v.x + a), (v.y + a));
}

Vector2 operator-(const Vector2 &v1, const Vector2 &v2)
{
	return Vector2((v1.x - v2.x), (v1.y - v2.y));
}

Vector2 operator-(const Vector2 &v, double a)
{
	return Vector2((v.x - a), (v.y - a));
}

Vector2 operator-(double a, const Vector2 &v)
{
	return Vector2((v.x - a), (v.y - a));
}

double operator*(const Vector2 &v1, const Vector2 &v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y));
}

Vector2 operator*(const Vector2 &v, double a)
{
	return Vector2((v.x * a), (v.y * a));
}

Vector2 operator*(double a, const Vector2 &v)
{
	return Vector2((v.x * a), (v.y * a));
}

std::ostream &operator<<(std::ostream &out, const Vector2 &v) {
	out << v.x << " + " << v.y << "i" << std::endl;
	return out;
}



