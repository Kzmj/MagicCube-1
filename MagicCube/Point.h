#pragma once

#include <gl/freeglut.h>
#include "tool_1.h"

using namespace std;

class Point {

	TOOL_CREATE_GET_SET(GLfloat, x, X);
	TOOL_CREATE_GET_SET(GLfloat, y, Y);
	TOOL_CREATE_GET_SET(GLfloat, z, Z);

private:

	GLfloat vector3f[3];
	GLfloat vector4f[4];

public:

	static Point DIMENSION_X;               // x轴正方向
	static Point DIMENSION_X_OPPOSITE;      // x轴反方向
	static Point DIMENSION_Y;               // y轴正方向
	static Point DIMENSION_Y_OPPOSITE;      // y轴反方向
	static Point DIMENSION_Z;               // z轴正方向
	static Point DIMENSION_Z_OPPOSITE;      // z轴反方向

	Point();
	Point(GLfloat x, GLfloat y, GLfloat z);
	Point(Point &copy);
	~Point();

	void setXYZ(GLfloat x, GLfloat y, GLfloat z);
	void setPoint(Point &copy);

	/**
	* @brief 返回三维向量模式,忽略w
	*/
	GLfloat* toVector3f();

	/**
	* @brief 返回四维向量模式,加上w=1
	*/
	GLfloat* toVector4f();

	/**
	* @brief 绕X轴旋转
	* @param angle 角度,以x轴正方向俯视逆时针为正
	*/
	void rotateXAngle(GLfloat angle);

	/**
	* @brief 绕Y轴旋转
	* @param angle 角度,以y轴正方向俯视逆时针为正
	*/
	void rotateYAngle(GLfloat angle);

	/**
	* @brief 绕Z轴旋转
	* @param angle 角度,以z轴正方向俯视逆时针为正
	*/
	void rotateZAngle(GLfloat angle);

	/**
	* @brief 绕X轴旋转
	* @param radian 弧度,以x轴正方向俯视逆时针为正
	*/
	void rotateXRadian(GLfloat radian);

	/**
	* @brief 绕Y轴旋转
	* @param radian 弧度,以y轴正方向俯视逆时针为正
	*/
	void rotateYRadian(GLfloat radian);

	/**
	* @brief 绕Z轴旋转
	* @param radian 弧度,以z轴正方向俯视逆时针为正
	*/
	void rotateZRadian(GLfloat radian);

	/**
	* @brief 绕X轴旋转,以x轴正方向俯视逆时针为弧度正方向
	*/
	void rotateX(GLfloat sinRadian, GLfloat cosRadian);

	/**
	* @brief 绕Y轴旋转,以y轴正方向俯视逆时针为弧度正方向
	*/
	void rotateY(GLfloat sinRadian, GLfloat cosRadian);

	/**
	* @brief 绕Z轴旋转,以z轴正方向俯视逆时针为弧度正方向
	*/
	void rotateZ(GLfloat sinRadian, GLfloat cosRadian);

	/**
	* @brief 绕定点转动,以x轴正方向俯视逆时针为弧度正方向
	*/
	void rotateCenterX(Point &center,GLfloat radian);

	/**
	* @brief 绕定点转动,以y轴正方向俯视逆时针为弧度正方向
	*/
	void rotateCenterY(Point &center, GLfloat radian);

	/**
	* @brief 绕定点转动,以y轴正方向俯视逆时针为弧度正方向
	*/
	void rotateCenterZ(Point &center, GLfloat radian);

	/**
	* @brief 单位化
	*/
	void normalize();

	/**
	* @brief 系数乘积
	*/
	void multiply(GLfloat times);

	/**
	* @brief 取反,x,y,z都加负号
	*/
	void negate();

	/**
	* @params needDone 是否需要实际执行,代表着当前x,y,z坐标变化
	* @return 得到副本单位化的向量
	*/
	Point getNormalized(bool needDone);

	/**
	* @params needDone 是否需要实际执行,代表着当前x,y,z坐标变化
	* @return 得到副本翻倍的向量
	*/
	Point getMultiply(GLfloat times,bool needDone);

	/**
	* @params needDone 是否需要实际执行,代表着当前x,y,z坐标变化
	* @return 得到副本取反的向量
	*/
	Point getNegate(bool needDone);

	/**
	* @brief 获得向量的长度
	*/
	GLfloat length();

	friend Point operator+(Point vertex1, Point vertex2);

	friend Point operator-(Point vertex1, Point vertex2);

	/**
	* @brief 向量之间的叉乘
	*/
	friend Point operator*(Point vertex1, Point vertex2);

};

