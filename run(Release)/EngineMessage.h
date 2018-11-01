#ifndef _EngineMessage_h_
#define _EngineMessage_h_

typedef enum EN_ENGINE_MSG{
	ENGINE_MSG_BEGIN,		///< ����, lParam: NULL
	ENGINE_MSG_WAIT_BGN,	///< ��ʼ�ȴ���Ϣ, ����, lParam: NULL
	ENGINE_MSG_WAITTING,	///< �ȴ���, ����, lParam: NULL
	ENGINE_MSG_WAIT_END,	///< �ȴ�������Ϣ
	ENGINE_MSG_PARSE_BGN,	///< ������ʼ, ����, lParam: NULL
	ENGINE_MSG_PARSING,		///< ���ڽ�����, lParam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data������: fmcse::ParseNotification 
	ENGINE_MSG_PARSE_ERROR,	///< ��������, lParam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data������: fmcse::ParseNotification 
	ENGINE_MSG_PARSE_END,	///< ����������Ϣ, lParam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data������: FMINT*, 0��ʾ����ʧ��, 1��ʾ�����ɹ�
	ENGINE_MSG_EXEC_BGN,	///< ��ʼִ��, lParam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data������: fmcse::ExecBeginNotification 
	ENGINE_MSG_EXEC_RESULT, ///< ִ�н����NotificationWrap* nw = (NotificationWrap*)lParam; nw->data������: fmcse::ExecNotification 
	ENGINE_MSG_EXEC_END,	///< ִ�н�����Ϣ, lparam: lParam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data������: FMINT*, <1��ʾʧ��, 1��ʾ�ɹ�

	ENGINE_MSG_DEBUG_BREAK,	///< NotificationWrap* nw = (NotificationWrap*)lParam; nw->data������: fmcse::BreakpointNotification 

	ENGINE_MSG_MSGBOX,		///< ������MessageBox����, lparam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data������: fmcse::MsgNotification
	ENGINE_MSG_PRINTINFO,	///< ������PrintInfo����, lparam: NotificationWrap* nw = (NotificationWrap*)lParam; nw->data������: fmcse::MsgNotification

	ENGINE_MSG_LOG,			///< ����, lParam: NULL
	ENGINE_MSG_END,			///< ����, lParam: NULL
};
#endif // _EngineMessage_h_
