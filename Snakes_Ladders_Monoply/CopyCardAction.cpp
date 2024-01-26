#include "CopyCardAction.h"
#include "Grid.h"
#include"Card.h"


CopyCardAction::CopyCardAction(ApplicationManager* pApp) : Action(pApp)
{

}

void CopyCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Click on The Cell to copy it ...");

	CellPosition pos = pIn->GetCellClicked();
		Copycell = pos;

}
void CopyCardAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	ReadActionParameters();
	//Checks IF the cell has a card Object OR nOt"NULL"
	Card* Pcard = pGrid->getCardfrompos(Copycell);
	if (Pcard != NULL)

	{

		pGrid->SetClipboard(Pcard);  // Saves The Card Theat Pcard Pointing to


		pGrid->PrintErrorMessage("(Done): Cell Is copied Press To Continue ...");

		pIn->GetCellClicked();   // Just To Give Time For User
		pOut->ClearStatusBar();

	}
	else {
		pGrid->PrintErrorMessage("There is no Card to copy | Click to Continue ...");

	}
}
	CopyCardAction::~CopyCardAction()
	{
	}