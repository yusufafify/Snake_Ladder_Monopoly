#include "CardOwner.h"

CardOwner::CardOwner()
{
	cOwner = nullptr;
}

CardOwner::~CardOwner()
{

}

Player* CardOwner::GetOwner() const
{
	return cOwner;
}

void CardOwner::SetOwner(Player* pPlayer)
{
	cOwner = pPlayer;
}