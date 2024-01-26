#pragma once

#include "Card.h"

class CardFive : public Card
{

public:
	CardFive(const CellPosition& pos); // A Constructor takes card position
	CardFive();
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player

	virtual void Save(ofstream& outFile, Type gameObj); //Saves the start cell and the end cell of Snake in a file

	virtual ~CardFive(); // A Virtual Destructor
};

