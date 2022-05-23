//�G�l�~�[�p���N���X

#pragma once
#include "DxLib.h"
#include "../Library/Animation/Animation.h"

class CEnemyBase : public CAnim3D
{

public:
	
	//�Ԑ����Ƃ̏���
	enum MOVE_DIR
	{
		MOVE_INIT = 0,
		FRONT_MOVE,
		BACK_MOVE,
		RIGHT_MOVE,
		LEFT_MOVE,
		MOVE_MAX_NUM
	};
	

public:
	CEnemyBase();
	virtual ~CEnemyBase();


	//������
	virtual void Init() = 0;
	//�ǂݍ���
	virtual void Load() = 0;
	//�ݒ�
	virtual void Set() = 0;
	//���t���[���Ăԏ���
	virtual void Step() = 0;
	//�`��
	virtual void Draw() = 0;
	//�X�V
	virtual void Update() = 0;
	//�폜
	virtual void Delete() = 0;
	//�㏈��
	virtual void Fin() = 0;

	//�����蔻��n��
	virtual void Hit() = 0;

public:
	//----------�Z�b�^�[--------
	
	//�����蔻�菈���t���O�𗧂Ă�
	void SetColFlg(bool flg) { colFlg_ = flg; }
	 //�_���[�W�ʂ��Z�b�g����
	void SetDmg(int dmg) { dmg_ = dmg; }


	//---------�Q�b�^�[--------
	
	//�v���C���[�����t���O���擾����
	bool GetFindFlg() { return findFlg_; }
	//�����x�N�g�����擾����
	VECTOR GetForwardVec() { return forward_; }
	
public:
	int GetEnemyAIState() const { return ai_state_; }

public:
	int			ai_state_;		// AI���
	int			hp_;			//�@HP�@
	int			dmg_;

	float		move_;

	bool		colFlg_;		//�����蔻��t���O
	bool		findFlg_;		//�v���C���[�������Ă��邩�ǂ���

	VECTOR		forward_;		//�����x�N�g���i�[
}; 