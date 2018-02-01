#include "stdafx.h"
#include "Vec.h"
#include <math.h>
#include <stdexcept>


Vec2D::Vec2D() {

	x = 0.0f;
	y = 0.0f;

};


Vec2D::~Vec2D() {

};


Vec2D::Vec2D(float x, float y) {

	this->x = x;
	this->y = y;

};



Vec2D Vec2D::operator*(const Vec2D& operand) {

	return Vec2D(x * operand.x, y * operand.y);

};


Vec2D Vec2D::operator/(const Vec2D& operand) {

	return Vec2D(x / operand.x, y / operand.y);

};

Vec2D Vec2D::operator+(const Vec2D& operand) {

	return Vec2D(x + operand.x, y + operand.y);

};


Vec2D Vec2D::operator-(const Vec2D& operand) {

	return Vec2D(x - operand.x, y - operand.y);

};

void Vec2D::operator=(const Vec2D& operand) {

	x = operand.x;
	y = operand.y;

};



/* Vec2D SCALAR OPERATIONS */
Vec2D Vec2D::operator/(const float operand) {

	return Vec2D(x / operand, y / operand);

};

Vec2D Vec2D::operator+(const float operand) {

	return Vec2D(x + operand, y + operand);

};

Vec2D Vec2D::operator-(const float operand) {

	return Vec2D(x - operand, y - operand);

};

Vec2D Vec2D::operator*(const float operand) {

	return Vec2D(x * operand, y * operand);

};



float Vec2D::length() {

	return sqrt(pow(x, 2) + pow(y, 2));

};

Vec2D Vec2D::normalize() {

	float length = this->length();
	return Vec2D(x / length, y / length);

};

float Vec2D::getFromIndex(int index) {

	switch (index) {
		case 0:
			return x;
		case 1:
			return y;
		default:
			// 'shouldn't get there.
			return -1;
	}
}


void Vec2D::setFromIndex(int index, float value) {

	switch (index) {
	case 0:
		x = value;
		return;
	case 1:
		y = value;
		return;
	default:
		// 'shouldn't get there.
		return;
	}

}


float& Vec2D::operator[](const int i) {

	switch (i) {
		case 0:
			return x;
		case 1:
			return y;
	}

	throw std::out_of_range("index out of range");


}

Vec2D Vec2D::absolute() {

	return Vec2D(fabs(x), fabs(y));

}

/* Vec3D */

Vec3D::Vec3D() {

	x = 0.0f;
	y = 0.0f;
	z = 0.0f;

};

Vec3D::~Vec3D() {



};

Vec3D::Vec3D(float x, float y, float z) {

	this->x = x;
	this->y = y;
	this->z = z;

};




Vec3D Vec3D::operator*(const Vec3D& operand) {

	return Vec3D(x * operand.x, y * operand.y, z * operand.z);

};


Vec3D Vec3D::operator/(const Vec3D& operand) {

	return Vec3D(x / operand.x, y / operand.y, z / operand.z);

};

Vec3D Vec3D::operator+(const Vec3D& operand) {

	return Vec3D(x + operand.x, y + operand.y, z + operand.z);

};


Vec3D Vec3D::operator-(const Vec3D& operand) {

	return Vec3D(x - operand.x, y - operand.y, z - operand.z);

};


void Vec3D::operator=(const Vec3D& operand) {

	x = operand.x;
	y = operand.y;
	z = operand.z;

};


/* VEC3D SCALAR OPERATIONS */
Vec3D Vec3D::operator/(const float operand) {

	return Vec3D(x / operand, y / operand, z / operand);

};

Vec3D Vec3D::operator+(const float operand) {

	return Vec3D(x + operand, y + operand, z + operand);

};

Vec3D Vec3D::operator-(const float operand) {

	return Vec3D(x - operand, y - operand, z - operand);

};

Vec3D Vec3D::operator*(const float operand) {

	return Vec3D(x * operand, y * operand, z * operand);

};


float Vec3D::length() {

	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

};

Vec3D Vec3D::normalize() {

	float length = this->length();
	return Vec3D(x / length, y / length, z / length);

};

Vec3D Vec3D::absolute() {

	return Vec3D(fabs(x), fabs(y), fabs(z));

};

float Vec3D::getFromIndex(int index) {

	switch (index) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			// 'shouldn't get there
			return -1;
	}
}

void Vec3D::setFromIndex(int index, float value) {

	switch (index) {
		case 0:
			x = value;
			return;
		case 1:
			y = value;
			return;
		case 2:
			z = value;
			return;
		default:
			// 'shouldn't get there
			return;
	}

}


float& Vec3D::operator[](int i) {

	switch (i) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;		
	}

	throw std::out_of_range("index out of range");
}



Vec3D Vec3D::operator+(const Vec2D& operand) {

	return Vec3D(x + operand.x, y + operand.y, z);

}
Vec3D Vec3D::operator-(const Vec2D& operand) {

	return Vec3D(x - operand.x, y - operand.y, z);

}
Vec3D Vec3D::operator*(const Vec2D& operand) {

	return Vec3D(x * operand.x, y * operand.y, z);

}
Vec3D Vec3D::operator/(const Vec2D& operand) {

	return Vec3D(x / operand.x, y / operand.y, z);

}

void Vec3D::operator=(const Vec2D& operand) {

	x = operand.x;
	y = operand.y;

}