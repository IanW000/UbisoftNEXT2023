#include "stdafx.h"
#include "Scene.h"
#include <App/App.h>
#include <Math/Utils.h>
#include <string>


//CSimpleSprite* testSprite;


std::vector<CSimpleSprite*> brickSprite;
std::vector<CSimpleSprite*> blockSprite;
std::vector<CSimpleSprite*> grassSprite;

int testSave, testSave2;
Scene::Scene() : m_UISettings(nullptr), deadScreen(false) 
{
}
//UI &UISettings
void Scene::Init(UI& UISettings)
{
	m_UISettings = &UISettings;


	for (int i = 0; i < ROW; i++) {
		Mat2D(i, 0) = Mat2D(i, COL - 1) = BLOCK;
	}

	for (int i = 0; i < COL; i++) {
		Mat2D(0, i) = Mat2D(ROW - 1, i) = BLOCK;
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i % 4 == 0 && j % 4 == 0) {
				Mat2D(i, j) = BLOCK;
			}
		}
	}

	for (int i = 0; i < brickNum; i++) {
		int r = Utils::RandomInt(1, ROW - 2);
		int c = Utils::RandomInt(1, COL - 2);
		if (Mat2D(r, c) == SPACE)
			Mat2D(r, c) = BRICK;
	}






		int x = Utils::RandomInt(2, Scene::COL - 3);
		int y = Utils::RandomInt(2, Scene::ROW - 3);

		testSave = x;
		testSave2 = y;


		Mat2D(y + 1, x + 1) = SPACE;
		Mat2D(y + 1, x) = SPACE;
		Mat2D(y + 1, x - 1) = SPACE;
		Mat2D(y, x + 1) = SPACE;
		Mat2D(y, x) = SPACE;
		Mat2D(y, x - 1) = SPACE;
		player.setX(x * Scene::BLOCK_BRICK_SIZE );
		player.setY(y * Scene::BLOCK_BRICK_SIZE +55);






	//int a[] = { 1 };
	//{
	//	
	//		Matrix matrix[] = [(y + 1, x + 1)

	//			


		player.Init();

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			switch (Mat2D(i,j)) {

			case SPACE:
				CSimpleSprite* space;
				space = App::CreateSprite(".\\res\\Sprite\\Ground.bmp", 1, 1);
				space->SetPosition(j * (float)BLOCK_BRICK_SIZE + 16, i * (float)BLOCK_BRICK_SIZE + 16);

				space->SetScale(0.2f);
				grassSprite.push_back(space);
				break;

			case BLOCK:
				CSimpleSprite* block;
				block = App::CreateSprite(".\\res\\Sprite\\Block.bmp", 1, 1);
				block->SetPosition(j * (float)BLOCK_BRICK_SIZE + 16, i * (float)BLOCK_BRICK_SIZE + 16);

				block->SetScale(0.2f);
				blockSprite.push_back(block);
				break;

			case BRICK:
				CSimpleSprite* brick;
				brick = App::CreateSprite(".\\res\\Sprite\\Brick.bmp", 1, 1);
				brick->SetPosition(j * (float)BLOCK_BRICK_SIZE + 16, i * (float)BLOCK_BRICK_SIZE + 16);

				brick->SetScale(0.2f);
				brickSprite.push_back(brick);
				break;

			}
		}
	}



	for (auto bombs : m_Bombs) {
		(*bombs).Init(player.getX(), player.getY());
	}


}


void Scene::Update(float deltaTime)
{
	
	switch ((*m_UISettings).getCurrentScreen()) {

		case Screens::MAINMENU:

			player.Reset();
			deadScreen = false;
			break;

		case Screens::GAME:

			player.Update(deltaTime,Mat2D);
			break;
	}

	if (player.died && !deadScreen) {
		deadScreen = true;

		(*m_UISettings).setCurrentScreen(Screens::DEAD);
	}



	if (App::IsKeyPressed('J'))
	{
		Bomb newBomb;
		m_Bombs.push_back(&newBomb);
	}
	
	for (auto bombs : m_Bombs) {
		(*bombs).Update();
	}
}

void Scene::Render()
{
	//Draw the background
	for (auto block : blockSprite) {
		block->Draw();
	}
	for (auto brick : brickSprite) {
		brick->Draw();
	}
	for (auto space : grassSprite) {
		space->Draw();
	}

	///BLOCK_BRICK_SIZE
	std::string debugLine = std::to_string(testSave);


	App::Print(40, 650, "Debug:", 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);
	App::Print(120, 650, debugLine.c_str(), 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);

	App::Print(120, 630, std::to_string(testSave2).c_str(), 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);

	//draw objects
	player.Render();

	for (auto bombs : m_Bombs) {
		(*bombs).Render();
	}
}
