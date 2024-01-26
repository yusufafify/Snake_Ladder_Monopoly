#include "CardSix.h"

CardSix::CardSix(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (1 here)
}

CardSix::CardSix()
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (1 here)

}

CardSix::~CardSix(void)
{
}

void CardSix::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("New CardSix: Enter cell number to move to: ");
	CellToMoveTo = pIn->GetInteger(pOut);
	while (true) {


		while (CellToMoveTo <= 1 || CellToMoveTo >= 99) {
			pOut->PrintMessage("Error!! Cells 1 and 99 are inValid. Enter a valid cell number to move to: ");
			CellToMoveTo = pIn->GetInteger(pOut);
		}
		if (pGrid->getCardfromCellNum(CellToMoveTo) != NULL) {


			while (pGrid->getCardfromCellNum(CellToMoveTo)->GetCardNumber() == 6 && pGrid->getCardfromCellNum(CellToMoveTo) != NULL) {
				pOut->PrintMessage("Error!! The cell you chose already has a card 6. Enter a valid cell number to move to: ");
				CellToMoveTo = pIn->GetInteger(pOut);
				if (pGrid->getCardfromCellNum(CellToMoveTo) == NULL) {
					break;
				}
			}
			

		}
		if (CellToMoveTo != 1 && CellToMoveTo != 99) {
			break;
		}
	}
	pOut->ClearStatusBar();

}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
	CellPosition NewCellPosition(CellToMoveTo);
	int Vertical = NewCellPosition.VCell();
	int Horizontal = NewCellPosition.HCell();
	Cell* NewCell = pGrid->GetCellList(Vertical, Horizontal);

	Output* pOut = pGrid->GetOutput();

	pGrid->UpdatePlayerCell(pPlayer, NewCell->GetCellPosition());
	if (NewCell->GetGameObject())
	{
		NewCell->GetGameObject()->Apply(pGrid, pPlayer);
	}
}


void CardSix::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << CellToMoveTo << ' ' << std::endl;
	}
}

void CardSix::Load(ifstream& InFile) {
	Card::Load(InFile);

	int cell;
	InFile >> cell;
	CellToMoveTo = cell;
}