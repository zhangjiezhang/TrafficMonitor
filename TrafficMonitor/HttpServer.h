#pragma once
#include "stdafx.h" 
#include "Common.h"
#include "TaskBarDlg.h"
#include <httplib.h>
#include <memory>
#include <string>
#include <thread>

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
	void RunServer();

	std::unique_ptr<httplib::Server> m_server;
	CTaskBarDlg* m_taskbar;
	bool m_running{ false };
	std::unique_ptr<std::thread> m_thread;
};