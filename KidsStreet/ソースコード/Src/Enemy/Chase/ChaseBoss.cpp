
#include <math.h>
#include "../../Library/MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Library/Animation/Animation.h"
#include "../../AI/ChaseAI/AIChaseBoss.h"
#include "ChaseBoss.h"
#include "../../Library/Error/Error.h"
#include "../../Field/FieldCommon.h"
#include "../../Collision/CollisionManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Library/Sound/Sound.h"
#include "../../Field/FieldManager.h"
#include "../EnemyManager.h"

namespace
{
	const VECTOR	CHASE_ROT_POS = VGet(0.0f, 1.6f, 0.0f);		//��]�l
	const VECTOR	FRAME_HIT_RADIUS = VGet(5.0, 5.0, 5.0);		//�{�[���̓����蔻��͈̔�
	const float		CHASE_SET = -50.0f;
	const int		FRAME_HAND = 13;							//��̃{�[���̔ԍ�
	const float		FIND_AREA = 500.0f;							//�v���C���[�������邱�Ƃ��ł���x���G���A�̔��a
	const float		BOSS_ATTACK_AREA = 10.0f;					//�{�X�̍U���͈�
	const int		BOSS_LOOP_START = 0;
	const int		BOSS_LOOP_END = 16;
	const int		ROUTE_NUM = 4;								//�ʂ郋�[�g�ɑ��݂���{�[���̐�
	const int		BOSS_ROUTE[ROUTE_NUM] = { BOSS_LOOP_START,6,10,BOSS_LOOP_END };
	const int		BOSS_ARRIVAL = 7;							//�{�X���������Ńv���C���[��ǂ�������Ƃ��Ƀv���C���[�ɒǂ����܂ł̎���
	const int		BOSS_SERCH_TIME = 4;						//�{�X���v���C���[���������Ă�����G�ɂ����鎞��
	const float		BOSS_RETURN_SPD = 0.5f;						//�{�X���ǂ�������̂���߂Č��̏��H�ɖ߂�Ƃ��̈ړ����x
	const float		BOSS_SPD = 0.8f;							//�{�X�̈ړ����x
	const float		BOSS_RETURN_AREA = 3.0f;					//�ڕW�̌����_�ɓ����������Ƃ��m�F����Ƃ��Ɏg��
	const VECTOR	BOSS_APPEAR = VGet(0.0f, 0.0f, 0.0f);
	const VECTOR	BOSS_MAP_POS = VGet(-20.0f, -10.0f, 0.0f);
	const int		BOSS_PUNCH_FRM = 33;						//�{�X�̃p���`�̃_���[�W�����t���[��
	const int		BOSS_PUNCH_DMG = 30;						//�{�X�̃p���`�̃_���[�W
	const int		BOSS_FINISHER_FRM = 8;						//�v���C���[���g����������t���[��
}



//�R���X�g���N�^
CChaseBoss::CChaseBoss()
{
	Init();
}

//�f�X�g���N�^
CChaseBoss::~CChaseBoss()
{
	Fin();
}


//������
void CChaseBoss::Init()
{
	
	forward_ = { 0 };
	serchInfo_ = { 0 };
	routeFlg_ = false;
	// AI��ԑJ�ڃA���S���Y����ݒ�
	enemy_ai_ = new AIChaseBoss;
	changeFlg_ = false;
	routeFlg_ = false;
	colMapHndl_ = 0;
	CSound::InitSound();
}

void CChaseBoss::Set()
{
	//�U���͈͐ݒ�
	rad_ = BOSS_ATTACK_AREA;
	move_ = BOSS_SPD;

	//�����ʒu���ݒ�
	CInter* inter = CFieldManager::GetInstance()->GetInter();
	pos_ = MV1GetFramePosition(inter->GetFrmHndl(), 0);
	pos_.y = -1.0f;
	changeFlg_ = true;

	/////////�ړ������Ɏg���}�b�v�̓����蔻������Z�b�g
	MV1SetupCollInfo(hndl_, -1, true);

	//���G�����ɕK�v�ȃ}�b�v�̃��f����ǂݍ��݁A�ʒu����ݒ肷��
	colMapHndl_ = MV1LoadModel("Data/Map/Field/map.x");
	MV1SetPosition(colMapHndl_, BOSS_MAP_POS);

	//�����X�e�[�^�X�ݒ�
	ai_state_ = AIBase::CHASE_APPEAR;
}

//�ǂݍ��݁i���[�h�j
void CChaseBoss::Load()
{
	//���f���ǂݍ���
	hndl_ = MV1LoadModel("Data/Enemy/Boss/enemyBossInit.x");

	/*rot_ = CHASE_ROT_POS;*/

	MV1SetRotationXYZ(hndl_, rot_);

	
	//�A�j���[�V��������
	CAnim3D::RequestEndLoop(APPEAR, 0.5f, (int)-1, (bool)-1);

	CSound::LoadBGM(CSound::BGM_ESCAPE);
	CSound::LoadSE(CSound::SE_DMG);
}

//���t���[���Ăԏ����i����j
void CChaseBoss::Step()
{
	//�O��̍��W���i�[
	oldPos_ = pos_;

	// ���݃A�j�����I��������
	end_animFlg_ = IsEndAnim();

	// ����AI��Ԃ�ݒ�
	ai_state_ = enemy_ai_->GetNextState(this);

	// AI�X�V
	StepAI();
	// �t���O��ON�Ȃ�{�X����Ƀv���C���[�̕�������
	Target(findFlg_);
	
}


//�X�V
void CChaseBoss::Update()
{
	//�A�j���[�V�����X�V
	CAnim3D::UpdateAnim();

	//�{�X�̎��ӂ̎Ԃ��~�߂�
	StopStreet();
	

	MV1RefreshCollInfo(hndl_, -1, true);
}

//�`��
void CChaseBoss::Draw()
{
	//���f���̉�]
	MV1SetRotationXYZ(hndl_, rot_);

	//���f���̈ʒu���W�Z�b�g
	MV1SetPosition(hndl_, pos_);

	//���f���`��
	MV1DrawModel(hndl_);
}


//�폜
void CChaseBoss::Delete()
{

	DeleteModel();
}



//�㏈��
void CChaseBoss::Fin()
{
	//Delete���Ă΂�Ă��Ȃ��Ȃ�
	if (hndl_ != 0)
	{
		//�폜���Ă�ł���
		Delete();
	}

	enemy_ai_ = nullptr;
	CSound::FinSound();
}




//---------------------�������牺���e����֐�------------------------------
// 
// 
// 


void CChaseBoss::StepAI()
{
	// ���݂̏�Ԃ���eAI������
	switch (ai_state_) {
	case AIBase::CHASE_APPEAR:		//�o���ԍX�V
		StepAppear();
		break;

	case AIBase::CHASE_WALK:		//���s��ԍX�V
		StepWalk();
		break;

	case AIBase::CHASE_RUN:			//�W�I��ԍX�V
		StepRun();
		break;

	case AIBase::CHASE_ROLL:		//�ʏ�U����ԍX�V
		StepRoll();
		break;

	case AIBase::CHASE_PUNCH:		//�L���b�`��ԍX�V
		StepPunch();
		break;

	case AIBase::CHASE_FINISHER:	//������ԍX�V
		StepFinisher();
		break;
	}
}

// �o���ԍX�V
void CChaseBoss::StepAppear()
{

}

// ���s��ԍX�V
void CChaseBoss::StepWalk()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestLoop(WALK, 1.0f, (int)-1, (bool)-1);
		findFlg_ = false;
		changeFlg_ = false;
		routeFlg_ = false;
	}

	//���[�g�ʂ�ɓ�������
	if (routeFlg_)
		LoopRoute();
	else
		//����̃��[�g�ɖ߂鏈��
		ReturnRoute();

	
	
	//�i��ł����������������
	VECTOR vec = CMyMath::VecCreate(oldPos_, pos_);
	vec.y = 0.0f;
	rot_.y = atan2f(vec.x, vec.z);
}

// ���s��ԍX�V
void CChaseBoss::StepRun()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestLoop(RUN, 1.0f, (int)-1, (bool)-1);
		frm_int_ = 0;
		changeFlg_ = false;
		CSound::StopBGM(CSound::BGM_ESCAPE);
		CSound::PlayBGM(CSound::BGM_ESCAPE);
		CSound::StopBGM(CSound::BGM_MAIN);
	}
	
	//��̂ǂ���ł��ʂ邽�тɉ��Z����K�v�̂���ϐ��Ȃ̂ł����ŉ��Z�A
	//�Ȃ����̉��̊֐��̓ǂݍ��݂��؂�ւ��Ƃ��ɏ����������
	frm_int_++;

	//���E������֐����ĂсA���E���Ƀv���C���[�����Ȃ��Ȃ�����
	//�t���O��܂�A�����ɕύX����
	if (!serchInfo_.flg_) {
		CheckChase();
	}
	else
	{
		SerchChase();

		//�i��ł����������������
		VECTOR vec = CMyMath::VecCreate(oldPos_, pos_);
		vec.y = 0.0f;
		rot_.y = atan2f(vec.x, vec.z);
	}
}

// ��]��ԍX�V
void CChaseBoss::StepRoll()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(ROLL, 1.0f, (int)-1, (bool)-1);	
	}

	//�P�t���[���ڂŌ����Ă���������ۑ����Ă����A���̕�����
	//�l�����Z��������

}

//�@�U����ԍX�V
void CChaseBoss::StepPunch()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(PUNCH, 1.0f, (int)-1, (bool)-1);
		changeFlg_ = false;
		frm_int_ = 0;

		CSound::StopBGM(CSound::BGM_MAIN);
		CSound::StopBGM(CSound::BGM_PLAY);
		CSound::PlayBGM(CSound::BGM_MAIN);
		CSound::PlayBGM(CSound::BGM_PLAY);
		CSound::StopBGM(CSound::BGM_ESCAPE);
	}

	frm_int_++;

	//�t���[���ԍ������炩���ߌ��߂Ă������l�ɂȂ�����A�_���[�W���v���C���[�ɉ�����
	if (frm_int_ == BOSS_PUNCH_FRM)
	{
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

		player->AddDamage(BOSS_PUNCH_DMG);
		CSound::PlaySE(CSound::SE_DMG);
	}
}

void CChaseBoss::StepFinisher()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(FINISHER, 1.0f, (int)-1, (bool)-1);
		frm_int_ = 0;
		changeFlg_ = false;
		findFlg_ = false;
	}

	frm_int_++;

	//�v���C���[���{�X�̎�ɂƂ炦��ꑱ���鏈��
	//�{�X�̃{�[���̏��̈ʒu�Ƀv���C���[�̈ʒu�����Z�b�g��������
	//����Ȃ��悤�ɂ���
	if (frm_int_ > BOSS_FINISHER_FRM)
	{
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		VECTOR bindPos = MV1GetFramePosition(hndl_, HAND_FRAME_NUM);
		bindPos.y -= player->GetRad();
		player->SetPosition(bindPos);
	}
}



//----------�����܂ł��X�e�[�^�X�֌W----------


void CChaseBoss::Target(bool flg)
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



void CChaseBoss::Hit()
{
	
}

bool CChaseBoss::CheckFirstTarget()
{
	//������ƕ��G�ɂȂ邩��֐��R�����g�Ȃ�����ɏڂ����R�����g�A�E�g����
	
	//---------�v���C���[�̈ʒu�����擾-----------
	CPlayerManager* playerManager = CPlayerManager::GetInstance();
	CPlayer* player = playerManager->GetPlayer();
	VECTOR playerPos = player->GetPosition();
	
	//---------�v���C���[�܂ł̋��������ꂷ���Ă���Ȃ炻�������������Ȃ��悤�ɂ���
	//�܂��͋������擾
	float dis = CMyMath::GetDistance(playerPos, pos_);

	//��������G���A�O�Ȃ珈�����I��
	if (dis > FIND_AREA)
	{
		return false;
	}
	
	//---------�}�b�v�̓����蔻��Ɏg�����߃n���h�����擾------
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	
	
	//�����̓����蔻����g���āA�v���C���[�ƃ{�X�̊Ԃɏ�Q�����Ȃ����ǂ����𔻒�
	//���肵�đ��v�Ȃ�{�X���v���C���[��ǂ������鏈���Ɏg���Ă���t���O���I���ɂ���
	MV1_COLL_RESULT_POLY colInfo = MV1CollCheck_Line(colMapHndl_, -1, pos_, playerPos);

	//��Q�����Ȃ��Ȃ�
	if (!colInfo.HitFlag)
	{
		return true;
	}
	else
		return false;
}

//�v���C���[��ǂ������鏈��
void CChaseBoss::CheckChase()
{
	//---------�����ł���������----------
	//�v���C���[���{�X���ǂ�������A�v���C���[���������������ǂ����̔���
	//-----------------------------------------

	//---------�v���C���[�̈ʒu�����擾-----------
	CPlayerManager* playerManager = CPlayerManager::GetInstance();
	CPlayer* player = playerManager->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	//---------�}�b�v�̓����蔻��Ɏg�����߃n���h�����擾------
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	CInter* inter = CFieldManager::GetInstance()->GetInter();
	

	//���݌������Ă��Ȃ����ǂ����̃`�F�b�N
	
	//�����̓����蔻����g���āA�v���C���[�ƃ{�X�̊Ԃɏ�Q�����Ȃ����ǂ����𔻒�
	//���肵�đ��v�Ȃ�{�X���v���C���[��ǂ������鏈���Ɏg���Ă���t���O���I���ɂ���
	MV1_COLL_RESULT_POLY colInfo;
	colInfo = MV1CollCheck_Line(colMapHndl_, -1, pos_, playerPos);


	//��Q��������Ȃ�v���C���[��ǂ�������̂͂�߂�
	if (colInfo.HitFlag)
	{
		//�{�X���v���C���[��T���悤�ɂ���
		serchInfo_.flg_ = true;

		//-----------���G�ɕK�v�ȏ��������œ��͂��Ă���-------

		//�ꎞ�I�ɒl��ێ����Ă����ϐ�
		float interDis = 0.0f;
		VECTOR targetPos = { 0.0f };

		//��ԋ߂������_�ʒu���W��������
		for (int interNum = 0; interNum < INTER_BONE_MAX_NUM; interNum++)
		{
			if (interNum % INTER_BW)
			{
				//�Q�Ƃ�������_�̈ʒu���W����ɓ����
				VECTOR interPos = MV1GetFramePosition(inter->GetFrmHndl(), interNum);
				float calcDis = 0.0f;

				//���ݒn����Q�Ƃ��Ă�������_�܂ł̋������i�[
				calcDis = CMyMath::GetDistance(pos_, interPos);

				//��Βl�Ŕ�ׂĂ��l���������ق��������_�ɋ߂��A
				//��񂪂܂������ĂȂ��ꍇ�͐�ɏ����i�[����K�v������̂Œʂ�
				if (interDis == 0.0f ||
					CMyMath::Abs(interDis) > CMyMath::Abs(calcDis)) {

					//�����܂Œʂ����Ƃ������Ƃ͈�ԋ߂������_���W�ł��邱�Ƃ͊ԈႢ�Ȃ����ߍX�V
					targetPos = interPos;
					interDis = calcDis;
				}
			}
		}
		
		//��ԋ߂������_�ʒu���n��
		serchInfo_.useInterPos_ = targetPos;

		//�t���[���P�ʂ̎��Ԍv�Z�Ɏg�p�����ϐ��̏�����
		frm_int_ = 0;
		
		
		return;
	}

	
	

	//�{�X���v���C���[��ǂ������锻��
	VECTOR move = { 0 };

	//�ړ��ʌv�Z
	move = CMyMath::VecCreate(pos_, playerPos);

	//6�b��Ƀv���C���[�̂��Ƃɂ��ǂ蒅���v�Z���Ɏg��
	int calcNum = BOSS_ARRIVAL * FRAME_RATE;

	//���X�ɋ߂Â�
	calcNum -= frm_int_;

	//�x�N�g���̊���Z���s��
	move.x /= calcNum;
	move.z /= calcNum;

	//�x�N�g�������ݍ��W�ɉ��Z
	pos_ = CMyMath::VecAdd(pos_, move);

	
}

//�v���C���[���������Ă����莞�ԍ��G�����鏈��
void CChaseBoss::SerchChase()
{
	//---------�����ł���������----------
	//�������K�莞�Ԉȏ�ʂ����̂Ɍ������Ȃ������������Ԃɖ߂�A
	// ���̌��߂�ꂽ���[�g�ɖ߂�悤�ɂ���
	//�v���C���[�������邽�ߍ��G���s��
	//-----------------------------------------

	//---------�v���C���[�̈ʒu�����擾-----------
	CPlayerManager* playerManager = CPlayerManager::GetInstance();
	CPlayer* player = playerManager->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	//---------�}�b�v�̓����蔻��Ɏg�����߃n���h�����擾------
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	CInter* inter = CFieldManager::GetInstance()->GetInter();
	
	//���݌������Ă��Ȃ����ǂ����̃`�F�b�N

	//�����̓����蔻����g���āA�v���C���[�ƃ{�X�̊Ԃɏ�Q�����Ȃ����ǂ����𔻒�
	//���肵�đ��v�Ȃ�{�X���v���C���[��ǂ������鏈���Ɏg���Ă���t���O���I���ɂ���
	MV1_COLL_RESULT_POLY colInfo = MV1CollCheck_Line(colMapHndl_, -1, pos_, playerPos);

	//��Q�����Ȃ��Ȃ猩���Ă���̂ŁA�ǐՊJ�n
	if (!colInfo.HitFlag)
	{
		//�{�X���v���C���[��T���悤�ɂ���
		serchInfo_.flg_ = false;
		frm_int_ = 0;
		//�����ŏ������I������
		return;
	}

	//-----------------�v���C���[���G����------------------
	//���݃v���C���[�����F�ł���\�����ł����������_�{�[����Ɍ�����
	VECTOR move = { 0 };

	//�ړ��ʌv�Z
	move = CMyMath::VecCreate(pos_, serchInfo_.useInterPos_);
	move.y = BOSS_APPEAR.y;

	//�K�莞�Ԍ�ɖړI�n�ɂ��ǂ蒅���v�Z���Ɏg��
	int calcNum = BOSS_SERCH_TIME * FRAME_RATE;

	//�x�N�g���̊���Z���s��
	move.x /= calcNum;
	move.z /= calcNum;

	//�x�N�g�������ݍ��W�ɉ��Z
	pos_ = CMyMath::VecAdd(pos_, move);

	//�����{�X���v���C���[��{������K�莞�Ԃ��߂��Ă��v���C���[���������Ă��Ȃ��ꍇ
	//�v���C���[��������̂�������߂āA���̃��[�g�ɖ߂�

	//�Ō�Ɉ�x�����T��
	if (frm_int_ > BOSS_SERCH_TIME * FRAME_RATE)
	{
		//�v���C���[�������鏈��
		if (CheckFirstTarget())
		{
			//�����Ă���t���O��true
			findFlg_ = true;
			//�X�e�[�^�X�ύX�t���O��true
			changeFlg_ = true;
			//�K�胋�[�g��ʂĂ��邩�t���O��false
			routeFlg_ = false;

			return;
		}

		//������ʂ�Ȃ�����ɖ߂�
		findFlg_ = false;

		CSound::StopBGM(CSound::BGM_MAIN);
		CSound::StopBGM(CSound::BGM_PLAY);
		CSound::PlayBGM(CSound::BGM_MAIN);
		CSound::PlayBGM(CSound::BGM_PLAY);
		CSound::StopBGM(CSound::BGM_ESCAPE);
		changeFlg_ = true;
	}
}

//�{�X�����܂������H��p�j���鏈��
void CChaseBoss::LoopRoute()
{
	//---------�����ł���������----------
	// �{�X�����[�g��ɂ��邱�Ƃ�O��Ƃ���
	// �{�X�����̃{�[���Ɍ������Đi�ݑ����鏈��
	//-----------------------------------------

	int boneStart = BOSS_LOOP_START;
	int boneEnd = BOSS_LOOP_END;

	CInter* inter = CFieldManager::GetInstance()->GetInter();
	int frmHndl = inter->GetFrmHndl();

	//�ړ��ʂ̉��Z
	pos_.z += move_;

	//�ړ��ʂ�z���W�ɂ����ā{�Ȃ�END�Q�ƁA-�Ȃ�START�Q��
	if (move_ > 0){
		if (pos_.z > MV1GetFramePosition(frmHndl, BOSS_LOOP_END).z){
			move_ *= -1.0f;
		}
	}
	else if (move_ < 0){
		if (pos_.z < MV1GetFramePosition(frmHndl, BOSS_LOOP_START).z){
			move_ *= -1.0f;
		}
	}

	//�v���C���[�������鏈��
	if (CheckFirstTarget())
	{
		//�����Ă���t���O��true
		findFlg_ = true;
		//�X�e�[�^�X�ύX�t���O��true
		changeFlg_ = true;
		//�K�胋�[�g��ʂĂ��邩�t���O��false
		routeFlg_ = false;
	}
}

//���̓��ɖ߂鏈��
void CChaseBoss::ReturnRoute()
{
	//---------�����ł���������----------
	// �{�X����ԋ߂��{�[���ԍ��̈ʒu���W�Ɍ����Ėڎw��
	// �ڎw���Ă����{�[�����W�ɓ��������Ƃ�
	//-----------------------------------------

	//---------�}�b�v�̓����蔻��Ɏg�����߃n���h�����擾------
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	CInter* inter = CFieldManager::GetInstance()->GetInter();
	

	//�����_�{�[�����
	int frmHndl = inter->GetFrmHndl();

	//----�ǂ������݈ʒu�����ԋ߂������_�����擾���A���̕����ɐi�ޏ���----
	
	//�w��̏����ɍ�������ԋ߂������_��T������
	//�ꎞ�I�ɒl��ێ����Ă����ϐ�
	float interDis = 0.0f;
	VECTOR targetPos = { 0.0f };

	//��ԋ߂������_�ʒu���W��������
	for (int interNum = 0; interNum < ROUTE_NUM; interNum++)
	{
		//�Q�Ƃ�������_�̈ʒu���W����ɓ����
		VECTOR interPos = MV1GetFramePosition(inter->GetFrmHndl(), BOSS_ROUTE[interNum]);
		float calcDis = 0.0f;

		//���ݒn����Q�Ƃ��Ă�������_�܂ł̋������i�[
		calcDis = CMyMath::GetDistance(pos_, interPos);

		//��Βl�Ŕ�ׂĂ��l���������ق��������_�ɋ߂��A
		//��񂪂܂������ĂȂ��ꍇ�͐�ɏ����i�[����K�v������̂Œʂ�
		if (interDis == 0.0f ||
			CMyMath::Abs(interDis) > CMyMath::Abs(calcDis)) {

			//�����܂Œʂ����Ƃ������Ƃ͈�ԋ߂������_���W�ł��邱�Ƃ͊ԈႢ�Ȃ����ߍX�V
			targetPos = interPos;
			interDis = calcDis;
		}
	}

	//-----�����_�͌������̂ŁA�����ɐi�ނ��߂̏���-------
	//�܂��͏�Q������

	VECTOR calcPos = { 0 };
	calcPos.x = pos_.x - targetPos.x;
	calcPos.z = pos_.z - targetPos.z;
	//0��菬�����Ɣ�ׂ��Ȃ��̂�
	calcPos.x = CMyMath::Abs(calcPos.x);
	calcPos.z = CMyMath::Abs(calcPos.z);

	//�������Ă���Ȃ�t���O�𗧂ĂĂ����ŏ������I��
	if (calcPos.x < BOSS_RETURN_AREA && calcPos.z < BOSS_RETURN_AREA)
	{
		routeFlg_ = true;
		return;
	}

	//���̏����ɒʂ�ꍇ�͍��G���[�h�ɓ����Č�����Ȃ��������Ȃ̂�
	//�����_�͉��ɕ���ł��閔�͂��łɊY���̌����_���̂ǂ��炩
	if (calcPos.x > BOSS_RETURN_AREA)
	{
		if (pos_.x < targetPos.x)
		{
			pos_.x += BOSS_RETURN_SPD;
		}
		else
			pos_.x -= BOSS_RETURN_SPD;
	}
	if (calcPos.z > BOSS_RETURN_AREA)
	{
		if (pos_.z < targetPos.z)
		{
			pos_.z += BOSS_RETURN_SPD;
		}
		else
			pos_.z -= BOSS_RETURN_SPD;
	}
}

//�{�X�̎��ӂ̎Ԃ��~�߂�
void CChaseBoss::StopStreet()
{
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++)
	{
		CEnemy* enemy = CEnemyManager::GetInstance()->GetEnemy(carNum);

		//�{�X���猈�߂�ꂽ���͈�
		if (CMyMath::RadiusCheck(pos_, SAFETY_CAR, enemy->GetPosition()))
		{
			enemy->SetMoveFlg(false);
		}
		else
			enemy->SetMoveFlg(true);
	}

	//�Ԃ��~�܂��Ă���Ԃƌ��˂��Ȃ��悤�ɂ��鏈��
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++)
	{
		CEnemy* enemy = CEnemyManager::GetInstance()->GetEnemy(carNum);

		if (!enemy->GetMoveFlg())
		{
			for (int checkNum = 0; checkNum < APPEAR_CAR_NUM; checkNum++)
			{
				CEnemy* checkEnemy = CEnemyManager::GetInstance()->GetEnemy(checkNum);

				if (checkNum != carNum)
				{
					//�{�X���猈�߂�ꂽ���͈�
					if (CMyMath::RadiusCheck(checkEnemy->GetPosition(), SAFETY_CAR, enemy->GetPosition()))
					{
						checkEnemy->SetMoveFlg(false);
					}
				}
			}
		}	
	}

	
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++)
	{
		CEnemy* enemy = CEnemyManager::GetInstance()->GetEnemy(carNum);

		if (!enemy->GetMoveFlg())
		{
			for (int checkNum = 0; checkNum < APPEAR_CAR_NUM; checkNum++)
			{
				CEnemy* checkEnemy = CEnemyManager::GetInstance()->GetEnemy(checkNum);

				if (checkNum != carNum)
				{
					//�{�X���猈�߂�ꂽ���͈�
					if (CMyMath::RadiusCheck(checkEnemy->GetPosition(), SAFETY_CAR, enemy->GetPosition()))
					{
						checkEnemy->SetMoveFlg(false);
					}
				}
			}
		}
	}
}