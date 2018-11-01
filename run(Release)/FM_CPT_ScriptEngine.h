#ifndef __FMCSE_API_H__
#define __FMCSE_API_H__

//**************************************************************************//
//																			//
//	������ĵ�����΢��ȫ��ʶ��Ӧ��ƽ̨��ͨ�ýű�������ο����ӿڹ淶.doc��	//
//			���ĵ��Դ�ͷ�ļ��Ľӿں�������ϸ��˵��							//
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
//�ű�������־
#define COMPONENT_LOG_NAME				"log"
//ҵ����־
#define COMPONENT_BUSINESS_LOG_NAME		"BusinessLog"

//ģ��id����󳤶�
#define MODULE_ID_MAX_LEN  65

/**
 * @brief  ����ģʽ
 */
enum enSTEP_MODE{
	STEP_GO_ON,	///< ���ϵ��ͣ(�൱��VC��F5)
	//�����sub���û�call����
	//ִ��sub���û�callģ�����sub���û�call������һ�������ͣ,���ϵ�ͣ
	//�൱��VC��F10
	STEP_OVER,	
	//����, ����sub,����sub�����ڵ���ִ��
	//�൱��F11
	STEP_INTO,	
	//����,��sub��ִ��ʱ,
	//ʹ�ø������ִ��sub�ڵ������sub���õ���һ�������ͣ,���ϵ�ͣ
	//�൱��shift+F11
	STEP_OUT,
};

/*
 *@brief ����ģʽ
 */
enum SCRIPT_EXECUTE_MODE
{
	SEM_EXEC_NORMAL	= 0,	///< �ű�������ģʽ��ִ��,���ϵ㲻ͣ
	SEM_DBG_NORMAL	= 1, 	///< ����������ģʽ����, ���ϵ�ͣ
	SEM_DBG_STEP	= 2,	///< �Ե�������ģʽ����, ͣ�ڿ�ʼģ��ĵ�һ����ִ�����
};

//ϵͳģ��Ĭ������
#define SYSTEM_MODULE_DEFAULT_NAME "CSE_SysSubs.dat"

//������������--ϵͳģ���ļ�·��
#define ENVI_NAME_SYSTEM_MODULE_PATH	"%SystemModulePath"
//������������
enum ENVI_VAR_TYPE
{
	EVT_INT = 1	,
	EVT_HEX		,
	EVT_STR		
};
//Э�鴦��������
enum CARD_PROTOCOL_TYPE
{
	CARD_PROTOCOL_7816 = 0,
	CARD_PROTOCOL_DESFIRE
};

//����ִ�н���ʱִ֪ͨ�н��
typedef int (__stdcall *PFCallbackExcuteEnd)(FMSTATUS exeResult);

//����Callback���Ļص�����
typedef int (__stdcall *PFCallbackAction)(FMINT nLineNo,FMSTATUS exeResult, const FMUCHAR* pActionCode, FMINT nActionCodeLen);//

//���ڻ�ȡ�ű���LoadFile���
typedef int (__stdcall *PFCallbackGetScriptText)(FMCSTR szScriptFileName, FMSTR szScriptText, FMINT textSize, FMINT* needSize);

//���ڻ�ȡ�ű���LoadFile���
typedef int (__stdcall *PFCallbackGetScriptTextEx)(FMCSTR szScriptFileName, FMSTR szScriptText, FMINT textSize, FMINT* needSize, FMCHAR scriptId[MODULE_ID_MAX_LEN]);

typedef struct stNotificationWrap{
	FMINT len;		//֪ͨ�е����ݳ���
	FMUCHAR const* data;	//֪ͨ�е�����
}NotificationWrap;

//���ڽ�����ִ�й����е��¼�֪ͨ
typedef int ( __stdcall *PFCallbackNotify)(FMINT wParam, FMINT lParam);

/**
 * @brief	��ȡ�ű�����汾��
 * @param[in] major ���汾��
 * @param[in] minor �ΰ汾��
 * @return  
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_GetVersion(FMINT* major, FMINT* minor);

/**
 * @brief	���û�������
 * @param[in] name ����������
 * @param[in] type ������������
 * @param[in] value  ��������ֵ
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetEnviroment(FMCSTR name, ENVI_VAR_TYPE type, FMCSTR value);
/*
 * @brief	���ÿ�ƬЭ������,�ڲ�Ĭ��ΪCARD_PROTOCOL_7816.
 * @param[in] cpt ��ƬЭ������
 * @return FM_OK--�ɹ�, ���򷵻ش�����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetCardProtocol(CARD_PROTOCOL_TYPE cpt);
/**
 * @brief	����ϵͳ�ű�
 * @param[in] sysScriptFile ϵͳ�ű�·��, �������ʱʹ�ýű����ݶ�ȡ������ȡ������
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_AddSystemModule(FMCSTR sysScriptFile);

/**
 * @brief	���ýű����ݶ�ȡ����
 * @param[in] pfGetScriptEx �ű���ȡ����ָ��
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetScriptReader(PFCallbackGetScriptTextEx pfGetScriptEx);

/**
 * @brief	����ȫ�ֱ�������
 * @param[in] name ȫ�ֱ�����
 * @param[in] type ȫ�ֱ�������
 * @param[in] value  ȫ�ֱ���ֵ
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_AddGlobalVarDefine(FMCSTR name, ENVI_VAR_TYPE type, FMCSTR value);
/**
 * @brief	���ȫ�ֱ�������
 * @param[in] 
 * @param[in] 
 * @return  
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_ClearGlobalVarDefine();
/**
 * @brief	��ȡ���һ�εĴ���(δʵ��)
 * @param[in] pOutErrInfo  ��������,��С����256(Դ��COST��ʵ��)
 * @param[in] nOutErrLine  �����к�
 * @return  ���һ�δ���Ĵ����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetLastError(FMSTR pOutErrInfo = NULL,FMINT* nOutErrLine = NULL);

/**
 * @brief	����֪ͨ�ص�����
 * @param[in] reserved  ����
 * @param[in] pNotify ֪ͨ�ص�����ָ��
 * @return  �Ƿ����óɹ�
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetNotify(FMINT reserved, PFCallbackNotify pNotify);

/**
 * @brief	����������ű�����
 * @param[in] thisHandle �ű�����ʵ�����, �ű�����ֻ��һ��ʵ��,�ò���������,������NULL
 * @param[in] alias �������, ���ڽű�����ʶ���������;. =COMPONENT_CONTAINER_NAME, 
              �ű�������Ϊ����������ʵ��
 * @param[in] module  ʵ������ģ����
 * @param[in] handle  ʵ�����, 
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ýӿ�ֻ��alias == COMPONENT_CONTAINER_NAMEʱ��Ч,�ű�����ᱣ��module����,thisHandle��handle������
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_SC_Attach(void* thisHandle, FMCSTR  alias
												 ,  void*  module, void* handle);
/**
 * @brief	���ؽű�
 * @deprecated �����Ƽ�ʹ�øýӿ�. �Ƽ�ʹ��FM_CSE_LoadEx
 * @param[in] szScriptText �ű�����
 * @param[in] pfGetScript  ���ڶ�ȡ�ű��ļ�(����:call�������Ҫ��ȡ�ű��ļ�)
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_Load(FMCSTR szScriptText,PFCallbackGetScriptText pfGetScript = NULL);

/**
 * @brief	���ؽű�
 * @param[in] szScriptId   �ű�id
 * @param[in] szScriptText �ű�����
 * @param[in] pfGetScript  ���ڶ�ȡ�ű��ļ�(����:call�������Ҫ��ȡ�ű��ļ�)
 * ΪNULLʱʹ��FM_CSE_SetScriptReader�ӿ����õĶ�ȡ����
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_LoadEx(FMCSTR szScriptId, FMCSTR szScriptText,PFCallbackGetScriptTextEx pfGetScriptEx = NULL);

/**
 * @brief	���ؽű��ļ�
 * @deprecated �����Ƽ�ʹ�øýӿ�. �Ƽ�ʹ��FM_CSE_LoadFileEx
 * @param[in] szScriptFileName  �ļ���
 * @param[in] pfGetScript  ���ڶ�ȡ�ű��ļ�(����:szScriptFileName���ļ�,��call����ȡ�ļ�)
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_LoadFile(FMCSTR szScriptFileName,PFCallbackGetScriptText pfGetScript = NULL);

/**
 * @brief	���ؽű��ļ�
 * @param[in] szScriptFileName  �ļ���
 * @param[in] pfGetScriptEx  ���ڶ�ȡ�ű��ļ�(����:szScriptFileName���ļ�,��call����ȡ�ļ�), 
 * ΪNULLʱʹ��FM_CSE_SetScriptReader�ӿ����õĶ�ȡ����
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_LoadFileEx(FMCSTR szScriptFileName,PFCallbackGetScriptTextEx pfGetScriptEx = NULL);

/**
 * @brief	�����ű�����
 * @param[in] sync true--ͬ�������ű�, false--�첽�����ű�
 * @return  false--ʧ��, ����ɹ�
 * @remark  ÿһ�еĽ������ͨ��PFCallbackNotify�ص�����֪ͨ���ű�����ʹ����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_Parse(FMBOOL sync = FM_TRUE);

/**
 * @brief	ͬ��ִ�нű�
 * @param[in] pfAction  ִ��Callback���ʱ�Ļص�����ָ��
 * @return  false--ʧ��, ����ɹ�
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_Execute(PFCallbackAction pfAction = NULL);

/**
 * @brief	�첽ִ�нű�
 * @deprecated ���Ƽ�ʹ�øýӿ�, ��ʹ��FM_CSE_AsyncExec�ӿ� 
 * @param[in] bContinue  true--����ִ��,false--����ִ��
 * @param[in] pfAction  ִ��Callback���ʱ�Ļص�����ָ��
 * @param[in] pfExeEnd  ִ�����ʱ�Ļص�����ָ��
 * @return  true--����ִ���̳߳ɹ�, false--����ִ���߳�ʧ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_ExecuteStart(FMBOOL bContinue, PFCallbackAction pfAction = NULL, PFCallbackExcuteEnd pfExeEnd = NULL);

/**
 * @brief	�첽ִ�нű�
 * @param[in] execMode  ִ��ģʽ, @see enum SCRIPT_EXECUTE_MODE
 * @param[in] pfAction  ִ��Callback���ʱ�Ļص�����ָ��
 * @param[in] pfExeEnd  ִ�����ʱ�Ļص�����ָ��
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_AsyncExec(SCRIPT_EXECUTE_MODE execMode, PFCallbackAction pfAction = NULL, PFCallbackExcuteEnd pfExeEnd = NULL);

/**
 * @brief	����ִ��ģʽ,�ڶϵ��֪ͨ�ص��е���
 * @param[in] execMode  ִ��ģʽ, @see enum SCRIPT_EXECUTE_MODE
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetExecMode(SCRIPT_EXECUTE_MODE execMode);

/**
 * @brief	���ڶϵ�򵥲�ִ��ģʽ�¼���ִ����һ�����
 * @param[in] execMode ִ��ģʽ
 * @return  void
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_ResumeExec(enSTEP_MODE setpCmd);

/**
 * @brief	��ִͣ�й���
 * @return  void
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_PauseExecute();

/**
 * @brief	ִֹͣ�й���
 * @return  void
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_StopExecute();

/**
 * @brief	ǿ����ִֹ�й���
 * @return  void
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_TerminateExec();

/**
 * @brief	����Ĭ�ϵĶ�����ʵ������
 * @param[in] readerName ������ʵ������, == NULLʱ���Ըò���
 * @return  void
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_SetDefaultReader(FMCSTR readerName);
/**
 * @brief	����Ĭ�ϵĹ��ܼ�����ʵ������
 * @param[in] smName ���ܼ�����ʵ������, == NULLʱ���Ըò���
 * @param[in] pcscName PCSCʵ������,��ʵ���ǹ��ܼ�����ʵ�������, == NULLʱ���Ըò���
 * @return  void
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_SetDefaultSM(FMCSTR smName, FMCSTR pcscName);

//===========================================================================================================//
/**
 * @brief	��ȡint���ͱ���ֵ
 * @param[in] szVarName  ������
 * @param[out] outVarValue  ����ֵ
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetVariableInt(FMCSTR szVarName,FMINT* outVarValue );

/**
 * @brief	����int���ͱ���ֵ
 * @param[in] szVarName  ������
 * @param[in] nValue  ����ֵ
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetVariableInt(FMCSTR szVarName,FMINT nValue  );

/**
 * @brief	��ȡhexstr���ͱ���ֵ
 * @param[in] szVarName  ������
 * @param[out] outVarValue  ����ֵ
 * @param[out] outLen  ����ֵ����
 * @param[in]  bufferLen outVarValue����������
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetVariableHexstr(FMCSTR szVarName, FMUCHAR* outVarValue,FMINT* outLen, FMINT bufferLen);

/**
 * @brief	����hexstr���ͱ���ֵ
 * @param[in] szVarName  ������
 * @param[in] pValue  ����ֵ������ָ��
 * @param[in] nLen    ����ֵ����������
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetVariableHexstr(FMCSTR szVarName,const FMUCHAR* pValue,FMINT nLen  );

/**
 * @brief	��ȡstring���ͱ���ֵ
 * @param[in] szVarName  ������
 * @param[out] outVarValue  ����ֵ
 * @param[in,out] outLen  ����ֵ����
 * @param[in]  bufferLen outVarValue����������
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetVariableString(FMCSTR szVarName, FMSTR outVarValue,FMINT* outLen, FMINT bufferLen);

/**
 * @brief	����string���ͱ���ֵ
 * @param[in] szVarName  ������
 * @param[in] pValue  ����ֵ������ָ��, ����Ӧ��'\0'��β���ַ���
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetVariableString(FMCSTR szVarName,FMCSTR pValue);

/**
 * @brief	����/���һ���ϵ�
 * @param[in] szModuleId  ģ���ʶ
 * @param[in] lineNo		Դ������к�,������1��ʼ
 * @param[in] flag			=0ʱ����ϵ�,=1ʱ���öϵ�
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_SetBreakpoint(FMCSTR szModuleId,int lineNo, int flag);

/**
 * @brief  ɾ�����жϵ�
 */
EXTERN_C FMCSE_API void CALL_CONV FM_CSE_ClearAllBreakpoints();

/**
 * @brief	��ȡ��ǰջ֡�ϵ�ջ��������
 * @param[out] vtSerializedData ���������л��������,ʹ��fmcse::VariableTable��ParseFromString����
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetCurrentVariableTable(std::string& vtSerializedData);
/**
 * @brief	��ȡ��ǰջ֡�ϵı�����
 * @param[in]  blockId ��id
 * @param[out] vtSerializedData ���������л��������,ʹ��fmcse::VariableTable��ParseFromString����
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetParentVariableTable(FMUINT blockId, std::string& vtSerializedData);
/**
 * @brief	��ȡ���ö�ջ
 * @param[out] csSerializedData ���ö�ջ���л��������,ʹ��@see fmcse::CallStackNotification����
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetCallStacks(std::string& csSerializedData);

/**
 * @brief	��ȡ���ö�ջ���
 * @param[out] depth ���ö�ջ�����
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetCallStackDepth(FMUINT* depth);

/**
 * @brief	��ȡĳһջ֡�ϵ�ջ��������
 * @param[in] depth ջ֡���, ��Χ[0, FM_CSE_GetCallStackDepth���ε�ֵ)
 * @param[in] serializedData,���������л��������, @see fmcse::VariableTable
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetTopVariableTableInFrame(
	FMUINT depth
	, std::string& serializedData);
/**
 * @brief	��ȡĳһջ֡�ϵı�����
 * @param[in] depth ջ֡���, ��Χ[0, FM_CSE_GetCallStackDepth���ε�ֵ)
 * @param[in] blockId ���, fmcse::VariableTable��parentId
 * @param[in] serializedData,���������л��������, @see fmcse::VariableTable
 * @return  FM_OK--�ɹ�, ���򷵻ش�����
 * @remark �ڶϵ��ִ����ͣʱʹ��
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetPreVariableTableInFrame(
	FMUINT depth
	, FMUINT blockId
	, std::string& serializedData);
////////////////////////////////////////////////////////////////

/*
 * @brief	��ȡ����Դλ��
 * @param[in] searching �����ִ�(��ֻ֧��SUB�������)
 * @param[out] scriptId	���ض������ڵ�ģ���ID
 * @param[out] line_no ���������е��к�
 * @return FM_OK--�ɹ�, ���򷵻ش�����
 * @remark 
 */
EXTERN_C FMCSE_API FMSTATUS CALL_CONV FM_CSE_GetDefinitionPos(
	FMCSTR searching
	, FMCHAR scriptId[MODULE_ID_MAX_LEN]
	, FMUINT* line_no
	);

////////////////////////////////////////////////////////////////

#endif //__FMCSE_API_H__