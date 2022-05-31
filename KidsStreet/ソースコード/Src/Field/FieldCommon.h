//フィールド関係で共通に使う可能性のあるもの
#pragma once
#include "Dxlib.h"

//マップ情報
struct MapInfo
{
	int handle;						//画像ハンドル
	int col_handle;					//当たり判定用モデルハンドル
	VECTOR pos;						//座標

	MapInfo()
		:handle(0)
		,col_handle(0)
		,pos({0.0f}){}
};

struct InterInfo					//交差点情報構造体
{
	bool	front;					//前に進めるかどうか
	bool	back;					//後
	bool	right;					//右
	bool	left;					//左
};



namespace 
{
	const int		FRONT = 0, BACK = 1, RIGHT = 2, LEFT = 3;		//交差点としての角度を数値として扱う場合に使う
	const int		INTER_MAX_NUM = 17;								//交差点の数
	const int		INTER_BONE_MAX_NUM = 34;						//交差点ボーンの最大値
	const int		INTER_DIR_NUM = 4;								//交差点の曲がり角の分
	const int		INTER_BW = 2;									//交差点番号の配列確認用
	const int		POLE_BONE_START = 2;							//ポールの根元のボーン番号
	const int		POLE_BONE_END = 3;									//ポールの先端のボーン番号
}
