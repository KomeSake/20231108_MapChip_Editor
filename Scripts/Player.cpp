#include "Player.h"

Player::Player()
{
	Initial();
}

void Player::Initial()
{
	_pos = { 32 + 16,32 + 16 };
	_vel = { 0,0 };
	_dir = { 0,0 };
	_speed = 10;
	_jumpSpeed = 15;
	_gravity = 0.7f;
	_acc = { 0,0 };
	_velMax = 15;
	_friction = 0.4f;

	_width = 32;
	_height = 32;
	_sprite = LoadRes::_sl_playerIdle_R;
	_color = WHITE;

	_hp = 10;
	_damage = 2;

	_isJump = false;
}

void Player::Move(char prekeys[], char keys[], vector<vector<char>> mapData, float bgW, float bgH, float minMapSize)
{
	prekeys;
	if (keys[DIK_W] && !_isJump) {
		_isJump = true;
		_dir.y = 1;
	}
	else if (keys[DIK_S]) {
		//_dir.y = -1;
	}
	else {
		_dir.y = 0;
	}
	if (keys[DIK_A]) {
		_dir.x = -1;
	}
	else if (keys[DIK_D]) {
		_dir.x = 1;
	}
	else {
		_dir.x = 0;
	}
	//float vectorLength = sqrtf(powf(_dir.x, 2) + powf(_dir.y, 2));
	//if (vectorLength != 0) {
	//	_dir.x = _dir.x / vectorLength;
	//	_dir.y = _dir.y / vectorLength;
	//}

	//和地图碰撞的检测
	//先计算出当前所在的格子
	int playerCheckRow = (int)((bgH - _pos.y) / minMapSize);
	int playerCheckLine = (int)(_pos.x / minMapSize);
	//然后X轴开始移动

	_acc.x = _dir.x * _speed;
	if (_vel.x<_velMax && _vel.x>-_velMax) {
		_vel.x += _acc.x;
	}
	_vel.x = _vel.x * _friction;
	_pos.x += _vel.x;
	//接着算出新的4个角的坐标
	int checkUp = (int)((bgH - _pos.y - _height / 2) / minMapSize);
	int checkDown = (int)((bgH - _pos.y + _height / 2 - 1) / minMapSize);
	int checkLeft = (int)((_pos.x - _width / 2) / minMapSize);
	int checkRight = (int)((_pos.x + _width / 2 - 1) / minMapSize);
	//判断是否碰撞了，碰到了就退回去
	if (_vel.x > 0) {
		if (!Map::IsThrough(mapData, checkUp, checkRight)
			|| !Map::IsThrough(mapData, checkDown, checkRight)) {
			_pos.x = playerCheckLine * minMapSize + _width / 2;
			_vel.x = 0;
		}
	}
	else if (_vel.x < 0) {
		if (!Map::IsThrough(mapData, checkUp, checkLeft)
			|| !Map::IsThrough(mapData, checkDown, checkLeft)) {
			_pos.x = playerCheckLine * minMapSize + _width / 2;
			_vel.x = 0;
		}
	}
	//然后开始Y轴
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
			_isJump = false;
		}
	}

	//最外围的边界限制
	if (_pos.x + _width / 2 > bgW) {
		_pos.x = bgW - _width / 2;
	}
	else if (_pos.x - _width / 2 < 0) {
		_pos.x = _width / 2;
	}
	if (_pos.y + _height / 2 > bgH) {
		_pos.y = bgH - _height / 2;
	}
	else if (_pos.y - _height / 2 < 0) {
		_pos.y = _height / 2;
	}
}



void Player::Collide()
{
	Vector2 leftDownPos = { _pos.x - _width / 2 ,_pos.y - _height / 2 };
	Vector2 rightDownPos = { _pos.x + _width / 2,_pos.y - _height / 2 };
	for (Enemy* it : EnemyManager::_enemyUpdateVector) {
		//只有在下落的时候才算踩踏
		if (_vel.y < 0) {
			if (leftDownPos.x > it->_pos.x - it->_width / 2
				&& leftDownPos.x<it->_pos.x + it->_width / 2
				&& leftDownPos.y>it->_pos.y - it->_height / 2
				&& leftDownPos.y < it->_pos.y + it->_height / 2
				|| rightDownPos.x > it->_pos.x - it->_width / 2
				&& rightDownPos.x<it->_pos.x + it->_width / 2
				&& rightDownPos.y>it->_pos.y - it->_height / 2
				&& rightDownPos.y < it->_pos.y + it->_height / 2) {
				it->_hp -= _damage;
				//踩中了自己还会跳一下
				_vel.y = _jumpSpeed;
				continue;
			}
		}
		//不然就正常判断碰撞
		else {
			float length = sqrtf(powf(it->_pos.x - _pos.x, 2) + powf(it->_pos.y - _pos.y, 2));
			if (length < it->_width / 2 + _width / 2) {
				_hp -= it->_damage;
				_vel.y = _jumpSpeed * 0.7f;
				_vel.x = it->_dir.x * _speed * 2.f * -1;
				_color = RED;
				break;
			}
		}
	}
}

void Player::Show()
{
	//受伤会变成红色，所以要一段时间后把时间变回来
	if (_color != WHITE) {
		if (MyTimers(500, 0)) {
			_color = WHITE;
		}
	}

	if (_vel.x < 0.5f && _vel.x >= 0) {
		FrameAnimation(_pos.x, _pos.y, LoadRes::_sl_playerIdle_R, 0, _color, 300, 0);
	}
	else if (_vel.x > -0.5f && _vel.x <= 0) {
		FrameAnimation(_pos.x, _pos.y, LoadRes::_sl_playerIdle_L, 0, _color, 300, 0);
	}
	else if (_vel.x > 0.5f) {
		FrameAnimation(_pos.x, _pos.y, LoadRes::_sl_playerRun_R, 0, _color, 100, 0);
	}
	else if (_vel.x < -0.5f) {
		FrameAnimation(_pos.x, _pos.y, LoadRes::_sl_playerRun_L, 0, _color, 100, 0);
	}
}

void Player::IsDead()
{
	if (_hp <= 0) {
		_color = GREEN;
	}
}
