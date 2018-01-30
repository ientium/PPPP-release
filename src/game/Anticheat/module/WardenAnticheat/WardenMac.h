/*
* Copyright (C) 2010-2014 Anathema Engine project <http://valkyrie-wow.com/> 
* Copyright (C) C(ontinued)-MaNGOS <http://cmangos.net/>
*/

#ifndef _WARDEN_MAC_H
#define _WARDEN_MAC_H

#include "Warden.h"

class WorldSession;
class Warden;

class WardenMac : public Warden
{
public:
    WardenMac();
    ~WardenMac();

    WardenModule* GetModuleForClient();

    void Init(WorldSession* pClient, BigNumber* k);
    void RequestHash();
};

#endif