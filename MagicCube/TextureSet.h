#pragma once

#include <gl/freeglut.h>
#include <gl/GLAUX.H>
#include "tool_1.h"

#define TEXTURE_COUNT 6

using namespace std;

class TextureSet {

private:

	static TextureSet* instance;

	// front,left,bottom,right,top,back
	GLuint textureNames[TEXTURE_COUNT];

	TextureSet();
	~TextureSet();

	bool loadTexture(char* bmpPath, GLuint &textureName);

	AUX_RGBImageRec* loadBMP(char* Filename);
    GLboolean loadGLTexture(char* file, int index);

	char* getCurrentFilePath();

public:

	// front,left,bottom,right,top,back
	static char* TEXTURE_BMP[TEXTURE_COUNT];

	static TextureSet* GetInstance();
	static void DestoryInstance();

	GLuint getTextureNameFront();
	GLuint getTextureNameLeft();
	GLuint getTextureNameBottom();
	GLuint getTextureNameRight();
	GLuint getTextureNameTop();
	GLuint getTextureNameBack();
};