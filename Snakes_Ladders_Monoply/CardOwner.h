#pragma once
#include "Player.h"
#include <vector>

class CardOwner
{


protected:
    Player* cOwner;
    vector<int> m_positions;

public:
    CardOwner();
    virtual ~CardOwner();

    Player* GetOwner() const;
    void SetOwner(Player* pPlayer);

};

