#pragma once

#include "Card.h"
#include "Ladder.h"

class CardTwo : public Card
{


public:
	CardTwo(const CellPosition& pos); // A Constructor takes card position
	CardTwo();
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	virtual ~CardTwo(); // A Virtual Destructor

	virtual void Save(ofstream& outFile, Type gameObj); //Saves the start cell and the end cell of Snake in a file


};

