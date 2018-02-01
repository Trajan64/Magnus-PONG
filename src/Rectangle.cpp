#include "stdafx.h"
#include "Rectangle.h"


/** Creates a rectangular OpenGL shape
*
*	Allows the generation and rendering of an OpenGL vertices batch that is shaping a rectangle. 
*/
Rect::Rect(float width, float height) {

	m_width = width;
	m_height = height;

	m_useTexture = 0;

	vertices.resize(4 * 2);
	indices.resize(4);

	createBatch(0.0f, 0.0f, width, height, 0, &vertices, &indices);

}


/*
*	Surrounds the shape with borders.
*/
void Rect::generateBorders(float size) {

	verticesBorders.resize(4 * 4 * 2);
	indicesBorders.resize(4 * 4);

	createBatch((m_width + size) / 2.0f, 0.0f, size, m_height, 0, &verticesBorders, &indicesBorders);
	createBatch((-m_width - size) / 2.0f, 0.0f, size, m_height, 4, &verticesBorders, &indicesBorders);

	createBatch(0.0f, (m_height + size) / 2.0f, m_width+size*2, size, 8, &verticesBorders, &indicesBorders);
	createBatch(0.0f, (-m_height - size) / 2.0f, m_width + size*2, size, 12, &verticesBorders, &indicesBorders);

}


/*
*	Set shape's texels coordinates.
*/
void Rect::setTexels(float x1, float y1, float x2, float y2) {

	texcoords.resize(4 * 2);

	// Generate texels batch.
	for (int i = 0; i < 4; i++) {

		texcoords[(i * 2)] =	(i == 0 || i == 3) ? x1 : x2;
		texcoords[(i * 2) + 1] = (i < 2) ? y1 : y2;

	}

	// Indicate that we wish to make use of the texel batch during the drawing process.
	m_useTexture = 1;

}


/*
*	Helper method. Setup a batch of vertices.
*/
void Rect::createBatch(float offsetX, float offsetY, float width, float height, int startAt, std::vector<GLfloat> * attributes, std::vector<GLushort> * indices) {

	float halfWidth = width / 2.0f;
	float halfheight = height / 2.0f;

	for (int i = 0; i < 4; i++) {
		(*attributes)[(startAt + i) * 2] = (i == 0 || i == 3) ? (offsetX - halfWidth) : (offsetX + halfWidth);
		(*attributes)[(startAt + i) * 2 + 1] = (i < 2) ? (offsetY + halfheight) : (offsetY - halfheight);

		if (indices) {

			(*indices)[startAt + i] = startAt + i;

		}

	}

}

/*
*	Pass the shape's data to OpenGL so that it will be drawn on screen.
*/
void Rect::draw() {
	glDisableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	if (m_useTexture) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
	}
	glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT, &indices[0]);
}

/*
*	Renders the shape's generated borders. 
*/
void Rect::drawBorder() {

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, &verticesBorders[0]);
	glDrawElements(GL_QUADS, indicesBorders.size(), GL_UNSIGNED_SHORT, &indicesBorders[0]);

}