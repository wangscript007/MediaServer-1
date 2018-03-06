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
		result = target_.substr(fd_pos + aim_.size(), target_.find(fin_, fd_pos + aim_.size() - 1) - (fd_pos + aim_.size()));
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
		result = target_.substr(fd_pos, target_.find(fin_, fd_pos + 1) - (fd_pos-1)); //(fd_pos-1) last char too
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
		target_ = target_.erase(fd_pos, fd_pos + aim_.size() - 1);
	}
	return target_;
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//�������� � ������ ��� ���������
string replace_in_str(string target_, string what_, string to_what_)
{//target_ - ������, what_ - ���, to_what_ - �� ���
	size_t fd_pos=0;
	vector<size_t> vec_pos;
	vec_pos.push_back(-1);
	while ((fd_pos = target_.find(what_, fd_pos + 1)) != string::npos)
	{
		vec_pos.push_back(fd_pos);
	}
	for (int i = vec_pos.size() - 1; i > 0; --i)
	{
		target_ = target_.replace(vec_pos[i], what_.size() + 1, to_what_);
	}
	return target_;
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
void ReplyClient(SHP_MGCP mgcp_, string str_)
{
	cout << "\nReply is:\n" + str_+"_\n=======================================================================";//DEBUG
	outer_Socket->s.send_to(boost::asio::buffer(str_), mgcp_->sender);
}
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------
//*///------------------------------------------------------------------------------------------