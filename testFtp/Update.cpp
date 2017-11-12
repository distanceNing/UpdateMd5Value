// Update.cpp : �������̨Ӧ�ó������ڵ㡣
//�����������ˡ��޷��������ⲿ���š��Ĵ����������������ҵ��˽������--->�ڡ�Ԥ�����м���������
// http://www.cnblogs.com/ytjjyy/archive/2012/05/19/2508803.html

#include "manage.h"
// TODO
// Ŀǰ���Ը��³�����Ȼ���������������³������
// ������Ϊ�Լ�����Ҳ���������һ���֣����Բ����滻�Լ�


// һֱ�ƻ�дһ�������ĳ��򣬶�ȡ��Ҫ�滻���ļ��б�ִ���ļ��滻����
// ͻȻ�뵽�������ڳ����м���һ�� ��windows �滻�ű������ɷ���
// ֻҪ������ɹ������������ļ���������һ���ű����ű��滻��ɺ��ɽű���������

#include <vector>
#include <string>
using std::string;
using std::vector;
int main(int argc, char *argv[])
{
	char buffer[1024] = { '\0' };
	vector<string> fileList{
		"autoStart.exe",
		"CloudMonitor.exe",
		"Daemon.exe",
		"HooKeyboard.dll",
		"MonitorService.exe",
		"RemoveSelf.exe",
		"Service.exe",
		"Uninstall.exe",
};
	string update = "update";
	_mkdir(update.c_str());
	string hashListPath = update + "\\hashlist.txt";
	FILE* fp = fopen(hashListPath.c_str(), "w");
	string dir,dir64;
	dir = "D:\\��Ŀ\\cloudmonitor\\Release\\";
	dir64 = "D:\\��Ŀ\\cloudmonitor\\x64\\Release\\";

	vector<string> file64List{
		"HooKeyboard-64.dll",
		"MonitorService-64.exe",
	};
	for (int i = 0;i < file64List.size();++i)
	{
		std::string md5Value;
		string filePath = dir64 + file64List[i];
		GetFileMd5(filePath, md5Value);
		snprintf(buffer, 1024, "%s %s\n", md5Value.c_str(), file64List[i].c_str());
		string newFilePath = update + "\\" + file64List[i];
		CopyFileA(filePath.c_str(), newFilePath.c_str(), false);
		fwrite(buffer, 1, strlen(buffer), fp);
		std::cout << buffer;
		memset(buffer, '\0', 1024);
	}
	
		


	for (int i = 0;i < fileList.size();++i)
	{
		std::string md5Value;
		string filePath = dir + fileList[i];
		GetFileMd5(filePath, md5Value);
		snprintf(buffer, 1024, "%s %s\n", md5Value.c_str(), fileList[i].c_str());
		string newFilePath = update + "\\" + fileList[i];
		CopyFileA(filePath.c_str(), newFilePath.c_str(), false);
		fwrite(buffer, 1, strlen(buffer), fp);
		std::cout << buffer;
		memset(buffer, '\0', 1024);
	}

	time_t start_time = time(0);
	struct tm* tm = localtime(&start_time);
	snprintf(buffer, 1024, "update time: %d-%d-%d %d:%d\n", 1900+tm->tm_year, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min);
	std::cout << buffer;
	fwrite(buffer, 1, strlen(buffer), fp);
	fclose(fp);
	
	//win xp update
	update = "update_winxp";
	_mkdir(update.c_str());
	hashListPath = update + "\\hashlist.txt";
	FILE* fp_winxp = fopen(hashListPath.c_str(), "w");
	dir = "D:\\shared\\Release\\";
	for (int i = 0;i < fileList.size();++i)
	{
		memset(buffer, '\0', 1024);
		std::string md5Value;
		string filePath = dir + fileList[i];
		GetFileMd5(filePath, md5Value);
		snprintf(buffer, 1024, "%s %s\n", md5Value.c_str(), fileList[i].c_str());
		string newFilePath = update + "\\" + fileList[i];
		CopyFileA(filePath.c_str(), newFilePath.c_str(), false);
		fwrite(buffer, 1, strlen(buffer), fp_winxp);
		std::cout << buffer;
		
	}
	memset(buffer, '\0', 1024);
	start_time = time(0);
	tm = localtime(&start_time);
	snprintf(buffer, 1024, "update time: %d-%d-%d %d:%d\n", 1900 + tm->tm_year, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);
	std::cout << buffer;
	fwrite(buffer, 1, strlen(buffer), fp_winxp);
	fclose(fp_winxp);
	
	return 0;
}
