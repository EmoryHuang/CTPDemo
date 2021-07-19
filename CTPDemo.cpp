#include <iostream>
#include "MdSpi.h"
using namespace std;
#pragma comment (lib, "thostmduserapi_se.lib")								// 链接库

CThostFtdcMdApi* g_pMdUserApi = nullptr;									// 行情指针

int main()
{
	// 初始化行情线程
	g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();						// 创建行情实例
	CThostFtdcMdSpi* pMdUserSpi = new MdSpi;								// 创建行情回调实例
	g_pMdUserApi->RegisterSpi(pMdUserSpi);									// 注册事件类
	g_pMdUserApi->RegisterFront((char*)"tcp://180.168.146.187:10211");		// 设置行情前置地址
	g_pMdUserApi->Init();													// 连接运行
	// 等到线程退出
	g_pMdUserApi->Join();
	return 0;
}