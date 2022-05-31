//GameUI.cpp
//UIのベースとなるクラス

#include "GameUI.h"

CGameUI::CGameUI()
	:posX_(0.0f)
	,posY_(0.0f)
	,size_(0)
	,endPos_({0})
	,drawFlg_(false)
{
}

CGameUI::~CGameUI()
{
}