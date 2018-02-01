#include "stdafx.h"
#include "PNGTexture.h"
#include <iostream>
#include "SOIL/SOIL.h"


extern bool OpenGLInitialized;


/**	Initialize and store a 2D texture with the provided PNG image as argument.
*
*	hasAlpha indicates if the texture has alpha transparency.
*/
PNGTexture::PNGTexture(const char * filePath, const bool hasAlpha) {

	m_id = 0;
	m_filePath = filePath;
	m_initialized = 0;
	m_hasAlpha = hasAlpha;

};


/*
* Initialize and store texture.
*/
void PNGTexture::setup() {

	m_id = SOIL_load_OGL_texture(m_filePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA);

	// Output initialization status
	if (m_id) {

		cout << "Texture located at: " << m_filePath << " has been sucessfully loaded." << endl;
	}
	else {

		cout << "Texture located at: " << m_filePath << " failed to load." << endl;
	}

	// Indicate that the texture has now been initialized.
	m_initialized = 1;

}


/*
*	Bind texture id.
*
*	Must be called everytime the instance's texture has to be used. 
*/
void PNGTexture::bind() {

	if (!m_initialized && OpenGLInitialized) {

		setup();

	}

	glBindTexture(GL_TEXTURE_2D, m_id);

}


/*
*	Get the texture's width.
*/
int PNGTexture::getWidth() {

	return m_width;

};


/*
*	Get the texture's height.
*/

int PNGTexture::getHeight() {

	return m_height;
	
};

/*
*	Get the texture's identification.
*/
int PNGTexture::getId() {

	return m_id;

};

