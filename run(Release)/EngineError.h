#ifndef _EngineError_h_
#define _EngineError_h_

#include "FM_error.h"
#include <string>

typedef enum EN_ERROR_TYPE{ET_ERROR = 0, ET_WARN};

/**
 * @brief	���󼶱���ֵԽСԽ����
 */
typedef enum EN_ERROR_LEVEL{EL_ERROR = 0, EL_WARN_1, EL_WARN_2, EL_WARN_3, EL_WARN_4};

static const FMCHAR ITEM_SEPARATOR = '|';

typedef struct stParseError
{
	stParseError() : isEnable(0), nErrorLevel(0), nNumber(0)
	{}
	stParseError(FMINT t, FMINT n, FMBOOL e = 0) : nErrorLevel(t), nNumber(n), isEnable(e)
	{}

	FMBOOL isEnable;			///< �����Ƿ�ʹ��
	FMINT nErrorLevel;			///< ��������
	FMINT nNumber;				///< ������
}ParseError;

typedef struct stGrammarError 
{
	std::string scriptName;		///< �ű�����
	FMINT nLineNo;				///< �����к�
	ParseError parseError;		///< ��������
	void ToString(std::string& str)
	{
		//��ʽ�������
	}
	
}GrammarError;
//�������
typedef enum ERROR_CATALOG{
	EC_ENGINE,	//����
	EC_RTLIB,	//����ʱ��
	EC_CALLBACKACTION,	///< PFCallbackAction����
	EC_COMPONENT	//���
};

typedef enum EN_PARSE_ERROR{

	WARN_IMPORT_SELF= 0x80070200,	///< ��������
	WARN_VAR_NAME_ALLREADY_EXIST= 0x80070201,	 ///< �������Ѵ���

	ERR_IMPORT_FORMAT= 0x80070202,	///< import�﷨��ʽ����ȷ
	ERR_ILLEGAL_MODULE_NAME= 0x80070203,		///< ��Ч��ģ������, ģ�������������������ʹ��@������ͬ������������ģ��������Ϊ�ؼ���

	ERR_INCORRECT_IF_DEFINE		= 0x80070204,	///< 0x80070204 �������жϴ���Ϊif���Ķ��壬�����岻�Ϸ�!

	ERR_STATEMENT_AFTER_L_BRACE = 0x80070211,	///< 0x80070211 �������жϴ���Ϊ��{���Ķ��壬�����滹�в���ע�͵��ַ����ⲻ����!
	ERR_STATEMENT_AFTER_R_BRACE	= 0x80070212,	///< 0x80070212 �������жϴ���Ϊ��}���Ķ��壬�����滹�в���ע�͵��ַ����ⲻ����!
	ERR_STATEMENT_MISMATCH_R_BRACE	= 0x80070213,	///< 0x80070213 �������ж�ȱ�١�}���Ķ���

	ERR_CALL_FORMAT				= 0x80070218,	///< 0x80070218 �������жϴ���Ϊcall���Ķ��壬��Ŀ��ű��ļ�ȫ���Ʊ�����ƥ������ţ�����˫����!
	ERR_INCORRECT_VAR_DEFINE	= 0x8007021C,	///< 0x8007021C �������жϴ���ӦΪ���������У�������δ�ڴ����ַ�!
	ERR_INCORRECT_FOR_DEFINE	= 0x8007021D,	///< 0x8007021D �������жϴ���Ϊfor���Ķ��壬�����岻�Ϸ�!

	ERR_ILLEGAL_SUB_NAME		= 0x8007021E,	///< �������жϴ���Ϊ�ӳ���sub�Ķ��壬���ӳ������Ʋ����Ϲ淶!
	ERR_INCORRECT_SUB_DEFINE	= 0x80070220,	///< 0x80070220 �������жϴ���Ϊ�ӳ���sub�Ķ��壬�������ӳ���" + strSubName + "���������岻�Ϸ�
	ERR_UNEXPECT_STATEMENT		= 0x80070221,	///< 0x80070221�������жϴ���Ϊsub�ӳ�����Ŀ�ʼ����û��Ԥ�ڵ���{�����ⲻ����!
	ERR_ILLEGAL_SUB_DEFINE_POS	= 0x80070223,	///< 0x80070223�������жϴ���Ϊsub�ӳ�������ڲ�������������sub��䣬�ⲻ����!

	ERR_INCORRECT_VAR_EQUIP		= 0x80070227,	///< ����ı�����ֵ�﷨
	ERR_INCORRECT_SUB_INVOKE	= 0x80070228,	///< ������ӳ�������﷨
	ERR_INCORRECT_EXPRESSION	= 0x80070229,	///< ����ı��ʽ�﷨
	ERR_CALL_SELF				= 0x8007022A,	///< ����call����
	ERR_CALLBACK_FORMAT			= 0x8007022B,	///< Callback:��ʽ����
	ERR_VAR_DEF_CONFLIT			= 0x8007022C,	///< ���������ͻ,ͬ����ͬ����
	ERR_INVALID_JUMP_INSTRUCTION= 0x8007022D,	///< ��Ч����תָ��(break,continue)

	ERR_LOG_NOT_FOUND_INTERFACE		= 0x800702D0,		///< ��־��������Ч

	ERR_EXEC_BUILTINSUB_PARAM_MAP	= 0x80070313,	///< ���ú���,����ӳ��ʱ����
	ERR_EXEC_SUB_PARAM_MAP			= ERR_EXEC_BUILTINSUB_PARAM_MAP,	///< ִ��SUBʱ����ӳ�����
	ERR_EXEC_BUILTINSUB				= 0x80070315,	///< ���ú���ִ�д���
	ERR_EXEC_CALL_NOT_FOUND_MODULE	= 0x80070316,	///< call���ִ�д���--δ�ҵ�ģ�����
	ERR_EXEC_EQUIP					= 0x80070317,	///< ��ֵ���ִ�д���
	ERR_EXEC_FOR_CALC_CONDITIONS	= 0x80070318,	///< for������start,end,stepֵʱ����
	ERR_EXEC_IF_NO_CMDS				= 0x80070319,	///< if�������������

	ERR_EXEC_INSTANCESUB			= 0x8007031A,	///< ���ʵ����������(δָ���������)
	ERR_EXEC_INSTANCESUB_NOT_FOUND_COMP = 0x8007031B,	///< �������ʵ������ʱδ�ҵ����
	ERR_EXEC_INSTANCESUB_GETINFO	= 0x8007031C,		///< ִ�����ʵ������ʱGetInfo����
	ERR_EXEC_INSTANCESUB_XML		= 0x8007031D,		///< ִ�����ʵ������ʱ�����ӿ�����XML����
	ERR_EXEC_INSTANCESUB_EXCEPTION	= 0x8007031E,		///< ִ�����ʵ������ʱ���ýӿ��쳣
	ERR_EXEC_INSTRUCT				= 0x8007031F,		///< ִ��ָ��ʱ����(δָ���������)
	ERR_EXEC_INSTRUCT_CALC_SW		= 0x80070320,		///< ִ��ָ��ʱ����SWʱ����
	ERR_EXEC_INSTRUCT_CALC_RESP		= 0x80070321,		///< ִ��ָ��ʱ����RESPʱ����
	ERR_EXEC_RTLIBSUB				= 0x80070322,		///< ִ������ʱ�⺯������(δָ���������)
	ERR_EXEC_RTLIBSUB_NO_LIB_INFO	= 0x80070323,		///< ������ʱ�⺯���Ľӿ�������Ϣ
	ERR_EXEC_RTLIBSUB_GET_FUNC_INFO	= 0x80070324,		///< ִ������ʱ�⺯��ʱ��ȡ���õĽӿ���Ϣʧ��
	ERR_EXEC_RTLIBSUB_CALC_SW		= 0x80070325,		///< ִ������ʱ�⺯��ʱ����SWʱ����
	ERR_EXEC_RTLIBSUB_CALC_RESP		= 0x80070326,		///< ִ������ʱ�⺯��ʱ����RESPʱ����
	ERR_EXEC_RTLIBSUB_NOT_FOUND_RT	= 0x80070327,		///< ִ������ʱ�⺯��ʱδ�ҵ�����ʱ����
	ERR_EXEC_RTLIBSUB_EXCEPTION		= 0x80070328,		///< ִ������ʱ�⺯��ʱ���ýӿ��쳣

	ERR_EXEC_SUB					= 0x80070329,		///< ִ��SUB����(δָ���������)
	ERR_EXEC_VARDEF					= 0x8007032A,		///< ִ�б�������ʱ����(δָ���������)
	ERR_EXEC_VARDEF_CREATE			= 0x8007032B,		///< ��������ʧ��
	ERR_EXEC_VARDEF_NOT_FOUND_REF	= 0x8007032C,		///< �����ͱ�������,��δ�ҵ������õı���
	ERR_EXEC_VARDEF_ASSIGN_VALUE	= 0x8007032D,		///< �������ͱ�������ֵʧ��
	ERR_EXEC_VARDEF_SAVE_TO_VTABLE	= 0x8007032E,		///< ���浽������ʱ����
	ERR_EXEC_CHECKVALID				= 0x8007032F,		///< CheckValid�ӳ��򷵻صĴ���
	ERR_EXEC_EXIT					= 0x80070330,		///< Exit�ӳ��򷵻ش���
	ERR_EXEC_BUILTINSUB_GETINST		= 0x80070331,		///< ��ȡ���ʵ��ʧ��
	ERR_EXEC_VERIFY					= 0x80070332,		///< SW(RetSW)��RESP(RetRESP)У�����
	ERR_EXEC_STACK_OVERFLOW			= 0x80070333,		///< ջ֡���
	ERR_EXEC_CALL_FAILER_IN_COS		= 0x80070334,		///< ��CALL��COS�ڲ����ִ�д���

	ERR_DBG_NOT_FOUND_VAR_TABEL		= 0x80070360,		///< ָ��ID�ı�����δ�ҵ�
	//0x80070380 ������RuntimeLib
};

#endif // _EngineError_h_
