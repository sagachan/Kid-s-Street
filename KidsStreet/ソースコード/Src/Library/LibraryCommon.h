//LibraryCommon.h
//プロジェクト全体で共通に使うもの

#pragma once
#include "DxLib.h"
enum VOID_TYPE
{
	VOID_INIT,
	VOID_LOAD,
	VOID_SET,
	VOID_STEP,
	VOID_UPDATE,
	VOID_HIT,
	VOID_DRAW,
	VOID_DELETE,
	VOID_FIN
};

//必要に応じて変更
//当たり判定を持つオブジェクトの種類数
enum COL_CHECK_LIST
{
	COL_NONE = -1,

	COL_CHECK_PLAYER,
	COL_CHECK_CAR,
	COL_CHECK_BOSS,
	COL_CHECK_ITEM,
	COL_CHECK_KID,
	COL_CHECK_MAX
};

//当たり判定チェックボックス
enum COL_CHECK_BOX {
	CHECK_BOX_NONE,		//処理をそもそもしない
	CHECK_BOX_OVER,		//当たり判定内にいるときに知らせる
	CHECK_BOX_HIT		//当たり判定に触れた時に知らせる
};

//オブジェクト自身の当たり判定情報
enum OBJECT_TYPE {
	OBJECT_INIT,	//初期化状態
	OBJECT_PAWN,	//動的オブジェクト
	OBJECT_STATIC,	//静的オブジェクト
	OBJECT_DYNAMIC	//状態によっては通らない
};

//チェックボックスがNONE以外の対象物だけ処理を通る
struct COLLISION_UNREAL_TYPE {
	COL_CHECK_BOX pawn_;
	COL_CHECK_BOX static_;
	COL_CHECK_BOX dynamic_;
};

//当たり判定の形を選ぶ
enum COLLISION_SHAPE_TYPE {
	SHAPE_CUBE,
	SHAPE_SPHERE
};

//当たり判定のデータ
struct COL_DATA
{
	VECTOR	pos_;							//位置情報
	VECTOR	cubeRad_;						//箱の当たり判定
	float	sphereRad_;						//球の当たり判定
	bool	useFlg_;						//使用フラグ、これがtrueなら判定が行われる
	bool	hitFlg_;						//毎週フラグが折られる、判定結果を格納
	int		colNum_;						//これを使って各オブジェクトは自分の情報を確認する
	COL_CHECK_LIST			myList_;		//自分のオブジェクトリストタイプ格納、初期化が-1なので気を付ける
	COL_CHECK_LIST			list_[COL_CHECK_MAX];	//当たり判定が当たった場合に先頭から順に相手のタイプを格納
	COLLISION_UNREAL_TYPE	type_;			//参照相手との当たり判定がとる必要があるのか格納、疑似チェックボックスを用いている
	OBJECT_TYPE				object_;		//オブジェクト自身が持つ情報
	COLLISION_SHAPE_TYPE	shapeCol_;		//当たり判定の形を格納

	COL_DATA()
	{
		pos_ = { 0.0f };
		cubeRad_ = { 0.0f };
		sphereRad_ = 0.0f;
		useFlg_ = false;
		hitFlg_ = false;
		colNum_ = 0;
		myList_ = COL_NONE;
		for (int listNum = 0; listNum < COL_CHECK_MAX; listNum++)
			list_[listNum] = COL_NONE;
		type_.pawn_ = CHECK_BOX_NONE;
		type_.static_ = CHECK_BOX_NONE;
		type_.dynamic_ = CHECK_BOX_NONE;
		object_ = OBJECT_INIT;
		shapeCol_ = SHAPE_CUBE;
	}
};

//2Dの位置座標関係に使えるベクター
struct VECTOR2
{
	float x;
	float y;
};

namespace
{
	// 定義関連
	const VECTOR DEFAULT_SCALE = { 1.0f, 1.0f, 1.0f };	// 通常スケールはオール1なので
}
