#pragma once 

#include "Cube.h"

#define CUBE_DIMENSION 3
#define CUBE_COUNT 27

/**
* @brief ��ǰ�����һ�㿪ʼ�����ϽǷ���Ǻ�0������ɨ�裬��߼Ǻ�3�����¼Ǻ�6
*        ���м�㣬���Ͻ�9�����㣬���Ͻ�18
*/
class MagicCube {

	// ħ��������
	TOOL_CREATE_GET(Point*, center, Center);

	// ħ����ÿ������ı߳�
	TOOL_CREATE_GET(GLfloat, eachSide, EachSide);

	// ħ�������ڷ���֮��ļ��
	TOOL_CREATE_GET(GLfloat, betweenGap, BetweenGap);

	/**
	* @brief ��ת����
	* @enmu IDLE,CLOCKWISE,ANTI_CLOCKWISE�е�һ��
	*/
	TOOL_CREATE_GET(GLint, orientation, Orientation);

	/**
	* @biref ��ת����
	* @enmu ROTATE_FRONT, ROTATE_LEFT, ROTATE_BOTTOM
	*       ROTATE_RIGHT, ROTATE_TOP,  ROTATE_BACK
	*/
	TOOL_CREATE_GET(GLint, rotateSurface, RotateSurface);

private:

	Cube* cubes[CUBE_COUNT];

	// �Ѿ�ת�˶��ٽǶ�
	GLdouble angle;

	// ��ת��ʼ��ʱ��
	INT64 startMilliTime;

	void init(Point center, GLfloat eachSide, GLfloat betweenGap);

protected:

	/**
	* @brief ʵ�ʻ�ͼ����
	*/
	void onDraw();

	void rotateFront();
	void rotateLeft();
	void rotateBottom();
	void rotateRight();
	void rotateTop();
	void rotateBack();

public:

	static const long ANIMATION_DURATION = 800;  // ����

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
	MagicCube(GLfloat eachSide);                                       // ����λ��(0,0,0),betweenGap=0
	MagicCube(GLfloat eachSide, GLfloat betweenGap);                   // ����λ��(0,0,0)
	MagicCube(Point center, GLfloat eachSide);                         // betweenGap=0
	MagicCube(Point center, GLfloat eachSide, GLfloat betweenGap);
	~MagicCube();

	/**
	* @brief ���ݻ�ͼ,����onDraw()
	*/
	void dispatchDraw();

	/**
	* @brief ����һ����ת
	*/
	void startRotate(GLint orientation, GLint rotateSurface);

	/**
	* @brief ������ת֮��ı仯
	*/
	void calulateRotate();

	/**
	* @brief �Ƿ���Ҫ�����趨��ת
	* @note main.cpp �е�idle()�е���
	*/
	GLboolean isNeedRefresh();
};