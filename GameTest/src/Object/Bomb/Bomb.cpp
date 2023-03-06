#include "stdafx.h"
#include "Bomb.h"
#include <GameManager/GameManager.h>
#include <Math/Utils.h>

std::vector<CSimpleSprite*>  bombSpriteVector;
std::vector<CSimpleSprite*>  ExplosionSpriteVector;


CSimpleSprite* bombSprite;

void Bomb::Init(GameManager& gameManager) {
    int id = 0;
    for (int i = 0; i < TOTAL; i++)
    {
        // Allocate memory
        id = gameManager.CreateId();
    }

    SetScene(&gameManager);
    SetBegin(id - (TOTAL - 1));
    SetSize(id - (TOTAL - 1));
    SetEnd(id);
}

void Bomb::Update(GameManager& gameManager)
{

    float current = gameManager.GetTime();

    int id = GetBegin();
    while (id < GetSize())
    {
        Timer timer = gameManager.GetTimer(id);

        if (timer.timeElapsed(current) >= timer.stayAlive)
        {
            Deactivate(id);

            float x, y;
   
            bombSpriteVector[count]->GetPosition(x, y);
            count++;

            Exploding(gameManager,x,y);
            if (bombSpriteVector.size() > 0) {
                bombSpriteVector.pop_back();
                count--;
            }
            App::PlaySoundW(".\\res\\Sound\\TEST.wav");
        }
        else
        {
            id++;
        }
    }
    
    for (auto bomb : bombSpriteVector) {

        bomb->Update(gameManager.GetDeltaTime());
        bomb->SetAnimation(0);

    }

    for (auto explosion : ExplosionSpriteVector) {

        if (explosion != nullptr) {

            explosion->Update(gameManager.GetDeltaTime());
            explosion->SetAnimation(0);

            if (explosion->GetFrame() == 5)
                ExplosionSpriteVector.erase(std::remove(ExplosionSpriteVector.begin(), ExplosionSpriteVector.end(), explosion), ExplosionSpriteVector.end());
        }
    }


    UpdateIds();
}

void Bomb::Render(GameManager& gameManager) {

    for (auto bomb : bombSpriteVector) {
            bomb->Draw();
    }

    for (auto exSprite : ExplosionSpriteVector) {
            exSprite->Draw();
    }
}

void Bomb::addBombPower()
{
    BombPower++;
}

void Bomb::spawnBomb(GameManager& gameManager, float x, float y)
{
    int bomb = GetSize();

    if (Activate(bomb)) {
        App::PlaySound(".\\res\\Sound\\hover.wav");

        CSimpleSprite* latested;
        latested = App::CreateSprite(".\\res\\Sprite\\Bomb.bmp", 4, 1);
        latested->CreateAnimation(0, .2f, { 0,1,2,3 });
        latested->SetScale(0.4f);

        latested->SetPosition(x, y);
        bombSpriteVector.push_back(latested);

        float width = 0.1f;

        Timer timer;
        timer.start = gameManager.GetTime();
        timer.stayAlive = 2.0f;
        gameManager.BomberTimer(bomb, timer);
    }
}

void Bomb::Exploding(GameManager& gameManager, float x, float y)
{
    int xaxis = (int)(x-16) / GameManager::BLOCK_BRICK_SIZE;
    int yaxis = (int)(y-16) / GameManager::BLOCK_BRICK_SIZE;

    gameManager.Mat2D(yaxis, xaxis) = SPACE;

    CSimpleSprite* explosionSprite;
    explosionSprite = App::CreateSprite(".\\res\\Sprite\\ExplosionStart.bmp", 8, 1);
    float animSpeed = 1.0f / 15.0f;
    explosionSprite->SetPosition(x, y);
    explosionSprite->CreateAnimation(0, animSpeed*3, { 0,1,2,3,4,5,6,7 });
    explosionSprite->SetScale(0.2f);
    ExplosionSpriteVector.push_back(explosionSprite);

    CSimpleSprite* destructionSprite;
    destructionSprite = App::CreateSprite(".\\res\\Sprite\\BrickAnimation.bmp", 6, 1);
    destructionSprite->CreateAnimation(0, animSpeed*2, { 0,1,2,3,4,5 });
    destructionSprite->SetScale(0.4f);

    //Top
    for (int i = 0; i < BombPower+1; i++) {

        if (gameManager.Mat2D(yaxis + i, xaxis) == BRICK) {

            gameManager.Mat2D(yaxis + i, xaxis) = SPACE;
            gameManager.m_powerUp.dropPowerUp(gameManager, (float)x, (float)y + 32 * i);
            destructionSprite->SetPosition((float)x, (float)y + 32 * i);
            ExplosionSpriteVector.push_back(destructionSprite);

        }
        else if (gameManager.Mat2D(yaxis + i, xaxis) == SPACE) {
            if (i == BombPower) {
                 explosionSprite = App::CreateSprite(".\\res\\Sprite\\ExplosionEnd.bmp", 8, 1);
                 explosionSprite->CreateAnimation(0, animSpeed, { 0,1,2,3,4,5,6,7 });
                 explosionSprite->SetPosition((float)x, (float)y + 32 * i);
                 explosionSprite->SetAngle(1.5f);
                 explosionSprite->SetScale(0.2f);
             }
             else if(i>0) {
                 explosionSprite = App::CreateSprite(".\\res\\Sprite\\ExplosionMiddle.bmp", 8, 1);
                 explosionSprite->CreateAnimation(0, animSpeed, { 0,1,2,3,4,5,6,7 });
                 explosionSprite->SetPosition((float)x, (float)y + 32 * i);
                 explosionSprite->SetAngle(1.5f);
                 explosionSprite->SetScale(0.2f);
             }
            ExplosionSpriteVector.push_back(explosionSprite);
        }
    
        //Down

        if (gameManager.Mat2D(yaxis - i, xaxis) == BRICK) {
            gameManager.m_powerUp.dropPowerUp(gameManager, (float)x, (float)y - 32 * i);
            gameManager.Mat2D(yaxis - i, xaxis) = SPACE;
            destructionSprite->SetPosition((float)x, (float)y - 32 * i);
            ExplosionSpriteVector.push_back(destructionSprite);
        }
        else if (gameManager.Mat2D(yaxis - i, xaxis) == SPACE) {
            if (i == BombPower) {
                explosionSprite = App::CreateSprite(".\\res\\Sprite\\ExplosionEnd.bmp", 8, 1);
                explosionSprite->CreateAnimation(0, animSpeed, { 0,1,2,3,4,5,6,7 });
                explosionSprite->SetPosition((float)x, (float)y - 32 * i);
                explosionSprite->SetAngle(-1.5f);
                explosionSprite->SetScale(0.2f);
            }
            else if (i > 0) {
                explosionSprite = App::CreateSprite(".\\res\\Sprite\\ExplosionMiddle.bmp", 8, 1);
                explosionSprite->CreateAnimation(0, animSpeed, { 0,1,2,3,4,5,6,7 });
                explosionSprite->SetPosition((float)x, (float)y - 32 * i);
                explosionSprite->SetAngle(-1.5f);
                explosionSprite->SetScale(0.2f);
            }
            ExplosionSpriteVector.push_back(explosionSprite);
        }
    

        //Right

        if (gameManager.Mat2D(yaxis , xaxis + i) == BRICK) {
            gameManager.m_powerUp.dropPowerUp(gameManager, (float)x + 32 * i, (float)y);
            gameManager.Mat2D(yaxis , xaxis + i) = SPACE;
            destructionSprite->SetPosition((float)x + 32 * i, (float)y);
            ExplosionSpriteVector.push_back(destructionSprite);
        }
        else if (gameManager.Mat2D(yaxis, xaxis + i) == SPACE) {
            if (i == BombPower) {
                explosionSprite = App::CreateSprite(".\\res\\Sprite\\ExplosionEnd.bmp", 8, 1);
                explosionSprite->CreateAnimation(0, animSpeed, { 0,1,2,3,4,5,6,7 });
                explosionSprite->SetPosition((float)x + 32 * i, (float)y );
                explosionSprite->SetAngle(0.0f);
                explosionSprite->SetScale(0.2f);
            }
            else if (i > 0) {
                explosionSprite = App::CreateSprite(".\\res\\Sprite\\ExplosionMiddle.bmp", 8, 1);
                explosionSprite->CreateAnimation(0, animSpeed, { 0,1,2,3,4,5,6,7 });
                explosionSprite->SetPosition((float)x + 32 * i, (float)y);
                explosionSprite->SetAngle(0.0f);
                explosionSprite->SetScale(0.2f);
            }
            ExplosionSpriteVector.push_back(explosionSprite);
        }
    
        //Left

        if (gameManager.Mat2D(yaxis, xaxis - i) == BRICK) {
            gameManager.m_powerUp.dropPowerUp(gameManager, (float)x - 32 * i, (float)y);
            gameManager.Mat2D(yaxis, xaxis - i) = SPACE;
            destructionSprite->SetPosition((float)x - 32 * i, (float)y);
            ExplosionSpriteVector.push_back(destructionSprite);
        }
        else if (gameManager.Mat2D(yaxis, xaxis - i) == SPACE) {
            if (i == BombPower) {
                explosionSprite = App::CreateSprite(".\\res\\Sprite\\ExplosionEnd.bmp", 8, 1);
                explosionSprite->CreateAnimation(0, animSpeed, { 0,1,2,3,4,5,6,7 });
                explosionSprite->SetPosition((float)x - 32 * i, (float)y );
                explosionSprite->SetAngle(3.0f);
                explosionSprite->SetScale(0.2f);
            }
            else if (i > 0) {
                explosionSprite = App::CreateSprite(".\\res\\Sprite\\ExplosionMiddle.bmp", 8, 1);
                explosionSprite->CreateAnimation(0, animSpeed, { 0,1,2,3,4,5,6,7 });
                explosionSprite->SetPosition((float)x - 32 * i, (float)y );
                explosionSprite->SetAngle(3.0f);
                explosionSprite->SetScale(0.2f);
            }
            ExplosionSpriteVector.push_back(explosionSprite);
        }
    }


    for (int i = 0; i < BombPower + 1; i++) {

        if (((x > gameManager.m_player.getX() && x - i * 40 < gameManager.m_player.getX()) || (x < gameManager.m_player.getX() && x + i * 40 > gameManager.m_player.getX())) && (abs(y - gameManager.m_player.getY()) < 24)
            || ((y > gameManager.m_player.getY() && y - i * 40 < gameManager.m_player.getY()) || (y < gameManager.m_player.getY() && y + i * 40 > gameManager.m_player.getY())) && (abs(x - gameManager.m_player.getX()) < 24))
        {
            gameManager.m_player.setHP(5);
            App::PlaySoundW(".\\res\\Sound\\takeDamage.wav");
        }      
        if (((x > gameManager.m_enemy.getX() && x - i * 40 < gameManager.m_enemy.getX()) || (x < gameManager.m_enemy.getX() && x + i * 40 > gameManager.m_enemy.getX())) && (abs(y - gameManager.m_enemy.getY()) < 24)
            || ((y > gameManager.m_enemy.getY() && y - i * 40 < gameManager.m_enemy.getY()) || (y < gameManager.m_enemy.getY() && y + i * 40 > gameManager.m_enemy.getY())) && (abs(x - gameManager.m_enemy.getX()) < 24))
        {
            gameManager.m_enemy.setHP(5);
            App::PlaySoundW(".\\res\\Sound\\takeDamage.wav");
        }
    }
    gameManager.UpdateMap(xaxis, yaxis);
}

GameManager* Bomb::GetGameManager() const
{
    return m_gameManager;
    return nullptr;
}

int Bomb::GetBegin() const
{
    return m_begin;
}

int Bomb::GetSize() const
{
    return m_size;
}

bool Bomb::Activate(int id)
{
    //assert(id >= m_size);

    if (m_size > m_end)
    {
        return false;
    }

    SwapMemory(id);
    m_size++;
    return true;
}

bool Bomb::Deactivate(int id)
{
    //assert(id < m_size);

    m_size--;

    SwapMemory(id);

    return true;
}

void Bomb::UpdateIds()
{
    m_ids.clear();

    for (int id = m_begin; id < m_size; id++)
    {
        m_ids.push_back(id);
    }
}

void Bomb::Reset()
{
    BombPower = 1;
}


void Bomb::SetScene(GameManager* mapManager)
{
    m_gameManager = mapManager;
}

void Bomb::SetBegin(int id)
{
    m_begin = id;
}

void Bomb::SetSize(int id)
{
    m_size = id;
}

void Bomb::SetEnd(int id)
{
    m_end = id;
}

void Bomb::SwapMemory(int id)
{
    //assert(m_gameManager != nullptr);

    if (m_size == id)
    {
        return;
    }
    Timer timer = m_gameManager->GetTimer(m_size);
    m_gameManager->BomberTimer(m_size, m_gameManager->GetTimer(id));
    m_gameManager->BomberTimer(id, timer);
}