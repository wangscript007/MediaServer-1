#pragma once
#include "stdafx.h"
#include "SharedLib.h"
#include "MSsip_SIPparser.h"


namespace sip
{
	class Point
	{
	public:

		enum State{ login, pass, ready, paused };
		Point(SHP_SIP, string, string, string);

		void DTMFResult(SHP_IPL);
		void SQLResult(SHP_IPL);

		void PlayAnn(string);
		void StopAnn();
		void ListenDTMF();
		void StopDTMF();
		void SQLCheck(string);
		void StopAll();

		string serverSDP;
		string clientSDP;
		string serverPort;
		string clientPort;
		string clientIP;
		string callID;

		string eventID;
		string roomID;

		int state = login;
	private:

		string GetIPfromSDP(string);
		string GetPortFromSDP(string);

	};
	typedef shared_ptr<Point> SHP_Point;
}