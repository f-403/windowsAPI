#include <iostream>
#include <Windows.h>
#pragma comment(lib,"Netapi32.lib")
#include <LM.h>

int main() {
	SetConsoleOutputCP(CP_UTF8);
	std::locale::global(std::locale(""));
	NET_API_STATUS status;
	LPWSTR username = NULL;
	LPSESSION_INFO_10 lpsession=nullptr;
	DWORD read=0, total=0, resume_hand=0;
	status = NetSessionEnum(NULL,
		NULL,
		username,
		10,
		(LPBYTE*)&lpsession,
		MAX_PREFERRED_LENGTH,
		&read,
		&total,
		&resume_hand);
	if ((status == NERR_Success) || (status == ERROR_MORE_DATA)) {
		std::wcout << L"成功获取会话信息" << std::endl;
		std::wcout << L"共找到 " << read << L" 个会话" << std::endl;
		if (lpsession != NULL) {
			std::wcout << L"client:" << lpsession->sesi10_cname;
			std::wcout << L"user:" << lpsession->sesi10_username;
			std::wcout << L"active:" << lpsession->sesi10_time;
			std::wcout << L"dle:" << lpsession->sesi10_idle_time;
		}
	}

}