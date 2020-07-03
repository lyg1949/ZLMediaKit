/*
 * Copyright (c) 2016 The ZLMediaKit project authors. All Rights Reserved.
 *
 * This file is part of ZLMediaKit(https://github.com/xiongziliang/ZLMediaKit).
 *
 * Use of this source code is governed by MIT license that can be found in the
 * LICENSE file in the root of the source tree. All contributing project authors
 * may be found in the AUTHORS file in the root of the source tree.
 */

#include <ctime>
#include <sys/stat.h>
#include "Common/config.h"
#include "AudioRecorder.h"

using namespace toolkit;

namespace mediakit {

AudioRecorder::AudioRecorder(const string& strPath,
                   const string &strVhost,
                   const string &strApp,
                   const string &strStreamId) {            
    _strPath = strPath;
    /////record 业务逻辑//////
    _strAppName = strApp;
    _strStreamId = strStreamId;
    _strVhost = strVhost;
    _strFolder = strPath;
}
AudioRecorder::~AudioRecorder() {
    closeFile();
}

void AudioRecorder::createFile() {
    closeFile();
    auto strDate = getTimeStr("%Y-%m-%d");
    auto strTime = getTimeStr("%H-%M-%S");
    auto strFileTmp = _strPath + strDate + "/." + strTime + strExt;
    auto strFile =	_strPath + strDate + "/" + strTime + strExt;

    /////record 业务逻辑//////
   // _info.ui64StartedTime = ::time(NULL);
    //_info.strFileName = strTime + _info.strExt;
   // _info.strFilePath = strFile;
    GET_CONFIG(string,appName,Record::kAppName);
   // _info.strUrl = appName + "/"
   //                + _info.strAppName + "/"
   //                + _info.strStreamId + "/"
   //                + strDate + "/"
   //                + strTime + _info.strExt;

    try {
        _file = shared_ptr<FILE>(File::create_file(strFileTmp.data(), "wb"), [](FILE *fp) {
        if (fp) {
            fclose(fp);
        }
    });
        _strFileTmp = strFileTmp;
        _strFile = strFile;
        _createFileTicker.resetTime();
    }catch(std::exception &ex) {
        WarnL << ex.what();
    }
}

void AudioRecorder::closeFile() {
    if (_file) {
        //_info.ui64TimeLen = ::time(NULL) - _info.ui64StartedTime;
        _file.reset();
        rename(_strFileTmp.data(),_strFile.data());
        //struct stat fileData;
        //stat(_strFile.data(), &fileData);
        //_info.ui64FileSize = fileData.st_size;
        ///广播？？
    }
}

void AudioRecorder::inputFrame(const Frame::Ptr &frame) {
    if(frame->getTrackType() != TrackAudio)
    {
        return;
    }
    if(!_hasExt)
    {
        ///只判断一次帧类型，之后默认都相同
        _hasExt = true;
        switch (frame->getCodecId())
        {
        case CodecAAC:
            strExt = ".aac";
            break;
        case CodecG711A:
        case CodecG711U:
            strExt = ".g711";
            break;
        case CodecOpus:
            strExt = ".opus";
            break;
        default:
            strExt = ".aud";
            break;
        }
    }
    GET_CONFIG(uint32_t,recordSec,Record::kFileSecond);
    if(!_file || ((_createFileTicker.elapsedTime() > recordSec * 1000))){
        //成立条件
        //1、_file为空
        //2、到了切片时间
        createFile();
    }

    if(_file){
        //写音频文件
        fwrite(frame->data(), frame->size(), 1, _file.get());
    }
}

void AudioRecorder::addTrack(const Track::Ptr & track){
    //留空
}

void AudioRecorder::resetTracks() {
    closeFile();
    _createFileTicker.resetTime();
    _hasExt = false;
}

} /* namespace mediakit */

