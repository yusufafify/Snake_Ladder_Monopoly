#pragma once

#include "Card.h"

class CardEight : public Card
{
	int PrisonFee = 0;

public:
	CardEight(const CellPosition& pos); // A Constructor takes card position
	CardEight();
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player

	virtual ~CardEight(); // A Virtual Destructor
	virtual void Save(ofstream& outFile, Type gameObj); //Saves the start cell and the end cell of Snake in a file

	virtual void Load(ifstream& InFile);
};

