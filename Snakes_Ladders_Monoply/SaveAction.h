#pragma once

#include "Action.h"
#include <fstream>
class SaveAction : public Action
{
	string FileName;
public:
	SaveAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads SaveGridAction action parameters (FileName)

	virtual void Execute(); //  Reads the Parameters of SaveGridAction 
	// then calls SaveAll of every gameobject



};
