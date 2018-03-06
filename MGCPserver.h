#pragma once
#include "stdafx.h"
#include "Logger.h"
#include "MGCPControl.h"
#include "Functions.h"
#include "Parser.h"
#include "ConfRoom.h"
/************************************************************************
	CMGCPServer
************************************************************************/
class MGCPControl;
extern string DateStr;
extern Logger* CLogger;
class CMGCPServer
{
public:
	

	MGCPControl* MGCPConference;
	

	enum Event_type { mgcp };
	enum { max_length = 2048 };

	struct TArgs
	{
		asio::io_service&		io_service; 
		const udp::endpoint&	MGCPendpnt;
		string					strMmediaPath;
	};
	struct MGCPdata
	{
		SHP_Socket socket;
		MGCP data;
		std::mutex  mutex_;
		std::queue<MGCP> Que;
	};
	
	CMGCPServer(const TArgs&);
	const udp::endpoint& EndP_Local() const { return m_args.MGCPendpnt; }
	void RunBuffer();
	void Run();
	void reply(const string&, const udp::endpoint&, Event_type);

	int GetFreePort();
	void SetFreePort(int port);

	TArgs	m_args;
private:
/*�������*/
	void loggit(string a);

/*��������� ��������� ������*/
	void receive_h(boost::system::error_code, size_t, Event_type);
	void proceedReceiveBuffer();
	MGCPdata MGCPst;
	udp::endpoint sender_endpoint_;
	

	//std::mutex  mutex_;
	asio::io_service& io_service__;
	
	//std::queue<MGCP> Que;
};

