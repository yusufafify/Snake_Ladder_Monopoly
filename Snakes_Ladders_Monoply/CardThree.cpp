#include "CardThree.h"

CardThree::CardThree(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 3; // set the inherited cardNumber data member with the card number (1 here)
}

CardThree::CardThree()
{
	cardNumber = 3; // set the inherited cardNumber data member with the card number (1 here)

}

CardThree::~CardThree(void)
{
}

void CardThree::ReadCardParameters(Grid* pGrid)
{


}

void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
	pGrid->PrintErrorMessage("Now you Have an Extra Dice Roll | Click to continue");
	pPlayer->isExtraDice(true);
	pGrid->HoldCurrentPlayer();


}


void CardThree::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << std::endl;
	}
}

