#include "CardFive.h"
#include"Player.h"
#include<fstream>
CardFive::CardFive(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 5; // set the inherited cardNumber data member with the card number (1 here)
}

CardFive::CardFive()
{
	cardNumber = 5; // set the inherited cardNumber data member with the card number (1 here)

}

CardFive::~CardFive(void)
{
}

void CardFive::ReadCardParameters(Grid* pGrid)
{

}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
		pPlayer->setNextTurn(1);
	
	
}

void CardFive::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << std::endl;
	}
}

