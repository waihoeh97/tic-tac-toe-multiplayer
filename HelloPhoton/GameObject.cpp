#include "GameObject.h"

GameObject::GameObject()
{
	name = "Test";
}

GameObject::GameObject(Sprite& sprite) : GameObject()
{
	SetSprite(sprite);
}

GameObject::~GameObject()
{
}

void GameObject::SetTransform(Transform2D transform)
{
	m_transform = transform;
}

void GameObject::SetTransform(Vector2 position, Vector2 scale, float rotation)
{
	m_transform.position.x = position.x;
	m_transform.position.y = position.y;
	m_transform.scale.x = scale.x;
	m_transform.scale.y = scale.y;
	m_transform.rotation = rotation;
}

void GameObject::SetSprite(Sprite& sprite)
{
	m_sprite = sprite;
}

void GameObject::Start()
{

}

void GameObject::Update(float deltaTime)
{

}

void GameObject::Draw()
{
	GetSprite().Draw(GetTransform());
}