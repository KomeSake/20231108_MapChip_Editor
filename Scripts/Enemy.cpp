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
	_rad = 0;
	_speed = 1;
	_jumpSpeed = 5;
	_velMax = 3;
	_gravity = 0.05f;

	_width = 32;
	_height = 32;
	_sprite = LoadRes::_sl_Enemy_R;
	_color = WHITE;

	_hp = 10;
	_damage = 1;

	_isLeft = true;
	_isJump = false;
	_isDead = false;
	_isHurt = false;
	_isDeadOffset = false;

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
		Novice::PlayAudio(LoadRes::_audio_enemyJump, 0, 0.3f);
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

void Enemy::Collide()
{
	for (Bullet* it : BulletManager::_bulletUpdateVector) {
		if (!it->_isDead) {
			float length = sqrtf(powf(it->_pos.x - _pos.x, 2) + powf(it->_pos.y - _pos.y, 2));
			if (length < it->_width / 2 + _width / 2) {
				_hp -= it->_damage;
				it->_isDead = true;
				_isHurt = true;
				if (it->_dir.x > 0) {
					_pos.x += 10;
					ParticleManager::ADD_Particle(_pos.x - 10, _pos.y, Emitter::enemyHurtL);
					Novice::PlayAudio(LoadRes::_audio_enemyHurt, 0, 1);
				}
				else if (it->_dir.x < 0) {
					_pos.x -= 10;
					ParticleManager::ADD_Particle(_pos.x + 10, _pos.y, Emitter::enemyHurtR);
					Novice::PlayAudio(LoadRes::_audio_enemyHurt, 0, 1);
				}
			}
		}
	}
}

void Enemy::Dead()
{
	if (_isDeadOffset) {
		_isDeadOffset = false;
	}
	if (_hp <= 0 && !_isDead) {
		_vel.y = _jumpSpeed * 0.9f;
		Novice::PlayAudio(LoadRes::_audio_enemyDead, 0, 1);
		Novice::PlayAudio(LoadRes::_audio_enemyDead2, 0, 1);
		_isDead = true;
		_isDeadOffset = true;
	}
	if (_isDead) {
		_color = RED;
		_vel.x = _speed * 0.5f;
		_pos.x += _vel.x;
		_vel.y -= _gravity * 3;
		_pos.y += _vel.y;

		_rad += -_vel.y * 0.01f;

		if (_pos.y < -50) {
			EnemyManager::ReleaseEnemy(this);
		}
	}
}

void Enemy::Show()
{
	if (_isHurt) {
		_color = BLUE;
		if (MyTimers(100, 1)) {
			_isHurt = false;
			_color = WHITE;
		}
	}
	if (_vel.x >= 0) {
		FrameAnimation(_pos.x, _pos.y, LoadRes::_sl_Enemy_R, _rad, _color, 100, 0);
	}
	else if (_vel.x < 0) {
		FrameAnimation(_pos.x, _pos.y, LoadRes::_sl_Enemy_L, _rad, _color, 100, 0);
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
		if (!it->_isDead) {
			it->Move(mapData, bgW, bgH, minSize);
			it->Collide();
		}
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

bool EnemyManager::IsEnemyDeadOffset()
{
	for (Enemy* it : _enemyUpdateVector) {
		if (it->_isDeadOffset) {
			return true;
		}
	}
	return false;
}
