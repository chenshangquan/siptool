#pragma once


/*
	消息处理接口
*/
class ISipToolMsgManager : public Singleton<ISipToolMsgManager>
{
public:
	ISipToolMsgManager(){}
	virtual ~ISipToolMsgManager(){}
/** 广播消息 
 *  @param[in] tMsgParam 消息结构体 
 *  @node 
 *  @return 是否成功
 */
	virtual void SendMsg(TMsgParam& tMsgParam) = 0;
/** 广播消息 异步
 *  @param[in] tMsgParam 消息结构体 
 *  @node 
 *  @return 是否成功
 */
	virtual void PostMsg(TMsgParam& tMsgParam) = 0;
/** 添加/删除观察者 
 *  @param[in] 
 *  @node 
 *  @return 是否成功
 */
	virtual void AddObserver(IObserver_MsgPrama* pOb) = 0;
	virtual void RemoveObserver(IObserver_MsgPrama* pOb) = 0;
	virtual void AddWindowObserver(HWND hwnd) = 0;
	virtual void RemoveWindowObserver(HWND hwnd) = 0;
};

template<> ISipToolMsgManager* Singleton<ISipToolMsgManager>::ms_pSingleton  = 0;



class CSipToolMsgManager : public ISipToolMsgManager
{
public:
	CSipToolMsgManager(void);
	~CSipToolMsgManager(void);

	virtual void SendMsg(TMsgParam& tMsgParam);
	virtual void PostMsg(TMsgParam& tMsgParam);
	virtual void AddObserver(IObserver_MsgPrama* pOb);
	virtual void RemoveObserver(IObserver_MsgPrama* pOb);
	virtual void AddWindowObserver(HWND hwnd);
	virtual void RemoveWindowObserver(HWND hwnd);
protected:
	typedef map<HWND, IObserver_MsgPrama*> WndObMap;

	WndObMap m_mapWndObs;
	CMsgManager m_cMsgManager;
};

