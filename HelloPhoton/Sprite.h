#pragma once
#include <GLFW/glfw3.h>
#include "bitmap.h"
#include "Matrix.h"
#include "Vector2.h"

struct Transform2D
{
	Vector2 position;
	Vector2 scale;
	float rotation;
};

enum BlendMode
{
	NONE = 0,
	ADDITIVE,
	ALPHA,
	MULTIPLY
};

struct Color 
{
	GLubyte R, G, B, A;

	Color()
	{
		R = 255;
		G = 255;
		B = 255;
		A = 255;
	}

	Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		this->R = r;
		this->G = g;
		this->B = b;
		this->A = a;
	}
};


class Sprite
{
private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_textureID[1];
	Transform2D m_transform;
	Color m_color;
	BlendMode m_blendMode;

	Matrix SetTranslate(float x, float y);
	Matrix SetRotate(float rotation);
	Matrix SetScale(float x, float y);

	Matrix translateMatrix;
	Matrix rotateMatrix;
	Matrix scaleMatrix;

public:
	Sprite();
	Sprite(const std::string& path);
	~Sprite();

	const Matrix GetTranslate() { return translateMatrix; };
	const Matrix GetRotate() { return rotateMatrix; };
	const Matrix GetScale() { return scaleMatrix; };

	const int GetWidth() { return m_width; };
	const int GetHeight() { return m_height; };
	const int GetTextureID(int index) { return m_textureID[index]; };
	const Color& GetColor() { return m_color; };
	const BlendMode GetBlendingMode() { return m_blendMode; };

	static void LoadTexture(const char *path, GLuint textureID, unsigned int &width, unsigned int &height);
	static void DrawSquare(GLuint textureID, int xPos, int yPos, int width, int height, GLubyte r, GLubyte g, GLubyte b);

	void SetFilePath(const std::string& path);
	void SetDimension(unsigned int width, unsigned int height);
	void SetTextureID(GLuint textureID);
	void SetColor(const Color& color);
	void SetBlendingMode(BlendMode blend);

	// Overload draw functions.
	void Draw();
	void Draw(float xPos, float yPos, float rotation, float xScale, float yScale);
	void Draw(Vector2 position, float rotation, Vector2 scale);
	void Draw(Transform2D transform);
};

