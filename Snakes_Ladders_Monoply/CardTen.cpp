#include "CardTen.h"
int CardTen::Price_CardTen = 0;
int CardTen::fees_CardTen = 0;
Player* CardTen::cOwner_CardTen = NULL;

CardTen::CardTen(const CellPosition& pos) :CardNineToEleven(pos)
{
	cardNumber = 10;

}

CardTen::CardTen()
{
	cardNumber = 10;

}

void CardTen::ReadCardParameters(Grid* pGrid)
{
	CardNineToEleven::ReadCardParameters(pGrid, Price_CardTen, fees_CardTen, cOwner_CardTen);
}

void CardTen::Apply(Grid* pGrid, Player* pPlayer)
{
	CardNineToEleven::Apply(pGrid, pPlayer, Price_CardTen, fees_CardTen, cOwner_CardTen);
}

Player* CardTen::get_cOwner()
{
	return cOwner_CardTen;
}

int CardTen::getPrice()
{
	return Price_CardTen;
}

void CardTen::set_cOwner(Player* pplayer)
{
	cOwner_CardTen = pplayer;
}

Card* CardTen::get_Copy(const CellPosition& pos)
{
	return new CardTen(pos);
}


void CardTen::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);


		outFile << Price_CardTen << ' ' << fees_CardTen << std::endl;

	}
}

void CardTen::Load(ifstream& InFile) {
	Card::Load(InFile);

	int price;
	int rent;

	InFile >> price >> rent;
	Price_CardTen = price;
	fees_CardTen = rent;

}