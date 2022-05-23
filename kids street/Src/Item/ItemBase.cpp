#include "ItemBase.h"

CItemBase::CItemBase()
{
	
}

CItemBase::~CItemBase()
{

}

//åªç›égópåpë±ÇµÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©
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