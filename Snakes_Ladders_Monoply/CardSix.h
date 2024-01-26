#pragma once

#include "Card.h"

class CardSix : public Card
{
	int CellToMoveTo; // the wallet value to decrease from the player

public:
	CardSix(const CellPosition& pos); // A Constructor takes card position
	CardSix();
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player

	virtual void Save(ofstream& outFile, Type gameObj); //Saves the start cell and the end cell of Snake in a file

	virtual void Load(ifstream& InFile);
	virtual ~CardSix(); // A Virtual Destructor
};

