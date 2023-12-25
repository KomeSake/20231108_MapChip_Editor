#pragma once
#include <random>
#include "LoadRes.h"
#include "MyBase.h"

class Camera :
	public MyBase
{
public:
	Vector2 _pos;
	Vector2 _playerOffset;
	Vector2 _enemyDeadOffset;
	Vector2 _playerAttackOffset;
	float _bgWidth;
	float _bgHeight;
	float _screenWidth;
	float _screenHeight;

	float _randPlayerAttack;
	float _randEnemyDead;
	int _currentTime;
	int _enemyDeadTime;

	bool _shakeEnemyDead;

	Camera(const int screenW, const int screenH, int bgW, int bgH);
	void Move(Vector2 playerPos, bool isEnemyDeadOffset);
};

