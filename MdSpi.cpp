// MdSpi.cpp
#include <iostream>
#include "MdSpi.h"
using namespace std;

extern CThostFtdcMdApi* g_pMdUserApi;

void MdSpi::OnFrontConnected()
{
	cout << "建立网络连接成功" << endl;
	// 开始登录
	CThostFtdcReqUserLoginField loginReq;
	memset(&loginReq, 0, sizeof(loginReq));
	strcpy(loginReq.BrokerID, "9999");
	strcpy(loginReq.UserID, "000000");			// 修改为你自己的
	strcpy(loginReq.Password, "123456");		// 修改为你自己的
	static int requestID = 0;
	int result = g_pMdUserApi->ReqUserLogin(&loginReq, ++requestID);
	if (!result)
		cout << "发送登录请求成功" << endl;
	else
		cerr << "发送登录请求失败" << endl;
}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		cout << "账户登录成功" << endl;
		cout << "交易日： " << pRspUserLogin->TradingDay << endl;
		// 开始订阅行情												
		char** ppInstrumentID = new char* [50];						
		ppInstrumentID[0] = "cu2108";								
		g_pMdUserApi->SubscribeMarketData(ppInstrumentID, 1);
	}
	else
		cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
}

void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		cout << "订阅行情成功" << endl;
		cout << "合约代码： " << pSpecificInstrument->InstrumentID << endl;
	}
	else
		cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
}

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	cout << "=====获得深度行情成功====="  << endl;
	// 可以在这里写入文件
	cout << "合约代码：" << pDepthMarketData->InstrumentID << endl;
	cout << "最新价：" << pDepthMarketData->LastPrice << endl;
	cout << "成交量：" << pDepthMarketData->Volume << endl;
}
