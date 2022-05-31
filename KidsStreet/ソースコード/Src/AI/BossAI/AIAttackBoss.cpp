#include "AIAttackBoss.h"
#include "../../Enemy/EnemyCommon.h"
#include "../../Enemy/EnemyManager.h"
namespace
{
	
}

AIAttackBoss::AIAttackBoss() : AIBase()
{
	Init();
}

AIAttackBoss::~AIAttackBoss()
{
}

void AIAttackBoss::Init()
{
	time_ = 0.0f;
	target_time_ = 0.0f;
	attack_time_ = 0.0f;
	counterFlg_ = false;
	get_timeflg_ = false;
}

int AIAttackBoss::GetNextState(CEnemyBase* enemy)
{
	// �ԋp�p�ϐ�next
	int next = BOSS_APPEAR;

	//���݃A�j���[�V�������Đ�����Ă��Ȃ���
	end_animFlg_ = enemy->GetEndAnimFlg();

	//���݃^�[�Q�b�g������Ă��邩�ǂ������X�V����
	findFlg_ = enemy->GetFindFlg();
	
	// ���݂̏�Ԃ��擾
	int now_state = enemy->GetEnemyAIState();

	// ���݂̏�Ԃ��Ƃ̏����̊֐�����
	switch (now_state) {
	case BOSS_APPEAR:			// �o���Ԃ���̑J��
		next = AIAttackFromAppear(enemy);
		break;

	case BOSS_STAND:			//�ҋ@��Ԃ���̑J��
		next = AIAttackFromStand(enemy);
		break;

	case BOSS_TARGET:			 //�W�I��Ԃ���̑J��
		next = AIAttackFromTarget(enemy);
		break;

	case BOSS_MOTION_ATTACK:	//�U���J�n�O�\����Ԃ���̑J��
		next = AIAttackFromReady(enemy);
		break;

	case BOSS_NORMAL_ATTACK:	//�ʏ�U����Ԃ���̑J��
		next = AIAttackFromPunch(enemy);
		break;

	case BOSS_RARE_ATTACK:		//����U����Ԃ���̑J��
		next = AIAttackFromJump(enemy);
		break;

	case BOSS_CATCH:			//�L���b�`��ԑJ��
		next = AIAttackFromCatch(enemy);
		break;

	case BOSS_THROW:			//������ԑJ��
		next = AIAttackFromThrow(enemy);
		break;

	case BOSS_RAGE:				//�\���ԑJ��
		next = AIAttackFromRage(enemy);
		break;

	case BOSS_SLASH:				//�_�E����ԑJ��
		next = AIAttackFromSlash(enemy);
		break;
	}

	//��Ԃ��ύX�����Ȃ�
	if (now_state != next)
	{
		get_timeflg_ = false;
	}
	// ���͂ǂ̏�Ԃ���ԋp
	return next;
}

// �o���ԑJ��
int AIAttackBoss::AIAttackFromAppear(CEnemyBase* enemy)
{
	
	//�A�j���[�V���������ݍĐ�����Ă��Ȃ����ɑҋ@��ԂɂȂ鏈��
	if (end_animFlg_){
		return BOSS_STAND;
	}

	//�����蔻��N���X�ɂ���ăJ�E���^�[�t���O��true����Ă���Ȃ�
	if (counterFlg_){
		return BOSS_CATCH;//�L���b�`��Ԃ�
	}
	
	// �����Ȃ���Γo��̂܂�
	return BOSS_APPEAR;
}

// �ҋ@��ԑJ��
int AIAttackBoss::AIAttackFromStand(CEnemyBase* enemy)
{
	//�����蔻��N���X�ɂ���ăJ�E���^�[�t���O��true����Ă���Ȃ�
	if (counterFlg_)	{
		return BOSS_CATCH;//�L���b�`��Ԃ�
	}

	//�v���C���[�̃��b�N�I�����ł��Ă��Ȃ���
	if (!findFlg_){
		GetCount();
		//�ŏ��Ɏ��Ԃ��m�F����������w�莞�Ԃ��o�߂����Ȃ�
		if (SetWaitCount(target_time_)){
			return BOSS_TARGET;
		}
	}

	//�v���C���[�����b�N�I�����Ă���K�莞�Ԃ��߂����ꍇ
	if (findFlg_)	{
		GetCount();
		//�ŏ��Ɏ��Ԃ��m�F����������w�莞�Ԃ��o�߂����Ȃ�
		if (SetWaitCount(attack_time_)){
			return BOSS_NORMAL_ATTACK;
		}
	}

	//�v���C���[�����b�N�I�����Ă���ꍇ
	if (findFlg_) {
		if (GetRand(BOSS_RARE_CHANCE) == 0) {
			return BOSS_MOTION_ATTACK;
		}
	}

	//�܂�ɖ\���
	if (GetRand(BOSS_RAGE_CHANCE) == 0){
		return BOSS_RAGE;
	}
	
	if (findFlg_) {
		//�{�X�̗͎̑擾
		int hp = CEnemyManager::GetInstance()->GetBoss()->GetHP();
		//HP��50���ȉ��̂Ƃ��܂�ɓガ����
		if (hp < BOSS_HP_LOW){
			if (GetRand(BOSS_SLASH_CHANCE) == 0){
				return BOSS_SLASH;
			}
		}
	}

	// �����Ȃ���Όx���̂܂�
	return BOSS_STAND;
}

// �W�I��ԑJ��
int AIAttackBoss::AIAttackFromTarget(CEnemyBase* enemy)
{
	// //�A�j���[�V���������ݍĐ�����Ă��Ȃ����ɑҋ@��ԂɂȂ鏈��
	if (end_animFlg_) {
		return BOSS_STAND;
	}

	//�����蔻��N���X�ɂ���ăJ�E���^�[�t���O��true����Ă���Ȃ�
	if (counterFlg_){
		return BOSS_CATCH;//�L���b�`��Ԃ�
	}

	// �����Ȃ���ΕW�I��Ԃ̂܂�
	return BOSS_TARGET;
}

//�@�\����ԑJ��
int AIAttackBoss::AIAttackFromReady(CEnemyBase* enemy)
{
	//�A�j���[�V���������ݍĐ�����Ă��Ȃ����ɑҋ@��ԂɂȂ鏈��
	if (end_animFlg_) {
		return BOSS_RARE_ATTACK;
	}

	return BOSS_MOTION_ATTACK;
}

// ���ŏ�ԑJ��
int AIAttackBoss::AIAttackFromPunch(CEnemyBase* enemy)
{
	//�A�j���[�V���������ݍĐ�����Ă��Ȃ����ɑҋ@��ԂɂȂ鏈��
	if (end_animFlg_) {
		return BOSS_STAND;
	}

	return BOSS_NORMAL_ATTACK;
}

//����U����ԑJ��
int AIAttackBoss::AIAttackFromJump(CEnemyBase* enemy)
{
	//�A�j���[�V���������ݍĐ�����Ă��Ȃ����ɑҋ@��ԂɂȂ鏈��
	if (end_animFlg_) {
		return BOSS_STAND;
	}

	return BOSS_RARE_ATTACK;
}

//�L���b�`��ԑJ��
int AIAttackBoss::AIAttackFromCatch(CEnemyBase* enemy)
{
	//�L���b�`�͏�ԂƂ��Ă��邾���ŃA�j���[�V�������Ȃ�����
	return BOSS_THROW;
}

//������ԑJ��
int AIAttackBoss::AIAttackFromThrow(CEnemyBase* enemy)
{
	//�A�j���[�V���������ݍĐ�����Ă��Ȃ����ɑҋ@��ԂɂȂ鏈��
	if (end_animFlg_) {
		counterFlg_ = false;
		return BOSS_STAND;

	}
	return BOSS_THROW;
}

//�\���ԑJ��
int AIAttackBoss::AIAttackFromRage(CEnemyBase* enemy)
{
	//�A�j���[�V���������ݍĐ�����Ă��Ȃ����ɑҋ@��ԂɂȂ鏈��
	if (end_animFlg_) {
		return BOSS_STAND;
	}

	
	return BOSS_RAGE;
}

int AIAttackBoss::AIAttackFromSlash(CEnemyBase* enemy)
{
	// //�A�j���[�V���������ݍĐ�����Ă��Ȃ����ɑҋ@��ԂɂȂ鏈��
	if (end_animFlg_) {
		return BOSS_STAND;
	}
	
	return BOSS_SLASH;
}
//------�����܂ł���ԑJ�ڊ֐�-----------------------






//�ŏ��ɓǂݍ��񂾎��̎��Ԃ��i�[
void AIAttackBoss::GetCount()
{
	//���Ƀt���O��false�ɂ����܂ł͒ʂ�Ȃ�
	if (!get_timeflg_)
	{
		//�ǂݍ��݊J�n���Ԃ�ϐ��Ɋi�[
		time_ = (float)GetNowCount();
		get_timeflg_ = true;
	}
}


//�������w�肵���b�����o�߂������m�F����֐�
bool AIAttackBoss::SetWaitCount(float wait_time)
{
	//���̎��Ԃ�ϐ��Ɋi�[
	float now_time = (float)GetNowCount();

	//���̎��Ԃ���ǂݍ��݊J�n���Ԃ��������ƂŌo�ߎ��Ԃ��o��
	now_time -= time_;

	//�ݒ肳�ꂽ�b�����o�ߎ��Ԃ̕��������Ȃ�true��Ԃ�
	if (wait_time < now_time)
	{
		get_timeflg_ = false;
		return true;
	}
	else
		return false;
}
