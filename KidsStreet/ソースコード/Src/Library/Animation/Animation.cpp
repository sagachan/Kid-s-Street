#include "Animation.h"

//アニメ再生タイプ
enum 
{
	ANIMSTATE_LOOP,		//繰り返しループ
	ANIMSTATE_END,		//最終フレームで停止

	ANIMSTATE_NUM		//アニメ再生タイプ数
};

//コンストラクタ
CAnim3D::CAnim3D()
{
	//---基底クラスのコンストラクタが自動で先に呼ばれている---//
	frm_int_ = 0;
	end_animFlg_ = false;
	changeFlg_ = false;
	ZeroMemory(&anim_data_, sizeof(anim_data_));	//アニメ再生関連データ
}

//デストラクタ
CAnim3D::~CAnim3D()
{
	DetachAnim();
}

//初期化
void CAnim3D::Init()
{
	CModel::Init();	//基底クラスから先に初期化
	ZeroMemory(&anim_data_, sizeof(anim_data_));	//アニメ再生関連データ
}

//更新処理
void CAnim3D::Update()
{
	//モデルの更新（座標、回転値、拡縮値の設定）
	CModel::Update();

	//アニメーションの更新
	UpdateAnim();
}

//後処理
void CAnim3D::Fin()
{
	//アニメーションをデタッチ
	DetachAnim();

	//基底クラスを後から破棄（先にアニメをデタッチしてから、ハンドルを削除）
	CModel::Fin();
}


//ループアニメリクエスト
void CAnim3D::RequestLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, iAnimSpd, iAnimSrcHndl, NameCheck);
	//ここだけループに変える
	anim_data_.state_ = ANIMSTATE_LOOP;
}

//エンドループアニメリクエスト
void CAnim3D::RequestEndLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, iAnimSpd, iAnimSrcHndl, NameCheck);
	//ここだけエンドループに変える
	anim_data_.state_ = ANIMSTATE_END;
}

//アニメリクエスト
void CAnim3D::Request(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	//アニメ消去
	DetachAnim();

	//アニメ再生＆各種データをセット
	anim_data_.handle_ = MV1AttachAnim(hndl_, iAnimID, iAnimSrcHndl, NameCheck);
	anim_data_.id_ = iAnimID;
	anim_data_.end_frm_ = MV1GetAnimTotalTime(hndl_, iAnimID);
	anim_data_.frm_ = 0.0f;
	
	anim_data_.spd_ = iAnimSpd;
}

//アニメーションデタッチ
void CAnim3D::DetachAnim()
{
	if (anim_data_.handle_ != -1)
	{
		MV1DetachAnim(hndl_, anim_data_.handle_);
		anim_data_.handle_ = -1;
	}
}

//アニメアップデート
void CAnim3D::UpdateAnim()
{
	if (anim_data_.handle_ == -1)return;	//アニメーションが再生されていない

	//アニメーション速度更新
	anim_data_.frm_ += anim_data_.spd_;

	if (anim_data_.frm_ >= anim_data_.end_frm_)
	{
		//最終フレームまで来たら、状態に合わせて動作を変える
		switch (anim_data_.state_)
		{
		//ループは最初に戻るだけ
		case ANIMSTATE_LOOP:
			anim_data_.frm_ = 0.0f;
			break;
		//エンドループは最後で止める
		case ANIMSTATE_END:
			anim_data_.frm_ = anim_data_.end_frm_;
			break;
		}
	}

	//再生時間設定
	MV1SetAttachAnimTime(hndl_, anim_data_.handle_, anim_data_.frm_);
}