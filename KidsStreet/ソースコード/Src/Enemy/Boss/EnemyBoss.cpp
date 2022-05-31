
#include <math.h>
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Player/PlayerManager.h"
#include "../../Library/Animation/Animation.h"
#include "../../AI/BossAI/AIAttackBoss.h"
#include "../../Item/UseItem/ItemManager.h"
#include "../../Item/UseItem/ItemBase.h"
#include "EnemyBoss.h"
#include "../../Library/Sound/Sound.h"
#include "../../Field/FieldManager.h"
#include "../../Collision/CollisionCommon.h"
#include "../../Library/LibraryCommon.h"

namespace
{
	const VECTOR	BOSS_SET			= VGet(-12.0f, -5.0f, 150.0f);
	const VECTOR	BOSS_ROT_POS		= VGet(0.0f, 1.6f, 0.0f);		//��]�l
	const VECTOR	FRAME_HIT_RADIUS	= VGet(5.0, 3.0, 5.0);			//�{�[���̓����蔻��͈̔�
	const int		FRAME_HAND			= 12;							//��̃{�[���̔ԍ�
	const int		THROW_TIME			= 90;							//�����A�j���[�V�������n�܂��Ď肩��A�C�e���������t���[����
	const int		JUMP_FRM_TIME		= 30;							//�{�X�̃W�����v����
	const int		JUMP_CALC_Z			= 60;							
	const int		JUMP_CALC_X			= 60;
	const int		PUNCH_ATTRACT		= 20;
	const float		RADIUS				= 2.0f;							//�����蔻��p�A�����`��ӂ��Ƃ̒���
	const int		BOSS_STAND_END		= 60;							//�{�X�̃X�^���h���[�V�������I���t���[��
	const int		BOSS_TARGET_FRM		= 60;							//�{�X���^�[�Q�b�g���n�߂�t���[��
	const float		BOSS_PUNCH_AREA		= 20.0f;						//�{�X�̃p���`�\�G���A
	const int		BOSS_PUNCH_FIRST	= 120;
	const int		BOSS_PUNCH_SECOND	= 140;
	const int		BOSS_PUNCH_THIRD	= 160;
	const int		BOSS_GET_POLE		= 20;							//�{�X���d�������^�C�~���O
	const int		BOSS_SLASH_START	= 50;							//�{�X���ガ�����n�߂�
	const int		SLASH_SOUND_FRM		= 65;							//�ガ�������𗬂��^�C�~���O
	const int		ATTRACT_FRM_START	= 15;
	const int		ATTRACT_FRM_END		= 90;
	//�A�N�V�������Ƃɂ����鏀������
	const int		TARGET_TIME = 3000;
	//�U���ɂ����鎞��
	const int		ATTACK_TIME = 3000;
}

//�R���X�g���N�^
CBoss::CBoss()
{
	Init();
}

//�f�X�g���N�^
CBoss::~CBoss()
{
	Fin();
}


//������
void CBoss::Init()
{
	doonce_ = false;
	time_ = 0;
	counterFlg_ = false;
	// AI��ԑJ�ڃA���S���Y����ݒ�
	enemy_ai_ = new AIAttackBoss;
	static_cast<AIAttackBoss*>(enemy_ai_)->SetTargetTime(TARGET_TIME, ATTACK_TIME);
}

void CBoss::Set()
{
	//�����蔻��͈͐ݒ�
	rad_ = RADIUS;
	hp_ = BOSS_MAX_HP;

	
	VECTOR framePos[FRAME_MAX];

	//�����蔻�菈���̃Z�b�g
	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++)
	{
		//�t���[���̐������i�[
		framePos[frameNum] = MV1GetFramePosition(hndl_,frameNum);
	}
	
	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++)
	{
		//�����蔻��𐶐�
		CCollisionManager* collision = CCollisionManager::GetInstance();
		colFrmData_[frameNum].pos_ = MV1GetFramePosition(hndl_, frameNum);
		colFrmData_[frameNum].cubeRad_ = FRAME_HIT_RADIUS;
		colFrmData_[frameNum].useFlg_ = true;
		colFrmData_[frameNum].myList_ = COL_CHECK_BOSS;
		colFrmData_[frameNum].type_.pawn_ = CHECK_BOX_HIT;
		colFrmData_[frameNum].type_.static_ = CHECK_BOX_NONE;
		colFrmData_[frameNum].type_.dynamic_ = CHECK_BOX_NONE;
		colFrmData_[frameNum].object_ = OBJECT_PAWN;
		colFrmData_[frameNum].shapeCol_ = SHAPE_CUBE;

		colFrmData_[frameNum].colNum_ = collision->CreateCol(&colFrmData_[frameNum]);
	}
}



//�ǂݍ��݁i���[�h�j
void CBoss::Load()
{
	//���f���ǂݍ���
	hndl_= MV1LoadModel("Data/Enemy/Boss/BOSS.x");

	//enemyBoss_anime
	rot_ = BOSS_ROT_POS;

	MV1SetRotationXYZ(hndl_, rot_);

	//�A�j���[�V��������
	CAnim3D::RequestEndLoop(APPEAR, 0.5f, (int)-1, (bool)-1);

	//SE�̓ǂݍ���
	CSound::LoadSE(CSound::SE_IMPACT);
	CSound::LoadSE(CSound::SE_NICE);
	CSound::LoadSE(CSound::SE_SWING);
}

//���t���[���Ăԏ����i����j
void CBoss::Step()
{
	//�����蔻�菈��
	Hit();

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	CItemManager* item_manager = CItemManager::GetInstance();


	//�����x�N�g������ɍX�V
	forward_.x = sinf(rot_.y);
	forward_.z = cosf(rot_.y);

	//���݃A�j�����I��������
	end_animFlg_ = IsEndAnim();

	//�O��X�e�[�^�X��ۑ�
	int old_ai = ai_state_;
	// ����AI��Ԃ�ݒ�
	ai_state_ = enemy_ai_->GetNextState(this);

	if (ai_state_ != old_ai)
	{
		changeFlg_ = true;
		frm_int_ = 0;
		counterFlg_ = true;
	}

	// AI�X�V
	StepAI();

	//�t���O��ON�Ȃ�{�X����Ƀv���C���[�̕�������
	Target(findFlg_);

	//���̏������n�܂��Ă��牽�t���[���ڂȂ̂����i�[���邽�߂ɒʂ邲�Ƃɉ��Z
	frm_int_++;
}


//�X�V
void CBoss::Update()
{
	//�A�j���[�V�����X�V
	CAnim3D::UpdateAnim();

	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++) {
		//�����蔻��֌W�X�V
		CCollisionManager::GetInstance()->
			SetUpdateColInfo(colFrmData_[frameNum].colNum_, MV1GetFramePosition(hndl_, frameNum), colFrmData_[frameNum].useFlg_);
	}
}

//�`��
void CBoss::Draw()
{
	//���f���̉�]
	MV1SetRotationXYZ(hndl_, rot_);
	//���f���̈ʒu���W�Z�b�g
	MV1SetPosition(hndl_, pos_);
	//���f���`��
	MV1DrawModel(hndl_);
}


//�폜
void CBoss::Delete()
{
	MV1DeleteModel(hndl_);
}



//�㏈��
void CBoss::Fin()
{
	//Delete���Ă΂�Ă��Ȃ��Ȃ�
	if (hndl_!= 0){
		//�폜���Ă�ł���
		Delete();
	}

	enemy_ai_ = nullptr;
}





void CBoss::StepAI()
{
	// ���݂̏�Ԃ���eAI������(�֐��|�C���^���g���ƂȂ��ǂ�)
	switch (ai_state_) {
	case AIBase::BOSS_APPEAR:	// �ҋ@��ԍX�V
		StepAppear();
		break;

	case AIBase::BOSS_STAND:// �x����ԍX�V
		StepStand();
		break;

	case AIBase::BOSS_TARGET:	// �W�I��ԍX�V
		StepTarget();
		break;

	case AIBase::BOSS_NORMAL_ATTACK:	// �ʏ�U����ԍX�V
		StepNormAttack();
		break;

	case AIBase::BOSS_CATCH:			//�L���b�`��ԍX�V
		StepCatch();
		break;

	case AIBase::BOSS_THROW:			//������ԍX�V
		StepThrow();
		break;

	case AIBase::BOSS_RAGE:				//�\���ԍX�V
		StepRage();
		break;

	case AIBase::BOSS_SLASH:				//�ガ������ԍX�V
		StepSlash();
		break;



	case AIBase::BOSS_MOTION_ATTACK:	// �\����ԍX�V
		StepMotion();
		break;

	case AIBase::BOSS_RARE_ATTACK:	// ����U����ԍX�V
		StepRareAttack();
		break;
	}
}

// �o���ԍX�V
void CBoss::StepAppear()
{
	
	counterFlg_ = true;
}

// �ҋ@��ԍX�V
void CBoss::StepStand()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestLoop(STAND, 0.5f, (int)-1, (bool)-1);
		changeFlg_ = false;
		counterFlg_ = false;
		doonce_ = false;
	}
	
	if (frm_int_ > BOSS_STAND_END)
	{
		counterFlg_ = true;
	}
}

// �W�I��ԍX�V
void CBoss::StepTarget()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(TARGET, 1.0f, (int)-1, (bool)-1);
		counterFlg_ = true;
		changeFlg_ = false;
	}

	if (frm_int_ > BOSS_TARGET_FRM)
	{
		findFlg_ = true;
	}
}

// �ʏ�U����ԍX�V
void CBoss::StepNormAttack()		
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(ATTACK, 1.5f, (int)-1, (bool)-1);
		counterFlg_ = false;
		changeFlg_ = false;
	}

	//�N���X�擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	//��x�����ʂ鏈��
	if (frm_int_ == JUMP_FRM_TIME && !doonce_)
	{
		//�W�����v�J�n���̃v���C���[�̈ʒu���W���擾
		VECTOR pos = player->GetPosition();
		VECTOR vec = CMyMath::VecCreate(pos_, pos);
		//�v���C���[�̌��ݒn�܂ł̃t���[�����Ƃ̈ړ��ʂ��v�Z
		add_pos_ = VGet(vec.x / JUMP_CALC_X, vec.y, vec.z / JUMP_CALC_Z);
		//�W�����v���̍��W�i�[
		jump_pos_ = pos_;
		jump_dis_ = CMyMath::GetDistance(pos_, player->GetPosition());
		doonce_ = true;
	}
		
		//�t���[�����Ǘ��A�v���C���[�̂ق��Ɍ���������
	if (frm_int_ > JUMP_FRM_TIME)
	{
		pos_.x += add_pos_.x;
		pos_.z += add_pos_.z;

		if (jump_dis_ > CMyMath::GetDistance(jump_pos_, player->GetPosition()))
		{
			frm_int_ = JUMP_FRM_TIME;
		}
	}
	
}

void CBoss::StepCatch()
{
	//�`����ʂ�A�A�j���[�V�����Đ����K�v�Ȃ�
	findFlg_ = true;
	CItemManager* itemManager = CItemManager::GetInstance();

	//�L���b�`���Ă�Ԃ̓{�X�̒��S�ɃA�C�e��������
	itemManager->SetBossItemPos(pos_);
	frm_int_ = 0;
}

void CBoss::StepThrow()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(THROW, 1.0f, (int)-1, (bool)-1);
		changeFlg_ = false;
		counterFlg_ = false;
	}
	

	CItemManager* itemManager = CItemManager::GetInstance();

	if (frm_int_ == THROW_TIME)
	{
		//�A�C�e���N���X�̃{�X�p�����t���O���I���ɂ���
		itemManager->SetBossItemThrow();
		//�N���X�擾
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		player->AddDamage(DMG_NORMAL);

		CSound::PlaySE(CSound::SE_DMG);
	}
	else if (frm_int_ < THROW_TIME)
	{
		//�{�X�̎�ɃA�C�e��������
		itemManager->SetBossItemPos(GetBossHand());
		
	}

}

void CBoss::StepRage()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(RAGE, 0.5f, (int)-1, (bool)-1);
		counterFlg_ = false;
		changeFlg_ = false;
	}
	
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	if (frm_int_ == BOSS_PUNCH_FIRST || 
		frm_int_ == BOSS_PUNCH_SECOND || 
		frm_int_ == BOSS_PUNCH_THIRD)
	{
		CSound::PlaySE(CSound::SE_IMPACT);

		//�v���C���[���W�����v���ĂȂ��Ȃ�
		if (!player->GetIsInAir())
		{
			player->AddDamage(DMG_STRONG);
			CSound::PlaySE(CSound::SE_DMG);
		}
		else
			CSound::PlaySE(CSound::SE_NICE);
	}
}

void CBoss::StepMotion()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(STAND_ATTACK_MOTION, 1.0f, (int)-1, (bool)-1);
		changeFlg_ = false;
		counterFlg_ = false;
	}
}

void CBoss::StepRareAttack()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(RARE_ATTACK, 1.0f, (int)-1, (bool)-1);
		changeFlg_ = false;
		counterFlg_ = false;
	}

	if (frm_int_ > ATTRACT_FRM_START &&
		frm_int_ < ATTRACT_FRM_END)
	{
		//�N���X�擾
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		//�v���C���[�̈ʒu���W���擾
		VECTOR pos = player->GetPosition();
		VECTOR vec = CMyMath::VecCreate(pos, pos_);
		//�v���C���[�̌��ݒn�܂ł̃t���[�����Ƃ̈ړ��ʂ��v�Z
		add_pos_ = VGet(vec.x / (float)PUNCH_ATTRACT, vec.y, vec.z / (float)PUNCH_ATTRACT);
		add_pos_.x += pos.x;
		add_pos_.z += pos.z;
		add_pos_.y = pos.y;
		player->SetPosition(add_pos_);
	}

	if (frm_int_ == BOSS_PUNCH_FIRST)
	{
		//�N���X�擾
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		//�v���C���[�̈ʒu���W���擾
		VECTOR pos = player->GetPosition();
		float dis = CMyMath::GetDistance(pos_, pos);

		//�{�X�̍U���\�͈͂Ƀv���C���[������Ȃ�
		if (dis < BOSS_PUNCH_AREA){
			player->AddDamage(DMG_NORMAL);
			CSound::PlaySE(CSound::SE_DMG);
		}
		else
			CSound::PlaySE(CSound::SE_NICE);
	}
}

void CBoss::StepSlash()
{
	if (changeFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(SLASH, 1.5f, (int)-1, (bool)-1);
		changeFlg_ = false;
		counterFlg_ = false;
	}

	if (frm_int_ == BOSS_GET_POLE)
	{
		CPole* pole = CFieldManager::GetInstance()->GetPole();
		pole->SetRot(VGet(1.6f, rot_.y - 0.8f, 0.0f));
		pole->SetPosition(MV1GetFramePosition(hndl_, FRAME_HAND));
		findFlg_ = false;
	}
	
	if (frm_int_ > BOSS_GET_POLE)
	{
		CPole* pole = CFieldManager::GetInstance()->GetPole();
		pole->SetPosition(MV1GetFramePosition(hndl_, FRAME_HAND));
	}
	
	if (frm_int_ > BOSS_SLASH_START)
	{
		CPole* pole = CFieldManager::GetInstance()->GetPole();
		VECTOR poleRot = pole->GetRot();
		poleRot.y += 0.03f;
		pole->SetRot(poleRot);
	}

	if (frm_int_ == SLASH_SOUND_FRM)
	{
		CSound::PlaySE(CSound::SE_SWING);
	}

	if (!doonce_)
	{
		//�N���X�擾
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		//�v���C���[�̃��f���n���h�����擾
		int playerHndl = player->GetHandle();

		CPole* pole = CFieldManager::GetInstance()->GetPole();
		VECTOR startHndlPos = MV1GetFramePosition(pole->GetHandle(), POLE_BONE_START);
		VECTOR endHndlPos = MV1GetFramePosition(pole->GetHandle(), POLE_BONE_END);
		MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(playerHndl, -1, startHndlPos, endHndlPos);

		if (result.HitFlag)
		{
			player->AddDamage(DMG_STRONG);
			CSound::PlaySE(CSound::SE_DMG);
			doonce_ = true;
		}
	}
}

//----------�����܂ł��X�e�[�^�X�֌W----------
void CBoss::Target(bool flg)
{
	if (flg == true)
	{
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		//�G���v���C���[����������
		VECTOR vec = CMyMath::VecCreate(pos_, player->GetPosition());
		vec.y = 0.0f;
		rot_.y = atan2f(vec.x, vec.z);
	}
}

void CBoss::Hit()
{
	CCollisionManager* collision = CCollisionManager::GetInstance();

	//�����蔻�茋�ʎ擾
	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++)
	{
		colFrmData_[frameNum] = collision->GetCollisionData(colFrmData_[frameNum].colNum_);
	}

	//�����̓����蔻��ɓ����I�u�W�F�N�g���G��Ă����ꍇ�ɏ����𕡐���J��Ԃ��Ă��܂�Ȃ��悤�ɂ���
	//�������s�������X�g�̃^�C�v�̌�enum�ԍ��̃t���O�𗧂Ă�
	bool checkFlg[COL_CHECK_MAX] = { false };

	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++)
	{
		//�����蔻����s�����ǂ���
		if (colFrmData_[frameNum].hitFlg_)
		{
			//���X�g�̒��g��S�Ċm�F���Ĕ��菈�����s�����̂�������
			for (int checkNum = 0; checkNum < COL_CHECK_MAX; checkNum++)
			{
				//�������Ă����̂��v���C���[�̎�
				if (colFrmData_[frameNum].list_[checkNum] == COL_CHECK_PLAYER && !checkFlg[COL_CHECK_PLAYER])
				{
					//�����������ɋN���鏈��
					CPlayerManager::GetInstance()->GetPlayer()->AddDamage(1);
					checkFlg[COL_CHECK_PLAYER] = true;
				}
			}
		}
	}
}

void CBoss::Damage(int dmg)
{ 
	//�_���[�W����
	hp_ -= dmg;
	
	//�̗͂��Ȃ��Ȃ�����
	if (hp_ < 0 && !doonce_)
	{

		
		CFieldManager::GetInstance()->GetUmbrella()->CutinMovie();
		doonce_ = true;
	}
}

//�����蔻��N���X�ɂ���ă{�X�̒�R���\���Ɣ��f���ꂽ�Ƃ��Ɏg����
void CBoss::SetBossAIFlg(bool flg)
{
	static_cast<AIAttackBoss*>(enemy_ai_)->SetCounterFlg(flg);
}

VECTOR CBoss::GetBossHand()
{
	return MV1GetFramePosition(hndl_, FRAME_HAND);
}