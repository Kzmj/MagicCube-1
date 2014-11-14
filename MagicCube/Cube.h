#pragma once 

#include "Surface.h"

#define SURFACE_COUNT 6

/**
* @brief 前面为0，左面为1，下面为2，右面为3，上面为4，背面为5
*/
class Cube {

	// 方块的中心坐标
	TOOL_CREATE_GET(Point*, center, Center);

	// 方块的边长
	TOOL_CREATE_GET(GLfloat, lengthOfSide, LengthOfSide);

private:

	Surface* surfaces[SURFACE_COUNT];

protected:

	/**
	* @brief 实际绘图函数
	*/
	void onDraw();

public:

	Cube();
	Cube(Point center, GLfloat lengthOfSide);
	Cube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat lengthOfSide);
	~Cube();

	/**
	* @brief 传递绘图,调用onDraw()
	*/
	void dispatchDraw();

	void rotateX(GLfloat radian,GLboolean isVirtual);
	void rotateY(GLfloat radian,GLboolean isVirtual);
	void rotateZ(GLfloat radian,GLboolean isVirtual);

	void rotateCenterX(GLfloat radian);
	void rotateCenterY(GLfloat radian);
	void rotateCenterZ(GLfloat radian);
};