#include "stdafx.h"
#include "HttpServer.h"
// https://github.com/nlohmann/json
#include "json/json.hpp"

using json = nlohmann::json;

CHttpServer::CHttpServer(CTaskBarDlg* taskbar)
    : m_taskbar(taskbar)
{
    m_server = std::make_unique<httplib::Server>();
}

CHttpServer::~CHttpServer()
{
    Stop();
}

bool CHttpServer::Start(int port)
{
    if (m_running) return true;

    SetupRoutes();

    m_thread = std::make_unique<std::thread>(&CHttpServer::RunServer, this);
    m_running = true;
    return true;
}

void CHttpServer::Stop()
{
    if (!m_running) return;

    m_server->stop();
    if (m_thread && m_thread->joinable())
    {
        m_thread->join();
    }
    m_running = false;
}


// 设置 HTTP 路由
void CHttpServer::SetupRoutes()
{
    // 设置 /metrics 路由返回性能指标数据
    m_server->Get("/metrics", [this](const httplib::Request&, httplib::Response& res) {
        res.set_header("Content-Type", "application/json");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.body = GetMetricsJson();
    });
}

void CHttpServer::RunServer()
{
    if (!m_server->listen("0.0.0.0", 12555)) {
        // 处理错误
        m_running = false;
    }
}

std::string CHttpServer::GetMetricsJson()
{
    json metrics;

    // 从应用程序实例获取CPU和内存使用率
    metrics["cpu_usage"] = theApp.m_cpu_usage;
    metrics["memory_usage"] = theApp.m_memory_usage;

    // 从任务栏对话框获取网络速度
    if (m_taskbar != nullptr)
    {
        metrics["up_speed"] = theApp.m_out_speed;
        metrics["down_speed"] = theApp.m_in_speed;
    }
    else
    {
        metrics["up_speed"] = 0;
        metrics["down_speed"] = 0;
    }

    // 添加额外的系统信息
    metrics["total_memory"] = theApp.m_total_memory;
    metrics["used_memory"] = theApp.m_used_memory;

    if (theApp.m_general_data.IsHardwareEnable(HI_CPU))
    {
        metrics["cpu_temperature"] = theApp.m_cpu_temperature;
        metrics["cpu_freq"] = theApp.m_cpu_freq;
    }

    if (theApp.m_general_data.IsHardwareEnable(HI_GPU))
    {
        metrics["gpu_usage"] = theApp.m_gpu_usage;
        metrics["gpu_temperature"] = theApp.m_gpu_temperature;
    }

    if (theApp.m_general_data.IsHardwareEnable(HI_HDD))
    {
        metrics["hdd_temperature"] = theApp.m_hdd_temperature;
    }

    return metrics.dump();
}