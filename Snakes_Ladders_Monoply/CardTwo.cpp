#include "CardTwo.h"
#include<fstream>
CardTwo::CardTwo(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number (1 here)
}

CardTwo::CardTwo()
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number (1 here)

}

CardTwo::~CardTwo(void)
{
}

void CardTwo::ReadCardParameters(Grid* pGrid)
{


}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);

	Ladder* pLadder = pGrid->GetNextLadder(position);
	if (pLadder != NULL)
	{
		pGrid->UpdatePlayerCell(pPlayer, pLadder->GetEndPosition());
	}
	else {
		pGrid->PrintErrorMessage("There is no Ladder on the Grid | Click to Continue..");
	}
}

void CardTwo::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << std::endl;
	}
}
