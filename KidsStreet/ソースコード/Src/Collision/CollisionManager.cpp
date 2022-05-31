
#include "CollisionManager.h"
#include "../Library/MyMath/MyMath.h"
#include "ColField/ColField.h"

//CEnemyManager�̎��̐錾�A������
CCollisionManager* CCollisionManager::instance_ = nullptr;

CCollisionManager::CCollisionManager()
{
	Init();
}

CCollisionManager::~CCollisionManager()
{
	DeleteAll();
}

void CCollisionManager::Init()
{
	vectorMax_ = 0;
}
void CCollisionManager::Step()
{
	//�}�b�v�Ƃ̓����蔻��֌W�X�V
	CColField::CheckColField();

	//�܂��͑O��̔��茋�ʂ̏�����
	for (auto itr = col_vec_.begin(); itr != col_vec_.end(); itr++) {
		(*itr)->hitFlg_ = false;
		for (int num = 0; num < COL_CHECK_MAX; num++){
			(*itr)->list_[num] = COL_NONE;
		}

	}
	//�����őS�Ă��Q�Ƃ��ă^�C�v���Ƃɏ����𕪂���
	for (auto masterItr = col_vec_.begin(); masterItr != col_vec_.end(); masterItr++) {
		for (auto targetItr = col_vec_.begin(); targetItr != col_vec_.end(); targetItr++) {
			//�^�[�Q�b�g�̓����蔻��^�C�v���i�[
			OBJECT_TYPE object = (*targetItr)->object_;
			bool checkFlg = false;
			//�����̎g�p�t���O�������Ă���Ȃ�ʂ�
			if ((*masterItr)->useFlg_ && (*targetItr)->useFlg_){
				//���݂��̃^�C�v���Ⴄ�Ȃ�ʂ�
				if ((*masterItr)->myList_ != (*targetItr)->myList_)
				{
					//�^�[�Q�b�g�̓����蔻��^�C�v�ɑ΂��錳�̓����蔻���
					//�`�F�b�N�{�b�N�X��NONE�ȊO��I��ł���Ȃ�
					if (object == OBJECT_PAWN && (*masterItr)->type_.pawn_ != CHECK_BOX_NONE) {
						checkFlg = true;
					}
					if (object == OBJECT_STATIC && (*masterItr)->type_.static_ != CHECK_BOX_NONE) {
						checkFlg = true;
					}
					if (object == OBJECT_DYNAMIC && (*masterItr)->type_.dynamic_ != CHECK_BOX_NONE) {
						checkFlg = true;
					}
				}
				if (checkFlg)
					CollisionCheck((*masterItr), (*targetItr));
			}
		}
	}
}

void CCollisionManager::CollisionCheck(COL_DATA* master, COL_DATA* target)
{
	for (int num = 0; num < COL_CHECK_MAX; num++){
		//�ʂ̃^�C�~���O�ł��łɓ����X�g�̃I�u�W�F�N�g�ƐG��Ă���ꍇ�͏I���
		//�擪����������Ă����̂ŋ󂪌����������_�ŏI���
		if (master->list_[num] == target->myList_) {
			return;
		}
	}
	
	//�����蔻��̌`�Ɉ˂����������s��
	//�����{�b�N�X
	if (master->shapeCol_ == SHAPE_CUBE && target->shapeCol_ == SHAPE_CUBE){
		if (CCollision::IsHitRect
			(master->pos_, master->cubeRad_.x, master->cubeRad_.y, master->cubeRad_.z,
			target->pos_, target->cubeRad_.x, target->cubeRad_.y, target->cubeRad_.z)){
			ColHitResult(master, target);
		}	
	}

	//master������target����
	else if (master->shapeCol_ == SHAPE_CUBE && target->shapeCol_ == SHAPE_SPHERE){
		if(CCollision::IsHitSphereCube
			(master->pos_,master->cubeRad_.x, master->cubeRad_.y,master->cubeRad_.z, 
			target->pos_,target->sphereRad_)){
			ColHitResult(master, target);
		}
	}

	//master������target����
	else if (master->shapeCol_ == SHAPE_SPHERE && target->shapeCol_ == SHAPE_CUBE){
		if (CCollision::IsHitSphereCube
			(target->pos_,target->cubeRad_.x, target->cubeRad_.y, target->cubeRad_.z,
			master->pos_, master->sphereRad_)){
			ColHitResult(master, target);
		}

	}

	//������
	else if (master->shapeCol_ == SHAPE_SPHERE && target->shapeCol_ == SHAPE_SPHERE){
		if (CCollision::IsHitSphere
			(master->pos_, master->sphereRad_, target->pos_, target->sphereRad_)){
			ColHitResult(master, target);
		}
	}

	
}

void CCollisionManager::ColHitResult(COL_DATA* master, COL_DATA* target)
{
	master->hitFlg_ = true;
	for (int num = 0; num < COL_CHECK_MAX; num++) {
		//�擪���珇�ɎQ�Ƃ��āA���g���܂������Ă��Ȃ����̂ɂ����
		if (master->list_[num] == COL_NONE) {
			master->list_[num] = target->myList_;
			break;
		}
	}
}

void CCollisionManager::SetUpdateColInfo(int num, VECTOR pos, bool use)
{
	col_vec_[num]->pos_ = pos;
	col_vec_[num]->useFlg_ = use;
}

int CCollisionManager::CreateCol(COL_DATA* data)
{
	//���݂̔z��ԍ������[�J���ϐ��ɓ���ĕێ�����
	//������Ō�Ƀ��^�[�����Ċe�N���X�Ɏ����̓����蔻��ԍ�����������
	int result = vectorMax_;

	//�����蔻��\���̔z��ɏ���ǉ�
	col_vec_.push_back(data); 

	//�x�N�^�[�z��̒��g����������̎���œ���ւ��邱�Ƃ����������̂��߂�
	//�z��ԍ����\���̂ł��Ǘ����Ă���
	col_vec_[vectorMax_]->colNum_ = vectorMax_;
	vectorMax_++; 
	return result; 
}

//�폜�ivector���̓����蔻������ׂč폜�j
void CCollisionManager::DeleteAll()
{
	
	//�z����폜����
	col_vec_.clear();
	col_vec_.shrink_to_fit();
}