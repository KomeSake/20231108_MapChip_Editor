#pragma warning(disable: 28251)//WinMain関数の警告を無視
#include <Novice.h>
#include "Scripts/MyBase.h"
#include "Scripts/Camera.h"
#include "Scripts/Player.h"
#include "Scripts/Scene.h"
#include "Scripts/Map.h"


const char kWindowTitle[] = "v20230707";
unsigned int screenW = 800, screenH = 800;
unsigned int bgW = 50 * 32, bgH = 25 * 32;

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

	Camera* CameraObj = new Camera(screenW, screenH, bgW, bgH);
	Player* PlayerObj = new Player();
	Scene* SceneObj = new Scene();
	Map* MapObj = new Map();


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
		switch (SceneObj->_sceneIndex) {
		case Scene::Loading:
			break;
		case Scene::Start:
			break;
		case Scene::Game:
			PlayerObj->Move(keys);
			CameraObj->Move(PlayerObj->_pos);
			MyTools::CheckCameraValume(CameraObj->_pos, screenW, screenH);
			PlayerObj->Collide();

			PlayerObj->IsDead();

			MapObj->MapShow(Map::_mapData, 32);
			PlayerObj->Show();

			SceneObj->SceneStart();
			break;
		case Scene::GameOver:
			break;
		}
		///
		/// ↑描画処理ここまで
		///

		//Debug情報
		Novice::ScreenPrintf(10, 10, "Player(%d,%d)", int(PlayerObj->_pos.x), int(PlayerObj->_pos.y));
		Novice::ScreenPrintf(10, 30, "Camera(%d,%d)", int(CameraObj->_pos.x), int(CameraObj->_pos.y));

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
