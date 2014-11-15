#pragma once

#include <gl/freeglut.h>

#define PI 3.1415926

/**
* @brief ���ٽ���get,set����
*
* @param type ��������
* @param name ��������
* @param Name get,set�����г��ֵĴ�д����
*/
#define TOOL_CREATE_GET_SET(type,name,Name) \
	private: type name; \
	public: type get##Name() const { return name; } \
	public: void set##Name(type name) { this->name = name; }

/**
* @brief ���ٽ���get����
*
* @param type ��������
* @param name ��������
* @param Name get�����г��ֵĴ�д����
*/
#define TOOL_CREATE_GET(type,name,Name) \
	private: type name; \
	public: type get##Name() const { return name; }

/**
* @brief ���ٽ���set����
*
* @param type ��������
* @param name ��������
* @param Name set�����г��ֵĴ�д����
*/
#define TOOL_CREATE_SET(type,name,Name) \
	private: type name; \
	public: void set##Name(type name) { this->name = name; }

/**
* @brief ��ȫdelete
*/
#define TOOL_SAFE_DELETE(p) if ((p) != NULL) { delete (p); p=NULL; }

/**
* @brief ��ȫdelete []
*/
#define TOOL_SAFE_DELETE_GROUP(p) if ((p) != NULL) {delete [] (p); p=NULL; }

/**
* @brief �Ƕȱ仡��
*/
GLfloat angleToRadian(GLfloat angle);

/**
* @brief ���ȱ�Ƕ�
*/
GLfloat radianToAngle(GLfloat radian);

