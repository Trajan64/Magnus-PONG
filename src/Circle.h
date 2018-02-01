#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>

class Circle {

	public:

		Circle(int, float);
		~Circle();

		void					draw();

	private:

		std::vector<GLfloat>	vertices;
		std::vector<GLushort>	indices;
};