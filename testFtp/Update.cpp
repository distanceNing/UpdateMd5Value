// Update.cpp : 定义控制台应用程序的入口点。
//编译中遇到了“无法解析的外部符号”的错误，在以下链接中找到了解决方法--->在‘预处理’中加入两条宏
// http://www.cnblogs.com/ytjjyy/archive/2012/05/19/2508803.html

#include "manage.h"
// TODO
// 目前的自更新程序虽然可以下载所有最新程序组件
// 但是因为自己本身也属于软件的一部分，所以不能替换自己


// 一直计划写一个独立的程序，读取需要替换的文件列表并执行文件替换操作
// 突然想到，可以在程序中加入一个 ‘windows 替换脚本’生成方案
// 只要本程序成功下载了所有文件，就生成一个脚本，脚本替换完成后，由脚本开启服务

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
	dir = "D:\\项目\\cloudmonitor\\Release\\";
	dir64 = "D:\\项目\\cloudmonitor\\x64\\Release\\";

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
