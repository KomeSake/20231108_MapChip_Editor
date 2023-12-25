#pragma once
#include <vector>
#include <queue>
#include <random>
#include <cmath>
#include "MyTools.h"
#include "Map.h"
#include "Enemy.h"
class Bullet :
	public MyTools
{
public:
	Vector2 _pos;
	Vector2 _dir;
	float _speed;

	float _width;
	float _height;
	LoadRes::Sprite _sprite;
	unsigned int _color;

	float _randomMoveY;//发射时候一点点的随机方向偏移
	float _damage;

	bool _isDead;

	Bullet();
	void Initial();
	void Move(vector<vector<char>>mapData, float bgW, float bgH, float minMapSize);
	void Dead();
	void Collide();
	void Show();
	void Instantiated(float posX, float posY, bool isLeft);
};

class BulletManager :
	public MyTools {
public:
	inline static std::vector<Bullet*> _bulletUpdateVector;
	inline static std::queue<Bullet*> _bulletIdiePool;

	static void BulletUpdate(vector<vector<char>>mapData, float bgW, float bgH, float minSize);
	static void BulletUpdateShow();
	static Bullet* AcquireBullet(float posX, float posY, bool isLeft);
	static void ReleaseBullet(Bullet* bullet);
};

