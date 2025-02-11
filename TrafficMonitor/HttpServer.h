#pragma once
// 禁用 SSL/HTTPS 支持
#define CPPHTTPLIB_OPENSSL_SUPPORT 0
// 禁用 Zlib 支持
#define CPPHTTPLIB_ZLIB_SUPPORT 0
// 禁用 Brotli 支持
#define CPPHTTPLIB_BROTLI_SUPPORT 0
// 使用 WinHTTP 后端
#define CPPHTTPLIB_USE_WINHTTP 1
// 禁用 WinSock 废弃函数警告
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