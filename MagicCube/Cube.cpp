#pragma once 

#include "Cube.h"

Cube::Cube() {
	center = new Point();
	lengthOfSide = 0;

	for (int i = 0; i < SURFACE_COUNT; ++i) {
		surfaces[i] = new Surface();
	}
}

Cube::Cube(Point center, GLfloat lengthOfSide) {
	this->center = new Point(center);
	this->lengthOfSide = lengthOfSide;

	GLfloat halfLength = lengthOfSide / 2;
	surfaces[0] = new Surface(Point::DIMENSION_Z,
		Point(center.getX(), center.getY(), center.getZ() + halfLength),
		lengthOfSide);
	surfaces[1] = new Surface(Point::DIMENSION_X_OPPOSITE,
		Point(center.getX() - halfLength, center.getY(), center.getZ()),
		lengthOfSide);
	surfaces[2] = new Surface(Point::DIMENSION_Y_OPPOSITE,
		Point(center.getX(), center.getY() - halfLength, center.getZ()),
		lengthOfSide);
	surfaces[3] = new Surface(Point::DIMENSION_X,
		Point(center.getX() + halfLength, center.getY(), center.getZ()),
		lengthOfSide);
	surfaces[4] = new Surface(Point::DIMENSION_Y,
		Point(center.getX(), center.getY() + halfLength, center.getZ()),
		lengthOfSide);
	surfaces[5] = new Surface(Point::DIMENSION_Z_OPPOSITE,
		Point(center.getX(), center.getY(), center.getZ() - halfLength),
		halfLength);
}

Cube::Cube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat lengthOfSide) {
	center = new Point(centerX, centerY, centerZ);
	this->lengthOfSide = lengthOfSide;

	GLfloat halfLength = lengthOfSide / 2;
	surfaces[0] = new Surface(Point::DIMENSION_Z,
		Point(centerX, centerY, centerZ + halfLength),
		lengthOfSide);
	surfaces[1] = new Surface(Point::DIMENSION_X_OPPOSITE,
		Point(centerX - halfLength, centerY, centerZ),
		lengthOfSide);
	surfaces[2] = new Surface(Point::DIMENSION_Y_OPPOSITE,
		Point(centerX, centerY - halfLength, centerZ),
		lengthOfSide);
	surfaces[3] = new Surface(Point::DIMENSION_X,
		Point(centerX + halfLength, centerY, centerZ),
		lengthOfSide);
	surfaces[4] = new Surface(Point::DIMENSION_Y,
		Point(centerX, centerY + halfLength, centerZ),
		lengthOfSide);
	surfaces[5] = new Surface(Point::DIMENSION_Z_OPPOSITE,
		Point(centerX, centerY, centerZ - halfLength),
		lengthOfSide);
}

Cube::~Cube() {
	TOOL_SAFE_DELETE(center);

	for (int i = 0; i < SURFACE_COUNT; ++i) {
		TOOL_SAFE_DELETE(surfaces[i]);
	}
}

void Cube::dispatchDraw() {
	for (int i = 0; i < SURFACE_COUNT; ++i) {
		if (surfaces[i] != nullptr) {
			surfaces[i]->dispatchDraw();
		}
	}

	onDraw();
}

void Cube::onDraw() {

}

void Cube::rotateX(GLfloat radian, GLboolean isVirtual) {
	for (int i = 0; i < SURFACE_COUNT; ++i) {
		surfaces[i]->rotateX(radian, isVirtual);
	}
	if (!isVirtual) center->rotateXRadian(radian);
}

void Cube::rotateY(GLfloat radian, GLboolean isVirtual) {
	for (int i = 0; i < SURFACE_COUNT; ++i) {
		surfaces[i]->rotateY(radian, isVirtual);
	}
	if (!isVirtual) center->rotateYRadian(radian);
}

void Cube::rotateZ(GLfloat radian, GLboolean isVirtual) {
	for (int i = 0; i < SURFACE_COUNT; ++i) {
		surfaces[i]->rotateZ(radian, isVirtual);
	}
	if (!isVirtual) center->rotateZRadian(radian);
}

void Cube::rotateCenterX(GLfloat radian) {
	for (int i = 0; i < SURFACE_COUNT; ++i) {
		surfaces[i]->rotateCenterX(*center, radian);
	}
}

void Cube::rotateCenterY(GLfloat radian) {
	for (int i = 0; i < SURFACE_COUNT; ++i) {
		surfaces[i]->rotateCenterY(*center, radian);
	}
}

void Cube::rotateCenterZ(GLfloat radian) {
	for (int i = 0; i < SURFACE_COUNT; ++i) {
		surfaces[i]->rotateCenterZ(*center, radian);
	}
}