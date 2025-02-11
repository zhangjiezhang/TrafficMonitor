#pragma once
// ���� SSL/HTTPS ֧��
#define CPPHTTPLIB_OPENSSL_SUPPORT 0
// ���� Zlib ֧��
#define CPPHTTPLIB_ZLIB_SUPPORT 0
// ���� Brotli ֧��
#define CPPHTTPLIB_BROTLI_SUPPORT 0
// ʹ�� WinHTTP ���
#define CPPHTTPLIB_USE_WINHTTP 1
// ���� WinSock ������������
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Common.h"
#include "TaskBarDlg.h"
#include <httplib.h>
#include <memory>
#include <string>

class CHttpServer
{
public:
	CHttpServer(CTaskBarDlg* taskbar);
	~CHttpServer();

	bool Start(int port = 12555);
	void Stop();

private:
	void SetupRoutes();
	std::string GetMetricsJson();

	std::unique_ptr<httplib::Server> m_server;
	CTaskBarDlg* m_taskbar;
	bool m_running{ false };
};