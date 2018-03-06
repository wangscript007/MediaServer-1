#pragma once
#include "stdafx.h"
#include "Structs.h"
#include "Functions.h"
#include "MusicStore.h"
#include "Ann.h"
using namespace std;

extern SHP_IPar init_Params;

//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
class Control
{
public:
	Control();
	void Preprocessing(SHP_IPL);


private:
	void CR(SHP_IPL);
	void DL(SHP_IPL);

	SHP_Ann FindAnn(SHP_IPL);
	void RemoveAnn(SHP_Ann);

	vector<SHP_Ann> vecAnn;
	SHP_MusicStore musicStore;
};
typedef shared_ptr<Control> SHP_Control;