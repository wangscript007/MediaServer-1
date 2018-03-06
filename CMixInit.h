#pragma once
#include "stdafx.h"
#include "Logger.h"
#include "Functions.h"
#include "Structs.h"
#define INPUT_SAMPLERATE     8000
//#define INPUT_SAMPLERATE     44100
#define INPUT_FORMAT         AV_SAMPLE_FMT_S16
#define INPUT_CHANNEL_LAYOUT AV_CH_LAYOUT_STEREO

/** The output bit rate in kbit/s */
#define OUTPUT_BIT_RATE 8000
/** The number of output channels */
#define OUTPUT_CHANNELS 1
/** The audio sample output format */
#define OUTPUT_SAMPLE_FORMAT AV_SAMPLE_FMT_S16

#define VOLUME_VAL 0.90
using boost::asio::ip::udp;
using namespace boost::asio;
using namespace std;

extern FILE *FileLogMixerInit;
extern Logger CLogger;
struct Initing;
//struct SSource;
struct NetworkData;

//typedef shared_ptr<CAVPacket> SHP_CAVPacket;

class CMixInit
{
public:
	CMixInit(){ tracks=0; }
	CMixInit(NetworkData net)
	{
		tracks = net.my_ports.size();
		net_ = net;
		init(net.input_SDPs);
	}
	Initing data;
	void FreeSockFFmpeg();//
private:
	void loggit(string a);
	int FirstInit();
	int init(vector<string> input_SDPs);

	int write_output_file_header(AVFormatContext *output_format_context);
	int write_output_file_trailer(AVFormatContext *output_format_context);
	int sdp_open(AVFormatContext **pctx, const char *data, AVDictionary **options);
	int init_filter_graph(int ForClient);
	int open_input_file(const char *sdp_string, int i);
	int open_output_file(const char *filename, int i);

	int tracks;

	NetworkData net_;
};
typedef std::shared_ptr<CMixInit> SHP_CMixInit;