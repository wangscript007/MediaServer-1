#include "stdafx.h"
#include "MSreceiver.h"

Receiver::Receiver()
{
	Run();
	NET::outerIO->run();
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Receiver::Run()
{
	NET::GS(NET::OUTER::sip_)->s.async_receive_from(boost::asio::buffer(message.data, 2048), message.sender,
		boost::bind(&Receiver::ReceiveSIP, this, _1, _2));
	NET::GS(NET::OUTER::mgcp_)->s.async_receive_from(boost::asio::buffer(message.data, 2048), message.sender,
		boost::bind(&Receiver::ReceiveMGCP, this, _1, _2));
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Receiver::ReceiveSIP(boost::system::error_code ec_, size_t size_)
{
	NET::GS(NET::OUTER::sip_)->s.async_receive_from(boost::asio::buffer(message.data, 2048), message.sender,
		boost::bind(&Receiver::ReceiveSIP, this, _1, _2));
	if (size_ > 10) 
	{ 
		message.data[size_] = 0;
		NET::vecSigsOUT[NET::OUTER::sip_](message);
	}
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void Receiver::ReceiveMGCP(boost::system::error_code ec_, size_t size_)
{
	NET::GS(NET::OUTER::mgcp_)->s.async_receive_from(boost::asio::buffer(message.data, 2048), message.sender,
		boost::bind(&Receiver::ReceiveMGCP, this, _1, _2));
	if (size_ > 10)
	{
		message.data[size_] = 0;
		NET::vecSigsOUT[NET::OUTER::mgcp_](message);
	}
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
