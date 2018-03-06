#pragma once
#include "stdafx.h"

extern string DateStr;
class MGCP
{
public:
	//func
	MGCP(string);
	MGCP() {}
	~MGCP()
	{
		
	}
	string ResponseOK(int code, string end);
	std::string ResponseBAD(int code, string message);
	void Parse(bool);

	enum Eventor {ann, cnf, prx};
	int error;
	char mes[2049];
	udp::endpoint sender;

	//data
	std::string mgcp;
	std::string CMD;//
	Eventor Event;

	std::string EventS; //cnf/,ann/,prx/
	std::string EventNum;//cnf/n
	std::string EventEx;//cnf/1@[10.77.7.19]
	std::string paramM;
	std::string paramL;
	std::string paramI;
	std::string paramZ;
	std::string paramC;
	std::string paramS;
	std::string MessNum;
	std::string SDP;
private:
	
	void parseCMD();
	void EventP();
	void ParamM();
	void ParamC();
	void Remove();
	bool Valid();	
};
typedef shared_ptr<MGCP> SHP_MGCP;