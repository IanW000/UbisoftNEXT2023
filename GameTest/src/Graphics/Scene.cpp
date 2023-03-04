#include "stdafx.h"
#include "Scene.h"
#include <App/App.h>
#include <Math/Utils.h>
#include <string>


//CSimpleSprite* testSprite;

CSimpleSprite* bomBSprite;
std::vector<CSimpleSprite*> brickSprite;
std::vector<CSimpleSprite*> blockSprite;
std::vector<CSimpleSprite*> grassSprite;

struct Boom {
	int x;
	int y;

	int exist;
	bool explode;
}boom;


Scene::Scene() 
{
}
//UI &UISettings
void Scene::Init()
{
	//this->UISettings = &UISettings;

	boom.exist = false;
	boom.explode = false;
	boom.x = 0;
	boom.y = 0;

	for (int i = 0; i < ROW; i++) {
		Mat2D(i, 0) = Mat2D(i, COL - 1) = BLOCK;
	}

	for (int i = 0; i < COL; i++) {
		Mat2D(0, i) = Mat2D(ROW - 1,i) = BLOCK;
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i % 4 == 0 && j % 4 == 0) {
				Mat2D(i,j) = BLOCK;
			}
		}
	}

	player.Init(Mat2D);
	
	for (int i = 0; i < brickNum; i++) {
		int r = Utils::RandomInt(1,ROW - 2);
		int c = Utils::RandomInt(1,COL - 2);
		if(Mat2D(r,c) == SPACE)
			Mat2D(r, c) = BRICK;
	}

	bomBSprite = App::CreateSprite(".\\res\\Sprite\\Bomb.bmp", 4, 1);
	float bombSpeed = 1.0f / 15.0f;
	bomBSprite->SetPosition(400, 400);
	bomBSprite->CreateAnimation(0 , bombSpeed, { 0,1,2,3 });
	bomBSprite->SetScale(.5f);


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
}

void Scene::Update(float deltaTime)
{
	
	player.Update(deltaTime);

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

	
	std::string debugLine = std::to_string(player.currentHP);
	App::Print(40, 650, "Debug:", 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);
	App::Print(120, 650, debugLine.c_str(), 1.0f, .25f, .5f, GLUT_BITMAP_HELVETICA_18);

	//draw objects
	bomBSprite->Draw();
	player.Render();
}
