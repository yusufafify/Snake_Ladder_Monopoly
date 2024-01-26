#include "Ladder.h"
#include<fstream>
Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}

Ladder::Ladder()
{
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	pGrid->PrintErrorMessage("You have reached a Ladder. | Click to continue ...");

	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

}

CellPosition Ladder::GetPosition() const
{
	return position;
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

Ladder::~Ladder()
{
}


void Ladder::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == LADDERS)
	{
		outFile << position.GetCellNum() << ' ' << endCellPos.GetCellNum() << std::endl;
	}
}

void Ladder::Load(ifstream& InFile)
{
	int startPosNumber, endPosNumber;
	InFile >> startPosNumber >> endPosNumber;

	position = CellPosition(startPosNumber);
	endCellPos = CellPosition(endPosNumber);
}
