/*
 * Copyright (C) 2009 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#include "core/html/canvas/WebGLBuffer.h"

#include "core/html/canvas/WebGLRenderingContext.h"

namespace WebCore {

PassRefPtr<WebGLBuffer> WebGLBuffer::create(WebGLRenderingContext* ctx)
{
    return adoptRef(new WebGLBuffer(ctx));
}

WebGLBuffer::WebGLBuffer(WebGLRenderingContext* ctx)
    : WebGLSharedObject(ctx)
    , m_target(0)
{
    ScriptWrappable::init(this);
    setObject(ctx->webGraphicsContext3D()->createBuffer());
}

WebGLBuffer::~WebGLBuffer()
{
    deleteObject(0);
}

void WebGLBuffer::deleteObjectImpl(blink::WebGraphicsContext3D* context3d, Platform3DObject object)
{
      context3d->deleteBuffer(object);
}

void WebGLBuffer::setTarget(GLenum target)
{
    // In WebGL, a buffer is bound to one target in its lifetime
    if (m_target)
        return;
    if (target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER)
        m_target = target;
}

}
