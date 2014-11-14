#pragma once 

#include <stdio.h>
#include <assert.h>
#include "Surface.h"

Surface::Surface() {
	center = new Point();
	lengthOfSide = 0;
	radianX = 0;
	radianY = 0;
	radianZ = 0;

	for (int i = 0; i < VERTEX_COUNT; ++i) {
		vertexes[i] = new Point();
	}
}

Surface::Surface(Point normal, Point center, GLfloat lengthOfSide) {
	this->center = new Point(center);
	this->lengthOfSide = lengthOfSide;
	radianX = 0;
	radianY = 0;
	radianZ = 0;

	// 验证法向量是否跟坐标轴平行
	// 只有三个坐标中只有一个非零时，倍数才是2
	GLfloat before = normal.getX()*normal.getY()*normal.getZ();
	Point temporary = normal.getMultiply(2, false);
	GLfloat after = temporary.getX()*temporary.getY()*temporary.getZ();
	assert(after == before * 2);

	GLfloat halfLength = lengthOfSide / 2;
	if (normal.getX() > 0) {  // x轴正向
		vertexes[0] = new Point(center.getX(), center.getY() - halfLength, center.getZ() + halfLength);
		vertexes[1] = new Point(center.getX(), center.getY() - halfLength, center.getZ() - halfLength);
		vertexes[2] = new Point(center.getX(), center.getY() + halfLength, center.getZ() - halfLength);
		vertexes[3] = new Point(center.getX(), center.getY() + halfLength, center.getZ() + halfLength);
	}
	if (normal.getX() < 0) {  // x轴反向
		vertexes[0] = new Point(center.getX(), center.getY() - halfLength, center.getZ() + halfLength);
		vertexes[1] = new Point(center.getX(), center.getY() + halfLength, center.getZ() + halfLength);
		vertexes[2] = new Point(center.getX(), center.getY() + halfLength, center.getZ() - halfLength);
		vertexes[3] = new Point(center.getX(), center.getY() - halfLength, center.getZ() - halfLength);
	}
	if (normal.getY() > 0) {  // y轴正向
		vertexes[0] = new Point(center.getX() + halfLength, center.getY(), center.getZ() - halfLength);
		vertexes[1] = new Point(center.getX() - halfLength, center.getY(), center.getZ() - halfLength);
		vertexes[2] = new Point(center.getX() - halfLength, center.getY(), center.getZ() + halfLength);
		vertexes[3] = new Point(center.getX() + halfLength, center.getY(), center.getZ() + halfLength);
	}
	if (normal.getY() < 0) {  // y轴反向
		vertexes[0] = new Point(center.getX() + halfLength, center.getY(), center.getZ() - halfLength);
		vertexes[1] = new Point(center.getX() + halfLength, center.getY(), center.getZ() + halfLength);
		vertexes[2] = new Point(center.getX() - halfLength, center.getY(), center.getZ() + halfLength);
		vertexes[3] = new Point(center.getX() - halfLength, center.getY(), center.getZ() - halfLength);
	}
	if (normal.getZ() > 0) {  // z轴正向
		vertexes[0] = new Point(center.getX() - halfLength, center.getY() + halfLength, center.getZ());
		vertexes[1] = new Point(center.getX() - halfLength, center.getY() - halfLength, center.getZ());
		vertexes[2] = new Point(center.getX() + halfLength, center.getY() - halfLength, center.getZ());
		vertexes[3] = new Point(center.getX() + halfLength, center.getY() + halfLength, center.getZ());
	}
	if (normal.getZ() < 0) {  // z轴反向
		vertexes[0] = new Point(center.getX() - halfLength, center.getY() + halfLength, center.getZ());
		vertexes[1] = new Point(center.getX() + halfLength, center.getY() + halfLength, center.getZ());
		vertexes[2] = new Point(center.getX() + halfLength, center.getY() - halfLength, center.getZ());
		vertexes[3] = new Point(center.getX() - halfLength, center.getY() - halfLength, center.getZ());
	}
}

Surface::~Surface() {
	TOOL_SAFE_DELETE(center);

	for (int i = 0; i < VERTEX_COUNT; ++i) {
		TOOL_SAFE_DELETE(vertexes[i]);
	}
}

Point Surface::getNormal() {
	Point normal((*vertexes[0] - *vertexes[2])*(*vertexes[1] - *vertexes[3]));
	// 90度会随机方向，尽量避免
	if (vectorDotProduct(normal, *center) < 0) normal.negate();
	return normal;
}

void Surface::dispatchDraw() {
	onDraw();
}

void Surface::onDraw() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	{
		for (int i = 0; i < VERTEX_COUNT; ++i) {
			Point vertex(*vertexes[i]);
			if (radianX != 0) vertex.rotateXRadian(radianX);
			if (radianY != 0) vertex.rotateYRadian(radianY);
			if (radianZ != 0) vertex.rotateZRadian(radianZ);

			glVertex3fv(vertex.toVector3f());
		}
	}
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	{
		for (int i = 0; i < VERTEX_COUNT; ++i) {
			Point vertex(*vertexes[i]);
			if (radianX != 0) vertex.rotateXRadian(radianX);
			if (radianY != 0) vertex.rotateYRadian(radianY);
			if (radianZ != 0) vertex.rotateZRadian(radianZ);

			glVertex3fv(vertex.toVector3f());
		}
	}
	glEnd();
}

void Surface::rotateX(GLfloat radian, GLboolean isVirtual) {
	if (isVirtual) {
		radianX = radian;
	}
	else {
		for (int i = 0; i < VERTEX_COUNT; ++i) {
			vertexes[i]->rotateXRadian(radian);
		}
		center->rotateXRadian(radian);
	}
}

void Surface::rotateY(GLfloat radian, GLboolean isVirtual) {
	if (isVirtual) {
		radianY = radian;
	}
	else {
		for (int i = 0; i < VERTEX_COUNT; ++i) {
			vertexes[i]->rotateYRadian(radian);
		}
		center->rotateYRadian(radian);
	}
}

void Surface::rotateZ(GLfloat radian, GLboolean isVirtual) {
	if (isVirtual) {
		radianZ = radian;
	}
	else {
		for (int i = 0; i < VERTEX_COUNT; ++i) {
			vertexes[i]->rotateZRadian(radian);
		}
		center->rotateZRadian(radian);
	}
}

void Surface::rotateCenterX(Point cubeCenter, GLfloat radian) {
	for (int i = 0; i < VERTEX_COUNT; ++i) {
		vertexes[i]->rotateCenterX(cubeCenter, radian);
	}
}

void Surface::rotateCenterY(Point cubeCenter, GLfloat radian) {
	for (int i = 0; i < VERTEX_COUNT; ++i) {
		vertexes[i]->rotateCenterY(cubeCenter, radian);
	}
}

void Surface::rotateCenterZ(Point cuberCenter, GLfloat radian) {
	for (int i = 0; i < VERTEX_COUNT; ++i) {
		vertexes[i]->rotateCenterZ(cuberCenter, radian);
	}
}