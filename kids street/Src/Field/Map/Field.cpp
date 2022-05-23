//Field.cpp
//フィールドクラス

#include "Field.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Player/PlayerManager.h"

//フィールド関連
namespace
{
	VECTOR FIELD_POS = VGet(0.0f, 0.0f, 0.0f);	//フィールドの座標
	int    FIELD_D = 36;						//フィールドの奥行
}

//コンストラクタ
CField::CField()
{
	Init();
}

//デストラクタ
CField::~CField()
{
	Fin();
}


void CField::Init()
{
	//回転値
	rot_ = { 0.0f };
	
	for (int type_num = 0; type_num < MAP_TYPE_NUM; type_num++)
	{
		m_handle[type_num] = 0;
	}
}


void CField::Load()
{
	//ロード
	m_handle[school] = MV1LoadModel("Data/Map/Field/school.x");
	m_handle[bill] = MV1LoadModel("Data/Map/Field/bill.x");
	m_handle[house] = MV1LoadModel("Data/Map/Field/house.x");
	m_handle[sky] = MV1LoadModel("Data/Map/Field/sky.x");
}


void CField::Set()
{
	
}


void CField::Step()
{
	
}


void CField::Update()
{
	//プレイヤー位置情報取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//とりあえず入れたモデル全部初期値に
	for (int type_num = 0; type_num < MAP_TYPE_NUM; type_num++)
	{
		MV1SetPosition(m_handle[type_num], VGet(-20.0f, -1.0f, 0.0f));
	}

	//初期座標に変更があるものだけこっちで変更
	MV1SetPosition(m_handle[sky], player->GetPosition());
}


void CField::Draw()
{
	

	for (int type_num = 0; type_num < MAP_TYPE_NUM; type_num++)
	{ 
		MV1DrawModel(m_handle[type_num]);
	}
	
}


void CField::Delete()
{
	for (int type_num = 0; type_num < MAP_TYPE_NUM; type_num++)
	{
		MV1DeleteModel(m_handle[type_num]);
		m_handle[type_num] = 0;
	}
}


void CField::Fin()
{
	if (m_handle[0] != 0)
	{
		//Deleteを呼んでおく
		Delete();
	}
}