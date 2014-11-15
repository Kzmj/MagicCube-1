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

	// �󶨵�����
	TOOL_CREATE_GET(GLuint, textureName, TextureName);

private:

	// ����ĸ�����
	Point* vertexes[VERTEX_COUNT];

	// ��������
	// �����澹Ȼ���ܳ�ʼ����Ա���飡��ܳ����
	GLfloat textureCoord[VERTEX_COUNT][2];
	//={ { 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f } };

	GLfloat radianX;
	GLfloat radianY;
	GLfloat radianZ;

	void initTextureCoord();

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