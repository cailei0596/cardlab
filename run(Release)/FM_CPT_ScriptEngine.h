#ifndef __FMCSE_API_H__
#define __FMCSE_API_H__

//**************************************************************************//
//																			//
//	请参阅文档《复微安全与识别应用平台—通用脚本引擎二次开发接口规范.doc》	//
//			此文档对此头文件的接口函数有详细的说明							//
//																			//
//**************************************************************************//

#include "FM_Define.h"

#include <string>

#ifdef FMCSE_EXPORTS
#define FMCSE_API __declspec(dllexport)
#else
#define FMCSE_API __declspec(dllimport)
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#define CALL_CONV __stdcall
//#define CALL_CONV __cdecl

#ifdef __cplusplus
#define EXTERN_C extern "C" 
#else
#define EXTERN_C extern 
#endif // __cplusplus

#define COMPONENT_CONTAINER_NAME "ComponentContainer"
//脚本引擎日志
#define COMPONENT_LOG_NAME				"log"
//业务日志
#define COMPONENT_BUSINESS_LOG_NAME		"BusinessLog"

//模块id的最大长度
#define MODULE_ID_MAX_LEN  65

/**
 * @brief  步进模式
 */
enum enSTEP_MODE{
	STEP_GO_ON,	///< 遇断点才停(相当于VC中F5)
	//如果是sub调用或call调用
	//执行sub调用或call模块后在sub调用或call语句的下一条语句暂停,遇断点停
	//相当于VC中F10
	STEP_OVER,	
	//步入, 遇到sub,进入sub语句块内单步执行
	//相当于F11
	STEP_INTO,	
	//步出,在sub内执行时,
	//使用该命令后执行sub内的语句在sub调用的下一条语句暂停,遇断点停
	//相当于shift+F11
	STEP_OUT,
};

/*
 *@brief 运行模式
 */
enum SCRIPT_EXECUTE_MODE
{
	SEM_EXEC_NORMAL	= 0,	///< 脚本在正常模式下执行,遇断点不停
	SEM_DBG_NORMAL	= 1, 	///< 以正常调试模式启动, 遇断点停
	SEM_DBG_STEP	= 2,	///< 以单步调试模式启动, 停在开始模块的第一条可执行语句
};

//系统模块默认名称
#define SYSTEM_MODULE_DEFAULT_NAME "CSE_SysSubs.dat"

//环境变量名称--系统模块文件路径
#define ENVI_NAME_SYSTEM_MODULE_PATH	"%SystemModulePath"
//环境变量类型
enum ENVI_VAR_TYPE
{
	EVT_INT = 1	,
	EVT_HEX		,
	EVT_STR		
};
//协议处理器类型
enum CARD_PROTOCOL_TYPE
{
	CARD_PROTOCOL_7816 = 0,
	CARD_PROTOCOL_DESFIRE
};

//用于执行结束时通知执行结果
typedef int (__stdcall *PFCallbackExcuteEnd)(FMSTATUS exeResult);

//用于Callback语句的回调函数
typedef int (__stdcall *PFCallbackAction)(FMINT nLineNo,FMSTATUS exeResult, const FMUCHAR* pActionCode, FMINT nActionCodeLen);//

//用于获取脚本或LoadFile语句
typedef int (__stdcall *PFCallbackGetScriptText)(FMCSTR szScriptFileName, FMSTR szScriptText, FMINT textSize, FMINT* needSize);

//用于获取脚本或LoadFile语句
typedef int (__stdcall *PFCallbackGetScriptTextEx)(FMCSTR szScriptFileName, FMSTR szScriptText, FMINT textSize, FMINT* needSize, FMCHAR scriptId[MODULE_ID_MAX_LEN]);

typedef struct stNotificationWrap{
	FMINT len;		//通知中的数据长度
	FMUCHAR const* data;	//通知中的数据
}NotificationWrap;

//用于解析、执行过程中的事件通知
typedef int ( __stdcall *PFCallbackNotify)(FMINT wParam, FMINT lParam);

/**
 * @brief	获取脚本引擎版本号
 * @param[in] major 主版本号
 * @param[in] minor 次版本号
 * @return  
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_GetVersion(FMINT* major, FMINT* minor);

/**
 * @brief	设置环境变量
 * @param[in] name 环境变量名
 * @param[in] type 环境变量类型
 * @param[in] value  环境变量值
 * @return  FM_OK--成功, 否则返回错误码
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetEnviroment(FMCSTR name, ENVI_VAR_TYPE type, FMCSTR value);
/*
 * @brief	设置卡片协议类型,内部默认为CARD_PROTOCOL_7816.
 * @param[in] cpt 卡片协议类型
 * @return FM_OK--成功, 否则返回错误码
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetCardProtocol(CARD_PROTOCOL_TYPE cpt);
/**
 * @brief	增加系统脚本
 * @param[in] sysScriptFile 系统脚本路径, 引擎解析时使用脚本内容读取函数获取其内容
 * @return  FM_OK--成功, 否则返回错误码
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_AddSystemModule(FMCSTR sysScriptFile);

/**
 * @brief	设置脚本内容读取函数
 * @param[in] pfGetScriptEx 脚本读取函数指针
 * @return  FM_OK--成功, 否则返回错误码
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetScriptReader(PFCallbackGetScriptTextEx pfGetScriptEx);

/**
 * @brief	新增全局变量定义
 * @param[in] name 全局变量名
 * @param[in] type 全局变量类型
 * @param[in] value  全局变量值
 * @return  FM_OK--成功, 否则返回错误码
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_AddGlobalVarDefine(FMCSTR name, ENVI_VAR_TYPE type, FMCSTR value);
/**
 * @brief	清除全局变量定义
 * @param[in] 
 * @param[in] 
 * @return  
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_ClearGlobalVarDefine();
/**
 * @brief	获取最后一次的错误(未实现)
 * @param[in] pOutErrInfo  错误描述,最小长度256(源自COST的实现)
 * @param[in] nOutErrLine  错误行号
 * @return  最后一次错误的错误号
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetLastError(FMSTR pOutErrInfo = NULL,FMINT* nOutErrLine = NULL);

/**
 * @brief	设置通知回调函数
 * @param[in] reserved  保留
 * @param[in] pNotify 通知回调函数指针
 * @return  是否设置成功
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetNotify(FMINT reserved, PFCallbackNotify pNotify);

/**
 * @brief	关联组件给脚本引擎
 * @param[in] thisHandle 脚本引擎实例句柄, 脚本引擎只有一个实例,该参数被忽略,请设置NULL
 * @param[in] alias 组件别名, 用于脚本引擎识别组件的用途. =COMPONENT_CONTAINER_NAME, 
              脚本引擎认为该组件是组件实例
 * @param[in] module  实例所在模块句柄
 * @param[in] handle  实例句柄, 
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 该接口只有alias == COMPONENT_CONTAINER_NAME时有效,脚本引擎会保留module参数,thisHandle和handle被忽略
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_SC_Attach(void* thisHandle, FMCSTR  alias
												 ,  void*  module, void* handle);
/**
 * @brief	加载脚本
 * @deprecated 不再推荐使用该接口. 推荐使用FM_CSE_LoadEx
 * @param[in] szScriptText 脚本内容
 * @param[in] pfGetScript  用于读取脚本文件(比如:call语句中需要读取脚本文件)
 * @return  FM_OK--成功, 否则返回错误码
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_Load(FMCSTR szScriptText,PFCallbackGetScriptText pfGetScript = NULL);

/**
 * @brief	加载脚本
 * @param[in] szScriptId   脚本id
 * @param[in] szScriptText 脚本内容
 * @param[in] pfGetScript  用于读取脚本文件(比如:call语句中需要读取脚本文件)
 * 为NULL时使用FM_CSE_SetScriptReader接口设置的读取函数
 * @return  FM_OK--成功, 否则返回错误码
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_LoadEx(FMCSTR szScriptId, FMCSTR szScriptText,PFCallbackGetScriptTextEx pfGetScriptEx = NULL);

/**
 * @brief	加载脚本文件
 * @deprecated 不再推荐使用该接口. 推荐使用FM_CSE_LoadFileEx
 * @param[in] szScriptFileName  文件名
 * @param[in] pfGetScript  用于读取脚本文件(比如:szScriptFileName的文件,或call语句读取文件)
 * @return  FM_OK--成功, 否则返回错误码
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_LoadFile(FMCSTR szScriptFileName,PFCallbackGetScriptText pfGetScript = NULL);

/**
 * @brief	加载脚本文件
 * @param[in] szScriptFileName  文件名
 * @param[in] pfGetScriptEx  用于读取脚本文件(比如:szScriptFileName的文件,或call语句读取文件), 
 * 为NULL时使用FM_CSE_SetScriptReader接口设置的读取函数
 * @return  FM_OK--成功, 否则返回错误码
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_LoadFileEx(FMCSTR szScriptFileName,PFCallbackGetScriptTextEx pfGetScriptEx = NULL);

/**
 * @brief	解析脚本内容
 * @param[in] sync true--同步解析脚本, false--异步解析脚本
 * @return  false--失败, 否则成功
 * @remark  每一行的解析结果通过PFCallbackNotify回调函数通知给脚本引擎使用者
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_Parse(FMBOOL sync = FM_TRUE);

/**
 * @brief	同步执行脚本
 * @param[in] pfAction  执行Callback语句时的回调函数指针
 * @return  false--失败, 否则成功
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_Execute(PFCallbackAction pfAction = NULL);

/**
 * @brief	异步执行脚本
 * @deprecated 不推荐使用该接口, 请使用FM_CSE_AsyncExec接口 
 * @param[in] bContinue  true--连续执行,false--单步执行
 * @param[in] pfAction  执行Callback语句时的回调函数指针
 * @param[in] pfExeEnd  执行完成时的回调函数指针
 * @return  true--启动执行线程成功, false--启动执行线程失败
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_ExecuteStart(FMBOOL bContinue, PFCallbackAction pfAction = NULL, PFCallbackExcuteEnd pfExeEnd = NULL);

/**
 * @brief	异步执行脚本
 * @param[in] execMode  执行模式, @see enum SCRIPT_EXECUTE_MODE
 * @param[in] pfAction  执行Callback语句时的回调函数指针
 * @param[in] pfExeEnd  执行完成时的回调函数指针
 * @return  FM_OK--成功, 否则返回错误码
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_AsyncExec(SCRIPT_EXECUTE_MODE execMode, PFCallbackAction pfAction = NULL, PFCallbackExcuteEnd pfExeEnd = NULL);

/**
 * @brief	设置执行模式,在断点或通知回调中调用
 * @param[in] execMode  执行模式, @see enum SCRIPT_EXECUTE_MODE
 * @return  FM_OK--成功, 否则返回错误码
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetExecMode(SCRIPT_EXECUTE_MODE execMode);

/**
 * @brief	用于断点或单步执行模式下继续执行下一条语句
 * @param[in] execMode 执行模式
 * @return  void
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_ResumeExec(enSTEP_MODE setpCmd);

/**
 * @brief	暂停执行过程
 * @return  void
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_PauseExecute();

/**
 * @brief	停止执行过程
 * @return  void
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_StopExecute();

/**
 * @brief	强制终止执行过程
 * @return  void
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_TerminateExec();

/**
 * @brief	设置默认的读卡器实例名称
 * @param[in] readerName 读卡器实例名称, == NULL时忽略该参数
 * @return  void
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_SetDefaultReader(FMCSTR readerName);
/**
 * @brief	设置默认的国密计算器实例名称
 * @param[in] smName 国密计算器实例名称, == NULL时忽略该参数
 * @param[in] pcscName PCSC实例名称,该实例是国密计算器实例必需的, == NULL时忽略该参数
 * @return  void
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_SetDefaultSM(FMCSTR smName, FMCSTR pcscName);

//===========================================================================================================//
/**
 * @brief	获取int类型变量值
 * @param[in] szVarName  变量名
 * @param[out] outVarValue  变量值
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetVariableInt(FMCSTR szVarName,FMINT* outVarValue );

/**
 * @brief	设置int类型变量值
 * @param[in] szVarName  变量名
 * @param[in] nValue  变量值
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetVariableInt(FMCSTR szVarName,FMINT nValue  );

/**
 * @brief	获取hexstr类型变量值
 * @param[in] szVarName  变量名
 * @param[out] outVarValue  变量值
 * @param[out] outLen  变量值长度
 * @param[in]  bufferLen outVarValue缓冲区长度
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetVariableHexstr(FMCSTR szVarName, FMUCHAR* outVarValue,FMINT* outLen, FMINT bufferLen);

/**
 * @brief	设置hexstr类型变量值
 * @param[in] szVarName  变量名
 * @param[in] pValue  变量值缓冲区指针
 * @param[in] nLen    变量值缓冲区长度
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetVariableHexstr(FMCSTR szVarName,const FMUCHAR* pValue,FMINT nLen  );

/**
 * @brief	获取string类型变量值
 * @param[in] szVarName  变量名
 * @param[out] outVarValue  变量值
 * @param[in,out] outLen  变量值长度
 * @param[in]  bufferLen outVarValue缓冲区长度
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetVariableString(FMCSTR szVarName, FMSTR outVarValue,FMINT* outLen, FMINT bufferLen);

/**
 * @brief	设置string类型变量值
 * @param[in] szVarName  变量名
 * @param[in] pValue  变量值缓冲区指针, 内容应是'\0'结尾的字符串
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetVariableString(FMCSTR szVarName,FMCSTR pValue);

/**
 * @brief	设置/清除一个断点
 * @param[in] szModuleId  模块标识
 * @param[in] lineNo		源代码的行号,索引从1开始
 * @param[in] flag			=0时清除断点,=1时设置断点
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetBreakpoint(FMCSTR szModuleId,int lineNo, int flag);

/**
 * @brief  删除所有断点
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_ClearAllBreakpoints();

/**
 * @brief	获取当前栈帧上的栈顶变量表
 * @param[out] vtSerializedData 变量表序列化后的数据,使用fmcse::VariableTable的ParseFromString解析
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetCurrentVariableTable(std::string& vtSerializedData);
/**
 * @brief	获取当前栈帧上的变量表
 * @param[in]  blockId 块id
 * @param[out] vtSerializedData 变量表序列化后的数据,使用fmcse::VariableTable的ParseFromString解析
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetParentVariableTable(FMUINT blockId, std::string& vtSerializedData);
/**
 * @brief	获取调用堆栈
 * @param[out] csSerializedData 调用堆栈序列化后的数据,使用@see fmcse::CallStackNotification解析
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetCallStacks(std::string& csSerializedData);

/**
 * @brief	获取调用堆栈深度
 * @param[out] depth 调用堆栈的深度
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetCallStackDepth(FMUINT* depth);

/**
 * @brief	获取某一栈帧上的栈顶变量表
 * @param[in] depth 栈帧深度, 范围[0, FM_CSE_GetCallStackDepth出参的值)
 * @param[in] serializedData,变量表序列化后的数据, @see fmcse::VariableTable
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetTopVariableTableInFrame(
	FMUINT depth
	, std::string& serializedData);
/**
 * @brief	获取某一栈帧上的变量表
 * @param[in] depth 栈帧深度, 范围[0, FM_CSE_GetCallStackDepth出参的值)
 * @param[in] blockId 块号, fmcse::VariableTable的parentId
 * @param[in] serializedData,变量表序列化后的数据, @see fmcse::VariableTable
 * @return  FM_OK--成功, 否则返回错误码
 * @remark 在断点或执行暂停时使用
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetPreVariableTableInFrame(
	FMUINT depth
	, FMUINT blockId
	, std::string& serializedData);
////////////////////////////////////////////////////////////////

/*
 * @brief	获取定义源位置
 * @param[in] searching 查找字串(现只支持SUB调用语句)
 * @param[out] scriptId	返回定义所在的模块的ID
 * @param[out] line_no 定义所在行的行号
 * @return FM_OK--成功, 否则返回错误码
 * @remark 
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetDefinitionPos(
	FMCSTR searching
	, FMCHAR scriptId[MODULE_ID_MAX_LEN]
	, FMUINT* line_no
	);

////////////////////////////////////////////////////////////////

#endif //__FMCSE_API_H__