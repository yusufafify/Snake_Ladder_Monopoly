#include "PasteCardAction.h"
#include "Grid.h"
#include"Card.h"


PasteCardAction::PasteCardAction(ApplicationManager* pApp) :Action(pApp)
{

}
void PasteCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Click On The Cell You want Paste to..");

	Newcell = pIn->GetCellClicked(); //Newcell is a data member


	pOut->ClearStatusBar();
}

void PasteCardAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();


	Card* Pcard = pGrid->GetClipboard();
	int x = Newcell.HCell();
	int y = Newcell.VCell();
	if (Pcard != NULL) {
		Pcard->setnewpos(x, y);

		if (pGrid->AddObjectToCell(Pcard)) // Add el Object "Card"with (Old Card Number and New Cellposition Choosen) + Checking if fe Object in cell

			pGrid->AddObjectToCell(Pcard);

		else

			pGrid->PrintErrorMessage("There Is An Object Choose another Cell");
	}
	else {
		pGrid->PrintErrorMessage("There is no copied or cut card | Click to continue..");

	}



}
PasteCardAction::~PasteCardAction(void)
{
}