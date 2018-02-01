#pragma once

class Vec2D {

	public:
		
		Vec2D();
		Vec2D(float, float);
		~Vec2D();

		Vec2D	operator+(const Vec2D&);
		Vec2D	operator-(const Vec2D&);
		Vec2D	operator*(const Vec2D&);
		Vec2D	operator/(const Vec2D&);
		void	operator=(const Vec2D&);


		Vec2D	operator/(const float);
		Vec2D	operator+(const float);
		Vec2D	operator-(const float);
		Vec2D	operator*(const float);


		float&	 operator[](int);

		float	length();
		Vec2D	normalize();
		Vec2D	absolute();
		float	getFromIndex(int);
		void	setFromIndex(int, float);

		float	x;
		float	y;

};


class Vec3D {

	public:

		Vec3D();
		Vec3D(float, float, float);
		~Vec3D();

		Vec3D	operator+(const Vec3D&);
		Vec3D	operator-(const Vec3D&);
		Vec3D	operator*(const Vec3D&);
		Vec3D	operator/(const Vec3D&);
		void	operator=(const Vec3D&);

		Vec3D	operator+(const Vec2D&);
		Vec3D	operator-(const Vec2D&);
		Vec3D	operator*(const Vec2D&);
		Vec3D	operator/(const Vec2D&);
		void	operator=(const Vec2D&);

		Vec3D	operator/(const float);
		Vec3D	operator+(const float);
		Vec3D	operator-(const float);
		Vec3D	operator*(const float);

		float&	operator[](const int);

		float	length();
		Vec3D	normalize();
		Vec3D	absolute();
		float	getFromIndex(int);
		void	setFromIndex(int, float);

		float	x;
		float	y;
		float	z;

};
