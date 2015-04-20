// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ServiceWorkerWindowClient_h
#define ServiceWorkerWindowClient_h

#include "bindings/core/v8/ScriptPromise.h"
#include "modules/serviceworkers/ServiceWorkerClient.h"
#include "platform/heap/Handle.h"
#include "wtf/Forward.h"

namespace blink {

class ScriptState;

class ServiceWorkerWindowClient final : public ServiceWorkerClient {
    DEFINE_WRAPPERTYPEINFO();
public:
    static ServiceWorkerWindowClient* create(const WebServiceWorkerClientInfo&);
    ~ServiceWorkerWindowClient() override;

    // WindowClient.idl
    String visibilityState() const;
    bool focused() const { return m_isFocused; }
    String frameType() const;
    ScriptPromise focus(ScriptState*);

    virtual void trace(Visitor*) override;

private:
    explicit ServiceWorkerWindowClient(const WebServiceWorkerClientInfo&);

    // FIXME: remove m_visibilityState when m_pageVisibilityState will be used
    // by Chromium.
    String m_visibilityState;
    WebPageVisibilityState m_pageVisibilityState;
    bool m_isFocused;
    WebURLRequest::FrameType m_frameType;
};

} // namespace blink

#endif // ServiceWorkerWindowClient_h