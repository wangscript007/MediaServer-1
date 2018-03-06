#pragma once
#include "stdafx.h"
#include "MGCPparser.h"
#include "MGCPcontrol.h"

extern SHP_STARTUP init_Params;
extern SHP_NETDATA net_Data;

class MGCPServer
{
public:
	MGCPServer();
	void Run();
	void Receive(boost::system::error_code, size_t);
private:
	SHP_MGCPcontrol mgcpManagement;
	REQUEST message = (REQUEST());
};