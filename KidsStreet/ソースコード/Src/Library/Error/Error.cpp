

#include "Error.h"
#include <cassert>


void CError::MinimizeVoidError()
{
	//ここを通った時点で確実にエラー
	assert(true);
}