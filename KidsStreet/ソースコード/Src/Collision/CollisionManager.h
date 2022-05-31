#pragma once

#include "../Library/Collision/Collision.h"
#include "DxLib.h"
#include "../Library/LibraryCommon.h"
#include <vector>
#include "CollisionCommon.h"



//UE�ɂ��铖���蔻������Ƃɍ���������蔻��N���X
//�e�N���X�̏�������Z�b�g�̎���CreateCol�֐����ĂԂ��Ƃœ��I�\���̔z���
//����ێ�����g���쐬
//���TUpdate�֐���setUpColInfo���Ă�ŏ����X�V�����
//GetCollisionData�œ����蔻��ɔ�������𖞂���������������������
//�����ē��������͉̂����A��bool�^��enum�^�Ŋm�F�ł���

class CCollisionManager
{
public:
	

public:
	CCollisionManager();	//�R���X�g���N�^
	~CCollisionManager();	//�f�X�g���N�^

public:
	//�C���X�^���X����
	static void CreateInstance() { if (!instance_) instance_ = new CCollisionManager; }
	//�C���X�^���X�擾
	static CCollisionManager* GetInstance() { return instance_; }
	//�C���X�^���X�폜
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	void Init();
	void Step();//�X�e�b�v
	void DeleteAll();//�z�񏉊���

public:
	//�����蔻��𐶐�����
	int CreateCol(COL_DATA* data);
	//�����̓����蔻��f�[�^���e�N���X���ŎQ�Ƃ��邽�߂̊֐�
	COL_DATA GetCollisionData(int num) { return *col_vec_[num]; }
	//�����̓����蔻������X�V����֐��A���T�ĂԕK�v������
	void SetUpdateColInfo(int num, VECTOR pos, bool use);
	//��������̎���œ����蔻��^�C�v��ύX�������Ƃ��ɌĂԊ֐�
	void SetUpdateColInfo(int num, OBJECT_TYPE type) { col_vec_[num]->object_ = type; }
	//�����蔻����m�F����֐�
	void CollisionCheck(COL_DATA* master,COL_DATA* target);
	//�����蔻�茋�ʂ�vector�Ɋi�[����
	void ColHitResult(COL_DATA* master, COL_DATA* target);

private:
	static CCollisionManager*	instance_;					//�C���X�^���X

	int vectorMax_;

	//����A�ǂ�ǂ�UI�������Ă����v�Ȃ悤��
	//���I�z��Ƃ��Đ錾
	std::vector<COL_DATA*> col_vec_;
};