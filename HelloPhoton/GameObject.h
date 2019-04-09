#pragma once
#include "Sprite.h"
#include "Matrix.h"
#include <string>

class GameObject
{
protected:
	Transform2D m_transform;
	Sprite	m_sprite;
	

public:
	std::string name;

	GameObject();
	GameObject(Sprite& sprite);
	~GameObject();

	Transform2D GetTransform() { return m_transform; };
	void SetTransform(Transform2D transform);
	void SetTransform(Vector2 position, Vector2 scale, float rotation);

	Sprite& GetSprite() { return m_sprite; };
	void SetSprite(Sprite& sprite);

	void Start();
	void Update(float deltaTime);
	void Draw();
};

