#include "AIKid.h"
#include "../../Scene/SceneManager.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Library/MyMath/MyMath.h"

namespace
{
	const int LOW_HP = 35;					//����ȏ㏭�Ȃ��ƃv���C���[�̗̑͂����Ȃ��ƔF�߂���
}

AIKid::AIKid() : AIBase()
{
	Init();
}

AIKid::~AIKid()
{
}

void AIKid::Init()
{

}

int AIKid::GetNextState(CEnemyBase* enemy)
{
	// �ԋp�p�ϐ�next
	int next = 0;

	//���݃A�j���[�V�������Đ�����Ă��Ȃ���
	end_animFlg_ = enemy->GetEndAnimFlg();

	//���݃^�[�Q�b�g������Ă��邩�ǂ������X�V����
	findFlg_ = enemy->GetFindFlg();

	// ���݂̏�Ԃ��擾
	int now_state = enemy->GetEnemyAIState();

	// ���݂̏�Ԃ��Ƃ̏����̊֐�����
	switch (now_state) {
	
	case KID_WALK:			//���s��Ԃ���̑J��
		next = AIKidFromWalk(enemy);
		break;

	case KID_BIND:
		next = AIKidFromBind(enemy);
		break;
	}
	// ���͂ǂ̏�Ԃ���ԋp
	return next;
}



// ���s��ԑJ��
int AIKid::AIKidFromWalk(CEnemyBase* enemy)
{
	//�v���C���[�����b�N�I�������ꍇ
	if (findFlg_)
	{
		//�����𖞂����Ă���ꍇ�ɑ��s��Ԃɂ���
		return KID_BIND;
	}

	// �����Ȃ����
	return KID_WALK;
}

int AIKid::AIKidFromBind(CEnemyBase* enemy)
{
	//�A�j���[�V�����I��
	if (end_animFlg_)
	{
		enemy->ChangeAnim(true);
		return KID_WALK;
	}

	//�����Ȃ����
	return KID_BIND;
}
