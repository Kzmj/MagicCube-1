#pragma once

#include <gl/freeglut.h>

#define PI 3.1415926

/**
* @brief 快速建立get,set方法
*
* @param type 变量类型
* @param name 变量名字
* @param Name get,set方法中出现的大写名字
*/
#define TOOL_CREATE_GET_SET(type,name,Name) \
	private: type name; \
	public: type get##Name() const { return name; } \
	public: void set##Name(type name) { this->name = name; }

/**
* @brief 快速建立get方法
*
* @param type 变量类型
* @param name 变量名字
* @param Name get方法中出现的大写名字
*/
#define TOOL_CREATE_GET(type,name,Name) \
	private: type name; \
	public: type get##Name() const { return name; }

/**
* @brief 快速建立set方法
*
* @param type 变量类型
* @param name 变量名字
* @param Name set方法中出现的大写名字
*/
#define TOOL_CREATE_SET(type,name,Name) \
	private: type name; \
	public: void set##Name(type name) { this->name = name; }

/**
* @brief 安全delete
*/
#define TOOL_SAFE_DELETE(p) if ((p) != NULL) { delete (p); p=NULL; }

/**
* @brief 安全delete []
*/
#define TOOL_SAFE_DELETE_GROUP(p) if ((p) != NULL) {delete [] (p); p=NULL; }

/**
* @brief 角度变弧度
*/
GLfloat angleToRadian(GLfloat angle);

/**
* @brief 弧度变角度
*/
GLfloat radianToAngle(GLfloat radian);

