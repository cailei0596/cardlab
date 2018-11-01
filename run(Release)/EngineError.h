#ifndef _EngineError_h_
#define _EngineError_h_

#include "FM_error.h"
#include <string>

typedef enum EN_ERROR_TYPE{ET_ERROR = 0, ET_WARN};

/**
 * @brief	错误级别，数值越小越严重
 */
typedef enum EN_ERROR_LEVEL{EL_ERROR = 0, EL_WARN_1, EL_WARN_2, EL_WARN_3, EL_WARN_4};

static const FMCHAR ITEM_SEPARATOR = '|';

typedef struct stParseError
{
	stParseError() : isEnable(0), nErrorLevel(0), nNumber(0)
	{}
	stParseError(FMINT t, FMINT n, FMBOOL e = 0) : nErrorLevel(t), nNumber(n), isEnable(e)
	{}

	FMBOOL isEnable;			///< 错误是否使能
	FMINT nErrorLevel;			///< 错误类型
	FMINT nNumber;				///< 错误编号
}ParseError;

typedef struct stGrammarError 
{
	std::string scriptName;		///< 脚本名称
	FMINT nLineNo;				///< 出错行号
	ParseError parseError;		///< 解析错误
	void ToString(std::string& str)
	{
		//格式化后输出
	}
	
}GrammarError;
//错误分类
typedef enum ERROR_CATALOG{
	EC_ENGINE,	//引擎
	EC_RTLIB,	//运行时库
	EC_CALLBACKACTION,	///< PFCallbackAction函数
	EC_COMPONENT	//组件
};

typedef enum EN_PARSE_ERROR{

	WARN_IMPORT_SELF= 0x80070200,	///< 导入自身
	WARN_VAR_NAME_ALLREADY_EXIST= 0x80070201,	 ///< 变量名已存在

	ERR_IMPORT_FORMAT= 0x80070202,	///< import语法格式不正确
	ERR_ILLEGAL_MODULE_NAME= 0x80070203,		///< 无效的模块名称, 模块名称命名规则除不能使用@外其他同变量命名规则，模块名不能为关键字

	ERR_INCORRECT_IF_DEFINE		= 0x80070204,	///< 0x80070204 解析器判断此行为if语句的定义，但定义不合法!

	ERR_STATEMENT_AFTER_L_BRACE = 0x80070211,	///< 0x80070211 解析器判断此行为“{”的定义，但后面还有不是注释的字符，这不允许!
	ERR_STATEMENT_AFTER_R_BRACE	= 0x80070212,	///< 0x80070212 解析器判断此行为“}”的定义，但后面还有不是注释的字符，这不允许!
	ERR_STATEMENT_MISMATCH_R_BRACE	= 0x80070213,	///< 0x80070213 解析器判断缺少“}”的定义

	ERR_CALL_FORMAT				= 0x80070218,	///< 0x80070218 解析器判断此行为call语句的定义，但目标脚本文件全名称必须在匹配的引号（单或双）中!
	ERR_INCORRECT_VAR_DEFINE	= 0x8007021C,	///< 0x8007021C 解析器判断此行应为变量定义行，但出现未期待的字符!
	ERR_INCORRECT_FOR_DEFINE	= 0x8007021D,	///< 0x8007021D 解析器判断此行为for语句的定义，但定义不合法!

	ERR_ILLEGAL_SUB_NAME		= 0x8007021E,	///< 解析器判断此行为子程序sub的定义，但子程序名称不符合规范!
	ERR_INCORRECT_SUB_DEFINE	= 0x80070220,	///< 0x80070220 解析器判断此行为子程序sub的定义，发现了子程序【" + strSubName + "】，但定义不合法
	ERR_UNEXPECT_STATEMENT		= 0x80070221,	///< 0x80070221解析器判断此行为sub子程序体的开始，但没有预期到“{”，这不允许!
	ERR_ILLEGAL_SUB_DEFINE_POS	= 0x80070223,	///< 0x80070223解析器判断此行为sub子程序体的内部，但又遇到了sub语句，这不允许!

	ERR_INCORRECT_VAR_EQUIP		= 0x80070227,	///< 错误的变量赋值语法
	ERR_INCORRECT_SUB_INVOKE	= 0x80070228,	///< 错误的子程序调用语法
	ERR_INCORRECT_EXPRESSION	= 0x80070229,	///< 错误的表达式语法
	ERR_CALL_SELF				= 0x8007022A,	///< 不能call自身
	ERR_CALLBACK_FORMAT			= 0x8007022B,	///< Callback:格式错误
	ERR_VAR_DEF_CONFLIT			= 0x8007022C,	///< 变量定义冲突,同名不同类型
	ERR_INVALID_JUMP_INSTRUCTION= 0x8007022D,	///< 无效的跳转指令(break,continue)

	ERR_LOG_NOT_FOUND_INTERFACE		= 0x800702D0,		///< 日志组件句柄无效

	ERR_EXEC_BUILTINSUB_PARAM_MAP	= 0x80070313,	///< 内置函数,参数映射时出错
	ERR_EXEC_SUB_PARAM_MAP			= ERR_EXEC_BUILTINSUB_PARAM_MAP,	///< 执行SUB时参数映射错误
	ERR_EXEC_BUILTINSUB				= 0x80070315,	///< 内置函数执行错误
	ERR_EXEC_CALL_NOT_FOUND_MODULE	= 0x80070316,	///< call语句执行错误--未找到模块对象
	ERR_EXEC_EQUIP					= 0x80070317,	///< 赋值语句执行错误
	ERR_EXEC_FOR_CALC_CONDITIONS	= 0x80070318,	///< for语句计算start,end,step值时出错
	ERR_EXEC_IF_NO_CMDS				= 0x80070319,	///< if语句无命令序列

	ERR_EXEC_INSTANCESUB			= 0x8007031A,	///< 组件实例函数错误(未指明具体错误)
	ERR_EXEC_INSTANCESUB_NOT_FOUND_COMP = 0x8007031B,	///< 调用组件实例函数时未找到组件
	ERR_EXEC_INSTANCESUB_GETINFO	= 0x8007031C,		///< 执行组件实例函数时GetInfo出错
	ERR_EXEC_INSTANCESUB_XML		= 0x8007031D,		///< 执行组件实例函数时解析接口描述XML出错
	ERR_EXEC_INSTANCESUB_EXCEPTION	= 0x8007031E,		///< 执行组件实例函数时调用接口异常
	ERR_EXEC_INSTRUCT				= 0x8007031F,		///< 执行指令时出错(未指明具体错误)
	ERR_EXEC_INSTRUCT_CALC_SW		= 0x80070320,		///< 执行指令时计算SW时出错
	ERR_EXEC_INSTRUCT_CALC_RESP		= 0x80070321,		///< 执行指令时计算RESP时出错
	ERR_EXEC_RTLIBSUB				= 0x80070322,		///< 执行运行时库函数出错(未指明具体错误)
	ERR_EXEC_RTLIBSUB_NO_LIB_INFO	= 0x80070323,		///< 无运行时库函数的接口描述信息
	ERR_EXEC_RTLIBSUB_GET_FUNC_INFO	= 0x80070324,		///< 执行运行时库函数时获取调用的接口信息失败
	ERR_EXEC_RTLIBSUB_CALC_SW		= 0x80070325,		///< 执行运行时库函数时计算SW时出错
	ERR_EXEC_RTLIBSUB_CALC_RESP		= 0x80070326,		///< 执行运行时库函数时计算RESP时出错
	ERR_EXEC_RTLIBSUB_NOT_FOUND_RT	= 0x80070327,		///< 执行运行时库函数时未找到运行时库句柄
	ERR_EXEC_RTLIBSUB_EXCEPTION		= 0x80070328,		///< 执行运行时库函数时调用接口异常

	ERR_EXEC_SUB					= 0x80070329,		///< 执行SUB出错(未指明具体错误)
	ERR_EXEC_VARDEF					= 0x8007032A,		///< 执行变量定义时出错(未指明具体错误)
	ERR_EXEC_VARDEF_CREATE			= 0x8007032B,		///< 创建变量失败
	ERR_EXEC_VARDEF_NOT_FOUND_REF	= 0x8007032C,		///< 引用型变量定义,但未找到被引用的变量
	ERR_EXEC_VARDEF_ASSIGN_VALUE	= 0x8007032D,		///< 非引用型变量赋初值失败
	ERR_EXEC_VARDEF_SAVE_TO_VTABLE	= 0x8007032E,		///< 保存到变量表时出错
	ERR_EXEC_CHECKVALID				= 0x8007032F,		///< CheckValid子程序返回的错误
	ERR_EXEC_EXIT					= 0x80070330,		///< Exit子程序返回错误
	ERR_EXEC_BUILTINSUB_GETINST		= 0x80070331,		///< 获取组件实例失败
	ERR_EXEC_VERIFY					= 0x80070332,		///< SW(RetSW)或RESP(RetRESP)校验错误
	ERR_EXEC_STACK_OVERFLOW			= 0x80070333,		///< 栈帧溢出
	ERR_EXEC_CALL_FAILER_IN_COS		= 0x80070334,		///< 被CALL的COS内部语句执行错误

	ERR_DBG_NOT_FOUND_VAR_TABEL		= 0x80070360,		///< 指定ID的变量表未找到
	//0x80070380 后分配给RuntimeLib
};

#endif // _EngineError_h_
