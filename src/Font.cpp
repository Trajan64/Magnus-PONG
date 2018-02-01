#include "stdafx.h"
#include "Font.h"
#include <vector>
#include <iostream>


/** Setup a font out a given image file.
*
*	Creates a texture out of an image file picturing an alphabet.
*	Provides the ability to generates texel coordinates mapping to a given character.
*
*	Informations regarding the structure of the alphabet cannot be retreived
*	automatically and has to be fed directly as arguments to the class's constructor.
*/
Font::Font(char * filePath, int nHorizontal, int nVertical, int alphaOffset, int alphaSize) {

	m_texture = new PNGTexture(filePath, 1);

	// Record the width & height of the alphabet texture.
	// (hack)
	m_width = 100;
	m_height = 100;

	// Store the number of characters at each line and row.
	m_nHorizontal = nHorizontal;
	m_nVertical = nVertical;

	// Some alphabet textures do not include the first few ASCII characters.
	// It is then necessary to specify the offset value at which the alphabet really starts.
	m_alphaOffset = alphaOffset;

	// Store the total number of characters inside the alphabet texture.
	m_alphaSize = alphaSize;

	// Calculate the width and height of the characters' cell.
	m_cellWidth = (float)m_width / (float)nHorizontal;
	m_cellHeight = (float)m_height / (float)nVertical;

};



Font::~Font() {

	delete m_texture;

};

/*  
*	Return a vector filled with texel coordinates. When mapped, those values will depict the character 
*	representing the supplied character value.
*/
std::vector<GLfloat> Font::getGlyph(int character) {

	std::vector<GLfloat> texels;

	// Get character's real identification within the alphabet.
	int glyph = character - m_alphaOffset;

	if (glyph > m_alphaSize) {

		// Character not available in alphabet -> return empty vector.
//		std::cerr << "Character:" << character << "not in alphabet" << endl;

		return texels;
	}

	// Get character's top left position.
	float x = (glyph % m_nHorizontal) * m_cellWidth;
	float y = (glyph / m_nVertical) * m_cellHeight;
	
	// Fill the vector with texels coordinates representing the visual boundaries of the character.
	texels.push_back(x / m_width); // top left
	texels.push_back((y + m_cellHeight) / m_height); // top right
	texels.push_back((x + m_cellWidth) / m_width); // bottom right
	texels.push_back(y / m_height); // bottom left


	return texels;

};


/*
*	Return the width of all the characters's cell.
*/
float Font::getCellWidth() {

	return m_cellWidth;

};

/*
*	Return the height of all the characters's cell.
*/
float Font::getCellHeight() {

	return m_cellHeight;

};


/*
*	Return the alphabet texture.
*/
PNGTexture * Font::getTexture() {

	return m_texture;

};