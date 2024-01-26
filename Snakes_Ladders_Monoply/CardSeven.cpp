#include "CardSeven.h"

CardSeven::CardSeven(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (1 here)
}

CardSeven::CardSeven()
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (1 here)

}

CardSeven::~CardSeven(void)
{
}

void CardSeven::ReadCardParameters(Grid* pGrid)
{

}

void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
	Player* NextPlayer = pGrid->GetNextPlayer(position);
	CellPosition StartSquare(1);
	pGrid->UpdatePlayerCell(NextPlayer, StartSquare);
}

void CardSeven::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << std::endl;
	}
}

void CardSeven::Load(ifstream& InFile) {
	Card::Load(InFile);

}