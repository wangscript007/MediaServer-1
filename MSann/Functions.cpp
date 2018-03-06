#include "stdafx.h"
#include "Functions.h"


//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//�������� ����� ���������� �����
string get_substr(string target_, string aim_, string fin_)
{//target_ - ������ ��������, aim_ - ������, fin - �����
	auto fd_pos = target_.find(aim_);
	string result = "";
	if (fd_pos != string::npos)
		result = target_.substr(fd_pos + aim_.length(), target_.find(fin_, fd_pos + aim_.length()) - (fd_pos + aim_.length()));
	return result;
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//�������� ��������� ������
string cut_substr(string target_, string aim_, string fin_)
{
	auto fd_pos = target_.find(aim_);
	string result = "";
	if (fd_pos != string::npos)
		result = target_.substr(fd_pos, target_.find(fin_, fd_pos + 1) - (fd_pos - 1)); //(fd_pos-1) last char too
	return result;
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//������� �� ������ ��� ���������
string remove_from_str(string target_, string aim_)
{//target_ - ������, aim_ - ���
	size_t fd_pos;
	while ((fd_pos = target_.find(aim_)) != string::npos)
	{
		target_ = target_.erase(fd_pos, fd_pos + aim_.length() - 1);
	}
	return target_;
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//�������� � ������ ��� ���������
string replace_in_str(string target_, string what_, string to_what_)
{//target_ - ������, what_ - ���, to_what_ - �� ���
	size_t fd_pos = 0;
	vector<size_t> vec_pos;
	vec_pos.push_back(-1);
	while ((fd_pos = target_.find(what_, fd_pos + 1)) != string::npos)
	{
		vec_pos.push_back(fd_pos);
	}
	for (int i = vec_pos.size() - 1; i > 0; --i)
	{
		target_ = target_.replace(vec_pos[i], what_.length() + 1, to_what_);
	}
	return target_;
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void init_ffmpeg()
{
	BOOST_LOG_SEV(lg, trace) << "init_ffmpeg()";
	av_log_set_level(0);
	av_register_all();
	avcodec_register_all();
	avfilter_register_all();
	avformat_network_init();
	BOOST_LOG_SEV(lg, trace) << "init_ffmpeg(): DONE";
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void LogsInit()
{
	logging::add_file_log
		(
		keywords::auto_flush = true,
		keywords::file_name = init_Params->data[IPar::homePath] + "\\logs\\%Y-%m-%d_ANN.log",                                        /*< file name pattern >*/
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 1), /*< ...or at midnight >*/
		keywords::format = "[%TimeStamp%]:[%ThreadID%] %Message%",                                 /*< log record format >*/
		keywords::open_mode = std::ios_base::app
		);
	logging::core::get()->set_filter(logging::trivial::severity >= stoi(init_Params->data[IPar::logLevel]));
	logging::add_common_attributes();
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------