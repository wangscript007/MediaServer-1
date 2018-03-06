#pragma once
#include "../SharedSource/stdafx.h"
#include "../SharedSource/Structs.h"
#include "../SharedSource/Functions.h"

extern SHP_STARTUP init_Params;

class MediaFile
{
public:
	MediaFile(string);

	SHP_PACKET GetPacket(int);
	int Size();

	string fileName;
	string error = "";
private:
	int OpenFile();
	void CutPackets(vector<SHP_PACKET>);

	vector<SHP_PACKET> data;
};
typedef shared_ptr<MediaFile> SHP_MediaFile;
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
class MusicStore
{
public:
	SHP_MediaFile GetFile(string);
private:
	SHP_MediaFile OpenNewFile(string);
	vector<SHP_MediaFile> data;
};
typedef shared_ptr<MusicStore> SHP_MusicStore;