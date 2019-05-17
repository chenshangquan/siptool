#include "StdAfx.h"
#include "system.h"


template<> CSystem* Singleton<CSystem>::ms_pSingleton  = NULL;
const String CSystem::strMainWindow		= _T("siptool");
const String CSystem::strSkin			= _T("skin");
const String CSystem::strDefaultSkin	= _T("skin\\");

const String g_stcStrMainFrameDlg = _T("siptool"); 
const String g_stcStrLoginDlg = _T("LoginDlg");
const String g_stcStrNetworkSetupDlg = _T("NetworkSetup");

CSystem::CSystem(void)
{
}

CSystem::CSystem(String strFile) : m_strFile(strFile)
{
	bool bRet = IniSystem();
}


CSystem::~CSystem(void)
{

}


bool CSystem::IniSystem()
{
	// 初始化消息管理器
	if (ISipToolMsgManager::GetSingletonPtr() == 0) new CSipToolMsgManager();

	String strValue = _T("");
	bool bRet = DOCMNGR()->GetDoc(m_strFile, strSkin, strValue);
	CPaintManagerUI::SetResourcePath( bRet ? strValue.c_str() : strDefaultSkin.c_str() );

    //是否自适应分辨率
    bRet = DOCMNGR()->GetDoc(m_strFile, _T("Resolution"), strValue);
    SIZE sizeSrc;
    SIZE sizeDst;
    sizeSrc.cx = 1100;
    sizeSrc.cy = 720;

    LPTSTR pstr = NULL;
    sizeDst.cx = _tcstol( (LPCTSTR)strValue.c_str(), &pstr, 10);  
    sizeDst.cy = _tcstol(pstr + 1, &pstr, 10);

    if ( (sizeDst.cx != sizeSrc.cx) || (sizeDst.cy != sizeSrc.cy ) )
    {
        CPaintManagerUI::SetSelfAdaption(true);
        CPaintManagerUI::SetAdpResolution( sizeSrc, sizeDst );
    }


	ISipToolCommonOp::RegLogics();

	return true;
}


bool CSystem::Launch()
{
	bool bRet;
	bRet = IWindowManager::GetSingletonPtr()->ShowWindowCenter(CSystem::strMainWindow.c_str());	
	if (bRet == true)
	{
		CPaintManagerUI::MessageLoop();
	}
	else
	{
		//PT_LOGEVENT("创建主程序窗口失败\n");
	}
	return false;
}