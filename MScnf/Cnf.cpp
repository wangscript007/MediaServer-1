#include "stdafx.h"
#include "Cnf.h"

//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
Cnf::Cnf(SHP_IPL ipl_)
{
	BOOST_LOG_SEV(lg, trace) << "Cnf::Cnf(...) id=" << ipl_->data[IPL::eventID];
	cnfID = ipl_->data[IPL::eventID];
	BOOST_LOG_SEV(lg, trace) << "Cnf::Cnf(...):ParsePoints(ipl_);";
	ParsePoints(ipl_);
	BOOST_LOG_SEV(lg, debug) << "Cnf::Cnf(...): mixerAudio.reset(new Audio(vecPoints));";
	mixerAudio.reset(new Audio(vecPoints));
	BOOST_LOG_SEV(lg, debug) << "Cnf::Cnf(...) DONE";
}
Cnf::~Cnf()
{
	BOOST_LOG_SEV(lg, debug) << "Cnf::~Cnf() id=" << cnfID;
	vecPoints.clear(); 
	mixerAudio.reset();
	BOOST_LOG_SEV(lg, debug) << "Cnf::~Cnf() DONE";
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Cnf::MD(SHP_IPL ipl_)
{
	BOOST_LOG_SEV(lg, trace) << "Cnf::MD(...) id=" << cnfID<<"->mixerAudio->Stop();";
	mixerAudio->Stop();
	BOOST_LOG_SEV(lg, debug) << "Cnf::MD(...)AddRmPoint(...) points was " << vecPoints.size();
	AddRmPoint({
		ipl_->data[IPL::clientPort],
		ipl_->data[IPL::serverPort],
		ipl_->data[IPL::clientIP]
	});
	BOOST_LOG_SEV(lg, debug) << "Cnf::MD(...) points now " << vecPoints.size();
	mixerAudio->MD(vecPoints);
	//mixerAudio->Stop();mixerAudio.reset(new Audio(vecPoints));
	BOOST_LOG_SEV(lg, trace) << "Cnf::MD(...) DONE";
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Cnf::DL(SHP_IPL ipl_)
{
	BOOST_LOG_SEV(lg, trace) << "Cnf::DL(...)";
	mixerAudio->Stop();
	BOOST_LOG_SEV(lg, trace) << "Cnf::DL(...) DONE";
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Cnf::ParsePoints(SHP_IPL ipl_)
{
	BOOST_LOG_SEV(lg, trace) << "Cnf::ParsePoints(...)";
	vector<vector<string>> points_params;
	points_params.resize(3);

	string client_ports = ipl_->data[IPL::clientPort];
	string server_ports = ipl_->data[IPL::serverPort];
	string client_IPs = ipl_->data[IPL::clientIP];
	size_t fd=0;
	while (fd != string::npos)
	{
		fd = client_ports.find(" ");
		points_params[0].push_back(client_ports.substr(0, fd));
		BOOST_LOG_SEV(lg, debug) << "Cnf::ParsePoints(...) port=" << client_ports.substr(0, fd);
		if (fd == string::npos) break;
		client_ports = client_ports.substr(fd+1);
	}fd = 0;
	
	while (fd != string::npos)
	{
		fd = server_ports.find(" ");
		points_params[1].push_back(server_ports.substr(0, fd));
		BOOST_LOG_SEV(lg, debug) << "Cnf::ParsePoints(...) port=" << server_ports.substr(0, fd);
		if (fd == string::npos) break;
		server_ports = server_ports.substr(fd+1);
	}fd = 0;
	while (fd != string::npos)
	{
		fd = client_IPs.find(" ");
		points_params[2].push_back(client_IPs.substr(0, fd));
		BOOST_LOG_SEV(lg, debug) << "Cnf::ParsePoints(...) port=" << client_IPs.substr(0, fd);
		if (fd == string::npos) break;
		client_IPs = client_IPs.substr(fd+1);
	}fd = 0;

	BOOST_LOG_SEV(lg, trace) << "Cnf::ParsePoints(...) DONE";
	CreatePoints(points_params);
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Cnf::CreatePoints(vector<vector<string>> data_)
{
	BOOST_LOG_SEV(lg, trace) << "Cnf::CreatePoints(...)";
	for (int i = 0; i < (int)data_[0].size(); ++i)
		vecPoints.push_back(
		make_shared<CnfPoint>(
		data_[0][i], 
		data_[1][i], 
		data_[2][i], 
		init_Params->data[IPar::outerIP],
		ioCnf
		));
	BOOST_LOG_SEV(lg, trace) << "Cnf::CreatePoints(...) DONE";
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Cnf::AddRmPoint(vector<string> params_)
{
	BOOST_LOG_SEV(lg, trace) << "Cnf::AddRmPoint(...)";
	for (int i = 0; i < (int)vecPoints.size(); ++i)
	{
		if (vecPoints[i]->serverPort == params_[1])
		{
			BOOST_LOG_SEV(lg, debug) << "Cnf::AddRmPoint(...) erase point with serverport=" << vecPoints[i]->serverPort;
			vecPoints.erase(remove(vecPoints.begin(), vecPoints.end(), vecPoints[i]), vecPoints.end());
			return;
		}
	}
	vecPoints.push_back(
		make_shared<CnfPoint>(
		params_[0],
		params_[1],
		params_[2],
		init_Params->data[IPar::outerIP],
		ioCnf
		));
	BOOST_LOG_SEV(lg, debug) << "Cnf::AddRmPoint(...) added point with serverport=" << vecPoints[vecPoints.size() - 1]->serverPort << " DONE";
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------