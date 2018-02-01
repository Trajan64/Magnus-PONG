#pragma once
#include "PNGTexture.h"
#include <vector>

class Font {

	public:

		Font(char *, int, int, int, int);
		~Font();

		std::vector<GLfloat>	getGlyph(int);
		float					getCellWidth();
		float					getCellHeight();
		PNGTexture *			getTexture();

	private:

		PNGTexture *			m_texture;
		int						m_nHorizontal;
		int						m_nVertical;
		int						m_alphaOffset;
		int						m_alphaSize;
		int						m_width;
		int						m_height;
		float					m_cellWidth;
		float					m_cellHeight;
		float					m_textCenter;
};
