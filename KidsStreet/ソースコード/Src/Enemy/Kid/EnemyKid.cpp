//�q���N���X

#include "EnemyKid.h"
#include <math.h>
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Scene/SceneManager.h"
#include "../../Player/PlayerManager.h"
#include "../../AI/KidAI/AIKid.h"
#include "../../Collision/CollisionManager.h"
#include "../../Collision/CollisionCommon.h"
#include "../../Library/LibraryCommon.h"


namespace
{
	
	const VECTOR ENEMY_ROT_POS = VGet(0.0f, 3.14f, 0.0f);					//�q��1�̉�]�l

	const float		SIMPLE_MOVE = 0.5f;
	const VECTOR	KID_FRONT = VGet(0, 0, SIMPLE_MOVE);					//�O�ɐi�ގԂ̈ړ����x(z)
	const VECTOR	KID_BACK = VGet(0, 0, -SIMPLE_MOVE);					//�������O�ɐi�ގԂ̈ړ����x(z)
	const VECTOR	KID_RIGHT = VGet(SIMPLE_MOVE, 0, 0);					//�E�ɐi�ގԂ̈ړ����x(x�j
	const VECTOR	KID_LEFT = VGet(-SIMPLE_MOVE, 0, 0);					//���ɐi�ގԂ̈ړ����x(x)
	const float		KID_SPD = 0.5f;											//�q���̐i�ޑ���
	const float		KID_WALK_TIME = 10.0f;									//�q����������i�ݐ؂鎞��
	const float		KID_HIGHT = 7.0f;										//�q���̍���
	const float		KID_RADIUS = 8.0f;										//�q���̓����蔻��͈�
	const VECTOR	COL_RADIUS = VGet(8.0f, 12.0f, 8.0f);					//�q���̓����蔻��͈�(VECTOR)
	const int		KID_DMG = 5;
	const int		BIND_FRM = 150;
}

//�R���X�g���N�^
CKid::CKid()
{
	Init();
}

//�f�X�g���N�^
CKid::~CKid()
{
	Fin();
}


//������
void CKid::Init()
{
	moveFlg_ = false;
}

//�Z�b�g
void CKid::Set()
{
	int routeArray[INTER_MAX_NUM]
	{
		START,
		NONE,
		NONE,
		ROTATION,
		START,
		END,
		START,
		NONE,
		NONE,
		ROTATION,
		START,
		END,
		START,
		NONE,
		NONE,
		NONE,
		END
	};

	for (int route = 0; route < INTER_MAX_NUM; route++)
	{
		kidRoute_[route] = routeArray[route];
	}

	int trueNum = 0;

	int posHandle = MV1LoadModel("Data/Enemy/Kid/mapKidBone.x");
	MV1SetPosition(posHandle,VGet(-20.0f, -1.0f, 0.0f));

	for (int arrayNum = 0; arrayNum < INTER_BONE_MAX_NUM; arrayNum++)
	{
		if (arrayNum % 2)
		{
			frmPosArray_[trueNum] = MV1GetFramePosition(posHandle, arrayNum);
			trueNum++;
		}	
	}
	
	pos_ = frmPosArray_[initRouteNum_];		//�q���̈ʒu�ݒ�

	pos_.y = KID_HIGHT;			//�q�������܂�Ȃ��悤�ɂ���

	currentRoute_ = initRouteNum_;

	// AI��ԑJ�ڃA���S���Y����ݒ�
	enemy_ai_ = new AIKid;
	ai_state_ = AIBase::KID_WALK;

	changeFlg_ = true;
	rad_ = KID_RADIUS;
	moveFlg_ = true;

	if (initRouteNum_ == 0 || initRouteNum_ == 6)
	{
		walkType_ = WALK_ROTATION;
	}
	else if (initRouteNum_ == 4 || initRouteNum_ == 10 || initRouteNum_ == 12)
	{
		walkType_ = WALK_START_END;
	}

	selectType_ = START_FROM_MOVE;

	//�����蔻��𐶐�
	CCollisionManager* collision = CCollisionManager::GetInstance();
	colData_.pos_ = pos_;
	colData_.cubeRad_ = COL_RADIUS;
	colData_.useFlg_ = true;
	colData_.myList_ = COL_CHECK_KID;
	colData_.type_.pawn_ = CHECK_BOX_HIT;
	colData_.type_.static_ = CHECK_BOX_NONE;
	colData_.type_.dynamic_ = CHECK_BOX_NONE;
	colData_.object_ = OBJECT_DYNAMIC;
	colData_.shapeCol_ = SHAPE_CUBE;

	colNum_ = collision->CreateCol(&colData_);
}

//�ǂݍ��݁i���[�h�j
void CKid::Load()
{
	//���f���ǂݍ���
	hndl_ = MV1LoadModel("Data/Enemy/Kid/enemy_kid.x");
}

//���t���[���Ăԏ����i����j
void CKid::Step()
{
	Hit();

	//�O��̍��W���i�[
	oldPos_ = pos_;

	// �A�j���[�V�����Ɏg��int�^�̃t���[�������Z
	frm_int_++;

	// ���݃A�j�����I��������
	end_animFlg_ = IsEndAnim();

	// ����AI��Ԃ�ݒ�
	ai_state_ = enemy_ai_->GetNextState(this);

	// AI�X�V
	StepAI();

	// �t���O��ON�Ȃ�{�X����Ƀv���C���[�̕�������
	Target(findFlg_);
	
	if (walkType_ == WALK_START_END)
	{
		StartEnd();
	}
	else
	{
		Rotation();
	}
}


//�X�V
void CKid::Update()
{
	//���ʎԐ��̂݉�]
	if (dir_ == FRONT_MOVE)
	{
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_FRONT);
	}
	if (dir_ == BACK_MOVE)
	{
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_BACK);
	}
	if (dir_ == RIGHT_MOVE)
	{
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_RIGHT);
	}
	if (dir_ == LEFT_MOVE)
	{
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_LEFT);
	}

	if(moveFlg_)
		Move(dir_);

	//���W�m��
	MV1SetPosition(hndl_, pos_);
	//�A�j���[�V�����X�V
	CAnim3D::UpdateAnim();
	
	//�����蔻��֌W�X�V
	CCollisionManager::GetInstance()->SetUpdateColInfo(colNum_, pos_, colData_.useFlg_);
}

void CKid::Hit()
{
	CCollisionManager* collision = CCollisionManager::GetInstance();
	colData_ = collision->GetCollisionData(colNum_);
	//�����̓����蔻��list�ɓ����I�u�W�F�N�g���G��Ă����ꍇ�ɏ����𕡐���J��Ԃ��Ă��܂�Ȃ��悤�ɂ���
	//�������s�������X�g�̃^�C�v�̌�enum�ԍ��̃t���O�𗧂Ă�
	bool checkFlg[COL_CHECK_MAX] = { false };

	if (colData_.hitFlg_)
	{
		for (int checkNum = 0; checkNum < COL_CHECK_MAX; checkNum++)
		{
			//�������Ă����̂��v���C���[�̎�
			if (colData_.list_[checkNum] == COL_CHECK_PLAYER && !checkFlg[COL_CHECK_PLAYER])
			{
				findFlg_ = true;
				changeFlg_ = true;
				colData_.useFlg_ = false;
				checkFlg[COL_CHECK_PLAYER] = true;
			}
		}
	}
}


//�`��
void CKid::Draw()
{
	MV1DrawModel(hndl_);
}


//�폜
void CKid::Delete()
{
	MV1DeleteModel(hndl_);
}



//�㏈��
void CKid::Fin()
{
	//Delete���Ă΂�Ă��Ȃ��Ȃ�
	if (hndl_ != 0)
	{
		//�폜���Ă�ł���
		Delete();
	}
}


//�N���[���֐�
CKid* CKid::Clone()
{
	return nullptr;
}



//�ړ�����
void CKid::Move(int dir)
{
	if (dir_ == FRONT_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, KID_FRONT);
	}
	else if (dir_ == BACK_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, KID_BACK);
	}
	else if (dir_ == RIGHT_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, KID_RIGHT);
	}
	else if (dir_ == LEFT_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, KID_LEFT);
	}
}


void CKid::Rotation()
{
	
	VECTOR originVec;
	int boneNum = currentRoute_;

	if (kidRoute_[boneNum] != ROTATION)
	{
		//���݂̃{�[�����玟�ɐi�ރ{�[���ւ̃x�N�g�����擾����
		originVec = CMyMath::VecCreate(frmPosArray_[boneNum], frmPosArray_[boneNum + 1]);
	}
	else if (kidRoute_[boneNum] == ROTATION)
	{
		//���[�e�[�V�����̃{�[������ŏ��̃{�[���ւ̃x�N�g�����擾����
		originVec = CMyMath::VecCreate(frmPosArray_[boneNum], frmPosArray_[initRouteNum_]);
	}
	
	

	//2�̃{�[���̃x�N�g���̍����傫�����ɐi�݂���
	if (CMyMath::Abs(originVec.x) > CMyMath::Abs(originVec.z))
	{
		if (originVec.x > 0.0f){
			dir_ = RIGHT_MOVE;
		}
		else {
			dir_ = LEFT_MOVE;
		}
	}
	else
	{
		if (originVec.z > 0.0f){
			dir_ = FRONT_MOVE;
		}
		else{
			dir_ = BACK_MOVE;
		}
	}

	if (kidRoute_[boneNum] != ROTATION)
	{
		if (dir_ == RIGHT_MOVE){
			if (pos_.x > frmPosArray_[boneNum + 1].x){
				currentRoute_++;
			}
		}
		if (dir_ == LEFT_MOVE){
			if (pos_.x < frmPosArray_[boneNum + 1].x){
				currentRoute_++;
			}
		}
		if (dir_ == FRONT_MOVE){
			if (pos_.z > frmPosArray_[boneNum + 1].z){
				currentRoute_++;
			}
		}
		if (dir_ == BACK_MOVE){
			if (pos_.z < frmPosArray_[boneNum + 1].z){
				currentRoute_++;
			}
		}
	}

	if (kidRoute_[boneNum] == ROTATION)
	{
		if (dir_ == RIGHT_MOVE) {
			if (pos_.x > frmPosArray_[initRouteNum_].x) {
				currentRoute_ = initRouteNum_;
			}
		}
		if (dir_ == LEFT_MOVE) {
			if (pos_.x < frmPosArray_[initRouteNum_].x) {
				currentRoute_ = initRouteNum_;
			}
		}
		if (dir_ == FRONT_MOVE) {
			if (pos_.z > frmPosArray_[initRouteNum_].z) {
				currentRoute_ = initRouteNum_;
			}
		}
		if (dir_ == BACK_MOVE) {
			if (pos_.z < frmPosArray_[initRouteNum_].z) {
				currentRoute_ = initRouteNum_;
			}
		}
	}
}

void CKid::StartEnd()
{
	VECTOR nextVec = {0};
	int boneNum = currentRoute_;
	
	if (kidRoute_[boneNum] == START){
		selectType_ = START_FROM_MOVE;
	}
	else if (kidRoute_[boneNum] == END){
		selectType_ = END_FROM_MOVE;
	}
	
	if (selectType_ == START_FROM_MOVE){
		//���̃{�[���܂ł̃x�N�g�����擾
		nextVec = CMyMath::VecCreate(frmPosArray_[boneNum], frmPosArray_[boneNum + 1]);
	}
	else if (selectType_ == END_FROM_MOVE){
		//���̃{�[���܂ł̃x�N�g�����擾
		nextVec = CMyMath::VecCreate(frmPosArray_[boneNum], frmPosArray_[boneNum - 1]);
	}

	//2�̃{�[���̃x�N�g���̍����傫�����ɐi�݂���
	if (CMyMath::Abs(nextVec.x) > CMyMath::Abs(nextVec.z))
	{
		if (nextVec.x > 0.0f){
			dir_ = RIGHT_MOVE;
		}
		else{
			dir_ = LEFT_MOVE;
		}
	}
	else
	{
		if (nextVec.z > 0.0f){
			dir_ = FRONT_MOVE;
		}
		else{
			dir_ = BACK_MOVE;
		}
	}

	if (selectType_ == START_FROM_MOVE)
	{
		//�ڕW�̃{�[����ʂ�߂��������݂̃{�[����ڕW�̃{�[���ԍ��ɕύX
		if (dir_ == RIGHT_MOVE) {
			if (pos_.x > frmPosArray_[boneNum + 1].x) {
				currentRoute_++;
			}
		}
		if (dir_ == LEFT_MOVE) {
			if (pos_.x < frmPosArray_[boneNum + 1].x) {
				currentRoute_++;
			}
		}
		if (dir_ == FRONT_MOVE) {
			if (pos_.z > frmPosArray_[boneNum + 1].z) {
				currentRoute_++;
			}
		}
		if (dir_ == BACK_MOVE) {
			if (pos_.z < frmPosArray_[boneNum + 1].z) {
				currentRoute_++;
			}
		}
	}
	else if (selectType_ == END_FROM_MOVE)
	{
		//�ڕW�̃{�[����ʂ�߂��������݂̃{�[����ڕW�̃{�[���ԍ��ɕύX
		if (dir_ == RIGHT_MOVE) {
			if (pos_.x > frmPosArray_[boneNum - 1].x) {
				currentRoute_--;
			}
		}
		if (dir_ == LEFT_MOVE) {
			if (pos_.x < frmPosArray_[boneNum - 1].x) {
				currentRoute_--;
			}
		}
		if (dir_ == FRONT_MOVE) {
			if (pos_.z > frmPosArray_[boneNum - 1].z) {
				currentRoute_--;
			}
		}
		if (dir_ == BACK_MOVE) {
			if (pos_.z < frmPosArray_[boneNum - 1].z) {
				currentRoute_--;
			}
		}
	}
}


void CKid::Target(bool flg)
{
	if (flg)
	{
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		//�v���C���[����������
		VECTOR vec = CMyMath::VecCreate(pos_, player->GetPosition());
		vec.y = 0.0f;
		rot_.y = atan2f(vec.x, vec.z);
	}
}


//---------------�������牺���X�e�[�^�X�֌W����--------------------------
void CKid::StepAI()
{
	// ���݂̏�Ԃ���eAI������(�֐��|�C���^���g���ƂȂ��ǂ�)
	switch (ai_state_) {
	case AIBase::KID_WALK:	//���s��ԍX�V
		StepWalk();
		break;

	case AIBase::KID_BIND:// �ߔ���ԍX�V
		StepBind();
		break;
	}
}

void CKid::StepWalk()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestLoop(WALK, 1.0f, (int)-1, (bool)-1);
		findFlg_ = false;
		changeFlg_ = false;
		frm_int_ = 0;
		moveFlg_ = true;
	}

	if (frm_int_ > BIND_FRM)
	{
		colData_.useFlg_ = true;
	}
}

void CKid::StepBind()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(BIND, 1.0f, (int)-1, (bool)-1);
		changeFlg_ = false;
		moveFlg_ = false;
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		player->AddDamage(KID_DMG);
		colData_.useFlg_ = false;
	}

	
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();
	VECTOR playerOldPos = player->GetOldPosition();
	//�ߔ�����
	player->SetPosition(playerOldPos);
}
