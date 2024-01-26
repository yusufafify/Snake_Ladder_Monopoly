#include "CardFour.h"
#include<fstream>
CardFour::CardFour(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number (1 here)
}

CardFour::CardFour()
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number (1 here)

}

CardFour::~CardFour(void)
{
}

void CardFour::ReadCardParameters(Grid* pGrid)
{


}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
	pPlayer->SetInValidRoll(1);
}

void CardFour::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << std::endl;
	}
}


