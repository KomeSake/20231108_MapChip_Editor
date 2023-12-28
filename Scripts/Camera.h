#pragma once
#include <random>
#include "LoadRes.h"
#include "MyBase.h"

class Camera :
	public MyBase
{
public:
	Vector2 _pos;
	Vector2 _playerPos;
	Vector2 _cameraOffset;//カメラを揺れるとか、そういう変数を変える
	float _bgWidth;
	float _bgHeight;
	float _screenWidth;
	float _screenHeight;

	float _randomMoveX;
	float _randomMoveY;

	Camera(const int screenW, const int screenH, int bgW, int bgH);
	void Move(Vector2 playerPos);
};

