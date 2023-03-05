#pragma once
#include <vector>

class GameManager; 

class Object
{
public:

	Object();

	virtual ~Object() = default;

	virtual void Init(GameManager & gameManager) = 0;

	virtual void Update(GameManager& gameManager) = 0;

    virtual void Render(GameManager& gameManager) = 0;

};

