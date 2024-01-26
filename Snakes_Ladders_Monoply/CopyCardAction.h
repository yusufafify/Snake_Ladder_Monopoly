#pragma once
#include "action.h"
class CopyCardAction : public Action
{
	CellPosition Copycell;

public:
	CopyCardAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();


	virtual ~CopyCardAction();
};