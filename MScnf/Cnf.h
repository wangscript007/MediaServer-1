#pragma once
#include "stdafx.h"
#include "CnfPoint.h"
#include "Audio.h"
namespace cnf
{
	class Cnf
	{
	public:
		Cnf(SHP_IPL);
		~Cnf();

		void MD(SHP_IPL);
		void DL(SHP_IPL);

		string cnfID;
	private:
		void ParsePoints(SHP_IPL);
		void AddRmPoint(vector<string>);
		void CreatePoints(vector<vector<string>>);

		SHP_Audio mixerAudio;
		vector<SHP_CnfPoint> vecPoints;
		//boost::asio::io_service ioCnf;
	};
	typedef shared_ptr<Cnf> SHP_Cnf;
}