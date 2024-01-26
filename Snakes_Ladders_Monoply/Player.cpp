#include "Player.h"

#include "GameObject.h"

Player::Player(Cell* pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	this->NextTurnCounter = 0;
	isIce=false;
	isFire=false;
	isPoison=false;
	isLightning=false;

	IsBurnt = false;
	burningCounter = 0;

	IsIced = false;
	freezCounter = 0;

	IsPoisoned = false;
	poisoncounter = 0;

	specialAttackCounter = 0;
	InvalidRoll_Counter = 0;

	ExtraDice = false;

	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell* cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	if (wallet < 0) {
		this->wallet = 0;
	}
	else {
		this->wallet = wallet;
	}

	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetDiceRolled()
{
	return justRolledDiceNum;
}

void Player::isExtraDice(bool E) {
	ExtraDice = E;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

int Player::GetplayerNum() const {
	return playerNum;
}

void Player::setNextTurn(int i)
{
	NextTurnCounter=i;
}

int Player::GetNextTurn()
{
	return NextTurnCounter;
}


bool Player::IsRollValid()
{
	for (int i = 0; i < 3; i++)
	{
		if (RollValid[i] == false)
		{
			RollValid[i] = true;
			return false;
		}
	}
	return TRUE;
}

void Player::SetInValidRoll(int Num)
{
	InvalidRoll_Counter = Num;
	for (int i = 0; i < Num; i++)
	{
		RollValid[i] = false;
	}
}

/*Setters for attack types*/
void Player:: setIce(bool isIce) {
	this->isIce = isIce;
}
void Player:: setFire(bool isFire) {
	this->isFire = isFire;
}
void Player:: setPoison(bool isPoison) {
	this->isPoison = isPoison;
}
void Player:: setLightning(bool isLightning) {
	this->isLightning = isLightning;
}

/*Checking if the attack type is used*/
bool Player::isIceUsed() {
	return isIce;
}
bool Player::isFireUsed() {
	return isFire;

}
bool Player::isPoisonUsed() {
	return isPoison;

}
bool Player::isLightningUsed() {
	return isLightning;

}

int Player::getPlayerNum() const {
	return  playerNum;
}

bool Player::isBurnt(bool isBurnt) {
	IsBurnt = isBurnt;
	return IsBurnt;
}

void Player:: isIced(bool ice) {
	this->IsIced = ice;
}

void Player::isPois(bool pois) {
	IsPoisoned = pois;
}

// ====== Drawing Functions ======

void Player::setturnCount(int count) {      // a counter that starts with 0, is incremented with each dice roll
	turnCount = count;
}

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];


	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;


	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	
	justRolledDiceNum = diceNumber;
	if (ExtraDice) {
		Player* Current_Pos = pGrid->GetCurrentPlayer();
		CellPosition pos = pCell->GetCellPosition();
		if (pCell->GetCellPosition().GetCellNum() + justRolledDiceNum >= 99) {
			pos.AddCellNum(99 - pCell->GetCellPosition().GetCellNum());
		}
		else {
				pos.AddCellNum(justRolledDiceNum);
		}
		pGrid->UpdatePlayerCell(Current_Pos, pos);
		if (pCell->GetGameObject())
			pCell->GetGameObject()->Apply(pGrid, this);
		ExtraDice = false;
		return;
	}

	turnCount++;
	if (!IsRollValid()) {
		justRolledDiceNum = 0;
		pGrid->PrintErrorMessage("P" + to_string(playerNum) + " Cannot Roll the Dice for the next "+to_string(InvalidRoll_Counter) +"Turns| Click to continue..");
		InvalidRoll_Counter--;
		if (turnCount == 3) {
			turnCount = 0;
		}
		return;
	}

	if (IsBurnt) {
		burningCounter++;
		wallet -= 20;
		string s3 = to_string(wallet);
		pGrid->PrintErrorMessage("Your Wallet has decreased by: 20 Coins | click to continue.");

		pGrid->PrintErrorMessage("Now The coins in P" + to_string(playerNum) + " Wallet is : " + s3 + " Coins | Click to continue.");
		if (burningCounter == 3) {
			IsBurnt = false;
			burningCounter = 0;
		}
	}



	if (IsIced) {
		justRolledDiceNum = 0;
		freezCounter++;
		pGrid->PrintErrorMessage("P" + to_string(playerNum) + " is freezed for this turn | Click to continue..");
		IsIced = false;
		freezCounter = 0;
		if (turnCount == 3) {
			turnCount = 0;
		}
		return;
	}

	if (IsPoisoned) {
		pGrid->PrintErrorMessage("Your poisoned, your dice number will decrease by 1 for the next " + to_string(5 - poisoncounter) + " Rounds");
		pGrid->PrintErrorMessage("Your Dice value before deducting 1 is " + to_string(justRolledDiceNum) + " | click to continue");
		justRolledDiceNum--;
		poisoncounter++;
		pGrid->PrintErrorMessage("Your Dice value before deducting 1 is " + to_string(justRolledDiceNum) + " | click to continue");
		if (poisoncounter == 5) {
			poisoncounter = 0;
			IsPoisoned = false;
		}

	}

	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if (turnCount == 3) {
		if (specialAttackCounter < 2) {
			pGrid->GetOutput()->PrintMessage("Do you wish to launch a special attack instead of recharging? y/n");
			string choice=pGrid->GetInput()->GetSrting(pGrid->GetOutput());
			if (choice == "y"||choice=="Y") {
				turnCount = 0;
				specialAttackCounter++;
				bool valid;
				while (true) {
					valid=SpecialAttacks(pGrid);
					if (valid) {
						break;
					}
				}
				

				return;
			}
			else {
				int Inc_Wallet = justRolledDiceNum * 10;
				wallet += Inc_Wallet;
				turnCount = 0;

				string s1 = to_string(Inc_Wallet);
				string s2 = to_string(wallet);
				pGrid->PrintErrorMessage("Your Wallet has increased by: " + s1 + " Coins | click to continue.");

				pGrid->PrintErrorMessage("Now The coins in P" + to_string(playerNum) + " Wallet is : " + s2 + " Coins | Click to continue.");

				return;
			}
		}
		else {
			pGrid->PrintErrorMessage("You have used the maximum number of special attacks you have. | click to continue..");
			pGrid->PrintErrorMessage("Now your wallet will increase. | click to continue..");
			int Inc_Wallet = justRolledDiceNum * 10;
			wallet += Inc_Wallet;
			turnCount = 0;

			string s1 = to_string(Inc_Wallet);
			string s2 = to_string(wallet);
			pGrid->PrintErrorMessage("Your Wallet has increased by: " + s1 + " Coins | click to continue.");

			pGrid->PrintErrorMessage("Now The coins in P" + to_string(playerNum) + " Wallet is : " + s2 + " Coins | Click to continue.");

			return;
		}

		
	}




	// 3- Set the justRolledDiceNum with the passed diceNumber

	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"
	Player* Current_Pos = pGrid->GetCurrentPlayer();
	CellPosition pos = pCell->GetCellPosition();
	if (pCell->GetCellPosition().GetCellNum() + justRolledDiceNum >= 99) {
		pos.AddCellNum(99 - pCell->GetCellPosition().GetCellNum());
	}
	else{
		if (NextTurnCounter == 1) {
			if (pCell->GetCellPosition().GetCellNum() - justRolledDiceNum <= 1) {
				pos.DecCellNum(pCell->GetCellPosition().GetCellNum()-1);
			}
			else {
				pos.DecCellNum(justRolledDiceNum);
			}
			NextTurnCounter = 0;
		}
		else {
			pos.AddCellNum(justRolledDiceNum);

		}
	}
	


	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell(Current_Pos, pos);
	// 6- Apply() the game object of the reached cell (if any)
	if (pCell->GetGameObject())
		pCell->GetGameObject()->Apply(pGrid, this);

	pGrid->UpdateInterface();
	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	if (pCell->GetCellPosition().GetCellNum() == 99) {
		pGrid->PrintErrorMessage("Winner Winner Chicken Dinner !! Player Number: " + to_string(playerNum) + " Won the Game | click on Newgame Icon To start a new game or the Close icon to exit..");
		pGrid->SetEndGame(true);
		return;
	}
}

void Player::AppendPlayerInfo(string& playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}


bool Player::SpecialAttacks(Grid* pGrid)
{
	pGrid->GetOutput()->PrintMessage("Choose Your Special Attack .. Ice[0]-Fire[1]-Poison[2]-Lightning[3]..");
	int attacktype = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	while (attacktype > 3) {
		pGrid->GetOutput()->PrintMessage("InValid entery, please choose number between 0-3, Ice[0]-Fire[1]-Poison[2]-Lightning[3].. ");
		attacktype = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}
	type = static_cast<attacks>(attacktype);
	bool valid;
	if (type == Ice) {
		valid= pGrid->IceAttack();
		if (valid) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (type == Fire) {
		valid= pGrid->FireAttack();
		if (valid) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (type == Poison) {
		valid= pGrid->PoisonAttack();
		if (valid) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (type == Lightning) {
		valid= pGrid->LightningAttack(this);
		if (valid) {
			return true;
		}
		else {
			return false;
		}
	}

}