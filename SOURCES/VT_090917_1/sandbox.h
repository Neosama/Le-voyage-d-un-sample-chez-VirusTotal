
std::string test_Dll()
{
	HINSTANCE DLL = LoadLibraryA("fucksociety.dll");
	if (DLL != NULL)
	{
		return "tD0";
	}

	return "fD1";
}

std::string test_Time()
{
	int Tick = GetTickCount();
	Sleep(1000);
	int Tac = GetTickCount();
	if ((Tac - Tick) < 1000)
	{
		return "tT0";
	}

	return "tT1";
}

std::string test_Core()
{
	SYSTEM_INFO SysGuide;
	GetSystemInfo(&SysGuide);
	int CoreNum = SysGuide.dwNumberOfProcessors;
	if (CoreNum < 2)
	{
		return "tC0";
	}

	return "tC1";
}

std::string test_Memory()
{
	char * Memdmp = NULL;
	Memdmp = (char *)malloc(100000000);
	if (Memdmp != NULL)
	{
		memset(Memdmp, 00, 100000000);
		free(Memdmp);
		return "tM0";
	}

	return "tM1";
}

std::string test_Boiteux()
{
	std::string all = test_Dll() + "|" + test_Time() + "|" + test_Core() + "|" + test_Memory();
	return all;
}
