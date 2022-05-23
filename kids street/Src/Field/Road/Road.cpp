//Road.cpp
//道クラス

#include "Road.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Library/Collision/Collision.h"

namespace
{
	//マップ関連
	const float MAP_FLOOR_NORM_Y(0.1f);	//法線のY成分がこの値以上であれば床
	const float MAP_CEIL_NORM_Y(-0.9f);	//法線のY成分がこの値以上であれば床
	const float MAP_WALL_NORM_Z(0.5f);	//法線のZ成分がこの値以上であれば壁

	const VECTOR MAP_HNDL_POS = VGet(-20.0f, -1.0f, 0.0f);
	const VECTOR MAP_COL_POS = VGet(-20.0f, -2.0f, 0.0f);
}

//コンストラクタ
CRoad::CRoad()
{
	air_flg_ = false;
	mapInfo_ = { 0 };
}

//デストラクタ
CRoad::~CRoad()
{
}

void CRoad::Init()
{
	

	// 当たり判定用モデルのポリゴン情報をセットアップ
	MV1SetupCollInfo(mapInfo_.col_handle);
	MV1SetupCollInfo(mapInfo_.handle);

}


//読み込み
void CRoad::Load()
{

}



//セット
void CRoad::Set()
{
	// モデル読み込み
	mapInfo_.handle = MV1LoadModel("Data/Map/Field/map.x");

	// 当たり判定モデル読み込み
	mapInfo_.col_handle = MV1LoadModel("Data/Map/Field/map.x");

	//マップの座標
	MV1SetPosition(mapInfo_.handle, MAP_HNDL_POS);
	MV1SetPosition(mapInfo_.col_handle, MAP_COL_POS);
}


//ステップ
void CRoad::Step()
{

}


//更新
void CRoad::Update()
{
	
	// ポリゴン情報を更新する
	/*MV1RefreshReferenceMesh(mapInfo_.col_handle, -1, TRUE);*/
	MV1RefreshCollInfo(mapInfo_.col_handle);

	/*MV1RefreshReferenceMesh(mapInfo_.handle, -1, TRUE);*/
	MV1RefreshCollInfo(mapInfo_.handle);
}


//描画
void CRoad::Draw()
{
	MV1DrawModel(mapInfo_.handle);
}


//削除
void CRoad::Delete()
{
}


//後処理
void CRoad::Fin()
{
	MV1DeleteModel(mapInfo_.handle);
	MV1DeleteModel(mapInfo_.col_handle);
}