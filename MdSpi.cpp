// MdSpi.cpp
#include <iostream>
#include "MdSpi.h"
using namespace std;

extern CThostFtdcMdApi* g_pMdUserApi;

void MdSpi::OnFrontConnected()
{
	cout << "�����������ӳɹ�" << endl;
	// ��ʼ��¼
	CThostFtdcReqUserLoginField loginReq;
	memset(&loginReq, 0, sizeof(loginReq));
	strcpy(loginReq.BrokerID, "9999");
	strcpy(loginReq.UserID, "000000");			// �޸�Ϊ���Լ���
	strcpy(loginReq.Password, "123456");		// �޸�Ϊ���Լ���
	static int requestID = 0;
	int result = g_pMdUserApi->ReqUserLogin(&loginReq, ++requestID);
	if (!result)
		cout << "���͵�¼����ɹ�" << endl;
	else
		cerr << "���͵�¼����ʧ��" << endl;
}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		cout << "�˻���¼�ɹ�" << endl;
		cout << "�����գ� " << pRspUserLogin->TradingDay << endl;
		// ��ʼ��������												
		char** ppInstrumentID = new char* [50];						
		ppInstrumentID[0] = "cu2108";								
		g_pMdUserApi->SubscribeMarketData(ppInstrumentID, 1);
	}
	else
		cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
}

void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		cout << "��������ɹ�" << endl;
		cout << "��Լ���룺 " << pSpecificInstrument->InstrumentID << endl;
	}
	else
		cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
}

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	cout << "=====����������ɹ�====="  << endl;
	// ����������д���ļ�
	cout << "��Լ���룺" << pDepthMarketData->InstrumentID << endl;
	cout << "���¼ۣ�" << pDepthMarketData->LastPrice << endl;
	cout << "�ɽ�����" << pDepthMarketData->Volume << endl;
}
