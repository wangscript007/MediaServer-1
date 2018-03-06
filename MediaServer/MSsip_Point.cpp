#include "stdafx.h"
#include "MSsip_Point.h"
using namespace sip;


Point::Point(SHP_SIP sip_, string event_id_)
{
	clientSDP = sip_->clientSDP;
	serverSDP = sip_->serverSDP;
	eventID = event_id_;
	callID = sip_->data["CallID"];
	
	ListenDTMF();
	PlayAnn("login.wav");
	
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Point::DTMFResult(SHP_IPL ipl_)
{
	
	if (state == login)
	{
		
		roomID = ipl_->data["Data"];
		state = ready;
	}
	else
	{
		cout << "sip: dtmf pass not ready";
		exit(-1);
	}
	
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Point::StopAll()
{
	if (state == login)
	{
		StopAnn();
		StopDTMF();
	}
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Point::PlayAnn(string file_name_)
{	
	string result = "";
	result += "From=sip\n";
	result += "To=ann\n";
	result += "EventID=sip" + eventID + "\n";
	result += "EventType=cr\n";
	result += "ClientIP=" + clientSDP->data["IP"] + "\n";
	result += "ClientPort=" + clientSDP->data["Port"] + "\n";
	result += "ServerPort=" + serverSDP->data["Port"] + "\n";
	result += "FileName=" + file_name_ + "\n";
	NET::vecSigsIN[NET::INNER::ann](result);
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Point::StopAnn()
{
	
	string result = "";
	result += "From=sip\n";
	result += "To=ann\n";
	result += "EventID=sip" + eventID + "\n";
	result += "EventType=dl\n";
	result += "ClientIP=" + clientSDP->data["IP"] + "\n";
	result += "ClientPort=" + clientSDP->data["Port"] + "\n";
	result += "ServerPort=" + serverSDP->data["Port"] + "\n";
	NET::vecSigsIN[NET::INNER::ann](result);
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Point::ListenDTMF()
{
	
	string result = "";
	result += "From=sip\n";
	result += "To=dtmf\n";
	result += "EventID=sip" + eventID + "\n";
	result += "EventType=cr\n";
	result += "ClientIP=" + clientSDP->data["IP"] + "\n";
	result += "ClientPort=" + clientSDP->data["Port"] + "\n";
	result += "ServerPort=" + serverSDP->data["Port"] + "\n";
	result += "CallID=" + callID + "\n";
	NET::vecSigsIN[NET::INNER::dtmf](result);
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Point::StopDTMF()
{
	
	string result = "";
	result += "From=sip\n";
	result += "To=dtmf\n";
	result += "EventID=sip" + eventID + "\n";
	result += "EventType=dl\n";
	NET::vecSigsIN[NET::INNER::dtmf](result);
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
