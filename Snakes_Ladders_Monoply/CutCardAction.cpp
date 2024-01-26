#include "CutCardAction.h"
#include"Grid.h"

CutCardAction::CutCardAction(ApplicationManager* pApp) :Action(pApp)
{

}

void CutCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();



	pOut->PrintMessage("Click on The Cell to Cut the Card ...");

	CellPosition C;
	C = pIn->GetCellClicked();

	if (C.IsValidCell())
		cutcell = C;  // The Cellposition of The Clicked Cell


	pOut->ClearStatusBar();

}

void CutCardAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	ReadActionParameters();

	Card* Pcard = pGrid->getCardfrompos(cutcell);
	//Checks IF the cell has a card Object OR nOt"NULL" 

	if (Pcard != NULL)

	{

		pGrid->SetClipboard(Pcard);  // Saves The Card Theat Pcard Pointing to

		pGrid->RemoveObjectFromCell(cutcell);

		pGrid->PrintErrorMessage("(Done): The Card Is Cut  | Click To Continue ...");

	}

	else
		pGrid->PrintErrorMessage("Error: There is no Card in this cell | Click to Continue ...");


}


CutCardAction::~CutCardAction(void)
{
}