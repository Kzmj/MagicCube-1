#pragma once 

#include "tool_1.h"
#include "tool_2.h"

/**
* @brief �Ƕȱ仡��
*/
GLfloat angleToRadian(GLfloat angle) {
	return angle / 180 * PI;
}

/**
* @brief ���ȱ�Ƕ�
*/
GLfloat radianToAngle(GLfloat radian) {
	return radian / PI * 180;
}

/**
* @brief ������֮����е�
*/
Point getMidpoint(Point vertex1, Point vertex2) {
	Point midpoint(
		(vertex1.getX() + vertex2.getX()) / 2,
		(vertex1.getY() + vertex2.getY()) / 2,
		(vertex1.getZ() + vertex2.getZ()) / 2
		);

	return midpoint;
}

/**
* @brief �����������ĵ��
*/
GLfloat vectorDotProduct(Point vertex1, Point vertex2) {
	GLfloat result = 0;
	result += vertex1.getX()*vertex2.getX();
	result += vertex1.getY()*vertex2.getY();
	result += vertex1.getZ()*vertex2.getZ();

	return result;
}

