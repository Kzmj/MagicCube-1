#pragma once

#include "Point.h"
#include "tool_2.h"

#define VERTEX_COUNT 4

/**
* ħ���е�ÿһ��С���������һ����
*
* �������ӷ��������ӣ���ʱ����ת
*/
class Surface {

	// �����������
	TOOL_CREATE_GET(Point*, center, Center);

	// ��ı߳�
	TOOL_CREATE_GET(GLfloat, lengthOfSide, LengthOfSide);

private:

	// ����ĸ�����
	Point* vertexes[VERTEX_COUNT];

	GLfloat radianX;
	GLfloat radianY;
	GLfloat radianZ;

protected:

	/**
	* @brief ʵ�ʻ�ͼ����
	*/
	void onDraw();

public:

	Surface();
	Surface(Point normal, Point center, GLfloat lengthOfSide);
	~Surface();

	/**
	* @brief ÿ����һ�Σ����ּ���һ�ε�ǰ������
	* @warning δ��λ��
	*/
	Point getNormal();

	/**
	* @brief ���ݻ�ͼ,����onDraw()
	*/
	void dispatchDraw();

	void rotateX(GLfloat radian,GLboolean isVirtual);
	void rotateY(GLfloat radian,GLboolean isVirtual);
	void rotateZ(GLfloat radian,GLboolean isVirtual);

	void rotateCenterX(Point cubeCenter,GLfloat radian);
	void rotateCenterY(Point cubeCenter,GLfloat radian);
	void rotateCenterZ(Point cubeCenter,GLfloat radian);
};