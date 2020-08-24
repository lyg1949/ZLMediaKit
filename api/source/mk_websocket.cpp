/*
 * Copyright (c) 2016 The ZLMediaKit project authors. All Rights Reserved.
 *
 * This file is part of ZLMediaKit(https://github.com/xiongziliang/ZLMediaKit).
 *
 * Use of this source code is governed by MIT license that can be found in the
 * LICENSE file in the root of the source tree. All contributing project authors
 * may be found in the AUTHORS file in the root of the source tree.
 */

#include "string.h"
#include "mk_websocket.h"
#include "mk_websocket_private.h"
using namespace mediakit;


////////////////////////////////////////////////////////////////////////////////////////
API_EXPORT mk_sock_info API_CALL mk_websocket_session_get_sock_info(const mk_websocket_session ctx){
    assert(ctx);
    WebsocketSessionForC *session = (WebsocketSessionForC *)ctx;
    return (SockInfo *)session;
}

API_EXPORT void API_CALL mk_websocket_session_shutdown(const mk_websocket_session ctx,int err,const char *err_msg){
    assert(ctx);
    WebsocketSessionForC *session = (WebsocketSessionForC *)ctx;
    session->shutdown(SockException((ErrCode)err,err_msg));
}

API_EXPORT void API_CALL mk_websocket_session_send(const mk_websocket_session ctx,int type,const char *data,int len){
    assert(ctx && data);
    WebsocketSessionForC *session = (WebsocketSessionForC *)ctx;
    session->sendData(type,data,len);
}


////////////////////////////////////////WebsocketSessionForC////////////////////////////////////////////////
static TcpServer::Ptr s_websocket_server[2];


WebsocketSessionForC::WebsocketSessionForC(const Parser &header,const Socket::Ptr &pSock) : TcpSession(pSock) {
    _local_port = get_local_port();
    _header = header;
    if (s_events_server.on_mk_websocket_session_create) {
        s_events_server.on_mk_websocket_session_create(_local_port,_header.Url().c_str(),_header.Params().c_str(), this);
    }
}

void WebsocketSessionForC::onRecv(const Buffer::Ptr &buffer) {
    if (s_events_server.on_mk_websocket_session_data) {
        weak_ptr<WebSocketBuffer> wb = dynamic_pointer_cast<WebSocketBuffer>(buffer);
        auto wbs = wb.lock();
        if(wbs)
        {
            s_events_server.on_mk_websocket_session_data(_local_port,_header.Url().c_str(),this,wbs->headType(), wbs->data(), wbs->size());
        }
    }
}

void WebsocketSessionForC::onError(const SockException &err) {
    if (s_events_server.on_mk_websocket_session_disconnect) {
        s_events_server.on_mk_websocket_session_disconnect(_local_port,_header.Url().c_str(),this, err.getErrCode(), err.what());
    }
}

void WebsocketSessionForC::onManager() {
    if (s_events_server.on_mk_websocket_session_manager) {
        s_events_server.on_mk_websocket_session_manager(_local_port,_header.Url().c_str(),this);
    }
}

void stopAllWebsocketServer(){
    CLEAR_ARR(s_websocket_server);
}

API_EXPORT void API_CALL mk_websocket_session_set_user_data(mk_websocket_session session,void *user_data){
    assert(session);
    WebsocketSessionForC *obj = (WebsocketSessionForC *)session;
    obj->_user_data = user_data;
}

API_EXPORT void* API_CALL mk_websocket_session_get_user_data(mk_websocket_session session){
    assert(session);
    WebsocketSessionForC *obj = (WebsocketSessionForC *)session;
    return obj->_user_data;
}

API_EXPORT void API_CALL mk_websocket_server_events_listen(const mk_websocket_session_events *events){
    if (events) {
        memcpy(&s_events_server, events, sizeof(s_events_server));
    } else {
        memset(&s_events_server, 0, sizeof(s_events_server));
    }
}

API_EXPORT uint16_t API_CALL mk_websocket_server_start(uint16_t port, mk_websocket_type type){
    type = MAX(mk_websocket_type_ws, MIN(type, mk_websocket_type_wss));
    try {
        s_websocket_server[type] = std::make_shared<TcpServer>();
        switch (type) {
            case mk_websocket_type_ws:
                //此处你也可以修改WebSocketHeader::BINARY
                s_websocket_server[type]->start<WebSocketSessionPrivate<WebsocketSessionCreator, HttpSession> >(port);
                break;
            case mk_websocket_type_wss:
                //此处你也可以修改WebSocketHeader::BINARY
                s_websocket_server[type]->start<WebSocketSessionPrivate<WebsocketSessionCreator, HttpsSession> >(port);
                break;
            default:
                return 0;
        }
        return s_websocket_server[type]->getPort();
    } catch (std::exception &ex) {
        s_websocket_server[type].reset();
        WarnL << ex.what();
        return 0;
    }
}