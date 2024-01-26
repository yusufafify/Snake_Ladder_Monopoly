#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include"Snake.h"
#include "Card.h"
#include "Player.h"




Player* Grid::GetPoorestPlayer()
{
	Player* MIN = PlayerList[0];
	for (size_t i = 0; i < MaxPlayerCount; i++)
	{
		MIN = PlayerList[i]->GetWallet() < MIN->GetWallet() ? PlayerList[i] : MIN;
	}
	return MIN;
}

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}


// Note: You may need to change the return type of this function (Think)
void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

void Grid::HoldCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 3) % MaxPlayerCount;
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder* Grid::GetNextLadder(const CellPosition& position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			Ladder* pLadder = CellList[i][j]->HasLadder();
			if (pLadder)
			{
				return pLadder;
			}
			///TODO: Check if CellList[i][j] has a ladder, if yes return it			

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Player* Grid::GetNextPlayer(const CellPosition& position)
{
	int CellNum = position.GetCellNum();
	int distance = 99, NextPlayerCell = 0;
	for (int i = 0; i < 4; i++)
	{
		CellPosition PlayerCell = PlayerList[i]->GetCell()->GetCellPosition();
		if (PlayerCell.GetCellNum() > CellNum && PlayerCell.GetCellNum() - CellNum < distance)
		{
			NextPlayerCell = i;
			distance = PlayerCell.GetCellNum() - CellNum;
		}
	}
	return PlayerList[NextPlayerCell];
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}






GameObject* Grid::GetSnakeorLadderObjFromCellPosition(const CellPosition& pos) {
	// Get the cell object that corresponds to the given CellPosition
	Cell* cell = CellList[pos.VCell()][pos.HCell()];
	if (cell->HasLadder()) {
		// If the cell has a ladder, return a pointer to that ladder object
		return cell->HasLadder();
	}
	// Check if the cell has a snake object on it
	else if (cell->HasSnake()) {
		// If the cell has a snake, return a pointer to that snake object
		return cell->HasSnake();
	}
	// If there is no game object at the given CellPosition, return a nullptr
	else {
		return nullptr;
	}
}





bool Grid::isLadderOverlap(Grid* pGrid, CellPosition startPos, CellPosition endPos) {
	// Initialize flags for detecting overlap with snakes, ladders, and opposite ladders
	bool hasSnakeOverlap = false;
	bool hasLadderOverlap = false;
	bool hasOppositeLadderOverlap = false;

	// Check for overlap with snakes or ladders on the same row as the ladder
	for (int i = startPos.GetCellNum(); i <= endPos.GetCellNum(); i += NumHorizontalCells) {
		GameObject* obj = pGrid->GetSnakeorLadderObjFromCellPosition(CellPosition(i));
		if (obj) {
			if (Snake* snake = dynamic_cast<Snake*>(obj)) {
				if (snake->GetPosition().GetCellNum() == endPos.GetCellNum()) {
					// If the ladder overlaps with a snake, set the snake overlap flag and break the loop
					pGrid->PrintErrorMessage("ERROR: You can not add the Ladder exactly on a Snake! Click to continue ...");
					hasSnakeOverlap = true;
					break;
				}
			}
			else if (Ladder* ladder = dynamic_cast<Ladder*>(obj)) {
				// If the ladder overlaps with another ladder, set the ladder overlap flag and break the loop
				pGrid->PrintErrorMessage("ERROR: It is not possible for two ladders to overlap! Click to continue ...");
				hasLadderOverlap = true;
				break;
			}
		}
	}
	// Check for overlap with opposite ladders on the same column as the ladder
	for (int i = NumVerticalCells - 1; i > 0 && !hasLadderOverlap && !hasSnakeOverlap; --i) {
		GameObject* obj = pGrid->GetSnakeorLadderObjFromCellPosition(CellPosition(i, startPos.HCell()));
		if (obj) {
			if (Ladder* ladder = dynamic_cast<Ladder*>(obj)) {
				if (startPos.VCell() < ladder->GetPosition().VCell() && startPos.VCell() >= ladder->GetEndPosition().VCell()) {
					// If the ladder overlaps with an opposite ladder, set the opposite ladder overlap flag and break the loop
					pGrid->PrintErrorMessage("ERROR: It is not possible for two ladders to overlap! Click to continue ...");
					hasOppositeLadderOverlap = true;
					break;
				}
			}
			else if (Snake* snake = dynamic_cast<Snake*>(obj)) {
				if (startPos.VCell() == snake->GetEndPosition().VCell()) {
					// If the ladder overlaps with a snake's end position, set the snake overlap flag and break the loop
					pGrid->PrintErrorMessage("ERROR: You can not select Ladder's start cell to be on a Snake end cell! Click to continue ...");
					hasSnakeOverlap = true;
					break;
				}
			}
		}
	}
	// Return true if any of the overlap flags are true
	return hasSnakeOverlap || hasLadderOverlap || hasOppositeLadderOverlap;
}


bool Grid::isSnakeOverlap(Grid* pGrid, CellPosition startPos, CellPosition endPos) {
	// Check for overlap with existing snakes or ladders in the same column as the new snake's ending cell
	bool hasOverlap = false;
	for (int i = startPos.GetCellNum(); i >= endPos.GetCellNum() && !hasOverlap; i -= NumHorizontalCells) {
		GameObject* obj = pGrid->GetSnakeorLadderObjFromCellPosition(CellPosition(i));
		if (obj) {
			if (Snake* snake = dynamic_cast<Snake*>(obj)) {
				if (snake->GetPosition().GetCellNum() == endPos.GetCellNum()) {
					pGrid->PrintErrorMessage("ERROR: You cannot add another snake exactly on this snake! Please select a different end position. Click to continue...");
					hasOverlap = true;
				}
			}
			else if (Ladder* ladder = dynamic_cast<Ladder*>(obj)) {
				if ((startPos.VCell() == ladder->GetEndPosition().VCell())) {
					pGrid->PrintErrorMessage("ERROR: You cannot add a snake exactly on a ladder! Please select a different end position. Click to continue...");
					hasOverlap = true;
				}
			}
		}
	}
	// Check for overlap with existing snakes in the same row as the new snake's starting cell
	for (int i = NumVerticalCells - 1; i > 0 && !hasOverlap; --i) {
		GameObject* obj = pGrid->GetSnakeorLadderObjFromCellPosition(CellPosition(i, startPos.HCell()));
		if (obj) {
			if (Snake* snake = dynamic_cast<Snake*>(obj)) {
				if (startPos.VCell() > snake->GetPosition().VCell() && startPos.VCell() <= snake->GetEndPosition().VCell()) {
					pGrid->PrintErrorMessage("ERROR: It is not possible for two snakes to overlap! Please select a different start position. Click to continue...");
					hasOverlap = true;
				}
				if (endPos.VCell() ==snake->GetEndPosition().VCell()) {
					pGrid->PrintErrorMessage("ERROR: It is not possible for two snakes to overlap! Please select a different start position. Click to continue...");
					hasOverlap = true;
				}
			}
			else if (Ladder* ladder = dynamic_cast<Ladder*>(obj)) {
				if (ladder->GetPosition().GetCellNum() == endPos.GetCellNum()) {
					pGrid->PrintErrorMessage("ERROR: You cannot select the snake's end cell to be on a ladder's start cell! Please select a different start position. Click to continue...");
					hasOverlap = true;
				}
			}
		}
	}

	return hasOverlap;
}



/*Applying Special Attacks*/
bool Grid::IceAttack() {
	if (GetCurrentPlayer()->isIceUsed()) {
		PrintErrorMessage("You already used this attack type, use another one  | click to continue");
		return false;
	}
	GetOutput()->PrintMessage(" Choose a player to Freez.");
	int player_Num = pIn->GetInteger(pOut);
	while (player_Num == currPlayerNumber) {
		GetOutput()->PrintMessage("You cannot use the attack on your self, choose another player.");
		player_Num = pIn->GetInteger(pOut);
	}
	while (player_Num > 3) {
		GetOutput()->PrintMessage("Please choose the player numbers between 0-3.");
		player_Num = pIn->GetInteger(pOut);
		while (player_Num == currPlayerNumber) {
			GetOutput()->PrintMessage("You cannot use the attack on your self, choose another player.");
			player_Num = pIn->GetInteger(pOut);
		}
	}
	pOut->ClearStatusBar();
	PlayerList[player_Num]->isIced(true);
	GetCurrentPlayer()->setIce(true);
	return true;
}
bool Grid::FireAttack() {
	if (GetCurrentPlayer()->isFireUsed()) {
		PrintErrorMessage("You already used this attack type, use another one | click to continue");
		return false;
	}
	GetOutput()->PrintMessage(" Choose a player to burn.");
	int player_Num = pIn->GetInteger(pOut);
	while (player_Num == currPlayerNumber) {
		GetOutput()->PrintMessage("You cannot use the attack on your self, choose another player.");
		player_Num = pIn->GetInteger(pOut);
	}
	while (player_Num > 3) {
		GetOutput()->PrintMessage("Please choose the player numbers between 0-3.");
		player_Num = pIn->GetInteger(pOut);
		while (player_Num == currPlayerNumber) {
			GetOutput()->PrintMessage("You cannot use the attack on your self, choose another player.");
			player_Num = pIn->GetInteger(pOut);
		}
	}

	pOut->ClearStatusBar();
	PlayerList[player_Num]->isBurnt(true);
	GetCurrentPlayer()->setFire(true);

	return true;
}
bool Grid::PoisonAttack() {
	if (GetCurrentPlayer()->isPoisonUsed()) {
		PrintErrorMessage("You already used this attack type, use another one  | click to continue");
		return false;
	}
	GetOutput()->PrintMessage(" Choose a player to poison.");
	int player_Num = pIn->GetInteger(pOut);
	while (player_Num == currPlayerNumber) {
		GetOutput()->PrintMessage("You cannot use the attack on your self, choose another player.");
		player_Num = pIn->GetInteger(pOut);
	}
	while (player_Num > 3) {
		GetOutput()->PrintMessage("Please choose the player numbers between 0-3.");
		player_Num = pIn->GetInteger(pOut);
		while (player_Num == currPlayerNumber) {
			GetOutput()->PrintMessage("You cannot use the attack on your self, choose another player.");
			player_Num = pIn->GetInteger(pOut);
		}
	}

	pOut->ClearStatusBar();
	PlayerList[player_Num]->isPois(true);
	GetCurrentPlayer()->setPoison(true);

	return true;
}
bool Grid::LightningAttack(Player* ptr) {
	if (GetCurrentPlayer()->isLightningUsed()) {
		PrintErrorMessage("You already used this attack type, use another one  | click to continue");
		return false;
	}
	for (int i = 0; i < 4; i++)
	{
		if (PlayerList[i] == GetCurrentPlayer()) {
			int wall = PlayerList[i]->GetWallet();
			PlayerList[i]->SetWallet((wall));
		}
		else {
			int wall = PlayerList[i]->GetWallet();
			PlayerList[i]->SetWallet((wall - 20));
			PrintErrorMessage("P" + to_string(i) + " got a Lightning Strike by P" + to_string(currPlayerNumber) + " and now P" + to_string(i) + "'s wallet will be decremented by 20 coins | click to continue");
		}

	}
	ptr->setLightning(true);
	return true;
}




int Grid::GetNumberOfGameObject(Type type) const {
	int count = 0;

	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			switch (type)
			{
			case LADDERS:
				if (CellList[i][j]->HasLadder())
					++count;
				break;
			case SNAKES:
				if (CellList[i][j]->HasSnake())
					++count;
				break;
			case CARDS:
				if (CellList[i][j]->HasCard())
					++count;
				break;

			}
		}
	}

	return count;
}


//================Additional Functions=========================

void Grid::SaveObjects(ofstream& outFile, Type gameObj) {
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->GetGameObject())
				CellList[i][j]->GetGameObject()->Save(outFile, gameObj);
		}
	}

}




Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}


void Grid::DeleteAllGameObjects()
{
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			Cell* cell = CellList[i][j];
			GameObject* gameObject = cell->GetGameObject();
			if (gameObject != nullptr)
			{
				RemoveObjectFromCell(gameObject->GetPosition());
			}
		}
	}
}

Cell* Grid::GetCellList(int Vertical, int Horizontal)
{
	return CellList[Vertical][Horizontal];
}

Card* Grid::getCardfrompos(CellPosition pos)
{
	if (CellList[pos.VCell()][pos.HCell()]->HasCard() != NULL)
	{
		return CellList[pos.VCell()][pos.HCell()]->HasCard();
	}
	return NULL;
}


Card* Grid::getCardfromCellNum(int pos)
{
	CellPosition pCell(pos);
	if (CellList[pCell.VCell()][pCell.HCell()]->HasCard() != NULL)
	{
		return CellList[pCell.VCell()][pCell.HCell()]->HasCard();
	}
	return NULL;
}


