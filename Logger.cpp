#include "stdafx.h"
#include "Logger.h"

void Logger::OpenLogFiles()
{
	using namespace boost;
	gregorian::date TODAY = gregorian::day_clock::local_day();
	std::string date = to_string(TODAY.day().as_number()) + "-" + to_string(TODAY.month().as_number()) + "-" + to_string(TODAY.year()) + "_";
	std::string tempPath = PathEXE + date;

	std::vector<std::string> path;
	/*0*/path.push_back(tempPath + "LOGS_main.txt");
	/*1*/path.push_back(tempPath + "LOGS_ConfRoom.txt");
	/*2*/path.push_back(tempPath + "LOGS_Mixer.txt");
	/*3*/path.push_back(tempPath + "LOGS_Server.txt");
	/*4*/path.push_back(tempPath + "LOGS_MixerInit.txt");
	/*5*/path.push_back(tempPath + "LOGS_Ann.txt");
	/*6*/path.push_back(tempPath + "LOGS_ConfControl.txt");
	for (unsigned i = 0; i < path.size(); ++i)
	{
		file.push_back(CreateFileA(
			path[i].c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)
			);
		if (file[i] == INVALID_HANDLE_VALUE)
		{
			printf("ERROR %x \n", GetLastError());
			std::cout << "\nRELOAD NEEDED. LOG ERROR";//messagebox
		}
		filesize.push_back(0);
		time_t rawtime;
		struct tm * t;
		time(&rawtime);
		t = localtime(&rawtime);
		std::string time = "";
		std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
		time += to_string(t->tm_year + 1900) + "." + to_string(t->tm_mon + 1) + "." + to_string(t->tm_mday) + "/" + to_string(t->tm_hour) + ":" + to_string(t->tm_min) + ":" + to_string(t->tm_sec) + "/" + to_string(t1.time_since_epoch().count() % 1000);
		output("Logs created on: " + time, i);
		std::vector<std::string> buf;
		buffer.push_back(buf);
	}
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Logger::Run()
{
	while (true)
	{
		for (unsigned i = 0; i < buffer.size(); ++i)
		{
			int size = buffer[i].size();
			if (size>0)
			{
				for (int k = 0; k < size; ++k)
				{
					output(pop(i, k), i);
				}
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Logger::output(std::string text, int i)
{
	WriteFile(file[i], (text).c_str(), (text).size(), &filesize[i], NULL);
	filesize[i] += (text).size();
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
std::string Logger::pop(int i, int j)
{
	std::string text;
	text = buffer[i][j];
	mutex_.lock();
	buffer[i].erase(buffer[i].begin());
	mutex_.unlock();
	return text;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Logger::AddToLog(unsigned type, std::string text)
{
	if (buffer.size() < type){ std::cout << "size!"; return; }
	mutex_.lock();
	buffer[type].push_back(text);
	mutex_.unlock();
}