#pragma once
#include <vector>
#include <queue>
#include <random>
#include "MyTools.h"
#include "Map.h"
class Particle :
	public MyTools
{
public:
	static enum TYPE
	{
		bulletDead,
		gunFire,
		playerJump,
		enemyHurtL,
		enemyHurtR,
		bulletShellL,
		bulletShellR,
	}_particleType;

	Vector2 _pos;
	Vector2 _vel;
	Vector2 _dir;
	Vector2 _acc;
	float _speed;
	float _gravity;

	TYPE _type;
	float _radius;
	float _angle;
	Vector2 _scale;
	LoadRes::Sprite _sprite;
	unsigned int _color;
	int alphaValue;

	int _currentTime;
	int _lifeTime;

	Particle(Vector2 pos, TYPE type);
	void Inital(Vector2 pos, TYPE type);
	void Move(vector<vector<char>> mapData, float bgW, float bgH, float minMapSize);
	void Show();
	void Dead();
	void Instantiated();
	//判断中心点是否和不可通过的地图块碰撞了
	bool IsMapTouch(vector<vector<char>> mapData, float bgW, float bgH, float minMapSize);
	//判断物体是X轴还是Y轴和不可通过的地图块碰撞了(0:no 1:X 2:Y)
	int IsXYMapTouch(vector<vector<char>> mapData, float bgW, float bgH, float minMapSize);
};

class Emitter :
	public MyTools
{
public:
	static enum TYPE
	{
		bulletDead,
		gunFire,
		playerJump,
		enemyHurtL,
		enemyHurtR,
		bulletShellL,
		bulletShellR,
	}_particleType;

	Vector2 _pos;
	float _angle;
	unsigned int _color;
	float _width;//粒子が出る位置の範囲
	float _height;
	Vector2 _scale;

	TYPE _type;
	int _currentTime;
	int _lifeTime;
	bool _isLoop;//Trueの場合、ずっと生きている
	int _particleGetTime;//パーティクルを生まれる間時間(１フレーム１個の生まれる時間もちょっと早すぎる)
	int _particleCurrentTime;//時間を計算用
	int _particleSum;

	bool _isDead;

	Emitter(Vector2 pos, TYPE type);
	void Inital(Vector2 pos, TYPE type);
	void ParticleStart();
	void Show();
	void Dead();
	void Instantiated();
};

class ParticleManager :
	public MyTools
{
public:
	inline static std::vector<Particle*> _particleUpdatePool;
	inline static std::queue<Particle*> _particleIdiePool;
	inline static std::vector<Emitter*> _emitterUpadtePool;
	inline static std::queue<Emitter*> _emitterIdiePool;

	static void ParticleUpdate(vector<vector<char>> mapData, float bgW, float bgH, float minMapSize);
	static void ParticleUpdateShow();
	static Particle* AcquireParticle(Vector2 startPos, Particle::TYPE type);
	static void ReleaseParticle(Particle* particle);

	static void EmitterUpdate();
	static void EmitterUpdateShow();
	static Emitter* AcquireEmitter(Vector2 pos, Emitter::TYPE type);
	static void ReleaseEmitter(Emitter* emitter);

	//普通のパーティクル：位置、Type
	static void ADD_Particle(float posX, float posY, Emitter::TYPE type);
	//更新用関数
	static void Update(vector<vector<char>> mapData, float bgW, float bgH, float minMapSize);
	//描画用関数
	static void Show();
};