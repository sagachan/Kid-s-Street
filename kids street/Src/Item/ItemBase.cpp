#include "ItemBase.h"

CItemBase::CItemBase()
{
	
}

CItemBase::~CItemBase()
{

}

//���ݎg�p�p�����Ă��邩�ǂ���
bool CItemBase::GetMoveFlg()
{
	if (isUse_ && !endflg_)
	{
		return true;
	}
	else
	{
		return false; 
	}
}