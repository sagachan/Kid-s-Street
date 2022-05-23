#include "AIChaseBoss.h"
#include "../../Scene/SceneManager.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Library/MyMath/MyMath.h"

namespace
{
	const int LOW_HP = 35;					//����ȏ㏭�Ȃ��ƃv���C���[�̗̑͂����Ȃ��ƔF�߂���
}

AIChaseBoss::AIChaseBoss() : AIBase()
{
	Init();
}

AIChaseBoss::~AIChaseBoss()
{
}

void AIChaseBoss::Init()
{
	doonce_ = false;
	
}

int AIChaseBoss::GetNextState(CEnemyBase* enemy)
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
	case CHASE_APPEAR:			// �o���Ԃ���̑J��
		next = AIChaseFromAppear(enemy);
		break;

	case CHASE_WALK:			//���s��Ԃ���̑J��
		next = AIChaseFromWalk(enemy);
		break;

	case CHASE_RUN:
		next = AIChaseFromRun(enemy);
		break;

	case CHASE_ROLL:
		next = AIChaseFromRoll(enemy);
		break;

	case CHASE_PUNCH:
		next = AIChaseFromPunch(enemy);
		break;

	case CHASE_FINISHER:
		next = AIChaseFromFinisher(enemy);
		break;
	}

	// ���͂ǂ̏�Ԃ���ԋp
	return next;
}

// �o���ԑJ��
int AIChaseBoss::AIChaseFromAppear(CEnemyBase* enemy)
{

	//�A�j���[�V���������ݍĐ�����Ă��Ȃ����ɕ��s��ԂɂȂ鏈��
	if (end_animFlg_) {
		return CHASE_WALK;
	}

	// �����Ȃ���Γo��̂܂�
	return CHASE_APPEAR;
}

// ���s��ԑJ��
int AIChaseBoss::AIChaseFromWalk(CEnemyBase* enemy)
{
	//�e�֐��Ŏg���ϐ��̏�����
	doonce_ = false;

	//�v���C���[�����b�N�I�������ꍇ
	if(findFlg_)
	{
		CEnemyManager* enemyManager = CEnemyManager::GetInstance();
		CChaseBoss* chaseBoss = enemyManager->GetChaseBoss();

		//��ԑJ�ڂ�����̂�
		chaseBoss->SetChangeFlg();
		//�����𖞂����Ă���ꍇ�ɑ��s��Ԃɂ���
		return CHASE_RUN;
	}

	// �����Ȃ����
	return CHASE_WALK;
}

// ���s��ԑJ��
int AIChaseBoss::AIChaseFromRun(CEnemyBase* enemy)
{
	CPlayerManager* playerManager = CPlayerManager::GetInstance();
	CPlayer* player = playerManager->GetPlayer();
	CEnemyManager* enemyManager = CEnemyManager::GetInstance();
	CChaseBoss* chaseBoss = enemyManager->GetChaseBoss();
	
	//�{�X�̔��a�擾
	float rad = chaseBoss->GetRad();

	//�v���C���[�̈ʒu���擾
	VECTOR playerPos = player->GetPosition();

	//�{�X�̈ʒu���擾
	VECTOR bossPos = chaseBoss->GetPosition();


	//���������Ƃ��ɕ��s��Ԃɕς�鏈��
	if (!findFlg_) {
		return CHASE_WALK;
	}

	//�v���C���[���{�X�̍U���\�����ɂ���Ƃ�
	if (CMyMath::RadiusCheck(bossPos.x,rad,playerPos.x) &&
		CMyMath::RadiusCheck(bossPos.z, rad, playerPos.z)) 
	{
		//��ԑJ�ڂ����邱�Ƃ��m�肵�Ă���̂�
		chaseBoss->SetChangeFlg();

		//�v���C���[�̗̑͂����Ȃ��Ƃ�
		if (player->GetHP() < LOW_HP)
		{
			//�m�E��Ԃɓ���
			return CHASE_FINISHER;
		}
		else
		{
			//�����ɍ����ꍇ�ɉ����Ԃɓ��鏈��
			return CHASE_PUNCH;
		}
	}

	

	// �����Ȃ����
	return CHASE_RUN;
}

//��]���
int AIChaseBoss::AIChaseFromRoll(CEnemyBase* enemy)
{
	CPlayerManager* playerManager = CPlayerManager::GetInstance();
	CPlayer* player = playerManager->GetPlayer();
	CEnemyManager* enemyManager = CEnemyManager::GetInstance();
	CChaseBoss* chaseBoss = enemyManager->GetChaseBoss();

	//�{�X�̔��a�擾
	float rad = chaseBoss->GetRad();

	//�v���C���[�̈ʒu���擾
	VECTOR playerPos = player->GetPosition();

	//�{�X�̈ʒu���擾
	VECTOR bossPos = chaseBoss->GetPosition();


	//�A�j���[�V���������ݍĐ�����Ă��Ȃ����ɕ��s��ԂɂȂ鏈��
	if (end_animFlg_) {
		return CHASE_WALK;
	}

	//��]���Ƀv���C���[�ɐG�ꂽ�ꍇ
	if (CMyMath::RadiusCheck(bossPos, rad, playerPos)) {
		//�m�E��Ԃɓ���
		return CHASE_FINISHER;
	}

	// �����Ȃ����
	return CHASE_ROLL;
}

//������
int AIChaseBoss::AIChaseFromPunch(CEnemyBase* enemy)
{
	//�A�j���[�V���������ݍĐ�����Ă��Ȃ����ɑ��s��ԂɂȂ鏈��
	if (end_animFlg_) {
		CEnemyManager* enemyManager = CEnemyManager::GetInstance();
		CChaseBoss* chaseBoss = enemyManager->GetChaseBoss();

		//��ԑJ�ڂ�����̂�
		chaseBoss->SetChangeFlg();
		return CHASE_WALK;
	}

	// �����Ȃ����
	return CHASE_PUNCH;
}

//�m�E���
int AIChaseBoss::AIChaseFromFinisher(CEnemyBase* enemy)
{
	//�A�j���[�V���������ݍĐ�����Ă��Ȃ�����
	//�Q�[���I�[�o�[
	if (end_animFlg_) {
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_OVER);
	}

	// �����Ȃ����
	return CHASE_FINISHER;
}