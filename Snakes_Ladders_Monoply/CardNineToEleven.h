#pragma once
#include "Card.h"
class CardNineToEleven :public Card
{
public:

	CardNineToEleven(const  CellPosition& pos);
	CardNineToEleven();
	virtual void ReadCardParameters(Grid* pGrid, int& Price, int& fees, Player*& cOwner);

	virtual void Apply(Grid* pGrid, Player* pPlayer, int& Price, int& fees, Player*& cOwner);


};
