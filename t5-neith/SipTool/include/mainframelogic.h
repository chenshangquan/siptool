/** @defgroup 主窗口逻辑单元 
 *  @version V1.0.0
 *  @author  csq
 *  @date    2019.4.25
 */
#if !defined(AFX_NETWORKSETUP_H_)
#define AFX_NETWORKSETUP_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EmCfgCtrlTabID
{
	emTabID_CascadeCfg = 0,
	emTabID_NeighborCfg,
	emTabID_LocalAreaNumCfg,
};

class CMainFrameLogic : public CNotifyUIImpl, public Singleton<CMainFrameLogic> 
{
public:
	CMainFrameLogic();
	~CMainFrameLogic();

public:
    // 显示遮罩窗口
    //bool OnShowShadeWindow(LPCTSTR lpstrName = g_stcStrShadeDlg.c_str(), bool bShow = true);

    // 显示提示信息
    void ShowTip(CString strTip);

protected:
    /** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

	/** 初始化消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnInit(TNotifyUI& msg);

    /** 关闭消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnDestroy(TNotifyUI& msg);

	//点击退出按钮
	bool OnExitBtnClicked(TNotifyUI& msg);
    //点击最小化按钮
    bool OnMinBtnClicked(TNotifyUI& msg);
    //点击关闭按钮
    bool OnCloseBtnClicked(TNotifyUI& msg);

	//级联配置
	bool OnTabCascadeCfg(TNotifyUI& msg);
	//邻居配置
	bool OnTabNeighborCfg(TNotifyUI& msg);
	//本地区号配置
	bool OnTabLocalAreaNumCfg(TNotifyUI& msg);

    //Siptool connected
    bool OnSipToolConnected(WPARAM wparam, LPARAM lparam, bool& bHandle);
    //登陆注销
    bool OnSipToolLogout(WPARAM wparam, LPARAM lparam, bool& bHandle);

    //显示提示定时器响应
    bool OnShowTipTimer(TNotifyUI& msg);

    APP_DECLARE_MSG_MAP()

private:
    //配置条目栏切换
    void SwitchCfgTabWnd( EmCfgCtrlTabID emSelCfgTabID );
    //配置项是否被修改
    bool IsCfgModify();

private:
    bool                  m_bLogin;          //是否登陆成功
    EmCfgCtrlTabID        m_emLastCfgTabID;  //上一选中的TabID

};

void showtip(CString strTip);
#define SHOWTIP showtip

#endif // !defined(AFX_NETWORKSETUP_H_)