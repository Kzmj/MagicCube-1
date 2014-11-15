#pragma once

#include <stdio.h>
#include "TextureSet.h"

char* TextureSet::TEXTURE_BMP[TEXTURE_COUNT]
= { "resourse/front.bmp", "resourse/left.bmp", "resourse/bottom.bmp", 
"resourse/right.bmp", "resourse/top.bmp", "resourse/back.bmp" };

TextureSet* TextureSet::instance = nullptr;

TextureSet* TextureSet::GetInstance() {
	if (instance == nullptr) {
		instance = new TextureSet();
	}

	return instance;
}

void TextureSet::DestoryInstance() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

TextureSet::TextureSet() {
	for (int i = 0; i < TEXTURE_COUNT; ++i) {
		loadTexture(TEXTURE_BMP[i], textureNames[i]);
	}
}

TextureSet::~TextureSet() {
	glDeleteTextures(TEXTURE_COUNT, textureNames);
}

GLuint TextureSet::getTextureNameFront() {
	return textureNames[0];
}

GLuint TextureSet::getTextureNameLeft() {
	return textureNames[1];
}

GLuint TextureSet::getTextureNameBottom() {
	return textureNames[2];
}

GLuint TextureSet::getTextureNameRight() {
	return textureNames[3];
}

GLuint TextureSet::getTextureNameTop() {
	return textureNames[4];
}

GLuint TextureSet::getTextureNameBack() {
	return textureNames[5];
}

bool TextureSet::loadTexture(char* bmpPath, GLuint &textureName) {
	WCHAR path[256] = { 0 };
	memset(path, 0, sizeof(path));
	MultiByteToWideChar(CP_ACP, 0, bmpPath, strlen(bmpPath) + 1, path,
		sizeof(path) / sizeof(path[0]));

	HBITMAP hBMP;            
	BITMAP BMP;    

	glGenTextures(1, &textureName);         
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), path, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if (!hBMP) return false;     

	GetObject(hBMP, sizeof(BMP), &BMP);       
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      
	glBindTexture(GL_TEXTURE_2D, textureName);      
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);          
	return true;           
}
