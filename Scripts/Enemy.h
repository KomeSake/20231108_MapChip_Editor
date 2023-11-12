#pragma once
#include "MyTools.h"
#include "Map.h"
#include <vector>
#include <queue>
#include <random>
class Enemy :
	public MyTools
{
public:
	Vector2 _pos;
	Vector2 _vel;
	Vector2 _dir;
	Vector2 _acc;
	float _speed;
	float _jumpSpeed;
	float _velMax;
	float _gravity;

	float _width;
	float _height;
	map<int, LoadRes::SpriteList> _sprite;
	unsigned int _color;

	float _hp;
	float _damage;

	bool _isLeft;
	bool _isJump;

	Enemy();
	void Initial();
	void Move(vector<vector<char>>mapData, float bgW, float bgH, float minMapSize);
	void Collide();
	void Dead();
	void Show();
	void Instantiated(float posX, float posY);
};


class EnemyManager :
	public MyTools {

public:
	inline static int _bornTime = 3000;
	inline static int _enemyMax = 20;

	inline static std::vector<Enemy*> _enemyUpdateVector;
	inline static std::queue<Enemy*> _enemyIdiePool;

	static void EnemyUpdate(vector<vector<char>>mapData, float bgW, float bgH, float minSize);
	static void EnemyUpdateShow();
	static Enemy* AcquireEnemy();
	static void ReleaseEnemy(Enemy* enemy);

	void EnemyBornToMap(vector<vector<char>>mapData, float bgW, float bgH, float minSize);
};