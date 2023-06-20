#pragma once

class GLFWwindow;

class IShader
{
public:
	virtual ~IShader() {}
	virtual void beforeLoop() = 0;
	virtual void drawTria(GLFWwindow* window) = 0;
};