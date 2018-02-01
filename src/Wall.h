#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include "Circle.h"
#include "Rectangle.h"
#include "Font.h"
#include "Vec.h"

class Wall {

	public:
		Wall(float, float, Vec3D, Vec3D, PNGTexture *);
		~Wall();

		void					draw();
		void					drawSphereSilhouette(Vec3D&, float);
		float&					operator[](const unsigned int);
		Vec3D&					getNormal();
		Vec3D&					getPosition();


	private:

		GLuint					m_textureId;
		Vec3D					m_normal;
		Vec3D					m_position;
		Circle *				m_shadow;
		PNGTexture *			m_texture;
		Rect *					m_shape;


};

