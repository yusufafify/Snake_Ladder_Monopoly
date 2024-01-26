#include "Snake.h"
#include "Player.h"
#include"Grid.h"
#include"Ladder.h"
#include <fstream>
Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}

Snake::Snake()
{
}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Save(ofstream& OutFile, Type Type)
{
	if (Type == SNAKES)
	{
		OutFile << position.GetCellNum() << ' ' << endCellPos.GetCellNum() << std::endl;
	}
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// 1- Print a message "You have reached a Snake. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a Snake. | Click to continue ...");
	// 2- Apply the Snake's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

void Snake::Load(ifstream& InFile)
{
	int startPosNumber, endPosNumber;
	InFile >> startPosNumber >> endPosNumber;

	position = CellPosition(startPosNumber);
	endCellPos = CellPosition(endPosNumber);
}

Snake::~Snake()
{
}



