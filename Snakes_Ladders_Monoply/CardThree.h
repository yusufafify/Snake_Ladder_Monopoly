#pragma once

#include "Card.h"

class CardThree : public Card
{


public:
	CardThree(const CellPosition& pos); // A Constructor takes card position
	CardThree();
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player

	virtual ~CardThree(); // A Virtual Destructor
	virtual void Save(ofstream& outFile, Type gameObj); //Saves the start cell and the end cell of Snake in a file

};

