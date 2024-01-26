#include "DeleteAction.h"

#include "Input.h"
#include "Output.h"
#include "Grid.h"


DeleteAction::DeleteAction(ApplicationManager* pApp) : Action(pApp)
{

}
void DeleteAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Click on Cell you want to delete ...");
	delcell=pIn->GetCellClicked();


	pOut->ClearStatusBar();
}

void DeleteAction::Execute()
{

	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Card* Pcard = pGrid->getCardfrompos(delcell);
	GameObject* pObj = pGrid->GetSnakeorLadderObjFromCellPosition(delcell);
	if (Pcard != NULL || pObj!=NULL) {
		pGrid->RemoveObjectFromCell(delcell);
		pGrid->PrintErrorMessage("Object is Deleted | click to continue..");
	}
	else {
		pGrid->PrintErrorMessage("There is no object to delete");
	}
	
	pGrid->UpdateInterface();
}
DeleteAction::~DeleteAction(void)
{
}

