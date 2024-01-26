#pragma once
#include "action.h"
class DeleteAction :public Action
{
	CellPosition delcell;

public:
	DeleteAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	~DeleteAction(void);
};



