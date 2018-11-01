#ifndef _EngineMessage_h_
#define _EngineMessage_h_

typedef enum EN_ENGINE_MSG{
	ENGINE_MSG_BEGIN,		///< 保留, lParam: NULL
	ENGINE_MSG_WAIT_BGN,	///< 开始等待消息, 保留, lParam: NULL
	ENGINE_MSG_WAITTING,	///< 等待中, 保留, lParam: NULL
	ENGINE_MSG_WAIT_END,	///< 等待结束消息
	ENGINE_MSG_PARSE_BGN,	///< 解析开始, 保留, lParam: NULL
	ENGINE_MSG_PARSING,		///< 正在解析中, lParam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data的类型: fmcse::ParseNotification 
	ENGINE_MSG_PARSE_ERROR,	///< 解析错误, lParam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data的类型: fmcse::ParseNotification 
	ENGINE_MSG_PARSE_END,	///< 解析结束消息, lParam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data的类型: FMINT*, 0表示解析失败, 1表示解析成功
	ENGINE_MSG_EXEC_BGN,	///< 开始执行, lParam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data的类型: fmcse::ExecBeginNotification 
	ENGINE_MSG_EXEC_RESULT, ///< 执行结果，NotificationWrap* nw = (NotificationWrap*)lParam; nw->data的类型: fmcse::ExecNotification 
	ENGINE_MSG_EXEC_END,	///< 执行结束消息, lparam: lParam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data的类型: FMINT*, <1表示失败, 1表示成功

	ENGINE_MSG_DEBUG_BREAK,	///< NotificationWrap* nw = (NotificationWrap*)lParam; nw->data的类型: fmcse::BreakpointNotification 

	ENGINE_MSG_MSGBOX,		///< 调用了MessageBox函数, lparam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data的类型: fmcse::MsgNotification
	ENGINE_MSG_PRINTINFO,	///< 调用了PrintInfo函数, lparam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data的类型: fmcse::MsgNotification

	ENGINE_MSG_LOG,			///< 保留, lParam: NULL
	ENGINE_MSG_END,			///< 保留, lParam: NULL
};
#endif // _EngineMessage_h_
