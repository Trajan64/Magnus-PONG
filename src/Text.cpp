#include "stdafx.h"
#include "Text.h"
#include "string.h"
#include "Font.h"
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>


Font * font = NULL;

/** Creates and renders a character string
*
*	To setup the visual string, this class creates multiple squared shapes whose texel coordinates all map to certain parts of a texture (which pictures an alphabet).
*	In order to ease the mapping process, this class uses a font loader instance. The class sequentially queries to it all the needed characters
*	and uses the returned data to setup the mapping.
*
*	The argument scaleFactor represents the font size of the string.
*/
Text::Text(char * string, float scaleFactor) {

	m_string = string;
	m_scaleFactor = scaleFactor;

	// Create Font instance with an alphabet texture as first argument.
	// Numerical arguments indicates how characters should be extracted from the texture.
	if (!font) {
		font = new Font((char *) "./textures/png_font.png", 10, 10, 32, 94);
	}

	// Calculate the length of the string.
	m_length = strlen(string);

	// Calculate real character width.
	m_characterWidth = font->getCellWidth() * scaleFactor;
	m_characterHeight = font->getCellHeight() * scaleFactor;
	
	// Calculate string's middle position.
	m_center = (float)(m_characterWidth * m_length) / 2.0f;

	// Save texture.
	m_texture = font->getTexture();

	// Resize array of characters (shapes).
	m_characters.resize(m_length);

	// Texel coordinates buffer.
	std::vector<GLfloat> texels;

	// Create the character shapes and map their texel coordinates. 
	for (int i = 0; string[i] != 0; i++) {

		texels = font->getGlyph(string[i]);

		m_characters[i] = new Rect(m_characterWidth, m_characterHeight);
		m_characters[i]->setTexels(texels[0], texels[1], texels[2], texels[3]);

	}
};



/*
*	Deconstructor
*/
Text::~Text() {

	for (int i = 0; i < m_length; i++) {

		delete m_characters[i];

	}

};



/*
*	Renders the string on screen.
*
*	With no previous translations, The string will be displayed as being centered at the origin.
*/
void Text::draw() {

	// Save current matrix at the top of stack.
	glPushMatrix();

	// Bind alphabet texture.
	m_texture->bind();

	// Set transparent alpha values.
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Translate so that the string will be centered.
    glTranslatef(-m_center + m_characterWidth / 2.0f, 0.0f, 0.0);

	// Draw all the characters part of the string.
	for (int i = 0; i < m_length; i++) {

		// Draw character.
		m_characters[i]->draw();

		// Offset position to the right, so that the next character will be displayed at the right of this one.
		glTranslatef(m_characterWidth, 0.0f, 0.0f);

	}

	// Restore OpenGL state.
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);

	// Restore matrix.
	glPopMatrix();

	glClear(GL_CURRENT_BIT);

};