#include "Enemy.h"

Enemy::Enemy()
{
	Initial();
}

void Enemy::Initial()
{
	_pos = { -100,-100 };
	_dir = { 0,0 };
	_vel = { 0,0 };
	_acc = { 0,0 };
	_speed = 1;
	_jumpSpeed = 5;
	_velMax = 3;
	_gravity = 0.2f;

	_width = 32;
	_height = 32;
	_sprite = LoadRes::_sl_Enemy_R;
	_color = WHITE;

	_hp = 2;
	_damage = 1;

	_isLeft = true;
	_isJump = false;

	//随机算出一开始往左还是往右
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution dis_moveX(0, 1);
	_isLeft = dis_moveX(gen);
}

void Enemy::Move(vector<vector<char>> mapData, float bgW, float bgH, float minMapSize)
{
	bgW;
	//随机来计算出是否要跳跃
	std::random_device rd;
	std::mt19937 gen(rd());
	if (MyTimers(500, 0)) {
		std::uniform_int_distribution dis_moveY(1, 10);
		if (dis_moveY(gen) >= 7) {
			_isJump = true;
		}
	}

	//通过状态来控制移动
	if (_isLeft) {
		_dir.x = -1;
	}
	else {
		_dir.x = 1;
	}
	if (_isJump) {
		_dir.y = 1;
		_isJump = false;
	}
	else {
		_dir.y = 0;
	}

	//和地图的碰撞检测
	int playerCheckRow = (int)((bgH - _pos.y) / minMapSize);
	int playerCheckLine = (int)(_pos.x / minMapSize);
	//X轴移动
	_acc.x = _dir.x * _speed;
	if (_vel.x<_velMax && _vel.x>-_velMax) {
		_vel.x += _acc.x;
	}
	_pos.x += _vel.x;

	int checkUp = (int)((bgH - _pos.y - _height / 2) / minMapSize);
	int checkDown = (int)((bgH - _pos.y + _height / 2 - 1) / minMapSize);
	int checkLeft = (int)((_pos.x - _width / 2) / minMapSize);
	int checkRight = (int)((_pos.x + _width / 2 - 1) / minMapSize);
	if (_vel.x > 0) {
		if (!Map::IsThrough(mapData, checkUp, checkRight)
			|| !Map::IsThrough(mapData, checkDown, checkRight)) {
			_pos.x = playerCheckLine * minMapSize + _width / 2;
			_vel.x = 0;
			_isLeft = true;
		}
	}
	else if (_vel.x < 0) {
		if (!Map::IsThrough(mapData, checkUp, checkLeft)
			|| !Map::IsThrough(mapData, checkDown, checkLeft)) {
			_pos.x = playerCheckLine * minMapSize + _width / 2;
			_vel.x = 0;
			_isLeft = false;
		}
	}
	//Y轴移动
	_acc.y = _dir.y * _jumpSpeed;
	_vel.y += _acc.y;
	_vel.y -= _gravity;
	_pos.y += _vel.y;

	checkUp = (int)((bgH - _pos.y - _height / 2) / minMapSize);
	checkDown = (int)((bgH - _pos.y + _height / 2 - 1) / minMapSize);
	checkLeft = (int)((_pos.x - _width / 2) / minMapSize);
	checkRight = (int)((_pos.x + _width / 2 - 1) / minMapSize);
	if (_vel.y > 0) {
		if (!Map::IsThrough(mapData, checkUp, checkLeft)
			|| !Map::IsThrough(mapData, checkUp, checkRight)) {
			_pos.y = bgH - playerCheckRow * minMapSize - _height / 2;
			_vel.y = 0;
		}
	}
	else if (_vel.y < 0) {
		if (!Map::IsThrough(mapData, checkDown, checkLeft)
			|| !Map::IsThrough(mapData, checkDown, checkRight)) {
			_pos.y = bgH - playerCheckRow * minMapSize - _height / 2;
			_vel.y = 0;
		}
	}
}

void Enemy::Dead()
{
	if (_hp <= 0) {
		Novice::PlayAudio(LoadRes::_audio_enemyDead, 0, 1);
		EnemyManager::ReleaseEnemy(this);
	}
}

void Enemy::Show()
{
	if (_vel.x >= 0) {
		FrameAnimation(_pos.x, _pos.y, LoadRes::_sl_Enemy_R, 0, _color, 100, 0);
	}
	else if (_vel.x < 0) {
		FrameAnimation(_pos.x, _pos.y, LoadRes::_sl_Enemy_L, 0, _color, 100, 0);
	}
}

void Enemy::Instantiated(float posX, float posY)
{
	_pos = { posX,posY };
	EnemyManager::_enemyUpdateVector.push_back(this);
}

void EnemyManager::EnemyUpdate(vector<vector<char>>mapData, float bgW, float bgH, float minSize)
{
	for (Enemy* it : _enemyUpdateVector) {
		it->Move(mapData, bgW, bgH, minSize);
		it->Dead();
	}
}

void EnemyManager::EnemyUpdateShow()
{
	for (Enemy* it : _enemyUpdateVector) {
		it->Show();
	}
}

Enemy* EnemyManager::AcquireEnemy()
{
	if (_enemyIdiePool.empty()) {
		Enemy* enemy = new Enemy();
		return enemy;
	}
	else {
		Enemy* enemy = _enemyIdiePool.front();
		_enemyIdiePool.pop();
		enemy->Initial();
		return enemy;
	}
}

void EnemyManager::ReleaseEnemy(Enemy* enemy)
{
	auto it = find(_enemyUpdateVector.begin(), _enemyUpdateVector.end(), enemy);
	if (it != _enemyUpdateVector.end()) {
		_enemyUpdateVector.erase(it);
	}
	_enemyIdiePool.push(enemy);
}

void EnemyManager::EnemyBornToMap(vector<vector<char>> mapData, float bgW, float bgH, float minSize)
{
	bgW;
	if (_enemyUpdateVector.size() < _enemyMax
		&& MyTimers(_bornTime, 0)) {
		Vector2 minMapPos{};
		minMapPos.x = minSize / 2;
		minMapPos.y = bgH - minSize / 2;
		for (const vector<char>& line : mapData) {
			Enemy* enemy = nullptr;
			for (const char& row : line) {
				switch (row) {
				case 'e':
					enemy = EnemyManager::AcquireEnemy();
					enemy->Instantiated(minMapPos.x, minMapPos.y);
					break;
				}
				minMapPos.x += minSize;
			}
			minMapPos.x = minSize / 2;
			minMapPos.y -= minSize;
		}
	}
}
