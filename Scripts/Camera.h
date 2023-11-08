#pragma once
#include <vector>
#include <cmath>
#include <map>
#include <ctime>
#include "LoadRes.h"
#include "MyBase.h"
using namespace std;

class Camera :
	public MyBase
{
public:
	Vector2 _pos;
	Vector2 _cameraOffset;//カメラを揺れるとか、そういう変数を変える
	float _bgWidth;
	float _bgHeight;
	float _screenWidth;
	float _screenHeight;

	Camera(const int screenW, const int screenH, int bgW, int bgH);
	void Move(Vector2 playerPos);
};

