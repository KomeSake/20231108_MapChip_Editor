#pragma warning(disable: 28251)//WinMain関数の警告を無視
#include <Novice.h>
#include "Scripts/MyBase.h"
#include "Scripts/Camera.h"
#include "Scripts/Player.h"
#include "Scripts/Scene.h"
#include "Scripts/Map.h"
#include "Scripts/Enemy.h"


const char kWindowTitle[] = "v20230707";
const int screenW = 800, screenH = 800;
const int bgW = 50 * 32, bgH = 25 * 32;
const float minMapSize = 32;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, screenW, screenH);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//自分の変数
	LoadRes::LoadResNovice();
	Map::LoaclMapLoad(Map::_mapFileName, Map::_mapData);
	int bgmLoopHandle = 0;//为了循环的Bgm而弄的

	Camera* CameraObj = new Camera(screenW, screenH, bgW, bgH);
	Player* PlayerObj = new Player();
	Scene* SceneObj = new Scene();
	Map* MapObj = new Map();
	EnemyManager* EnemyManagerObj = new EnemyManager();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		int mouseX{}, mouseY{};
		Novice::GetMousePosition(&mouseX, &mouseY);

		switch (SceneObj->_sceneIndex) {
		case Scene::Loading:
			Novice::StopAudio(bgmLoopHandle);

			EnemyManager::_enemyUpdateVector.clear();
			PlayerObj = new Player();
			CameraObj = new Camera(screenW, screenH, bgW, bgH);
			SceneObj->_sceneIndex = SceneObj->Game;
			break;

		case Scene::Start:
			CameraObj = new Camera(screenW, screenH, bgW, bgH);
			MyTools::CheckCameraValume(CameraObj->_pos, screenW, screenH);
			MapObj->MapShow(Map::_mapData, minMapSize);
			SceneObj->SceneStart(preKeys, keys);
			break;

		case Scene::Game:
			PlayerObj->Move(preKeys, keys, Map::_mapData, bgW, bgH, minMapSize);
			CameraObj->Move(PlayerObj->_pos);
			MyTools::CheckCameraValume(CameraObj->_pos, screenW, screenH);
			EnemyManagerObj->EnemyBornToMap(Map::_mapData, bgW, bgH, minMapSize);
			EnemyManager::EnemyUpdate(Map::_mapData, bgW, bgH, minMapSize);

			PlayerObj->Collide();

			PlayerObj->Dead();
			if (PlayerObj->_hp <= 0) {
				SceneObj->_sceneIndex = SceneObj->GameOver;
			}

			MapObj->MapShow(Map::_mapData, minMapSize);
			EnemyManager::EnemyUpdateShow();
			PlayerObj->Show();
			SceneObj->SceneGame(int(PlayerObj->_hp));

			if (!Novice::IsPlayingAudio(bgmLoopHandle) || bgmLoopHandle == -1) {
				bgmLoopHandle = Novice::PlayAudio(LoadRes::_audio_bgm, 0, 1);
			}
			break;

		case Scene::GameOver:
			PlayerObj->Dead();
			EnemyManager::EnemyUpdate(Map::_mapData, bgW, bgH, minMapSize);
			MapObj->MapShow(Map::_mapData, minMapSize);
			EnemyManager::EnemyUpdateShow();
			PlayerObj->Show();
			SceneObj->SceneGameOver(mouseX, mouseY, preKeys, keys);
			break;
		}
		///
		/// ↑描画処理ここまで
		///

		//Debug情報
		//Novice::ScreenPrintf(10, 10, "Player(%d,%d)", int(PlayerObj->_pos.x), int(PlayerObj->_pos.y));
		//Novice::ScreenPrintf(10, 30, "Camera(%d,%d)", int(CameraObj->_pos.x), int(CameraObj->_pos.y));

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
