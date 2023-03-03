#include "stdafx.h"
#include "Renderer.h"
#include <App/App.h>
#include <Math/Utils.h>


//CSimpleSprite* testSprite;
CSimpleSprite* playerSprite;

std::vector<CSimpleSprite*> brickSprite;

std::vector<CSimpleSprite*> blockSprite;

std::vector<CSimpleSprite*> grassSprite;


//Screen width is 1024, height is 768, each object will be 32*32

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768
#define BLOCK_BRICK_SIZE 32
#define ROW (WIN_HEIGHT/BLOCK_BRICK_SIZE)
#define COL (WIN_WIDTH/BLOCK_BRICK_SIZE)
#define BRICK_NUM 30

enum ATTR {
	SPACE,
	BLOCK,
	BRICK
};

int map[ROW][COL];

enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};


Renderer::Renderer()
{
}

void Renderer::Init()
{
	for (int i = 0; i < ROW; i++) {
		map[i][0] = map[i][COL - 1] = BLOCK;
	}

	for (int i = 0; i < COL; i++) {
		map[0][i] = map[ROW - 1][i] = BLOCK;
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i % 4 == 0 && j % 4 == 0) {
				map[i][j] = BLOCK;
			}
		}
	}
	map[2][2] = BRICK;
	
	for (int i = 0; i < 700; i++) {
		int r = Utils::RandomInt(1,ROW - 2);
		int c = Utils::RandomInt(1,COL - 2);
		if(map[r][c] == SPACE)
			map[r][c] = BRICK;
	}


	int playerX;
	int playerY;

	playerSprite = App::CreateSprite(".\\res\\Sprite\\Player.bmp", 4, 4);

	while (1) {
		int x = Utils::RandomInt(1, ROW - 2);
		int y = Utils::RandomInt(1, COL - 2);
		if (map[x][y] == SPACE) {
			playerX = y * BLOCK_BRICK_SIZE;
			playerY = x * BLOCK_BRICK_SIZE;
			break;
		}
	}



	playerSprite->SetPosition(playerX + 18, playerY + 24);
	float speed = 1.0f / 15.0f;
	playerSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 4,5,6,7 });
	playerSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11 });
	playerSprite->CreateAnimation(ANIM_RIGHT, speed, { 12,13,14,15 });
	playerSprite->CreateAnimation(ANIM_FORWARDS, speed, { 0,1,2,3 });
	playerSprite->SetScale(.2f);


	//testSprite = App::CreateSprite(".\\res\\Sprite\\Block.bmp", 1, 1);
	//testSprite->SetPosition(100, 100);
	//testSprite->SetScale(1.0f);

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			switch (map[i][j]) {

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

void Renderer::Update(float deltaTime)
{
	playerSprite->Update(deltaTime);

	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		playerSprite->SetAnimation(ANIM_RIGHT);
		float x, y;
		playerSprite->GetPosition(x, y);
		x += 1.0f;
		playerSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		playerSprite->SetAnimation(ANIM_LEFT);
		float x, y;
		playerSprite->GetPosition(x, y);
		x -= 1.0f;
		playerSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		playerSprite->SetAnimation(ANIM_FORWARDS);
		float x, y;
		playerSprite->GetPosition(x, y);
		y += 1.0f;
		playerSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		playerSprite->SetAnimation(ANIM_BACKWARDS);
		float x, y;
		playerSprite->GetPosition(x, y);
		y -= 1.0f;
		playerSprite->SetPosition(x, y);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		playerSprite->SetScale(playerSprite->GetScale() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		playerSprite->SetScale(playerSprite->GetScale() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		playerSprite->SetAngle(playerSprite->GetAngle() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		playerSprite->SetAngle(playerSprite->GetAngle() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		playerSprite->SetAnimation(-1);
	}


}

void Renderer::Render()
{
	for (auto block : blockSprite) {
		block->Draw();
	}
	for (auto brick : brickSprite) {
		brick->Draw();
	}
	for (auto space : grassSprite) {
		space->Draw();
	}



	//testSprite->Draw();
	playerSprite->Draw();
}
