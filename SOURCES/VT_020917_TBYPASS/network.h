
// Network Lib

std::string http_request(const char* hostname, int port, const char* agent, const char* verb, const char* obj_name,char szReq[1024], const char* hearders) // verb = GET/POST/...., obj_name = PATH URL, szReq = POST Param(OBS), hearders = Content-Type: text/html
{
	HINTERNET hIntSession = ::InternetOpenA(agent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	HINTERNET hHttpSession = InternetConnectA(hIntSession, hostname, port, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
	HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, verb, obj_name, 0, 0, 0, INTERNET_FLAG_RELOAD, 0);
	if( !HttpSendRequestA(hHttpRequest, hearders, strlen(hearders), szReq, strlen(szReq))) {
		DWORD dwErr = GetLastError();
	}
	std::string result = "";
	CHAR szBuffer[1025];
	DWORD dwRead=0;
	while(::InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer)-1, &dwRead) && dwRead) { 
		szBuffer[dwRead] = 0;
		OutputDebugStringA(szBuffer);
		dwRead=0;
		result += std::string(szBuffer);
	}
	::InternetCloseHandle(hHttpRequest);
	::InternetCloseHandle(hHttpSession);
	::InternetCloseHandle(hIntSession);
	return result;
}
