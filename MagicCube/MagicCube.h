#pragma once 

#include "Cube.h"

#define CUBE_DIMENSION 3
#define CUBE_COUNT 27

/**
* @brief 以前面的那一层开始，左上角方块记号0，横向扫描，左边记号3，左下记号6
*        再中间层，左上角9，最后层，左上角18
*/
class MagicCube {

	// 魔方的中心
	TOOL_CREATE_GET(Point*, center, Center);

	// 魔方的每个方块的边长
	TOOL_CREATE_GET(GLfloat, eachSide, EachSide);

	// 魔方的相邻方块之间的间距
	TOOL_CREATE_GET(GLfloat, betweenGap, BetweenGap);

	/**
	* @brief 旋转方向
	* @enmu IDLE,CLOCKWISE,ANTI_CLOCKWISE中的一个
	*/
	TOOL_CREATE_GET(GLint, orientation, Orientation);

	/**
	* @biref 旋转的面
	* @enmu ROTATE_FRONT, ROTATE_LEFT, ROTATE_BOTTOM
	*       ROTATE_RIGHT, ROTATE_TOP,  ROTATE_BACK
	*/
	TOOL_CREATE_GET(GLint, rotateSurface, RotateSurface);

private:

	Cube* cubes[CUBE_COUNT];

	// 已经转了多少角度
	GLdouble angle;

	// 旋转开始的时间
	INT64 startMilliTime;

	void init(Point center, GLfloat eachSide, GLfloat betweenGap);

protected:

	/**
	* @brief 实际绘图函数
	*/
	void onDraw();

	void rotateFront();
	void rotateLeft();
	void rotateBottom();
	void rotateRight();
	void rotateTop();
	void rotateBack();

public:

	static const long ANIMATION_DURATION = 800;  // 毫秒

	static const GLint IDLE = 0;
	static const GLint CLOCKWISE = 1;
	static const GLint ANTI_CLOCKWISE = 2;

	static const GLint ROTATE_FRONT = 0;
	static const GLint ROTATE_LEFT = 1;
	static const GLint ROTATE_BOTTOM = 2;
	static const GLint ROTATE_RIGHT = 3;
	static const GLint ROTATE_TOP = 4;
	static const GLint ROTATE_BACK = 5;

	static const GLint SURFACE_FRONT[CUBE_DIMENSION*CUBE_DIMENSION];
	static const GLint SURFACE_LEFT[CUBE_DIMENSION*CUBE_DIMENSION];
	static const GLint SURFACE_BOTTOM[CUBE_DIMENSION*CUBE_DIMENSION];
	static const GLint SURFACE_RIGHT[CUBE_DIMENSION*CUBE_DIMENSION];
	static const GLint SURFACE_TOP[CUBE_DIMENSION*CUBE_DIMENSION];
	static const GLint SURFACE_BACK[CUBE_DIMENSION*CUBE_DIMENSION];

	static const GLint SWAP_CLOCKWISE[CUBE_DIMENSION*CUBE_DIMENSION];
	static const GLint SWAP_ANTI_CLOCKWISE[CUBE_DIMENSION*CUBE_DIMENSION];

	MagicCube();
	MagicCube(GLfloat eachSide);                                       // 中心位于(0,0,0),betweenGap=0
	MagicCube(GLfloat eachSide, GLfloat betweenGap);                   // 中心位于(0,0,0)
	MagicCube(Point center, GLfloat eachSide);                         // betweenGap=0
	MagicCube(Point center, GLfloat eachSide, GLfloat betweenGap);
	~MagicCube();

	/**
	* @brief 传递绘图,调用onDraw()
	*/
	void dispatchDraw();

	/**
	* @brief 启动一个旋转
	*/
	void startRotate(GLint orientation, GLint rotateSurface);

	/**
	* @brief 计算旋转之后的变化
	*/
	void calulateRotate();

	/**
	* @brief 是否需要重新设定旋转
	* @note main.cpp 中的idle()中调用
	*/
	GLboolean isNeedRefresh();
};