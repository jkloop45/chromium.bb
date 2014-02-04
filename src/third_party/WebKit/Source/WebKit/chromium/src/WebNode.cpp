/*
 * Copyright (C) 2009 Google Inc. All rights reserved.
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

#include "config.h"
#include "WebNode.h"

#include "EventListenerWrapper.h"
#include "FrameLoaderClientImpl.h"
#include "WebDOMEvent.h"
#include "WebDOMEventListener.h"
#include "WebDocument.h"
#include "WebElement.h"
#include "WebFrameImpl.h"
#include "WebNodeList.h"
#include "WebPluginContainer.h"
#include "WebPluginContainerImpl.h"
#include "bindings/v8/ScriptController.h"
#include "core/dom/Document.h"
#include "core/dom/Element.h"
#include "core/dom/Event.h"
#include "core/dom/Node.h"
#include "core/dom/NodeList.h"
#include "core/editing/markup.h"
#include "core/page/Frame.h"
#include "core/platform/Widget.h"
#include "core/rendering/RenderObject.h"
#include "core/rendering/RenderWidget.h"
#include "public/platform/WebString.h"
#include "public/platform/WebVector.h"
#include <bindings/V8Node.h>

using namespace WebCore;

namespace {

class OptionalContextScope {
public:
    explicit inline OptionalContextScope(v8::Handle<v8::Context>* context) : context_(context) {
        if (context_) (*context_)->Enter();
    }
    inline ~OptionalContextScope() { if (context_) (*context_)->Exit(); }
private:
    v8::Handle<v8::Context>* context_;
};

};

namespace WebKit {

void WebNode::reset()
{
    m_private.reset();
}

void WebNode::assign(const WebNode& other)
{
    m_private = other.m_private;
}

bool WebNode::equals(const WebNode& n) const
{
    return (m_private.get() == n.m_private.get());
}

bool WebNode::lessThan(const WebNode& n) const
{
    return (m_private.get() < n.m_private.get());
}

WebNode::NodeType WebNode::nodeType() const
{
    return static_cast<NodeType>(m_private->nodeType());
}

WebNode WebNode::parentNode() const
{
    return WebNode(const_cast<ContainerNode*>(m_private->parentNode()));
}

WebString WebNode::nodeName() const
{
    return m_private->nodeName();
}

WebString WebNode::nodeValue() const
{
    return m_private->nodeValue();
}

bool WebNode::setNodeValue(const WebString& value)
{
    ExceptionCode exceptionCode = 0;
    m_private->setNodeValue(value, exceptionCode);
    return !exceptionCode;
}

WebDocument WebNode::document() const
{
    return WebDocument(m_private->document());
}

WebNode WebNode::firstChild() const
{
    return WebNode(m_private->firstChild());
}

WebNode WebNode::lastChild() const
{
    return WebNode(m_private->lastChild());
}

WebNode WebNode::previousSibling() const
{
    return WebNode(m_private->previousSibling());
}

WebNode WebNode::nextSibling() const
{
    return WebNode(m_private->nextSibling());
}

bool WebNode::hasChildNodes() const
{
    return m_private->hasChildNodes();
}

WebNodeList WebNode::childNodes()
{
    return WebNodeList(m_private->childNodes());
}

bool WebNode::insertBefore(const WebNode& newChild, const WebNode& refChild, bool shouldLazyAttach)
{
    ExceptionCode exceptionCode = 0;
    WebCore::AttachBehavior attachBehavior =
        shouldLazyAttach ? WebCore::AttachLazily : WebCore::AttachNow;
    m_private->insertBefore(newChild, refChild.m_private.get(), exceptionCode, attachBehavior);
    return !exceptionCode;
}

bool WebNode::replaceChild(const WebNode& newChild, const WebNode& oldChild, bool shouldLazyAttach)
{
    ExceptionCode exceptionCode = 0;
    WebCore::AttachBehavior attachBehavior =
        shouldLazyAttach ? WebCore::AttachLazily : WebCore::AttachNow;
    m_private->replaceChild(newChild, oldChild.m_private.get(), exceptionCode, attachBehavior);
    return !exceptionCode;
}

bool WebNode::appendChild(const WebNode& child, bool shouldLazyAttach)
{
    ExceptionCode exceptionCode = 0;
    WebCore::AttachBehavior attachBehavior =
        shouldLazyAttach ? WebCore::AttachLazily : WebCore::AttachNow;
    m_private->appendChild(child, exceptionCode, attachBehavior);
    return !exceptionCode;
}

WebString WebNode::createMarkup() const
{
    return WebCore::createMarkup(m_private.get());
}

bool WebNode::isLink() const
{
    return m_private->isLink();
}

bool WebNode::isTextNode() const
{
    return m_private->isTextNode();
}

bool WebNode::isFocusable() const
{
    m_private->document()->updateLayoutIgnorePendingStylesheets();
    return m_private->isFocusable();
}

bool WebNode::isContentEditable() const
{
    return m_private->isContentEditable();
}

bool WebNode::isElementNode() const
{
    return m_private->isElementNode();
}

void WebNode::addEventListener(const WebString& eventType, WebDOMEventListener* listener, bool useCapture)
{
    // Please do not add more eventTypes to this list without an API review.
    RELEASE_ASSERT(eventType == "mousedown");

    EventListenerWrapper* listenerWrapper = listener->createEventListenerWrapper(eventType, useCapture, m_private.get());
    // The listenerWrapper is only referenced by the actual Node.  Once it goes
    // away, the wrapper notifies the WebEventListener so it can clear its
    // pointer to it.
    m_private->addEventListener(eventType, adoptRef(listenerWrapper), useCapture);
}

bool WebNode::dispatchEvent(const WebDOMEvent& event)
{
    if (!event.isNull())
        return m_private->dispatchEvent(event);
    return false;
}

void WebNode::simulateClick()
{
    m_private->dispatchSimulatedClick(0);
}

WebNodeList WebNode::getElementsByTagName(const WebString& tag) const
{
    return WebNodeList(m_private->getElementsByTagName(tag));
}

WebElement WebNode::querySelector(const WebString& tag, WebExceptionCode& ec) const
{
    return WebElement(m_private->querySelector(tag, ec));
}

WebElement WebNode::rootEditableElement() const
{
    return WebElement(m_private->rootEditableElement());
}

bool WebNode::focused() const
{
    return m_private->focused();
}

bool WebNode::remove()
{
    ExceptionCode exceptionCode = 0;
    m_private->remove(exceptionCode);
    return !exceptionCode;
}

bool WebNode::setTextContent(const WebString& text)
{
    ExceptionCode exceptionCode = 0;
    m_private->setTextContent(text, exceptionCode);
    return !exceptionCode;
}

bool WebNode::removeChild(const WebNode& oldChild)
{
    ExceptionCode exceptionCode = 0;
    m_private->removeChild(oldChild.m_private.get(), exceptionCode);
    return !exceptionCode;
}

WebString WebNode::textContent() const
{
    return m_private->textContent();
}

bool WebNode::hasNonEmptyBoundingBox() const
{
    m_private->document()->updateLayoutIgnorePendingStylesheets();
    return m_private->hasNonEmptyBoundingBox();
}

WebPluginContainer* WebNode::pluginContainer() const
{
    if (isNull())
        return 0;
    const Node* coreNode = constUnwrap<Node>();
    if (coreNode->hasTagName(HTMLNames::objectTag) || coreNode->hasTagName(HTMLNames::embedTag)) {
        RenderObject* object = coreNode->renderer();
        if (object && object->isWidget()) {
            Widget* widget = WebCore::toRenderWidget(object)->widget();
            if (widget && widget->isPluginContainer())
                return static_cast<WebPluginContainerImpl*>(widget);
        }
    }
    return 0;
}

WebElement WebNode::shadowHost() const
{
    if (isNull())
        return WebElement();
    const Node* coreNode = constUnwrap<Node>();
    return WebElement(coreNode->shadowHost());
}

v8::Handle<v8::Value> WebNode::toV8Handle() const
{
    v8::Handle<v8::Context> context = WebCore::ScriptController::mainWorldContext(m_private->document()->frame());
    v8::Handle<v8::Context>* v8ContextToOpen = 0;
    if (!v8::Context::InContext()) {
        // If there is no current context, toV8 will crash, so force
        // our context to open if we aren't in a context.
        v8ContextToOpen = &context;
    }

    OptionalContextScope contextScope(v8ContextToOpen);
    return  WebCore::toV8(m_private.get(), context->Global(), context->GetIsolate());
}

bool WebNode::isWebNode(v8::Handle<v8::Value> handle)
{
    if (!handle->IsObject()) {
        return false;
    }
    v8::TryCatch tryCatch;
    v8::Handle<v8::Object> obj = handle->ToObject();
    if (!WebCore::V8Node::HasInstance(obj, obj->CreationContext()->GetIsolate(), WebCore::MainWorld)) {
        return false;
    }
    WebCore::V8Node::toNative(obj);
    return !tryCatch.HasCaught();
}

WebNode WebNode::fromV8Handle(v8::Handle<v8::Value> handle)
{
    return WebCore::V8Node::toNative(handle->ToObject());
}

WebNode::WebNode(const PassRefPtr<Node>& node)
    : m_private(node)
{
}

WebNode& WebNode::operator=(const PassRefPtr<Node>& node)
{
    m_private = node;
    return *this;
}

WebNode::operator PassRefPtr<Node>() const
{
    return m_private.get();
}

} // namespace WebKit