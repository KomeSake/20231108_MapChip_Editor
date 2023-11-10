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
	Vector2 _acc;
	float _speed;
	float _jumpSpeed;
	float _gravity;
	float _velMax;
	float _friction;

	float _width;
	float _height;
	map<int, LoadRes::SpriteList> _sprite;
	unsigned int _color;

	float _hp;

	bool _isJump;

	Player();
	void Initial();
	void Move(char prekeys[], char keys[], vector<vector<char>> mapData, float bgW, float bgH, float minMapSize);
	void Collide();
	void Show();
	void IsDead();
};

