#pragma once
#include <Object/Object.h>

struct PowerUp : public Object
{
	virtual void Init(GameManager& gameManager) override;

	virtual void Update(GameManager& gameManager) override;

	virtual void Render(GameManager& gameManager) override;

	void dropPowerUp(GameManager& gameManager, float x, float y);

};


