#pragma once
#include "MyPhoton.h"
#include "Sprite.h"
#include "GameObject.h"
#include "UIntPacker.h"
#include "GameObjectContainer.h"

const int RESOLUTION_X = 800;
const int RESOLUTION_Y = 600;
const int COL = 3;
const int ROW = 3;
const int SQUARE_SIZE = 100;
const int SQUARE_OFFSET = 10;

enum GameState
{
	START = 0,
	WAIT,
	OVER
};

class Application
{
protected:
	GameState m_state;

	GameObjectContainer<GameObject> m_GOs;
	std::list<GameObject*>::iterator iteGO;

	Sprite m_sprite_x;
	Sprite m_sprite_o;
	Sprite m_sprite_box;
	Sprite m_sprite_logo;
	Sprite m_sprite_reset;

	GameObject*	GO;
	GameObject* GO1;

	float offset = 120.0f;
	float mousePos[2];

	int currentTurn = 0;
	int currentPlayer = 0;
	int arrayCheck[9];

	bool stopRender = false;

	UIntPacker* packer = new UIntPacker;

public:
	
	Application();
	~Application();
	
	double timer = 0;

	GameObject* Spawn();
	GameObject* Spawn(GameObject* duplicate);
	GameObject* Spawn(Transform2D transform);
	GameObject* Spawn(Vector2 position, float rotation, Vector2 scale);
	GameObject& FindGameObject(int index);

	void Destroy(GameObject* gameObject);
	
	static Application& getInstance()
	{
		static Application app;
		return app;
	}

	void OnReceivedOpponentData(unsigned char data, int bitCount);

	virtual void start();
	virtual void update(double elapsedTime);
	virtual void drawBoard();
	virtual void updateBoard(int index);
	virtual void draw();
	
	virtual void setMousePos(float x, float y);
	virtual void onMouseClick();
	virtual void onMouseMoved(float mousePosX, float mousePosY);

	virtual void setTurn(int set);
	virtual void updateTurn();
	virtual void checkWin();
	virtual void setGameState(GameState state);
	virtual void resetGame();
	GameState getGameState();
};

