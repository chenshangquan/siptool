#include "stdafx.h"
#include <string>
#include "siptoolsession.h"
#include "siptoolmsgrecver.h"
#include "siptoolsysctrl.h"
#include "siptoolprintctrl.h"
#include "json.h"

#pragma comment(lib, "lib_json.lib")

//线程函数
DWORD WINAPI GetConfTempThread(LPVOID pParam);

CSipToolSession::CSipToolSession():m_bInitOsp(FALSE)
{
    InitializeOsp();
    SetAppId( AID_SIPTOOL_APP );

    m_pSysCtrlIf = NULL;
   
    //在该类中，new出所有的功能类，外部通过接口GetInterface()获取
    #define NEW_REG(pCtrlIF, clsName)         \
    pCtrlIF = new clsName(*this);     \
    RegHandler(pCtrlIF);

    NEW_REG( m_pSysCtrlIf, CSipToolSysCtrl );
}

CSipToolSession::~CSipToolSession()
{

}

u16 CSipToolSession::InitializeOsp()
{
    // 初始化OSP
    const u32 dwTelnetPort = 0;
    if( !IsOspInitd() )
    {

        BOOL bTelnet  = FALSE ;

#ifdef _DEBUG
        bTelnet = TRUE;
#endif

        if(!OspInit( bTelnet, dwTelnetPort))
        {
            return ERR_OSP_INIT;
        }
        else
        {
            m_bInitOsp = FALSE;
        }
    }
    else
    {
        m_bInitOsp = TRUE;
    }

    char szOspApp[] = "SipToolLib";
    const u32 dwPrior = 80;
    int nRet = g_SipToolApp.CreateApp(&szOspApp[0], AID_SIPTOOL_APP, dwPrior, 300, 200);
    ASSERT(nRet == 0);

    PrtSipToolMsg( "SipToolLib osp启动成功\n" );

    return NO_ERROR;
}

/*获取接口指针*/
u16 CSipToolSession::SipGetInterface(CSipToolSysCtrlIF **ppCtrl)
{
    if( m_pSysCtrlIf != NULL)
    {
        *ppCtrl = m_pSysCtrlIf;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_SIPTOOL;
    }
}


/*功    能： 是否已和CNS建立了连接*/
BOOL CSipToolSession::IsConnectedSip()
{
    //return g_SipToolApp.GetNodeId() != INVALID_NODE;
	return GetNodeId() != INVALID_NODE;
}

/*功    能： 连接*/
u16 CSipToolSession::ConnectSip(u32 dwIP, u32 dwPort, char* strUser, char* strPwd, BOOL32 bConnect /* = TRUE */)
{
    // 建立TCP连接
    if( IsConnectedSip() )
    { 
        //如何已经登录了该IP，则直接返回，否则断开重连
		/*if ( dwIP == m_dwSipIp )
		{
			return ERR_SIPTOOL_ACTIVE_CONNECT;
		}
		else
		{
			DisconnectSip();
			return ERR_SIPTOOL_ACTIVE_CONNECT;
		}*/
        
    }
    
    //ClearDisp();
    // 重构消息分发表
    //BuildEventsMap();
    
    //建立Osp的TCP连接,得到本地机器的IP地址
	u32 dwCnNodeId = 0;
    u32 dwLocalIp = 0;
	if ( bConnect )
	{
		dwCnNodeId = OspConnectTcpNode( htonl(dwIP), static_cast<u16>(dwPort), 5 , 3, 5000, &dwLocalIp );
		if( dwCnNodeId == INVALID_NODE )
		{
			return ERR_SIPTOOL_TCPCONNECT;
		}		
	}
	else
	{
		dwCnNodeId = 0;
	}

    //g_SipToolApp.SetNodeId( dwCnNodeId );
    SetNodeId( dwCnNodeId );
    //设置在node连接中断时需通知的appid和InstId
    ::OspNodeDiscCBReg( dwCnNodeId, AID_SIPTOOL_APP, 0);

    // 登陆消息封装发送
    Json::Value jsLoginInfo;
    jsLoginInfo["user"] = strUser;
    jsLoginInfo["password"] = strPwd;
    in_addr tAddr;
    tAddr.S_un.S_addr = dwLocalIp;
    jsLoginInfo["ClientIP"] = inet_ntoa(tAddr);

    string strLoginInfo = jsLoginInfo.toStyledString();
    CSipToolMsgDriver::s_pMsgDriver->PostCMsg(MULTIPLEREGSIGN, (char*)strLoginInfo.c_str(), strlen(strLoginInfo.c_str()));
    
	return NO_ERROR;
}

/*功    能： 断开Sip连接*/
u16 CSipToolSession::DisconnectSip()
{
    if( !IsConnectedSip() )
    {
        return NO_ERROR;
    }

    //OspDisconnectTcpNode(g_SipToolApp.GetNodeId()); 
    OspDisconnectTcpNode(GetNodeId()); 
	m_dwSipIp = 0;
    
    return NO_ERROR;
}

void CSipToolSession::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CSipToolSession, cMsg);
}

void CSipToolSession::OnTimeOut(u16 wEvent)
{ 
}


