#include "Enemy.h"
#include <math.h>
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Scene/SceneManager.h"
#include "../../Player/PlayerManager.h"
#include "../../Collision/CollisionManager.h"
#include "../../Collision/CollisionCommon.h"
#include "../../Library/LibraryCommon.h"

namespace
{
	const float		SIMPLE_MOVE = 3.0f;
	const VECTOR	CAR_FRONT = VGet(0, 0, SIMPLE_MOVE);									//�O�ɐi�ގԂ̈ړ����x(z)
	const VECTOR	CAR_BACK = VGet(0, 0, -SIMPLE_MOVE);									//�������O�ɐi�ގԂ̈ړ����x(z)
	const VECTOR	CAR_RIGHT = VGet(SIMPLE_MOVE, 0, 0);									//�E�ɐi�ގԂ̈ړ����x(x�j
	const VECTOR	CAR_LEFT = VGet(-SIMPLE_MOVE, 0, 0);									
	//���ɐi�ގԂ̈ړ����x(x)

	const float		RADIUS = 7.0;

	const VECTOR	COL_CUBE1 = VGet(4.0, 7.0, 7.0);
	const VECTOR	COL_CUBE2 = VGet(4.0, 4.0, 9.0);
	const VECTOR	COL_RADIUS = VGet(10.0f, 10.0f, 10.0f);
	const VECTOR	SCALE = VGet(1.0, 1.0, 1.0);
}

//�R���X�g���N�^
CEnemy::CEnemy()
{
	Init();
}

//�f�X�g���N�^
CEnemy::~CEnemy()
{
	Fin();
}


//������
void CEnemy::Init()
{
	moveFlg_ = false;						
	interInfo_ = { 0 };	
	dir_ = MOVE_INIT;
}

void CEnemy::Set()
{
	moveFlg_ = true;
	//�����蔻��𐶐�
	CCollisionManager* collision = CCollisionManager::GetInstance();
	colData_.pos_ = pos_;
	colData_.cubeRad_ = COL_RADIUS;
	colData_.useFlg_ = true;
	colData_.myList_ = COL_CHECK_CAR;
	colData_.type_.pawn_ = CHECK_BOX_HIT;
	colData_.type_.static_ = CHECK_BOX_NONE;
	colData_.type_.dynamic_ = CHECK_BOX_NONE;
	colData_.object_ = OBJECT_DYNAMIC;
	colData_.shapeCol_ = SHAPE_CUBE;

	colNum_ = collision->CreateCol(&colData_);
}

//�Z�b�g
void CEnemy::SetPos(VECTOR pos, CEnemyBase::MOVE_DIR dir)
{
	pos_ = pos;
	dir_ = dir;
	
}

//�ǂݍ��݁i���[�h�j
void CEnemy::Load()
{
	//�ԃ��f���ǂݍ���
	hndl_ = MV1LoadModel("Data/Enemy/Car/enemy_car_model.x");
}

//���t���[���Ăԏ����i����j
void CEnemy::Step()
{
	Hit();

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	oldPos_ = pos_;

	//�����_�̏����t���O��false���܂�����������Ă��Ȃ��Ȃ珈���I���t���O������������
	if (!interInfo_.flg_ && interInfo_.endFlg_)
	{
		interInfo_.endFlg_ = false;
	}

	if (interInfo_.flg_ && !interInfo_.endFlg_){
		//�����_�ړ�����
		InterMove();
	}

	//�ړ����\�ɂ���t���O�������Ă��邩�ǂ���
	if(moveFlg_)
	Move(dir_);
}


//�X�V
void CEnemy::Update()
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

	//���W�m��
	MV1SetPosition(hndl_, pos_);

	//�����蔻��֌W�X�V
	CCollisionManager::GetInstance()->SetUpdateColInfo(colNum_, pos_, colData_.useFlg_);
}

void CEnemy::Hit()
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
				//�Q�[���I�[�o�[�V�[���֕ύX
				CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_OVER);
				checkFlg[COL_CHECK_PLAYER] = true;
			}
		}
	}
}

//�`��
void CEnemy::Draw()
{
	MV1DrawModel(hndl_);
}


//�폜
void CEnemy::Delete()
{
	MV1DeleteModel(hndl_);
}



//�㏈��
void CEnemy::Fin()
{
	//Delete���Ă΂�Ă��Ȃ��Ȃ�
	if (hndl_ != 0){
		//�폜���Ă�ł���
		Delete();
	}
}



//�N���[���֐�
CEnemy* CEnemy::Clone()
{
	return nullptr;
}

//�Ԉړ�����
void CEnemy::Move(int dir)
{
	if (dir_ == FRONT_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, CAR_FRONT);
	}
	else if (dir_ == BACK_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, CAR_BACK);
	}
	else if (dir_ == RIGHT_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, CAR_RIGHT);
	}
	else if (dir_ == LEFT_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, CAR_LEFT);
	}
}

//�����_���ړ����鏈���A�����_�N���X�ɂĒʂ邩�ʂ�Ȃ��������肳���
void CEnemy::InterMove()
{
	//---------�����ł���������-----------
	//		�����_���Ȃ��邽�߂̈ړ�����
	//		�Z�b�g���ꂽ�����_�ϐ��̒��g�����Ƃɂǂ���ɋȂ��邩���`�F�b�N��
	//		���̕����ɋȂ��邽�߂̏������s��
	// 		���炩���ߌ��߂Ă��������C���܂ōs���Ƃ����Ō��߂��p�x�ɒ��p�ɋȂ���
	//-------------------------------------

	CInter* inter = CFieldManager::GetInstance()->GetInter();

	//�����_�Ƃ��ĔF�߂��Ă���͈�
	float interRad = inter->GetInterRad();
	//�����_�̋Ȃ���p���܂��鎞�Ɏg���w��ʒu���
	float nearInter = interRad / 3, farInter = nearInter + interRad;


	//�Ȃ���p�x�ƌ��݂̕������`�F�b�N
	//�O��������Ȃ��鎞
	if (interInfo_.just_ == FRONT) {
		if (interInfo_.check_ == BACK) {
			interInfo_.endFlg_ = true;
		}
		else if (interInfo_.check_ == RIGHT) {
			if (pos_.z < interInfo_.pos_.z + nearInter) {
				dir_ = RIGHT_MOVE;
			}
		}
		else if (interInfo_.check_ == LEFT) {
			if (pos_.z < interInfo_.pos_.z - nearInter) {
				dir_ = LEFT_MOVE;
			}
		}
	}
	//����������Ȃ��鎞
	if (interInfo_.just_ == BACK) {
		if (interInfo_.check_ == FRONT) {
			interInfo_.endFlg_ = true;
		}
		else if (interInfo_.check_ == RIGHT) {
			if (pos_.z > interInfo_.pos_.z + nearInter) {
				dir_ = RIGHT_MOVE;
			}
		}
		else if (interInfo_.check_ == LEFT) {
			if (pos_.z > interInfo_.pos_.z - nearInter) {
				dir_ = LEFT_MOVE;
			}
		}
	}
	//�E��������Ȃ��鎞
	if (interInfo_.just_ == RIGHT) {
		if (interInfo_.check_ == FRONT) {
			if (pos_.x < interInfo_.pos_.x - nearInter) {
				dir_ = FRONT_MOVE;
			}
		}
		else if (interInfo_.check_ == BACK) {
			if (pos_.x < interInfo_.pos_.x + nearInter) {
				dir_ = BACK_MOVE;
			}
			else if (interInfo_.check_ == LEFT) {
				interInfo_.endFlg_ = true;
			}
		}
	}
		//����������Ȃ��鎞
	if (interInfo_.just_ == LEFT) {
		if (interInfo_.check_ == FRONT) {
			if (pos_.x > interInfo_.pos_.x - nearInter) {
				dir_ = FRONT_MOVE;
			}
		}

		else if (interInfo_.check_ == BACK) {
			if (pos_.x > interInfo_.pos_.x + nearInter) {
				dir_ = BACK_MOVE;
			}
		}
		else if (interInfo_.check_ == RIGHT) {
			interInfo_.endFlg_ = true;
		}

	}
}