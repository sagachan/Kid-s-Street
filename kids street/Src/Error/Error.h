//�w��V�X�e���G���[�E�o�v���O����
#include "DxLib.h"

class CError {
public:
	
	static void ErrorManager();				//�G���[�`�F�b�N�Ǘ��֐�

	static void EnemyError();				//�G�l�~�[�֌W�̃G���[�`�F�b�N
	static void PlayerError();
	static void VoidError();				//Manager�N���X�̃e���v���[�g�֐��AMinimizeCall�֐��̌Ăяo�������s�����Ƃ��ɒʂ�
};