/*****************************************************************************
模块名      : CNC控制台
文件名      : cncConst.h
相关文件    : 
文件实现功能: 声明常量和错误代码,供cnc的UI部分和cnclib部分共同使用
作者        : 
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期       版本        修改人      修改内容
2014/12/20   1.4         肖楚然        创建
******************************************************************************/
#pragma once

#ifndef _SIPTOOLCONST_20190410_H_
#define _SIPTOOLCONST_20190410_H_

#include "kdvtype.h"
#include <map> 
using namespace std;

#define CONNETCT_SIPSERVER_PORT      60600                                     //sip服务器端口号 

#define PrtSipToolMsg (CSipToolPrintCtrl::GetPrintCtrl()->PrintMsg)                        //打印Curl消息接口
#define SIPTOOLMAPPING_HELPER (CSipToolPrintCtrl::GetPrintCtrl()->MappingHelper)                  //注册打印的消息名

//------------------------------错误码部分------begin-------------------------------
/*终端控制台错误(27501 - 29500)*/
#define ERR_BGN		100
#define ERR_END		ERR_BGN + 1999

#define MAX_AREACODE_LENGTH          5
#define MAX_IP_LENGTH               16
#define MAX_ALIAS_LENGTH            32
#define MAX_SEARCH_TIME             10000

//SipToolLib中的错误码
enum EmErrSipToolLib
{

#define ERR_SIPTOOL_LIB_BEGIN  ERR_BGN

    // 控制台错误
    errsiptool = ERR_SIPTOOL_LIB_BEGIN,
#define ERR_SIPTOOL                                 errsiptool

	// 控制台错误
	err_siptool_creatinstance,
#define ERR_SIPTOOL_CREATINSTANCE                    err_siptool_creatinstance

    // 实例无效
    errInterface,
#define ERR_SIPTOOL_INTERFACE                        errInterface

    //osp 初始化失败
    errOspInit,
#define  ERR_OSP_INIT                                errOspInit

    //已连接上
    errActiveConnect,
#define	ERR_SIPTOOL_ACTIVE_CONNECT                   errActiveConnect

    //TCP连接失败
    errTcpConnect,
#define	ERR_SIPTOOL_TCPCONNECT                       errTcpConnect


	errSipToolLibEnd,
#define ERR_SIPTOOL_LIB_END                         errSipToolLibEnd
		
};
 
#endif
