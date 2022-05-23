
#include <math.h>
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Player/PlayerManager.h"
#include "../../Library/Animation/Animation.h"
#include "../../AI/BossAI/AIAttackBoss.h"
#include "../../Item/UseItem/ItemManager.h"
#include "../../Item/UseItem/ItemBase.h"
#include "EnemyBoss.h"

namespace
{
	const VECTOR BOSS_SET = VGet(-12.0f, -5.0f, 150.0f);
	const VECTOR BOSS_ROT_POS = VGet(0.0f, 1.6f, 0.0f);			//��]�l
	const int ORIGIN = 0;											//�������l
	const float BACK_MOVE = -1.0f;										//�߂�
	const VECTOR FRAME_HIT_RADIUS = VGet(5.0, 5.0, 5.0);			//�{�[���̓����蔻��͈̔�
	const int FRAME_OUT = 0;										//��O�{�[���w��
	const int FRAME_HAND = 13;										//��̃{�[���̔ԍ�
	const int THROW_TIME = 90;								//�����A�j���[�V�������n�܂��Ď肩��A�C�e���������t���[����
	const int JUMP_FRM_TIME = 30;
	const int JUMP_CALC_Z = 90;								
	const int JUMP_CALC_X = 60;
	const VECTOR COL_CUBE1 = VGet(1.0, 1.0, 1.0);
	const VECTOR COL_CUBE2 = VGet(1.0, 1.0, 1.0);
	const float RADIUS = 2.0f;										//�����蔻��p�A�����`��ӂ��Ƃ̒���
	const int	MAXHP = 100;										//�̗͂̍ő�l

	//�A�N�V�������Ƃɂ����鏀������
	const int TARGET_TIME = 3000;
	//�U���ɂ����鎞��
	const int ATTACK_TIME = 3000;
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
	pos_ = { 0 };
	is_roop_ = false;
	old_distance_ = 0;
	distance_ = 0;
	end_animFlg_ = 0;
	findFlg_ = false;
	time_ = 0;
	radius_ = 0.0f;
	forward_ = { 0 };
	counterFlg_ = false;
	// AI��ԑJ�ڃA���S���Y����ݒ�
	enemy_ai_ = new AIAttackBoss;
	static_cast<AIAttackBoss*>(enemy_ai_)->SetTargetTime(TARGET_TIME, ATTACK_TIME);

}

void CBoss::Set()
{
	//�����蔻��͈͐ݒ�
	radius_ = RADIUS;
	hp_ = MAXHP;

	
	VECTOR framePos[FRAME_MAX];

	//�����蔻�菈���̃Z�b�g
	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++)
	{
		//�t���[���̐������i�[
		framePos[frameNum] = MV1GetFramePosition(hndl_,frameNum);
	}
	
	CCollisionManager::GetInstance()->SetBossCollision(framePos, RADIUS);
}



//�ǂݍ��݁i���[�h�j
void CBoss::Load()
{
	//���f���ǂݍ���
	hndl_= MV1LoadModel("Data/Enemy/Boss/enemyBoss_anime.x");

	rot_ = BOSS_ROT_POS;

	MV1SetRotationXYZ(hndl_, rot_);

	

	//�A�j���[�V��������
	CAnim3D::RequestEndLoop(APPEAR, 0.5f, (int)-1, (bool)-1);
}

//���t���[���Ăԏ����i����j
void CBoss::Step()
{
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	CItemManager* item_manager = CItemManager::GetInstance();

	/*if (doTwice_ == false)
	{
		item_manager->SetAppear(true);
		doTwice_ = true;
	}*/

	//�����x�N�g������ɍX�V
	forward_.x = sinf(rot_.y);
	forward_.z = cosf(rot_.y);

	//���݃A�j�����I��������
	end_animFlg_ = IsEndAnim();

	// ����AI��Ԃ�ݒ�
	ai_state_ = enemy_ai_->GetNextState(this);

	// AI�X�V
	StepAI();

	//�t���O��ON�Ȃ�{�X����Ƀv���C���[�̕�������
	Target(findFlg_);

	//�_���[�W����
	Damage(dmg_);
}


//�X�V
void CBoss::Update()
{
	//�A�j���[�V�����X�V
	CAnim3D::UpdateAnim();
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
	if (hndl_!= 0)
	{
		//�폜���Ă�ł���
		Delete();
	}

	enemy_ai_ = nullptr;
}




//---------------------�������牺���e����֐�------------------------------
// 
// 
// 
//�ŏ��ɓǂݍ��񂾎��̎��Ԃ��i�[
void CBoss::GetCount()
{
	//���Ƀt���O��false�ɂ����܂ł͒ʂ�Ȃ�
	if (get_timeflg_ == false)
	{
		//�ǂݍ��݊J�n���Ԃ�ϐ��Ɋi�[
		time_ = (float)GetNowCount();
		get_timeflg_ = true;
	}
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

	//case AIBase::BOSS_MOTION_ATTACK:	// �\����ԍX�V
	//	StepMotion();
	//	break;

	//case AIBase::BOSS_RARE_ATTACK:	// ����U����ԍX�V
	//	StepRareAttack();
	//	break;
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
	if (end_animFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(STAND, 0.5f, (int)-1, (bool)-1);
		//��Ԃ��Ƃ̕ϐ�������
		norm_attack_flg_ = false;
		doOnce_ = false;
		frame_num_ = 0;
		counterFlg_ = true;
	}
}

// �W�I��ԍX�V
void CBoss::StepTarget()
{
	if (end_animFlg_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(TARGET, 0.5f, (int)-1, (bool)-1);
		counterFlg_ = true;
		findFlg_ = true;
		get_timeflg_ = false;
		counterFlg_ = true;
	}
}

// �ʏ�U����ԍX�V
void CBoss::StepNormAttack()		
{
	//�N���X�擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	counterFlg_ = false;

	if (end_animFlg_)
	{
		
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(ATTACK, 1.5f, (int)-1, (bool)-1);
		counterFlg_ = false;
		get_timeflg_ = false;
		norm_attack_flg_ = true;
	}

	//�A�j���[�V�����Đ����J�n����Ă���Ȃ�
	if (norm_attack_flg_)
	{ 
		

		//��x�����ʂ鏈��
		if (frame_num_ == JUMP_FRM_TIME && !doOnce_)
		{
			//�W�����v�J�n���̃v���C���[�̈ʒu���W���擾
			VECTOR pos = player->GetPosition();
			VECTOR vec = CMyMath::VecCreate(pos_, pos);
			//�v���C���[�̌��ݒn�܂ł̃t���[�����Ƃ̈ړ��ʂ��v�Z
			add_pos_ = VGet(vec.x / JUMP_CALC_X, vec.y, vec.z / JUMP_CALC_Z);
			doOnce_ = true;
			//�W�����v���̍��W�i�[
			jump_pos_ = pos_;
			jump_dis_ = CMyMath::GetDistance(pos_, player->GetPosition());
		}
		
		//�t���[�����Ǘ��A�v���C���[�̂ق��Ɍ���������
		if (frame_num_ > JUMP_FRM_TIME)
		{
			pos_.x += add_pos_.x;
			pos_.z += add_pos_.z;

			if (jump_dis_ > CMyMath::GetDistance(jump_pos_, player->GetPosition()))
			{
				frame_num_ = JUMP_FRM_TIME;
			}
		}
		//���݂̃t���[����
		frame_num_++;
	}
}

void CBoss::StepCatch()
{
	//�`����ʂ�A�A�j���[�V�����Đ����K�v�Ȃ�
	findFlg_ = true;
	CItemManager* itemManager = CItemManager::GetInstance();

	//�L���b�`���Ă�Ԃ̓{�X�̒��S�ɃA�C�e��������
	itemManager->SetBossItemPos(pos_);
}

void CBoss::StepThrow()
{
	if (!doOnce_)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(THROW, 1.0f, (int)-1, (bool)-1);
		doOnce_ = true;
	}
	//���̏������n�܂��Ă��牽�t���[���ڂȂ̂����i�[���邽�߂ɒʂ邲�Ƃɉ��Z
	frame_num_++;

	CItemManager* itemManager = CItemManager::GetInstance();

	if (frame_num_ == THROW_TIME)
	{
		//�A�C�e���N���X�̃{�X�p�����t���O���I���ɂ���
		itemManager->SetBossItemThrow();
	}
	else if (frame_num_ < THROW_TIME)
	{
		//�{�X�̎�ɃA�C�e��������
		itemManager->SetBossItemPos(MV1GetFramePosition(hndl_, FRAME_HAND));
	}

}

void CBoss::StepRage()
{
	if (end_animFlg_ == true)
	{
		//�A�j���[�V��������
		CAnim3D::RequestEndLoop(RAGE, 0.5f, (int)-1, (bool)-1);

	}
	frame_num_++;

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//�v���C���[���W�����v���ĂȂ��Ȃ�
	if (!player->GetIsInAir())
	{
		doOnce_ = false;
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
	//�����蔻�菈���Ǘ��N���X�ɓn�������̒��g���X�V
	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++)
	{
		//�t���[���̐������i�[
		framePos[frameNum] = MV1GetFramePosition(hndl_, frameNum);
	}

	CCollisionManager::GetInstance()->SetBossCollision(framePos, RADIUS);
}

void CBoss::Damage(int dmg)
{ 
	//�����蔻��t���O���I���ɂȂ��Ă��Ȃ��Ȃ牽�����Ȃ�
	if (colFlg_ == false)
	{
		return;
	}
	colFlg_ = false;

	//�_���[�W����
	hp_ -= dmg;
	
	//�̗͂��Ȃ��Ȃ�����
	if (hp_ < 0)
	{
		//�Q�[���N���A�V�[���֕ύX
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_CLEAR);
	}
}

void CBoss::DrawHitCube(VECTOR pos)
{
	cube_pos1_ = pos, cube_pos2_ = pos;

	cube_pos1_.x = cube_pos1_.x + COL_CUBE1.x;
	cube_pos1_.y = cube_pos1_.y + COL_CUBE1.y;
	cube_pos1_.z = cube_pos1_.z + COL_CUBE1.z;

	cube_pos2_.x = cube_pos2_.x - COL_CUBE2.x;
	cube_pos2_.y = cube_pos2_.y - COL_CUBE2.y;
	cube_pos2_.z = cube_pos2_.z - COL_CUBE2.z;
}

//�����蔻��N���X�ɂ���ă{�X�̒�R���\���Ɣ��f���ꂽ�Ƃ��Ɏg����
void CBoss::SetBossAIFlg(bool flg)
{
	static_cast<AIAttackBoss*>(enemy_ai_)->SetCounterFlg(flg);
}

