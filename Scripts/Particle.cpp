#include "Particle.h"

Particle::Particle(Vector2 pos, TYPE type)
{
	Inital(pos, type);
}

void Particle::Inital(Vector2 pos, TYPE type)
{

	std::random_device rd;
	std::mt19937 gen(rd());

	_currentTime = 0;
	_pos = pos;
	_vel = { 0,0 };
	_acc = { 0,0 };
	_dir = { 0,0 };
	_gravity = 0.7f;
	_type = type;
	_sprite = {};
	_angle = 0;
	_scale = { 1,1 };
	alphaValue = 255;

	switch (_type) {
	case bulletDead: {
		_speed = 0.5f;
		std::uniform_real_distribution dis_dirX(-1.f, 1.f);
		std::uniform_real_distribution dis_dirY(-0.5f, 2.f);
		_dir = { dis_dirX(gen), dis_dirY(gen) };
		_radius = 3;
		std::uniform_real_distribution dis_angle(-10.f, 10.f);
		_angle = dis_angle(gen);
		_color = WHITE;
		std::uniform_int_distribution dis_life(5, 10);
		_lifeTime = dis_life(gen);
		break; }
	case gunFire: {
		_speed = 0.01f;
		std::uniform_real_distribution dis_dirX(-1.f, 1.f);
		std::uniform_real_distribution dis_dirY(-0.5f, 2.f);
		_dir = { dis_dirX(gen), dis_dirY(gen) };
		_radius = 1;
		_color = 0xfff59dff;
		std::uniform_int_distribution dis_life(10, 20);
		_lifeTime = dis_life(gen);
		break; }
	case playerJump: {
		_speed = 0.1f;
		std::uniform_real_distribution dis_dirX(-1.f, 1.f);
		std::uniform_real_distribution dis_dirY(0.f, 2.f);
		_dir = { dis_dirX(gen), dis_dirY(gen) };
		_radius = 5;
		_color = 0xe0e0e0ff;
		std::uniform_real_distribution dis_scale(1.f, 2.f);
		_scale = { dis_scale(rd),dis_scale(rd) };
		std::uniform_int_distribution dis_life(10, 20);
		_lifeTime = dis_life(gen);
		break; }
	case enemyHurtL:
	case enemyHurtR: {
		_speed = 0.5f;
		_dir.x = _type == enemyHurtL ? -1.f : 1.f;
		std::uniform_real_distribution dis_dirY(-0.5f, 2.f);
		_dir.y = dis_dirY(gen);
		_radius = 3;
		_color = 0xab47bcff;
		std::uniform_int_distribution dis_life(40, 60);
		_lifeTime = dis_life(gen);
		break; }
	case bulletShellL:
	case bulletShellR: {
		_sprite = LoadRes::_sp_BulletShell;
		_speed = 0.5f;
		_dir.x = _type == bulletShellL ? 1.f : -1.f;
		std::uniform_real_distribution dis_dirY(1.f, 2.f);
		_dir.y = dis_dirY(gen);
		_radius = 8;
		std::uniform_real_distribution dis_angle(-10.f, 10.f);
		//_angle = dis_angle(gen);
		_color = WHITE;
		_lifeTime = 240;
		break; }
	}
}

void Particle::Move(vector<vector<char>> mapData, float bgW, float bgH, float minMapSize)
{
	mapData, bgW, bgH, minMapSize;
	std::random_device rd;
	std::mt19937 gen(rd());

	switch (_type) {
	case bulletDead: {
		_acc.x = _dir.x * _speed;
		_acc.y = _dir.y * _speed;
		if (_currentTime < 10) {
			_vel.x += _acc.x;
			_vel.y += _acc.y;
		}
		_vel.y -= 0.5f;
		_pos = { _pos.x + _vel.x,_pos.y + _vel.y };
		break; }
	case gunFire: {
		_acc.x = _dir.x * _speed;
		_acc.y = _dir.y * _speed;
		if (_currentTime < 10) {
			_vel.x += _acc.x;
			_vel.y += _acc.y;
		}
		_vel.y += 0.1f;
		_pos = { _pos.x + _vel.x,_pos.y + _vel.y };
		_scale.x += 0.05f;
		_scale.y += 0.05f;
		float steps = float(_currentTime) / float(_lifeTime);
		_color = ColorInterpolation(0xfff59dff, 0xbdbdbdff, steps);
		break; }
	case playerJump: {
		_acc.x = _dir.x * _speed;
		_acc.y = _dir.y * _speed;
		if (_currentTime < 10) {
			_vel.x += _acc.x;
			_vel.y += _acc.y;
		}
		_pos = { _pos.x + _vel.x,_pos.y + _vel.y };
		if (alphaValue > 1) {
			_color = 0xe0e0e0ff | alphaValue << 0;
			alphaValue -= 5;
		}
		break; }
	case enemyHurtL:
	case enemyHurtR: {
		_acc.x = _dir.x * _speed;
		_acc.y = _dir.y * _speed;
		if (_currentTime < 10) {
			_vel.x += _acc.x;
			_vel.y += _acc.y;
		}
		_vel.y -= 0.5f;
		int checkUp = (int)((bgH - _pos.y - _radius) / minMapSize);
		int checkDown = (int)((bgH - _pos.y + _radius - 1) / minMapSize);
		int checkLeft = (int)((_pos.x - _radius) / minMapSize);
		int checkRight = (int)((_pos.x + _radius - 1) / minMapSize);
		if (!Map::IsThrough(mapData, checkUp, checkRight)
			&& !Map::IsThrough(mapData, checkDown, checkRight)
			|| !Map::IsThrough(mapData, checkUp, checkLeft)
			&& !Map::IsThrough(mapData, checkDown, checkLeft)) {
			_scale.y += 0.1f;
		}
		else if (!Map::IsThrough(mapData, checkUp, checkLeft)
			&& !Map::IsThrough(mapData, checkUp, checkRight)
			|| !Map::IsThrough(mapData, checkDown, checkLeft)
			&& !Map::IsThrough(mapData, checkDown, checkRight)) {
			_scale.x += 0.1f;
		}
		_vel.y -= 0.5f;
		int checkUp = (int)((bgH - _pos.y - 9) / minMapSize);
		int checkDown = (int)((bgH - _pos.y + 9 - 1) / minMapSize);
		int checkLeft = (int)((_pos.x - 7) / minMapSize);
		int checkRight = (int)((_pos.x + 7 - 1) / minMapSize);
		if (!Map::IsThrough(mapData, checkUp, checkRight)
			&& !Map::IsThrough(mapData, checkDown, checkRight)
			|| !Map::IsThrough(mapData, checkUp, checkLeft)
			&& !Map::IsThrough(mapData, checkDown, checkLeft)) {
			_vel.x *= -0.5f;
		}
		else if (!Map::IsThrough(mapData, checkUp, checkLeft)
			&& !Map::IsThrough(mapData, checkUp, checkRight)
			|| !Map::IsThrough(mapData, checkDown, checkLeft)
			&& !Map::IsThrough(mapData, checkDown, checkRight)) {
			_vel.y *= -0.5f;
		}
		break; }
	}

	_currentTime++;
}

void Particle::Show()
{
	Vector2 screenPos = MyTools::WorldToScreen(_pos.x, _pos.y);
	switch (_type) {
	case bulletDead:
		Novice::DrawBox(int(screenPos.x), int(screenPos.y), int(_radius * _scale.x), int(_radius * _scale.y), _angle, _color, kFillModeSolid);
		break;
	case gunFire:
	case playerJump:
	case enemyHurtL:
	case enemyHurtR:
		Novice::DrawEllipse(int(screenPos.x), int(screenPos.y), int(_radius * _scale.x), int(_radius * _scale.y), _angle, _color, kFillModeSolid);
		break;
	}
}

void Particle::Dead()
{
	if (_currentTime >= _lifeTime) {
		ParticleManager::ReleaseParticle(this);
	}
}

void Particle::Instantiated()
{
	ParticleManager::_particleUpdatePool.push_back(this);
}

bool Particle::IsMapTouch(vector<vector<char>> mapData, float bgW, float bgH, float minMapSize)
{
	bgW;
	int checkLine = (int)((bgH - _pos.y) / minMapSize);
	int checkRow = (int)(_pos.x / minMapSize);
	if (Map::IsThrough(mapData, checkLine, checkRow)) {
		return false;
	}
	else {
		return true;
	}
}

Emitter::Emitter(Vector2 pos, TYPE type)
{
	Inital(pos, type);
}

void Emitter::Inital(Vector2 pos, TYPE type)
{
	_pos = pos;
	_scale = { 1,1 };
	_type = type;
	_isDead = false;
	_color = WHITE;
	_angle = 0;
	_currentTime = 0;
	_lifeTime = 0;
	_isLoop = false;
	_particleCurrentTime = 0;

	switch (_type) {
	case bulletDead:
		_width = 5;
		_height = 5;
		_particleSum = 12;
		break;
	case gunFire:
		_width = 25;
		_height = 25;
		_particleSum = 1;
		_lifeTime = 2;
		_color = 0xfff59dff;
		break;
	case playerJump:
		_width = 2;
		_height = 10;
		_particleSum = 3;
		break;
	case enemyHurtL:
	case enemyHurtR:
		_width = 5;
		_height = 5;
		_particleSum = 1;
		break;
	}
}

void Emitter::ParticleStart()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution disX(-_width / 2, _width / 2);
	std::uniform_real_distribution disY(-_height / 2, _height / 2);
	Vector2 randomPos{};
	Particle* element{};


	if (_particleCurrentTime == 0) {
		for (int i = 0; i < _particleSum; i++) {
			randomPos = { disX(gen),disY(gen) };
			randomPos = { randomPos.x + _pos.x,randomPos.y + _pos.y };
			switch (_type) {
			case bulletDead:
				element = ParticleManager::AcquireParticle(randomPos, Particle::bulletDead);
				element->Instantiated();
				break;
			case gunFire:
				element = ParticleManager::AcquireParticle(randomPos, Particle::gunFire);
				element->Instantiated();
				break;
			case playerJump:
				element = ParticleManager::AcquireParticle(randomPos, Particle::playerJump);
				element->Instantiated();
				break;
			case enemyHurtL:
				element = ParticleManager::AcquireParticle(randomPos, Particle::enemyHurtL);
				element->Instantiated();
				break;
			case enemyHurtR:
				element = ParticleManager::AcquireParticle(randomPos, Particle::enemyHurtR);
				element->Instantiated();
				break;
			}
		}
	}

	//Emitter生きる時間
	_currentTime++;
	if (_currentTime >= _lifeTime && !_isLoop) {
		_isDead = true;
	}
	//パーティクルを生まれる時間
	_particleCurrentTime++;
	if (_particleCurrentTime > _particleGetTime) {
		_particleCurrentTime = 0;
	}
}

void Emitter::Show()
{
	Vector2 screenPos = MyTools::WorldToScreen(_pos.x, _pos.y);
	switch (_type) {
	case gunFire:
		Novice::DrawEllipse(int(screenPos.x), int(screenPos.y), int(_width / 2 * _scale.x), int(_height / 2 * _scale.y), _angle, _color, kFillModeSolid);
		break;
	}
}

void Emitter::Dead()
{
	if (_isDead) {
		ParticleManager::ReleaseEmitter(this);
	}
}

void Emitter::Instantiated()
{
	ParticleManager::_emitterUpadtePool.push_back(this);
}

void ParticleManager::ParticleUpdate(vector<vector<char>> mapData, float bgW, float bgH, float minMapSize)
{
	for (Particle* it : _particleUpdatePool) {
		it->Move(mapData, bgW, bgH, minMapSize);
		it->Dead();
	}
}

void ParticleManager::ParticleUpdateShow()
{
	for (Particle* it : _particleUpdatePool) {
		it->Show();
	}
}

Particle* ParticleManager::AcquireParticle(Vector2 startPos, Particle::TYPE type)
{
	//if (_particleIdiePool.empty()) {
	//	Particle* par = new Particle(startPos, type);
	//	return par;
	//}
	//else {
	//	Particle* par = _particleIdiePool.front();
	//	_particleIdiePool.pop();
	//	par->Inital(startPos, type);
	//	return par;
	//}
	Particle* par = new Particle(startPos, type);
	return par;
}

void ParticleManager::ReleaseParticle(Particle* particle)
{
	auto it = find(_particleUpdatePool.begin(), _particleUpdatePool.end(), particle);
	if (it != _particleUpdatePool.end()) {
		_particleUpdatePool.erase(it);
	}
	_particleIdiePool.push(particle);
}


void ParticleManager::EmitterUpdate()
{
	for (Emitter* it : _emitterUpadtePool) {
		it->ParticleStart();
		it->Dead();
	}
}

void ParticleManager::EmitterUpdateShow()
{
	for (Emitter* emi : _emitterUpadtePool) {
		emi->Show();
	}
}

Emitter* ParticleManager::AcquireEmitter(Vector2 pos, Emitter::TYPE type)
{
	//if (_emitterIdiePool.empty()) {
	//	return new Emitter(pos, type);
	//}
	//else {
	//	Emitter* emi = _emitterIdiePool.front();
	//	_emitterIdiePool.pop();
	//	emi->Inital(pos, type);
	//	return emi;
	//}

	//バッグがあるので、一応こんな感じにする
	Emitter* emi = new Emitter(pos, type);
	return emi;
}

void ParticleManager::ReleaseEmitter(Emitter* emitter)
{
	auto it = find(_emitterUpadtePool.begin(), _emitterUpadtePool.end(), emitter);
	if (it != _emitterUpadtePool.end()) {
		_emitterUpadtePool.erase(it);
	}
	_emitterIdiePool.push(emitter);
}

void ParticleManager::ADD_Particle(float posX, float posY, Emitter::TYPE type)
{
	Emitter* emi = AcquireEmitter({ posX,posY }, type);
	emi->Instantiated();
}

void ParticleManager::Update(vector<vector<char>> mapData, float bgW, float bgH, float minMapSize)
{
	ParticleUpdate(mapData, bgW, bgH, minMapSize);
	EmitterUpdate();
}

void ParticleManager::Show()
{
	ParticleUpdateShow();
	EmitterUpdateShow();
}
