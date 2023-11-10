#pragma once
#include "MyTools.h"
#include <cmath>
#include <vector>
using namespace std;

class Player :
	public MyTools
{
public:
	Vector2 _pos;
	Vector2 _vel;
	Vector2 _dir;
	float _speed;

	float _width;
	float _height;
	map<int, LoadRes::SpriteList> _sprite;
	unsigned int _color;

	float _hp;

	float _bgHeight;
	float _bgWidht;

	Player();
	void Initial();
	void Move(char keys[], vector<vector<char>> mapData, float bgW, float bgH, float minMapSize);
	void Collide();
	void Show();
	void IsDead();
};

