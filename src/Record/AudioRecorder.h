/*
 * Copyright (c) 2016 The ZLMediaKit project authors. All Rights Reserved.
 *
 * This file is part of ZLMediaKit(https://github.com/xiongziliang/ZLMediaKit).
 *
 * Use of this source code is governed by MIT license that can be found in the
 * LICENSE file in the root of the source tree. All contributing project authors
 * may be found in the AUTHORS file in the root of the source tree.
 */

#ifndef AUDIORECODER_H_
#define AUDIORECODER_H_

#include <mutex>
#include <memory>
#include "Player/PlayerBase.h"
#include "Util/util.h"
#include "Util/File.h"
#include "Util/logger.h"
#include "Util/TimeTicker.h"
#include "Common/MediaSink.h"
using namespace toolkit;

namespace mediakit {

class AudioInfo {
public:
    time_t ui64StartedTime; //GMT标准时间，单位秒,开始录像时间
    time_t ui64TimeLen;//录音时间，单位秒
    off_t ui64FileSize;//文件大小，单位BYTE
    string strFilePath;//文件路径
    string strFileName;//文件名称
    string strFolder;//文件夹路径
    string strUrl;//播放路径
    string strAppName;//应用名称
    string strStreamId;//流ID
    string strVhost;//vhost
    string strExt;//文件后缀名
};

class AudioRecorder : public MediaSinkInterface{
public:
    typedef std::shared_ptr<AudioRecorder> Ptr;

    AudioRecorder(const string &strPath,
                const string &strVhost,
                const string &strApp,
                const string &strStreamId);
    virtual ~AudioRecorder();

    /**
     * 重置所有Track
     */
    void resetTracks() override;

    /**
     * 输入frame
     */
    void inputFrame(const Frame::Ptr &frame) override;

    /**
     * 添加ready状态的track
     */
    void addTrack(const Track::Ptr & track) override;
private:
    void createFile();
    void closeFile();
private:
    string _strPath;
    string _strFile;
    string _strFileTmp;
    string _strFolder;//文件夹路径
    string _strAppName;//应用名称
    string _strStreamId;//流ID
    string _strVhost;//vhost
    Ticker _createFileTicker;
    //AudioInfo _info;
    std::shared_ptr<FILE> _file;
    bool _hasExt = false;
    string strExt;//文件后缀名
};

} /* namespace mediakit */

#endif /* AUDIORECODER_H_ */
