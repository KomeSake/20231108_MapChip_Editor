#include "Bullet.h"

Bullet::Bullet()
{
	Initial();
}

void Bullet::Initial()
{
	_pos = { -100,-100 };
	_dir = { 0,0 };
	_speed = 10;

	_width = 16;
	_height = 16;
	_sprite = LoadRes::_sp_Bullet;
	_color = WHITE;

	_randomMoveY = 0.1f;
	_damage = 1;

	_isDead = false;
}

void Bullet::Move(vector<vector<char>> mapData, float bgW, float bgH, float minMapSize)
{
	bgW;
	//和地图的碰撞检测
	_pos.x += _dir.x * _speed;
	int checkUp = (int)((bgH - _pos.y - _height / 2) / minMapSize);
	int checkDown = (int)((bgH - _pos.y + _height / 2 - 1) / minMapSize);
	int checkLeft = (int)((_pos.x - _width / 2) / minMapSize);
	int checkRight = (int)((_pos.x + _width / 2 - 1) / minMapSize);
	if (_dir.x > 0) {
		if (!Map::IsThrough(mapData, checkUp, checkRight)
			|| !Map::IsThrough(mapData, checkDown, checkRight)) {
			_isDead = true;
		}
	}
	else if (_dir.x < 0) {
		if (!Map::IsThrough(mapData, checkUp, checkLeft)
			|| !Map::IsThrough(mapData, checkDown, checkLeft)) {
			_isDead = true;
		}
	}
	_pos.y += _dir.y * _speed;
	checkUp = (int)((bgH - _pos.y - _height / 2) / minMapSize);
	checkDown = (int)((bgH - _pos.y + _height / 2 - 1) / minMapSize);
	checkLeft = (int)((_pos.x - _width / 2) / minMapSize);
	checkRight = (int)((_pos.x + _width / 2 - 1) / minMapSize);
	if (_dir.y > 0) {
		if (!Map::IsThrough(mapData, checkUp, checkLeft)
			|| !Map::IsThrough(mapData, checkUp, checkRight)) {
			_isDead = true;
		}
	}
	else if (_dir.y < 0) {
		if (!Map::IsThrough(mapData, checkDown, checkLeft)
			|| !Map::IsThrough(mapData, checkDown, checkRight)) {
			_isDead = true;
		}
	}
}

void Bullet::Dead()
{
	BulletManager::ReleaseBullet(this);
}

void Bullet::Show()
{
	float rad = MyTools::SpriteToObjDir(_dir);
	MyTools::FrameTexture(_pos.x, _pos.y, _sprite, 1, 1, rad, _color);
}

void Bullet::Instantiated(float posX, float posY, bool isLeft)
{
	_pos = { posX,posY };
	//设置方向(随机一个偏移角度出来，让子弹的发射更有趣)
	_dir.x = isLeft ? 1.f : -1.f;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution dis_moveY(-_randomMoveY, _randomMoveY);
	_dir.y = dis_moveY(rd);
	BulletManager::_bulletUpdateVector.push_back(this);
}

void BulletManager::BulletUpdate(vector<vector<char>> mapData, float bgW, float bgH, float minSize)
{
	for (Bullet* it : _bulletUpdateVector) {
		if (it->_isDead == false) {
			it->Move(mapData, bgW, bgH, minSize);
		}
		else {
			it->Dead();
		}
	}
}

void BulletManager::BulletUpdateShow()
{
	for (Bullet* it : _bulletUpdateVector) {
		it->Show();
	}
}

Bullet* BulletManager::AcquireBullet(float posX, float posY, bool isLeft)
{
	Bullet* obj{};
	if (_bulletIdiePool.empty()) {
		obj = new Bullet();
	}
	else {
		obj = _bulletIdiePool.front();
		_bulletIdiePool.pop();
		obj->Initial();
	}
	obj->Instantiated(posX, posY, isLeft);
	return obj;
}

void BulletManager::ReleaseBullet(Bullet* bullet)
{
	auto it = find(_bulletUpdateVector.begin(), _bulletUpdateVector.end(), bullet);
	if (it != _bulletUpdateVector.end()) {
		_bulletUpdateVector.erase(it);
	}
	_bulletIdiePool.push(bullet);
}
