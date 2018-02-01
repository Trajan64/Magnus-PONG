#include "stdafx.h"
#include "Vec.h"
#include <vector>
#include "Circle.h"


/**	Create an OpenGL 2D circle.
*	
*	 Creates a vertices batch shapping a 2D circle. It's level of detail depends on the value of the first argument passed to the constructor.
*/
Circle::Circle(int definition, float radius) {

	vertices.resize(4 * definition * 2 + 2 + 2);
	indices.resize(4 * definition + 1 + 1);

	float step = 2.0f / definition;

	float x = -1.0;
	float y = -1.0;
	float * current = &x;

	// Add origin to the vertices.
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;
	indices[0] = 0;

	int index = 1;
	for (int j = 0; j < 4; j++) {

		if (j % 2)
			current = &x;
		else
			current = &y;

		for (int i = 0; i < definition; i++) {

			Vec2D normalizedCoordinates = Vec2D(x, y).normalize();

			vertices[index * 2] =		normalizedCoordinates.x * radius;
			vertices[index * 2 + 1] =	normalizedCoordinates.y * radius;
			indices[index] = index;
			index++;

			if (j < 2) {
				*current += step;
			}
			else {
				*current -= step;
			}
		}
	}

	indices[index] = index;

	vertices[index * 2] = vertices[2];
	vertices[index * 2 + 1] = vertices[3];

}


/*
*	Deconstructor.
*/
Circle::~Circle() {

}


/*
*	Draw the circle.
*/
void Circle::draw() {

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
	glDrawElements(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);

}