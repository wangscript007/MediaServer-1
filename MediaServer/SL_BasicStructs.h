#pragma once
#include "stdafx.h"
#include "SL_Logs.h"


struct REQUEST
{
	EP sender;
	char data[2048];
};
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
struct RTP
{
	/* ������ ���� */
	uint8_t csrc_len : 4;//
	uint8_t extension : 1;//
	uint8_t padding : 1;//
	uint8_t version : 2;//
	/* ������ ���� */
	uint8_t payload_type : 7;//
	uint8_t marker : 1;//
	/* ������-��������� ����� */
	uint16_t seq_no;
	/* �����-������� ����� */
	uint32_t timestamp;//
	/* �������-����������� ���� */
	uint32_t ssrc;//
};
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
struct RTP_struct
{
	RTP header;
	long TS;
	int amount;

	RTP_struct();
	void Config();
	RTP Get();
};
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
struct Data
{
	uint8_t data[1000];
	int size = 160;
};
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
class SOCK
{
public:
	SOCK(string, int, SHP_IO);

	void ChangeIO(SHP_IO);
	~SOCK();

	RTP_struct rtp;
	SHP_IO io;
	boost::asio::ip::udp::socket s;
};
typedef shared_ptr<SOCK> SHP_SOCK;
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------