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

	static Point DIMENSION_X;               // x��������
	static Point DIMENSION_X_OPPOSITE;      // x�ᷴ����
	static Point DIMENSION_Y;               // y��������
	static Point DIMENSION_Y_OPPOSITE;      // y�ᷴ����
	static Point DIMENSION_Z;               // z��������
	static Point DIMENSION_Z_OPPOSITE;      // z�ᷴ����

	Point();
	Point(GLfloat x, GLfloat y, GLfloat z);
	Point(Point &copy);
	~Point();

	void setXYZ(GLfloat x, GLfloat y, GLfloat z);
	void setPoint(Point &copy);

	/**
	* @brief ������ά����ģʽ,����w
	*/
	GLfloat* toVector3f();

	/**
	* @brief ������ά����ģʽ,����w=1
	*/
	GLfloat* toVector4f();

	/**
	* @brief ��X����ת
	* @param angle �Ƕ�,��x������������ʱ��Ϊ��
	*/
	void rotateXAngle(GLfloat angle);

	/**
	* @brief ��Y����ת
	* @param angle �Ƕ�,��y������������ʱ��Ϊ��
	*/
	void rotateYAngle(GLfloat angle);

	/**
	* @brief ��Z����ת
	* @param angle �Ƕ�,��z������������ʱ��Ϊ��
	*/
	void rotateZAngle(GLfloat angle);

	/**
	* @brief ��X����ת
	* @param radian ����,��x������������ʱ��Ϊ��
	*/
	void rotateXRadian(GLfloat radian);

	/**
	* @brief ��Y����ת
	* @param radian ����,��y������������ʱ��Ϊ��
	*/
	void rotateYRadian(GLfloat radian);

	/**
	* @brief ��Z����ת
	* @param radian ����,��z������������ʱ��Ϊ��
	*/
	void rotateZRadian(GLfloat radian);

	/**
	* @brief ��X����ת,��x������������ʱ��Ϊ����������
	*/
	void rotateX(GLfloat sinRadian, GLfloat cosRadian);

	/**
	* @brief ��Y����ת,��y������������ʱ��Ϊ����������
	*/
	void rotateY(GLfloat sinRadian, GLfloat cosRadian);

	/**
	* @brief ��Z����ת,��z������������ʱ��Ϊ����������
	*/
	void rotateZ(GLfloat sinRadian, GLfloat cosRadian);

	/**
	* @brief �ƶ���ת��,��x������������ʱ��Ϊ����������
	*/
	void rotateCenterX(Point &center,GLfloat radian);

	/**
	* @brief �ƶ���ת��,��y������������ʱ��Ϊ����������
	*/
	void rotateCenterY(Point &center, GLfloat radian);

	/**
	* @brief �ƶ���ת��,��y������������ʱ��Ϊ����������
	*/
	void rotateCenterZ(Point &center, GLfloat radian);

	/**
	* @brief ��λ��
	*/
	void normalize();

	/**
	* @brief ϵ���˻�
	*/
	void multiply(GLfloat times);

	/**
	* @brief ȡ��,x,y,z���Ӹ���
	*/
	void negate();

	/**
	* @params needDone �Ƿ���Ҫʵ��ִ��,�����ŵ�ǰx,y,z����仯
	* @return �õ�������λ��������
	*/
	Point getNormalized(bool needDone);

	/**
	* @params needDone �Ƿ���Ҫʵ��ִ��,�����ŵ�ǰx,y,z����仯
	* @return �õ���������������
	*/
	Point getMultiply(GLfloat times,bool needDone);

	/**
	* @params needDone �Ƿ���Ҫʵ��ִ��,�����ŵ�ǰx,y,z����仯
	* @return �õ�����ȡ��������
	*/
	Point getNegate(bool needDone);

	/**
	* @brief ��������ĳ���
	*/
	GLfloat length();

	friend Point operator+(Point vertex1, Point vertex2);

	friend Point operator-(Point vertex1, Point vertex2);

	/**
	* @brief ����֮��Ĳ��
	*/
	friend Point operator*(Point vertex1, Point vertex2);

};

