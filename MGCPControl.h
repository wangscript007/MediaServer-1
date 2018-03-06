#pragma once
#include "stdafx.h"
#include "Structs.h"
#include "Functions.h"
#include "MGCPparser.h"
#include "EventAnn.h"
#include "EventCnf.h"

using namespace std;

extern SHP_InitParams init_Params;
extern boost::asio::io_service io_Server;
extern boost::asio::io_service io_Apps;
extern SHP_Socket outer_Socket;
extern SHP_Socket inner_Socket;

class MGCPcontrol
{
public:
	MGCPcontrol();

	void Preprocessing(SHP_MGCP);
private:
	SHP_EventAnn annControl;
	SHP_EventCnf cnfControl;
};
typedef shared_ptr<MGCPcontrol> SHP_MGCPcontrol;