/*
 * 将websocket单独出来，在原有基础上去掉数据编码类型（可以灵活指定）
 */

#ifndef MK_WEBSOCKET_H
#define MK_WEBSOCKET_H

#include "mk_common.h"

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////websocketSession/////////////////////////////////////////////
//TcpSession对象的C映射

typedef void* mk_sock_info;
typedef void* mk_websocket_session;
//获取基类指针以便获取其网络相关信息
API_EXPORT mk_sock_info API_CALL mk_websocket_session_get_sock_info(const mk_websocket_session ctx);

//TcpSession::safeShutdown(),不能在on_mk_websocket_session_create和on_mk_websocket_session_auth中调用safe方法
API_EXPORT void API_CALL mk_websocket_session_safe_shutdown(const mk_websocket_session ctx,int err,const char *err_msg);
API_EXPORT void API_CALL mk_websocket_session_shutdown(const mk_websocket_session ctx,int err,const char *err_msg);
//TcpSession::send(),type=1为text，2为binary
API_EXPORT void API_CALL mk_websocket_session_send(const mk_websocket_session ctx,int type,const char *data,int len);
//切换到该对象所在线程后再TcpSession::send(),type=1为text，2为binary
API_EXPORT void API_CALL mk_websocket_session_send_safe(const mk_websocket_session ctx,int type,const char *data,int len);

///////////////////////////////////////////自定义websocket服务/////////////////////////////////////////////

typedef struct {
    /**
     * 收到mk_websocket_session创建对象
     * @param server_port 服务器端口号
     * @param session 会话处理对象
     * @param url 访问的url
     * @param params 参数列表
     * @return 小于0表示认证失败
     */
    int (API_CALL *on_mk_websocket_session_auth)(uint16_t server_port,const char * url,const char* params);

    /**
     * 收到mk_websocket_session创建对象
     * @param server_port 服务器端口号
     * @param session 会话处理对象
     * @param url 访问的url
     * @param params 参数列表
     */
    void (API_CALL *on_mk_websocket_session_create)(uint16_t server_port,const char * url,const char* params,mk_websocket_session session);

    /**
     * 收到客户端发过来的数据
     * @param server_port 服务器端口号
     * @param session 会话处理对象
     * @param type 1表示text，2表示binary
     * @param data 数据指针
     * @param len 数据长度
     */
    void (API_CALL *on_mk_websocket_session_data)(uint16_t server_port,const char * url,mk_websocket_session session,int type,const char *data,int len);

    /**
     * 每隔2秒的定时器，用于管理超时等任务
     * @param server_port 服务器端口号
     * @param session 会话处理对象
     */
    void (API_CALL *on_mk_websocket_session_manager)(uint16_t server_port,const char * url,mk_websocket_session session);

    /**
     * 一般由于客户端断开tcp触发
     * @param server_port 服务器端口号
     * @param session 会话处理对象
     * @param code 错误代码
     * @param msg 错误提示
     */
    void (API_CALL *on_mk_websocket_session_disconnect)(uint16_t server_port,const char * url,mk_websocket_session session,int code,const char *msg);
} mk_websocket_session_events;


typedef enum {
    //基于websocket的连接
    mk_websocket_type_ws = 0,
    //基于ssl websocket的连接
    mk_websocket_type_wss = 1
}mk_websocket_type;

/**
 * websocket会话对象附着用户数据
 * 该函数只对mk_websocket_server_server_start启动的服务类型有效
 * @param session 会话对象
 * @param user_data 用户数据指针
 */
API_EXPORT void API_CALL mk_websocket_session_set_user_data(mk_websocket_session session,void *user_data);

/**
 * 获取websocket会话对象上附着的用户数据
 * 该函数只对mk_websocket_server_server_start启动的服务类型有效
 * @param session tcp会话对象
 * @return 用户数据指针
 */
API_EXPORT void* API_CALL mk_websocket_session_get_user_data(mk_websocket_session session);

/**
 * 开启tcp服务器
 * @param port 监听端口号，0则为随机
 * @param type 服务器类型
 */
API_EXPORT uint16_t API_CALL mk_websocket_server_start(uint16_t port, mk_websocket_type type);

/**
 * 监听tcp服务器事件
 */
API_EXPORT void API_CALL mk_websocket_server_events_listen(const mk_websocket_session_events *events);


#ifdef __cplusplus
}
#endif
#endif //MK_WEBSOCKET_H
