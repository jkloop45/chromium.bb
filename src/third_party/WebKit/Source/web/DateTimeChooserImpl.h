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

#ifndef DateTimeChooserImpl_h
#define DateTimeChooserImpl_h

#if ENABLE(INPUT_MULTIPLE_FIELDS_UI)
#include "core/page/PagePopupClient.h"
#include "platform/DateTimeChooser.h"

namespace WebCore {
class PagePopup;
class DateTimeChooserClient;
}

namespace blink {

class ChromeClientImpl;

class DateTimeChooserImpl FINAL : public WebCore::DateTimeChooser, public WebCore::PagePopupClient {
public:
    static PassRefPtr<DateTimeChooserImpl> create(ChromeClientImpl*, WebCore::DateTimeChooserClient*, const WebCore::DateTimeChooserParameters&);
    virtual ~DateTimeChooserImpl();

    // DateTimeChooser functions:
    virtual void endChooser() OVERRIDE;

private:
    DateTimeChooserImpl(ChromeClientImpl*, WebCore::DateTimeChooserClient*, const WebCore::DateTimeChooserParameters&);
    // PagePopupClient functions:
    virtual WebCore::IntSize contentSize() OVERRIDE;
    virtual void writeDocument(WebCore::SharedBuffer*) OVERRIDE;
    virtual WebCore::Locale& locale() OVERRIDE;
    virtual void setValueAndClosePopup(int, const String&) OVERRIDE;
    virtual void setValue(const String&) OVERRIDE;
    virtual void closePopup() OVERRIDE;
    virtual void didClosePopup() OVERRIDE;

    ChromeClientImpl* m_chromeClient;
    WebCore::DateTimeChooserClient* m_client;
    WebCore::PagePopup* m_popup;
    WebCore::DateTimeChooserParameters m_parameters;
    OwnPtr<WebCore::Locale> m_locale;
};

}

#endif // ENABLE(INPUT_MULTIPLE_FIELDS_UI)

#endif // DateTimeChooserImpl_h
