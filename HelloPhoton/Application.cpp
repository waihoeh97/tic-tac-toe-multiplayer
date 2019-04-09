#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "MyPhoton.h"

using namespace std;

Application::Application ()
{
}

Application::~Application ()
{	
}

GameObject* Application::Spawn()
{
	return Spawn(new GameObject());
}

GameObject* Application::Spawn(GameObject* duplicate)
{
	m_GOs.GetList().push_back(duplicate);
	return duplicate;
}

GameObject* Application::Spawn(Transform2D transform)
{
	GameObject* GO = new GameObject();
	GO->SetTransform(transform);

	return Spawn(GO);
}

GameObject* Application::Spawn(Vector2 position, float rotation, Vector2 scale)
{
	Transform2D transform;
	transform.position = position;
	transform.rotation = rotation;
	transform.scale = scale;

	return Spawn(transform);
}

GameObject& Application::FindGameObject(int index)
{
	return m_GOs.GetItem(index);
}

void Application::Destroy(GameObject* gameObject)
{
	GameObject* storedGOs = gameObject;
	m_GOs.GetList().remove(gameObject);
	delete gameObject;
}

void Application::start ()
{
	MyPhoton::getInstance().connect();

	m_sprite_x.SetFilePath("../media/x.bmp");
	m_sprite_o.SetFilePath("../media/o.bmp");
	m_sprite_box.SetFilePath("../media/box.bmp");
	m_sprite_logo.SetFilePath("../media/tictactoeLogo.bmp");
	m_sprite_reset.SetFilePath("../media/reset.bmp");

	drawBoard();
	
	setGameState(WAIT);
}

void Application::update (double elapsedTime)
{
	MyPhoton::getInstance().run();

	if (getGameState() == OVER)
	{
		timer += elapsedTime;

		if (stopRender)
		{
			GO1 = Spawn(Vector2(425.0f, 40.0f), 0.0f, Vector2(3.0f, 0.5f));
			GO1->SetSprite(m_sprite_reset);
			GO1->GetSprite().SetBlendingMode(ADDITIVE);
			stopRender = false;
		}

		//std::cout << timer << std::endl;

		if (timer >= 2)
		{
			Destroy(GO1);

			timer = 0;
			resetGame();
		}
	}
}

void Application::drawBoard()
{
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			GO = Spawn(Vector2(300.0f + (j * offset), 400.0f + (i * -offset)), 0.0f, Vector2(1.0f, 1.0f));
			GO->SetSprite(m_sprite_box);
			GO->GetSprite().SetBlendingMode(ADDITIVE);
		}
	}
	GO = Spawn(Vector2(150.0f, 550.0f), 0.0f, Vector2(2.0f, 1.0f));
	GO->SetSprite(m_sprite_logo);
	GO->GetSprite().SetBlendingMode(ADDITIVE);
}

void Application::updateBoard(int index)
{
	/* Determine player */
	if (currentPlayer == 1 && currentTurn == 0)
	{
		FindGameObject(index).SetSprite(m_sprite_o);
		m_sprite_o.SetBlendingMode(ADDITIVE);
		arrayCheck[index] = 1;
	}
	else if (currentPlayer == 2 && currentTurn == 0)
	{
		FindGameObject(index).SetSprite(m_sprite_o);
		m_sprite_o.SetBlendingMode(ADDITIVE);
		arrayCheck[index] = 1;
	}

	/* Determine turn */
	if (currentPlayer == 1 && currentTurn == 1)
	{
		FindGameObject(index).SetSprite(m_sprite_x);
		m_sprite_x.SetBlendingMode(ADDITIVE);
		arrayCheck[index] = 2;
	}
	else if (currentPlayer == 2 && currentTurn == 1)
	{
		FindGameObject(index).SetSprite(m_sprite_x);
		m_sprite_x.SetBlendingMode(ADDITIVE);
		arrayCheck[index] = 2;
	}
}

void Application::draw()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	iteGO = m_GOs.GetList().begin();
	while (iteGO != m_GOs.GetList().end())
	{
		GameObject GO = **iteGO;
		GO.Draw();
		++iteGO;
	}
}

void Application::setMousePos(float x, float y)
{
	mousePos[0] = x;
	mousePos[1] = y;
}

void Application::onMouseClick()
{
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			if (mousePos[0] >= 300.0f + (j * offset) - 50.0f &&
				mousePos[0] <= 300.0f + (j * offset) + 50.0f &&
				mousePos[1] >= 400.0f + (i * -offset) - 50.0f &&
				mousePos[1] <= 400.0f + (i * -offset) + 50.0f)
			{
				int box = (i * 3) + j;

				if (currentTurn == 0 && currentPlayer == 1)
				{
					if (arrayCheck[box] == 0)
					{
						arrayCheck[box] = 1;

						MyPhoton::getInstance().sendData(packer->pack(box + 1, 4));

						std::cout << "PLAYER 1 CHOICE [O] = " << box << std::endl;
						updateBoard(box);
						updateTurn();
					}
				}
				else if (currentTurn == 1 && currentPlayer == 2)
				{
					if (arrayCheck[box] == 0)
					{
						arrayCheck[box] = 2;

						MyPhoton::getInstance().sendData(packer->pack(box + 1, 4));

						std::cout << "PLAYER 2 CHOICE [X] = " << box << std::endl;
						updateBoard(box);
						updateTurn();
					}
				}
			}
		}
	}
}

void Application::onMouseMoved(float mousePosX, float mousePosY)
{
	setMousePos(mousePosX, RESOLUTION_Y - mousePosY);
	//std::cout << " X : " << mousePosX << " Y : " << mousePosY << std::endl;
}

void Application::setTurn(int set)
{
	if (currentPlayer == 0)
	{
		currentPlayer = set;
	}
}

void Application::updateTurn()
{
	++currentTurn;
	if (currentTurn % 2 == 0)
	{
		currentTurn = 0;
	}

	checkWin();
}

void Application::checkWin()
{
	if (// horizontal
		arrayCheck[0] == 1 && arrayCheck[1] == 1 && arrayCheck[2] == 1 ||
		arrayCheck[3] == 1 && arrayCheck[4] == 1 && arrayCheck[5] == 1 ||
		arrayCheck[6] == 1 && arrayCheck[7] == 1 && arrayCheck[8] == 1 ||
		// vertical
		arrayCheck[0] == 1 && arrayCheck[3] == 1 && arrayCheck[6] == 1 ||
		arrayCheck[1] == 1 && arrayCheck[4] == 1 && arrayCheck[7] == 1 ||
		arrayCheck[2] == 1 && arrayCheck[5] == 1 && arrayCheck[8] == 1 ||
		// diagonal
		arrayCheck[0] == 1 && arrayCheck[4] == 1 && arrayCheck[8] == 1 ||
		arrayCheck[2] == 1 && arrayCheck[4] == 1 && arrayCheck[6] == 1)
	{
		if (currentPlayer == 1)
		{
			std::cout << "PLAYER 1 WINS!" << std::endl;
		}
		else if (currentPlayer == 2)
		{
			std::cout << "PLAYER 2 LOST!" << std::endl;
		}
		stopRender = true;
		setGameState(OVER);
	}
	else if (
		// horizontal
		arrayCheck[0] == 2 && arrayCheck[1] == 2 && arrayCheck[2] == 2 ||
		arrayCheck[3] == 2 && arrayCheck[4] == 2 && arrayCheck[5] == 2 ||
		arrayCheck[6] == 2 && arrayCheck[7] == 2 && arrayCheck[8] == 2 ||
		// vertical
		arrayCheck[0] == 2 && arrayCheck[3] == 2 && arrayCheck[6] == 2 ||
		arrayCheck[1] == 2 && arrayCheck[4] == 2 && arrayCheck[7] == 2 ||
		arrayCheck[2] == 2 && arrayCheck[5] == 2 && arrayCheck[8] == 2 ||
		// diagonal
		arrayCheck[0] == 2 && arrayCheck[4] == 2 && arrayCheck[8] == 2 ||
		arrayCheck[2] == 2 && arrayCheck[4] == 2 && arrayCheck[6] == 2)
	{
		if (currentPlayer == 1)
		{
			std::cout << "PLAYER 1 LOST!" << std::endl;
		}
		else if (currentPlayer == 2)
		{
			std::cout << "PLAYER 2 WINS!" << std::endl;
		}
		stopRender = true;
		setGameState(OVER);
	}
	else if (
		// horizontal
		arrayCheck[0] != 0 && arrayCheck[1] != 0 && arrayCheck[2] != 0 &&
		arrayCheck[3] != 0 && arrayCheck[4] != 0 && arrayCheck[5] != 0 &&
		arrayCheck[6] != 0 && arrayCheck[7] != 0 && arrayCheck[8] != 0 &&
		// vertical
		arrayCheck[0] != 0 && arrayCheck[3] != 0 && arrayCheck[6] != 0 &&
		arrayCheck[1] != 0 && arrayCheck[4] != 0 && arrayCheck[7] != 0 &&
		arrayCheck[2] != 0 && arrayCheck[5] != 0 && arrayCheck[8] != 0 &&
		// diagonal
		arrayCheck[0] != 0 && arrayCheck[4] != 0 && arrayCheck[8] != 0 &&
		arrayCheck[2] != 0 && arrayCheck[4] != 0 && arrayCheck[6] != 0
		)
	{
		std::cout << "IT'S A DRAW!" << std::endl;
		stopRender = true;
		setGameState(OVER);
	}
}

void Application::setGameState(GameState state)
{
	m_state = state;
}

void Application::resetGame()
{
	for (int i = 0; i < 9; i++)
	{
		FindGameObject(i).SetSprite(m_sprite_box);
		arrayCheck[i] = 0;
	}

	currentTurn = 0;
	setGameState(START);
}

GameState Application::getGameState()
{
	return m_state;
}

void Application::OnReceivedOpponentData(unsigned char data, int bitCount)
{
	updateBoard((packer->unpack(data, bitCount)) - 1);
	updateTurn();
}
