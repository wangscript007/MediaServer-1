#pragma once
#include "stdafx.h"
#include "Structs.h"
#include "Functions.h"
#include "EventBase.h"
#include "MGCPparser.h"
#include "Ann.h"

using namespace std;

extern SHP_IPar init_Params;
extern SHP_NETDATA net_Data;





class EventAnn :EventBase
{
public:
	void CRCX(SHP_MGCP);
	void RQNT(SHP_MGCP);
	void DLCX(SHP_MGCP);

private:
	string CheckExistance(SHP_MGCP);
	SHP_Ann FindAnn(SHP_MGCP);
	void RemoveAnn(SHP_Ann);

	vector<SHP_Ann> vecAnn;
};
typedef shared_ptr<EventAnn> SHP_EventAnn;