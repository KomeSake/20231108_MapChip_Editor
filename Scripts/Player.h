#pragma once
#include "MyTools.h"
class Player :
	public MyTools
{
public:
	Vector2 _pos;
	float _width;
	float _height;
	map<int, LoadRes::SpriteList> _sprite;
	unsigned int _color;

	float _hp;

	Player();
	void Initial();
	void Move(char keys[]);
	void Collide();
	void Show();
	void IsDead();
};

