#pragma once
#include "stdafx.h"
#include "SharedLib.h"


namespace cnf
{
	class CnfPoint
	{
	public:
		CnfPoint(string, string, string, string);
		~CnfPoint();

		void SetMaxTimesTook(int);
		SHP_FRAME GetFrame();
		void StoreFrame(SHP_FRAME);

		string clientPort;
		string clientIP;
		string serverPort; //ID of point
		string serverIP;
		AVCodecContext* iccx;
		AVCodecContext* occx;
		SHP_SOCK socket;
		RTP_struct rtp;
		EP endPoint;

	private:
		void InitCodec(AVCodecContext**, bool);//true-decoder, false-encoder

		int timesTookMax = 0;
		int timesTook = 0;
		SHP_FRAME bufFrame = nullptr;
	};
	typedef shared_ptr<CnfPoint> SHP_CnfPoint;
}