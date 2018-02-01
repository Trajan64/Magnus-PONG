#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;


class PNGTexture {

	public:

		PNGTexture(const char *, const bool);

		int				getId();
		int				getWidth();
		int				getHeight();
		void			bind();

	private:

		void			setup();

		GLuint			m_id;
		GLubyte *		m_data;
		bool			m_hasAlpha;
		const char *	m_filePath;
		bool			m_initialized;
		int				m_width;
		int				m_height;
};


