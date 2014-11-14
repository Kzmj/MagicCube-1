#pragma once 

#include "Surface.h"

#define SURFACE_COUNT 6

/**
* @brief ǰ��Ϊ0������Ϊ1������Ϊ2������Ϊ3������Ϊ4������Ϊ5
*/
class Cube {

	// �������������
	TOOL_CREATE_GET(Point*, center, Center);

	// ����ı߳�
	TOOL_CREATE_GET(GLfloat, lengthOfSide, LengthOfSide);

private:

	Surface* surfaces[SURFACE_COUNT];

protected:

	/**
	* @brief ʵ�ʻ�ͼ����
	*/
	void onDraw();

public:

	Cube();
	Cube(Point center, GLfloat lengthOfSide);
	Cube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat lengthOfSide);
	~Cube();

	/**
	* @brief ���ݻ�ͼ,����onDraw()
	*/
	void dispatchDraw();

	void rotateX(GLfloat radian,GLboolean isVirtual);
	void rotateY(GLfloat radian,GLboolean isVirtual);
	void rotateZ(GLfloat radian,GLboolean isVirtual);

	void rotateCenterX(GLfloat radian);
	void rotateCenterY(GLfloat radian);
	void rotateCenterZ(GLfloat radian);
};