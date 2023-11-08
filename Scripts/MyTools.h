#pragma once
#include <cmath>
#include <ctime>
#include <map>
#include "LoadRes.h"
#include "MyBase.h"
using namespace std;

//それは自作の道具のクラス、Vector2構造体、Cameraのワールド座標、LoadRes構造体が要る
//MyTimers：ストップウォッチ
//FrameTexture：中心からワールド座標にテクスチャを描画関数(拡大縮小、回転、からー)
//FrameAnimation：中心からワールド座標にアニメーションを描画関数(拡大縮小、回転、からー)


class MyTools :
	public MyBase
{
	//描画関数の使い方法
	//1.　ToolsObjで参照しでください（ToolsObj.）
	//1.1　ToolsObjは一般的にポインタで宣言するから、「.」を書いて、自動に「->」を変えた
	//2.　オーバーロードになったから、引数によって、自動に適当な関数を使う
	//2.1　一般的に回る、拡大縮小、角度、色って引数がある
	//3.　番号の引数を注意してください。できるだけ、１つ物は１つ番号に対応してください。


public:
	//ワールド座標が要るので、関数はmain.cppの中に使用しないといけない
	static void CheckCameraValume(Vector2 cameraPos, unsigned int screenW, unsigned int screenH);

	//ストップウォッチ（３０番がある）
	int MyTimers(int milli, int index);

	//スライドの描画関数
	void FrameTexture(float x, float y, LoadRes::Sprite sprite, int color);
	void FrameTexture(float x, float y, LoadRes::Sprite sprite, float rad, int color);
	void FrameTexture(float x, float y, LoadRes::Sprite sprite, float scaleX, float scaleY, int color);
	void FrameTexture(float x, float y, LoadRes::Sprite sprite, float scaleX, float scaleY, float rad, int color);
	//スライドシートに指定したいフレームを描画する
	void FrameTexture(float x, float y, map<int, LoadRes::SpriteList>spList, int index, int color);
	void FrameTexture(float x, float y, map<int, LoadRes::SpriteList>spList, int index, float rad, int color);
	void FrameTexture(float x, float y, map<int, LoadRes::SpriteList>spList, int index, float scaleX, float scaleY, int color);
	void FrameTexture(float x, float y, map<int, LoadRes::SpriteList>spList, int index, float scaleX, float scaleY, float rad, int color);

	//スライドシートのアニメーション関数
	//位置ｘ、位置ｙ、シート、ラジアン、フレームごとにミリ秒、何番を使う
	void FrameAnimation(float x, float y, map<int, LoadRes::SpriteList>spList, float rad, int color, int frameTime, int playIndex);
	void FrameAnimation(float x, float y, map<int, LoadRes::SpriteList>spList, float scaleX, float scaleY, float rad, int color, int frameTime, int playIndex);

	//スクリーン座標はワールド座標に変える
	static Vector2 ScreenToWorld(float screenX, float screenY);
	//ワールド座標はスクリーン座標に変える
	static Vector2 WorldToScreen(float worldPosX, float worldPosY);
	//スライドはオブジェクトの向きと同じになる
	static float SpriteToObjDir(Vector2 dir);

	//ベクトルの正規化
	Vector2 VectorNormalization(float x, float y);
	//加法定理
	Vector2 AditionRule(Vector2 pos, float rad);

	//アニメーションのための変数
	static const int _frame_sum = 31;//３０番がある(参照しないでください)
	//指定したいフレイムからプレイする(例えば、０フレームから)
	//毎回Enemyは復活する時、もし一番目のフレームからプレイしたいなら、この変数に0を代入する
	int _frameAniIndex[_frame_sum] = { 0 };







	//以下は自作関数用の変数、参照しないでください
protected:
	//カメラ
	inline static Vector2 _cameraPos;
	inline static float _screenWidth;
	inline static float _screenHeight;
	//ストップウォッチ
	clock_t _timeStart[31] = { 0 };
	clock_t _timeEnd[31] = { 0 };
	bool _isTimeOpen[31] = { 0 };
	//アニメーション
	int FrameTimers(int milli, int index);// ストップウォッチ
	clock_t _frame_timeStart[_frame_sum] = { 0 };
	clock_t _frame_timeEnd[_frame_sum] = { 0 };
	bool _frame_isTimeOpen[_frame_sum] = { 0 };
};

