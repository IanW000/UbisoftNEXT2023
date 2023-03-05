#include "stdafx.h"
#include "PowerUp.h"
#include <gameManager/gameManager.h>
#include <Math/Utils.h>

std::vector<CSimpleSprite*>  FireUpSpriteVector;
std::vector<CSimpleSprite*>  SpeedUpSpriteVector;
std::vector<CSimpleSprite*>  BombUpSpriteVector;

void PowerUp::Init(GameManager& gameManager)
{
}

void PowerUp::Update(GameManager& gameManager)
{
    for (auto fireUps : FireUpSpriteVector) {
        float x, y;
        fireUps->GetPosition(x, y);
        if (Utils::Distance(x, y, (float)gameManager.m_player.getX(), (float)gameManager.m_player.getY()+ 0) < 16) {
            FireUpSpriteVector.erase(std::remove(FireUpSpriteVector.begin(), FireUpSpriteVector.end(), fireUps), FireUpSpriteVector.end());
            gameManager.m_bomb.addBombPower();
            (*gameManager.getUI()).addFireUp();
            App::PlaySoundW(".\\res\\Sound\\powerUp.wav");
        }
    }
    for (auto speedUps : SpeedUpSpriteVector) {
        float x, y;
        speedUps->GetPosition(x, y);
        if (Utils::Distance(x, y, (float)gameManager.m_player.getX(), (float)gameManager.m_player.getY() + 0) < 16) {
            SpeedUpSpriteVector.erase(std::remove(SpeedUpSpriteVector.begin(), SpeedUpSpriteVector.end(), speedUps), SpeedUpSpriteVector.end());
            gameManager.m_player.addSpeed(0.1f);
            (*gameManager.getUI()).addSpeedUp();
            App::PlaySoundW(".\\res\\Sound\\powerUp.wav");
        }
    }
    for (auto bombUps : BombUpSpriteVector) {
        float x, y;
        bombUps->GetPosition(x, y);
        if (Utils::Distance(x, y, (float)gameManager.m_player.getX(), (float)gameManager.m_player.getY() + 0) < 16) {
            BombUpSpriteVector.erase(std::remove(BombUpSpriteVector.begin(), BombUpSpriteVector.end(), bombUps), BombUpSpriteVector.end());
            (*gameManager.getUI()).addBombsUp();
            //gameManager get timer cool down
            App::PlaySoundW(".\\res\\Sound\\powerUp.wav");
        }
    }
}

void PowerUp::Render(GameManager& gameManager)
{
    for (auto fireUps : FireUpSpriteVector) {
        fireUps->Draw();
    }

    for (auto speedUps : SpeedUpSpriteVector) {
        speedUps->Draw();
    }

    for (auto bombUps : BombUpSpriteVector) {
        bombUps->Draw();
    }

}


void PowerUp::dropPowerUp(GameManager& gameManager, float x, float y)
{
    //20% a destructed block drop an item
    if (Utils::RandomBool(0, 100, 60)) {

        int rand = Utils::RandomInt(0, 3);

        switch (rand) {
        case 0:

            CSimpleSprite * powerUpSprite;
            powerUpSprite = App::CreateSprite(".\\res\\Sprite\\BombsUp.bmp", 1, 1);
            powerUpSprite->SetScale(0.15f);
            powerUpSprite->SetPosition(x, y);

            BombUpSpriteVector.push_back(powerUpSprite);
            break;
        case 1:

            powerUpSprite = App::CreateSprite(".\\res\\Sprite\\SpeedUp.bmp", 1, 1);
            powerUpSprite->SetScale(0.15f);
            powerUpSprite->SetPosition(x, y);

            SpeedUpSpriteVector.push_back(powerUpSprite);
            break;
        case 2:
            powerUpSprite = App::CreateSprite(".\\res\\Sprite\\FireUp.bmp", 1, 1);
            powerUpSprite->SetScale(0.15f);
            powerUpSprite->SetPosition(x, y);

            FireUpSpriteVector.push_back(powerUpSprite);
            break;

        }

    }

}
