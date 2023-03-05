#pragma once

#include <Object/Object.h>

struct Bomb : public Object
{

public:

	const int TOTAL = 100;

	virtual void Init(GameManager& gameManager) override;

	virtual void Update(GameManager& gameManager) override;

	virtual void Render(GameManager& gameManager) override;

	void addBombPower();

	void spawnBomb(GameManager& gameManager, float x, float y);

	void Exploding(GameManager& gameManager, float x, float y);

	GameManager* GetGameManager() const;

	std::vector<int> m_ids;

	int GetBegin() const;
	int GetSize() const;

	void SetScene(GameManager* scene);
	void SetBegin(int num);
	void SetSize(int num);
	void SetEnd(int num);
	bool Activate(int num);
	bool Deactivate(int num);
	void UpdateIds();

private:

	int count = 0;

	int BombPower = 1;

	GameManager *m_gameManager;
	int m_begin;
	int m_size;
	int m_end;
	void SwapMemory(int num);
};

