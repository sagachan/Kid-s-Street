//Pencil.cpp
//���M�N���X

#include "../../MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../ItemManager.h"
#include "../../Enemy/EnemyBase.h"
#include "Pencil.h"
#include "../../Input/Input.h"

namespace
{
	const float SCALE = 1.0;						//�傫��
	const VECTOR POS = VGet(0.0f,0.0f,0.0f);		//�ʒu
	const VECTOR ROT = VGet(4.71f,0.0f,0.0f);		//��]�l
	const float SPEED = 1.0;						//��ԑ��x
	const VECTOR HIT_RADIUS = VGet(1.0, 1.0, 1.0);	//�����蔻��̍L��
	const float SIMPLE_HIT_RADIUS = 1.0;			//�ȈՓ����蔻��p
	const int DMG = 15;
	const int END_TIME = 150;					//�g�p�J�n����Ă���g�p�I���܂ł̎���
	const int BOSS_THROW_TIME = 1000;			//�{�X�ɂ���ē�����ꂽ���ɂǂ̂��炢�ŏ����邩
}

//�R���X�g���N�^
CPencil::CPencil()
{
	Init();
}

//�f�X�g���N�^
CPencil::~CPencil()
{
	Fin();
}


void CPencil::Init()
{
	appear_flg_ = false;
	isUse_ = false;
	endflg_ = false;
	doOnce_ = false;
	bossFlg_ = false;
	bossThrowFlg_ = false;
	bossDoOnce_ = false;
}


void CPencil::Load()
{
	//���f���n���h���ǂݍ���
	LoadModel("Data/Item/Enpitu.x");
}


void CPencil::Set()
{
	hit_radius_ = HIT_RADIUS;
	add_pos_ = SPEED;
	m_rot_ = ROT;
	dmg_ = DMG;
	radius_ = SIMPLE_HIT_RADIUS;
}


void CPencil::Step()
{
	//�v���C���[�N���X�擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	m_rot_.y = player->GetRot().y;
}

void CPencil::Move()
{
	//�v���C���[�N���X�擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	CItemManager* item_manager = CItemManager::GetInstance();
	CBoss* boss = CEnemyManager::GetInstance()->GetBoss();

	//���̏���������ʂ��������i�[����
	add_num_++;

	//�{�X���A�C�e�����L���b�`���Ă��Ȃ�����
	if (!bossFlg_)
	{
		//��x�����ʂ�Ȃ�����
		if (!doOnce_)
		{
			doOnce_ = true;
			//�v���C���[�̌����x�N�g�����擾
			forward_vec_ = player->GetForwardVec();
		}

		//�ړ��v�Z
		pos_.x += forward_vec_.x * add_pos_;
		pos_.z += forward_vec_.z * add_pos_;

		if (add_num_ > END_TIME)
		{
			endflg_ = true;
			add_num_ = 0;
			doOnce_ = 0;
		}
	}
	
	//�{�X���A�C�e�����L���b�`���Ă���Ƃ��̓_���[�W��0�ɂ���
	//�A�C�e���ƃv���C���[�̓����蔻����L����
	if (bossFlg_)
	{
		dmg_ = 0;

		if (bossThrowFlg_)
		{
			if (!bossDoOnce_)
			{
				//�{�X�̌����x�N�g�����擾
				forward_vec_ = boss->GetForwardVec();
				bossDoOnce_ = true;
			}
			CCollisionManager::GetInstance()->BossItemHit(pos_, m_rad_);

			//�A�C�e����������ꂽ���Ɋi�[���ꂽ�����Ɍ�������
			pos_.x += forward_vec_.x;
			pos_.z += forward_vec_.z;

			//�{�X�ɓ������Ĉ�莞�Ԍ�{�X�t���O��܂�
			if (add_num_ > BOSS_THROW_TIME)
			{
				bossFlg_ = false;
				bossDoOnce_ = false;
				endflg_ = true;
				add_num_ = 0;
				doOnce_ = 0;

			}
		}
		else
		{
			//������ʂ��Ă���Ƃ��̓{�X�N���X�̂ق��ňʒu��񂪍X�V����Ă���
		}
	}
}

void CPencil::Update()
{

}


void CPencil::Draw()
{
	//���f���̉�]
	MV1SetRotationXYZ(m_hndl_, m_rot_);

	//���f���̈ʒu���W�Z�b�g
	MV1SetPosition(m_hndl_, pos_);
	MV1SetScale(m_hndl_, m_scale_);
	//���f���`��
	MV1DrawModel(m_hndl_);
}


void CPencil::Delete()
{

}


void CPencil::Fin()
{

}