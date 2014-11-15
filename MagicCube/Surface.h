#pragma once

#include "Point.h"
#include "tool_2.h"

#define VERTEX_COUNT 4

/**
* 魔方中的每一个小方块的其中一个面
*
* 计数：从法向量俯视，逆时针旋转
*/
class Surface {

	// 面的中心坐标
	TOOL_CREATE_GET(Point*, center, Center);

	// 面的边长
	TOOL_CREATE_GET(GLfloat, lengthOfSide, LengthOfSide);

	// 绑定的纹理
	TOOL_CREATE_GET(GLuint, textureName, TextureName);

private:

	// 面的四个定点
	Point* vertexes[VERTEX_COUNT];

	// 纹理坐标
	// 类里面竟然不能初始化成员数组！我艹他！
	GLfloat textureCoord[VERTEX_COUNT][2];
	//={ { 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f } };

	GLfloat radianX;
	GLfloat radianY;
	GLfloat radianZ;

	void initTextureCoord();

protected:

	/**
	* @brief 实际绘图函数
	*/
	void onDraw();

public:

	Surface();
	Surface(Point normal, Point center, GLfloat lengthOfSide);
	~Surface();

	/**
	* @brief 每调用一次，就现计算一次当前法向量
	* @warning 未单位化
	*/
	Point getNormal();

	/**
	* @brief 传递绘图,调用onDraw()
	*/
	void dispatchDraw();

	void rotateX(GLfloat radian,GLboolean isVirtual);
	void rotateY(GLfloat radian,GLboolean isVirtual);
	void rotateZ(GLfloat radian,GLboolean isVirtual);

	void rotateCenterX(Point cubeCenter,GLfloat radian);
	void rotateCenterY(Point cubeCenter,GLfloat radian);
	void rotateCenterZ(Point cubeCenter,GLfloat radian);
};