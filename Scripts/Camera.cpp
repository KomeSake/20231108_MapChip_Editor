#include "Camera.h"

Camera::Camera(const int screenW, const int screenH, int bgW, int bgH)
{
	_bgWidth = (float)bgW;
	_bgHeight = (float)bgH;
	_screenWidth = (float)screenW;
	_screenHeight = (float)screenH;

	_randPlayerAttack = 1;
	_randEnemyDead = 7;

	_currentTime = 0;
	_enemyDeadTime = 10;

	_shakeEnemyDead = false;

	_pos = { _screenWidth / 2,_screenHeight / 2 };
	_playerOffset = { _screenWidth / 2,_screenHeight / 2 };
	_playerAttackOffset = { 0,0 };
	_enemyDeadOffset = { 0,0 };
}

void Camera::Move(Vector2 playerPos, bool isEnemyDeadOffset, bool isCameraShake)
{
	if (isCameraShake) {
		if (Novice::IsPressMouse(0)) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution dis_moveX(-_randPlayerAttack, _randPlayerAttack);
			std::uniform_real_distribution dis_moveY(-_randPlayerAttack, _randPlayerAttack);
			_playerAttackOffset = { dis_moveX(rd),dis_moveY(rd) };
		}
		else {
			_playerAttackOffset = { 0,0 };
		}
		if (isEnemyDeadOffset) {
			_shakeEnemyDead = true;
		}
		if (_shakeEnemyDead) {
			_currentTime++;
			if (_currentTime > _enemyDeadTime) {
				_currentTime = 0;
				_shakeEnemyDead = false;
			}
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution dis_moveX(-_randEnemyDead, _randEnemyDead);
			std::uniform_real_distribution dis_moveY(-_randEnemyDead, _randEnemyDead);
			_enemyDeadOffset = { dis_moveX(rd),dis_moveY(rd) };
		}
	}

	if (playerPos.x >= _screenWidth / 2 && playerPos.x <= _bgWidth - _screenWidth / 2) {
		_playerOffset.x = playerPos.x;
	}
	if (playerPos.y >= _screenHeight / 2 && playerPos.y <= _bgHeight - _screenHeight / 2) {
		_playerOffset.y = playerPos.y;
	}

	_pos.x = _playerOffset.x + _playerAttackOffset.x + _enemyDeadOffset.x;
	_pos.y = _playerOffset.y + _playerAttackOffset.y + _enemyDeadOffset.y;
}