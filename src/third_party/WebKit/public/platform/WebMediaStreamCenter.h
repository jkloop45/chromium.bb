/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WebMediaStreamCenter_h
#define WebMediaStreamCenter_h

#include "WebVector.h"

namespace WebKit {
class WebMediaStream;
class WebMediaStreamSourcesRequest;
class WebMediaStreamTrack;
class WebMediaStreamTrackSourcesRequest;
class WebSourceInfo;
class WebString;

class WebMediaStreamCenter {
public:
    virtual ~WebMediaStreamCenter() { }

    // DEPRECATED
    virtual void queryMediaStreamSources(const WebMediaStreamSourcesRequest&) { }

    virtual bool getMediaStreamTrackSources(const WebMediaStreamTrackSourcesRequest&) { return false; }
    virtual void didEnableMediaStreamTrack(const WebMediaStream&, const WebMediaStreamTrack&) = 0;
    virtual void didDisableMediaStreamTrack(const WebMediaStream&, const WebMediaStreamTrack&) = 0;
    virtual bool didAddMediaStreamTrack(const WebMediaStream&, const WebMediaStreamTrack&) { return false; };
    virtual bool didRemoveMediaStreamTrack(const WebMediaStream&, const WebMediaStreamTrack&) { return false; };
    virtual void didStopLocalMediaStream(const WebMediaStream&) = 0;
    virtual void didCreateMediaStream(WebMediaStream&) = 0;
};

} // namespace WebKit

#endif // WebMediaStreamCenter_h
