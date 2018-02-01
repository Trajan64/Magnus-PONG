#pragma once

#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>

class Rect {

	public:
		Rect(float, float);

		void					generateBorders(float);
		void					setTexels(float, float, float, float);
		void					draw();
		void					drawBorder();


	private:

		std::vector<GLfloat>	vertices;
		std::vector<GLfloat>	texcoords;
		std::vector<GLushort>	indices;

		std::vector<GLfloat>	verticesBorders;
		std::vector<GLushort>	indicesBorders;

		float					m_height;
		float					m_width;
		float					m_borderSize;
		bool					m_useTexture;

		void					createBatch(float, float, float, float, int, std::vector<GLfloat> *, std::vector<GLushort> *);



};
