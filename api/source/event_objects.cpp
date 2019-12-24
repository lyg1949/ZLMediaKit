/*
 * MIT License
 *
 * Copyright (c) 2019 xiongziliang <771730766@qq.com>
 *
 * This file is part of ZLMediaKit(https://github.com/xiongziliang/ZLMediaKit).
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <assert.h>
#include "event_objects.h"
#include "Common/config.h"
#include "Record/MP4Recorder.h"
#include "Network/TcpSession.h"
#include "Http/HttpSession.h"
#include "Rtsp/RtspSession.h"
using namespace mediakit;

///////////////////////////////////////////MP4Info/////////////////////////////////////////////
API_EXPORT uint64_t API_CALL mk_mp4_info_get_start_time(const mk_mp4_info ctx){
    assert(ctx);
    MP4Info *info = (MP4Info *)ctx;
    return info->ui64StartedTime;
}

API_EXPORT uint64_t API_CALL mk_mp4_info_get_time_len(const mk_mp4_info ctx){
    assert(ctx);
    MP4Info *info = (MP4Info *)ctx;
    return info->ui64TimeLen;
}

API_EXPORT uint64_t API_CALL mk_mp4_info_get_file_size(const mk_mp4_info ctx){
    assert(ctx);
    MP4Info *info = (MP4Info *)ctx;
    return info->ui64FileSize;
}

API_EXPORT const char* API_CALL mk_mp4_info_get_file_path(const mk_mp4_info ctx){
    assert(ctx);
    MP4Info *info = (MP4Info *)ctx;
    return info->strFilePath.c_str();
}

API_EXPORT const char* API_CALL mk_mp4_info_get_file_name(const mk_mp4_info ctx){
    assert(ctx);
    MP4Info *info = (MP4Info *)ctx;
    return info->strFileName.c_str();
}

API_EXPORT const char* API_CALL mk_mp4_info_get_folder(const mk_mp4_info ctx){
    assert(ctx);
    MP4Info *info = (MP4Info *)ctx;
    return info->strFolder.c_str();
}

API_EXPORT const char* API_CALL mk_mp4_info_get_url(const mk_mp4_info ctx){
    assert(ctx);
    MP4Info *info = (MP4Info *)ctx;
    return info->strUrl.c_str();
}

API_EXPORT const char* API_CALL mk_mp4_info_get_vhost(const mk_mp4_info ctx){
    assert(ctx);
    MP4Info *info = (MP4Info *)ctx;
    return info->strVhost.c_str();
}

API_EXPORT const char* API_CALL mk_mp4_info_get_app(const mk_mp4_info ctx){
    assert(ctx);
    MP4Info *info = (MP4Info *)ctx;
    return info->strAppName.c_str();
}

API_EXPORT const char* API_CALL mk_mp4_info_get_stream(const mk_mp4_info ctx){
    assert(ctx);
    MP4Info *info = (MP4Info *)ctx;
    return info->strStreamId.c_str();
}

///////////////////////////////////////////Parser/////////////////////////////////////////////
API_EXPORT const char* API_CALL mk_parser_get_method(const mk_parser ctx){
    assert(ctx);
    Parser *parser = (Parser *)ctx;
    return parser->Method().c_str();
}
API_EXPORT const char* API_CALL mk_parser_get_url(const mk_parser ctx){
    assert(ctx);
    Parser *parser = (Parser *)ctx;
    return parser->Url().c_str();
}
API_EXPORT const char* API_CALL mk_parser_get_full_url(const mk_parser ctx){
    assert(ctx);
    Parser *parser = (Parser *)ctx;
    return parser->FullUrl().c_str();
}
API_EXPORT const char* API_CALL mk_parser_get_url_params(const mk_parser ctx){
    assert(ctx);
    Parser *parser = (Parser *)ctx;
    return parser->Params().c_str();
}
API_EXPORT const char* API_CALL mk_parser_get_url_param(const mk_parser ctx,const char *key){
    assert(ctx && key);
    Parser *parser = (Parser *)ctx;
    return parser->getUrlArgs()[key].c_str();
}
API_EXPORT const char* API_CALL mk_parser_get_tail(const mk_parser ctx){
    assert(ctx);
    Parser *parser = (Parser *)ctx;
    return parser->Tail().c_str();
}
API_EXPORT const char* API_CALL mk_parser_get_header(const mk_parser ctx,const char *key){
    assert(ctx && key);
    Parser *parser = (Parser *)ctx;
    return parser->getValues()[key].c_str();
}
API_EXPORT const char* API_CALL mk_parser_get_content(const mk_parser ctx){
    assert(ctx);
    Parser *parser = (Parser *)ctx;
    return parser->Content().c_str();
}

///////////////////////////////////////////MediaInfo/////////////////////////////////////////////
API_EXPORT const char* API_CALL mk_media_info_get_params(const mk_media_info ctx){
    assert(ctx);
    MediaInfo *info = (MediaInfo *)ctx;
    return info->_param_strs.c_str();
}
API_EXPORT const char* API_CALL mk_media_info_get_param(const mk_media_info ctx,const char *key){
    assert(ctx && key);
    MediaInfo *info = (MediaInfo *)ctx;
    return info->_params[key].c_str();
}
API_EXPORT const char* API_CALL mk_media_info_get_schema(const mk_media_info ctx){
    assert(ctx);
    MediaInfo *info = (MediaInfo *)ctx;
    return info->_schema.c_str();
}
API_EXPORT const char* API_CALL mk_media_info_get_vhost(const mk_media_info ctx){
    assert(ctx);
    MediaInfo *info = (MediaInfo *)ctx;
    return info->_vhost.c_str();
}
API_EXPORT const char* API_CALL mk_media_info_get_app(const mk_media_info ctx){
    assert(ctx);
    MediaInfo *info = (MediaInfo *)ctx;
    return info->_app.c_str();
}
API_EXPORT const char* API_CALL mk_media_info_get_stream(const mk_media_info ctx){
    assert(ctx);
    MediaInfo *info = (MediaInfo *)ctx;
    return info->_streamid.c_str();
}

///////////////////////////////////////////MediaSource/////////////////////////////////////////////
API_EXPORT const char* API_CALL mk_media_source_get_schema(const mk_media_source ctx){
    assert(ctx);
    MediaSource *src = (MediaSource *)ctx;
    return src->getSchema().c_str();
}
API_EXPORT const char* API_CALL mk_media_source_get_vhost(const mk_media_source ctx){
    assert(ctx);
    MediaSource *src = (MediaSource *)ctx;
    return src->getVhost().c_str();
}
API_EXPORT const char* API_CALL mk_media_source_get_app(const mk_media_source ctx){
    assert(ctx);
    MediaSource *src = (MediaSource *)ctx;
    return src->getApp().c_str();
}
API_EXPORT const char* API_CALL mk_media_source_get_stream(const mk_media_source ctx){
    assert(ctx);
    MediaSource *src = (MediaSource *)ctx;
    return src->getId().c_str();
}
API_EXPORT int API_CALL mk_media_source_get_reader_count(const mk_media_source ctx){
    assert(ctx);
    MediaSource *src = (MediaSource *)ctx;
    return src->readerCount();
}
API_EXPORT int API_CALL mk_media_source_close(const mk_media_source ctx,int force){
    assert(ctx);
    MediaSource *src = (MediaSource *)ctx;
    return src->close(force);
}
API_EXPORT int API_CALL mk_media_source_seek_to(const mk_media_source ctx,uint32_t stamp){
    assert(ctx);
    MediaSource *src = (MediaSource *)ctx;
    return src->seekTo(stamp);
}

API_EXPORT void API_CALL mk_media_source_find(const char *schema,
                                              const char *vhost,
                                              const char *app,
                                              const char *stream,
                                              void *user_data,
                                              on_mk_media_source_find_cb cb) {
    assert(schema && vhost && app && stream && cb);
    auto src = MediaSource::find(schema, vhost, app, stream);
    cb(user_data, src.get());
}

API_EXPORT void API_CALL mk_media_source_for_each(void *user_data, on_mk_media_source_find_cb cb){
    assert(cb);
    MediaSource::for_each_media([&](const MediaSource::Ptr &src){
        cb(user_data,src.get());
    });
}

///////////////////////////////////////////TcpSession/////////////////////////////////////////////
API_EXPORT void API_CALL mk_tcp_session_shutdown(const mk_tcp_session ctx,int err,const char *err_msg){
    assert(ctx);
    TcpSession *session = (TcpSession *)ctx;
    session->safeShutdown(SockException((ErrCode)err,err_msg));
}
API_EXPORT const char* API_CALL mk_tcp_session_peer_ip(const mk_tcp_session ctx){
    assert(ctx);
    TcpSession *session = (TcpSession *)ctx;
    return session->get_peer_ip().c_str();
}
API_EXPORT const char* API_CALL mk_tcp_session_local_ip(const mk_tcp_session ctx){
    assert(ctx);
    TcpSession *session = (TcpSession *)ctx;
    return session->get_local_ip().c_str();
}
API_EXPORT uint16_t API_CALL mk_tcp_session_peer_port(const mk_tcp_session ctx){
    assert(ctx);
    TcpSession *session = (TcpSession *)ctx;
    return session->get_peer_port();
}
API_EXPORT uint16_t API_CALL mk_tcp_session_local_port(const mk_tcp_session ctx){
    assert(ctx);
    TcpSession *session = (TcpSession *)ctx;
    return session->get_local_port();
}

///////////////////////////////////////////HttpResponseInvoker/////////////////////////////////////////////
static StrCaseMap get_http_header( const char *response_header[]){
    StrCaseMap header;
    for (int i = 0; response_header[i] != NULL;) {
        auto key = response_header[i];
        auto value = response_header[i + 1];
        if (key && value) {
            i += 2;
            header[key] = value;
            continue;
        }
        break;
    }
    return std::move(header);
}
API_EXPORT void API_CALL mk_http_response_invoker_do(const mk_http_response_invoker ctx,
                                                     const char *response_code,
                                                     const char *response_header[],
                                                     const char *response_content){
    assert(ctx && response_code && response_header && response_content);
    auto header = get_http_header(response_header);
    HttpSession::HttpResponseInvoker *invoker = (HttpSession::HttpResponseInvoker *)ctx;
    (*invoker)(response_code,header,response_content);
}

API_EXPORT void API_CALL mk_http_response_invoker_do_file(const mk_http_response_invoker ctx,
                                                          const mk_parser request_parser,
                                                          const char *response_header[],
                                                          const char *response_file_path){
    assert(ctx && request_parser && response_header && response_file_path);
    auto header = get_http_header(response_header);
    HttpSession::HttpResponseInvoker *invoker = (HttpSession::HttpResponseInvoker *)ctx;
    (*invoker).responseFile(((Parser*)(request_parser))->getValues(),header,response_file_path);
}

///////////////////////////////////////////HttpAccessPathInvoker/////////////////////////////////////////////
API_EXPORT void API_CALL mk_http_access_path_invoker_do(const mk_http_access_path_invoker ctx,
                                                        const char *err_msg,
                                                        const char *access_path,
                                                        int cookie_life_second){
    assert(ctx);
    HttpSession::HttpAccessPathInvoker *invoer = (HttpSession::HttpAccessPathInvoker *)ctx;
    (*invoer)(err_msg ? err_msg : "",
              access_path? access_path : "",
              cookie_life_second);
}
///////////////////////////////////////////RtspSession::onGetRealm/////////////////////////////////////////////
API_EXPORT void API_CALL mk_rtsp_get_realm_invoker_do(const mk_rtsp_get_realm_invoker ctx,
                                                      const char *realm){
    assert(ctx);
    RtspSession::onGetRealm *invoker = (RtspSession::onGetRealm *)ctx;
    (*invoker)(realm ? realm : "");
}

///////////////////////////////////////////RtspSession::onAuth/////////////////////////////////////////////
API_EXPORT void API_CALL mk_rtsp_auth_invoker_do(const mk_rtsp_auth_invoker ctx,
                                                 int encrypted,
                                                 const char *pwd_or_md5){
    assert(ctx);
    RtspSession::onAuth *invoker = (RtspSession::onAuth *)ctx;
    (*invoker)(encrypted, pwd_or_md5 ? pwd_or_md5 : "");
}

///////////////////////////////////////////Broadcast::PublishAuthInvoker/////////////////////////////////////////////
API_EXPORT void API_CALL mk_publish_auth_invoker_do(const mk_publish_auth_invoker ctx,
                                                    const char *err_msg,
                                                    int enable_rtxp,
                                                    int enable_hls,
                                                    int enable_mp4){
    assert(ctx);
    Broadcast::PublishAuthInvoker *invoker = (Broadcast::PublishAuthInvoker *)ctx;
    (*invoker)(err_msg ? err_msg : "", enable_rtxp, enable_hls, enable_mp4);
}

///////////////////////////////////////////Broadcast::AuthInvoker/////////////////////////////////////////////
API_EXPORT void API_CALL mk_auth_invoker_do(const mk_auth_invoker ctx, const char *err_msg){
    assert(ctx);
    Broadcast::AuthInvoker *invoker = (Broadcast::AuthInvoker *)ctx;
    (*invoker)(err_msg ? err_msg : "");
}
