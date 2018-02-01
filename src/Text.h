#pragma once
#include "Font.h"
#include "Rectangle.h"

class Text {

	public:

		Text(char *, float);
		~Text();

		void draw();


	private:

		float				m_scaleFactor;
		char *				m_string;
		float				m_center;
		int					m_length;
		float				m_characterWidth;
		float				m_characterHeight;
		PNGTexture *		m_texture;
		std::vector<Rect*>	m_characters;

};
