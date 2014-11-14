#pragma once 

#include <math.h>
#include "Point.h"

Point Point::DIMENSION_X = Point(1, 0, 0);
Point Point::DIMENSION_X_OPPOSITE = Point(-1, 0, 0);
Point Point::DIMENSION_Y = Point(0, 1, 0);
Point Point::DIMENSION_Y_OPPOSITE = Point(0, -1, 0);
Point Point::DIMENSION_Z = Point(0, 0, 1);
Point Point::DIMENSION_Z_OPPOSITE = Point(0, 0, -1);

Point::Point() {
	x = y = z = 0;
}

Point::Point(GLfloat x, GLfloat y, GLfloat z) {
	setXYZ(x, y, z);
}

Point::Point(Point &copy) {
	x = copy.getX();
	y = copy.getY();
	z = copy.getZ();
}

Point::~Point() {
}

void Point::setXYZ(GLfloat x, GLfloat y, GLfloat z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point::setPoint(Point &copy) {
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
}

GLfloat* Point::toVector3f() {
	vector3f[0] = x;
	vector3f[1] = y;
	vector3f[2] = z;

	return vector3f;
}

GLfloat* Point::toVector4f() {
	vector4f[0] = x;
	vector4f[1] = y;
	vector4f[2] = z;
	vector4f[3] = 1;

	return vector4f;
}

void Point::rotateXAngle(GLfloat angle) {
	rotateXRadian(angleToRadian(angle));
}

void Point::rotateXRadian(GLfloat radian) {
	rotateX(sin(radian), cos(radian));
}

void Point::rotateX(GLfloat sinRadian, GLfloat cosRadian) {
	GLfloat temporaryY = y*cosRadian - z*sinRadian;
	GLfloat temporaryZ = y*sinRadian + z*cosRadian;

	y = temporaryY;
	z = temporaryZ;
}


void Point::rotateYAngle(GLfloat angle) {
	rotateYRadian(angleToRadian(angle));
}

void Point::rotateYRadian(GLfloat radian) {
	rotateY(sin(radian), cos(radian));
}

void Point::rotateY(GLfloat sinRadian, GLfloat cosRadian) {
	GLfloat temporaryZ = z*cosRadian - x*sinRadian;
	GLfloat temporaryX = z*sinRadian + x*cosRadian;

	z = temporaryZ;
	x = temporaryX;
}

void Point::rotateZAngle(GLfloat angle) {
	rotateZRadian(angleToRadian(angle));
}

void Point::rotateZRadian(GLfloat radian) {
	rotateZ(sin(radian), cos(radian));
}

void Point::rotateZ(GLfloat sinRadian, GLfloat cosRadian) {
	GLfloat temporaryX = x*cosRadian - y*sinRadian;
	GLfloat temporaryY = x*sinRadian + y*cosRadian;

	x = temporaryX;
	y = temporaryY;
}

void Point::rotateCenterX(Point &center, GLfloat radian) {
	GLfloat sinRadian = sin(radian);
	GLfloat cosRadian = cos(radian);
	GLfloat y0 = center.getY();
	GLfloat z0 = center.getZ();

	GLfloat temporaryY = (y - y0)*cosRadian - (z - z0)*sinRadian + y0;
	GLfloat temporaryZ = (y - y0)*sinRadian + (z - z0)*cosRadian + z0;

	y = temporaryY;
	z = temporaryZ;
}

void Point::rotateCenterY(Point &center, GLfloat radian) {
	GLfloat sinRadian = sin(radian);
	GLfloat cosRadian = cos(radian);
	GLfloat z0 = center.getZ();
	GLfloat x0 = center.getX();

	GLfloat temporaryZ = (z - z0)*cosRadian - (x - x0)*sinRadian + z0;
	GLfloat temporaryX = (z - z0)*sinRadian + (x - x0)*cosRadian + x0;

	z = temporaryZ;
	x = temporaryX;
}

void Point::rotateCenterZ(Point &center, GLfloat radian) {
	GLfloat sinRadian = sin(radian);
	GLfloat cosRadian = cos(radian);
	GLfloat x0 = center.getX();
	GLfloat y0 = center.getY();

	GLfloat temporaryX = (x - x0)*cosRadian - (y - y0)*sinRadian + x0;
	GLfloat temporaryY = (x - x0)*sinRadian + (y - y0)*cosRadian + y0;

	x = temporaryX;
	y = temporaryY;
}

void Point::normalize() {
	GLfloat length = sqrt(x*x + y*y + z*z);
	x /= length;
	y /= length;
	z /= length;
}

void Point::multiply(GLfloat times) {
	x *= times;
	y *= times;
	z *= times;
}

void Point::negate() {
	x = -x;
	y = -y;
	z = -z;
}

Point Point::getNormalized(bool needDone) {
	GLfloat length = sqrt(x*x + y*y + z*z);

	if (needDone) {
		x /= length;
		y /= length;
		z /= length;
	}

	Point result(x / length, y / length, z / length);
	return result;
}

Point Point::getMultiply(GLfloat times, bool needDone) {
	Point result(x*times, y*times, z*times);
	if (needDone) {
		x *= times;
		y *= times;
		z *= times;
	}
	return result;
}

Point Point::getNegate(bool needDone) {
	Point result(-x, -y, -z);
	if (needDone) {
		x = -x;
		y = -y;
		z = -z;
	}
	return result;
}

GLfloat Point::length() {
	return sqrt(x*x + y*y + z*z);
}

Point operator+(Point vertex1, Point vertex2) {
	Point result(
		vertex1.getX() + vertex2.getX(),
		vertex1.getY() + vertex2.getY(),
		vertex1.getZ() + vertex2.getZ());

	return result;
}

Point operator-(Point vertex1, Point vertex2) {
	Point result(
		vertex1.getX() - vertex2.getX(),
		vertex1.getY() - vertex2.getY(),
		vertex1.getZ() - vertex2.getZ());

	return result;
}

Point operator*(Point vertex1, Point vertex2) {
	Point result(
		vertex1.getY()*vertex2.getZ() - vertex1.getZ()*vertex2.getY(),
		vertex1.getZ()*vertex2.getX() - vertex1.getX()*vertex2.getZ(),
		vertex1.getX()*vertex2.getY() - vertex1.getY()*vertex2.getX());

	return result;
}