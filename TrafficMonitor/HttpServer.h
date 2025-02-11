#pragma once
#include "stdafx.h" 
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