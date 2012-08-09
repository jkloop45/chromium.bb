/*
 * Copyright (C) 2010, 2011 Apple Inc. All Rights Reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

// This all-in-one cpp file cuts down on template bloat to allow us to build our Windows release build.

#include "ActiveDOMObject.cpp"
#include "Attr.cpp"
#include "BeforeTextInsertedEvent.cpp"
#include "BeforeUnloadEvent.cpp"
#include "CDATASection.cpp"
#include "CharacterData.cpp"
#include "CheckedRadioButtons.cpp"
#include "ChildListMutationScope.cpp"
#include "ChildNodeList.cpp"
#include "ClassNodeList.cpp"
#include "ClientRect.cpp"
#include "ClientRectList.cpp"
#include "Clipboard.cpp"
#include "ClipboardEvent.cpp"
#include "Comment.cpp"
#include "CompositionEvent.cpp"
#include "ContainerNode.cpp"
#include "ContainerNodeAlgorithms.cpp"
#include "ContextDestructionObserver.cpp"
#include "CustomEvent.cpp"
#include "DOMCoreException.cpp"
#include "DOMImplementation.cpp"
#include "DOMStringList.cpp"
#include "DOMStringMap.cpp"
#include "DatasetDOMStringMap.cpp"
#include "DecodedDataDocumentParser.cpp"
#include "DeviceMotionController.cpp"
#include "DeviceMotionData.cpp"
#include "DeviceMotionEvent.cpp"
#include "DeviceOrientation.cpp"
#include "DeviceOrientationController.cpp"
#include "DeviceOrientationEvent.cpp"
#include "Document.cpp"
#include "DocumentEventQueue.cpp"
#include "DocumentFragment.cpp"
#include "DocumentMarker.cpp"
#include "DocumentMarkerController.cpp"
#include "DocumentOrderedMap.cpp"
#include "DocumentParser.cpp"
#include "DocumentType.cpp"
#include "DynamicNodeList.cpp"
#include "EditingText.cpp"
#include "Element.cpp"
#include "ElementAttributeData.cpp"
#include "EntityReference.cpp"
#include "ErrorEvent.cpp"
#include "Event.cpp"
#include "EventContext.cpp"
#include "EventDispatchMediator.cpp"
#include "EventDispatcher.cpp"
#include "EventException.cpp"
#include "EventListenerMap.cpp"
#include "EventNames.cpp"
#include "EventTarget.cpp"
#include "ExceptionBase.cpp"
#include "ExceptionCodePlaceholder.cpp"
#include "IconURL.cpp"
#include "KeyboardEvent.cpp"
#include "MessageChannel.cpp"
#include "MessageEvent.cpp"
#include "MessagePort.cpp"
#include "MessagePortChannel.cpp"
#include "MouseEvent.cpp"
#include "MouseRelatedEvent.cpp"
#include "MutationEvent.cpp"
#include "MutationObserverInterestGroup.cpp"
#include "MutationObserverRegistration.cpp"
#include "MutationRecord.cpp"
#include "NameNodeList.cpp"
#include "NodeFilter.cpp"
#include "NodeFilterCondition.cpp"
#include "NodeIterator.cpp"
#include "NodeRenderingContext.cpp"
#include "Notation.cpp"
#include "OverflowEvent.cpp"
#include "PageTransitionEvent.cpp"
#include "PendingScript.cpp"
#include "PopStateEvent.cpp"
#include "Position.cpp"
#include "PositionIterator.cpp"
#include "ProcessingInstruction.cpp"
#include "ProgressEvent.cpp"
#include "Range.cpp"
#include "RangeException.cpp"
#include "RegisteredEventListener.cpp"
#include "ScopedEventQueue.cpp"
#include "ScriptElement.cpp"
#include "ScriptExecutionContext.cpp"
#include "ScriptRunner.cpp"
#include "ScriptableDocumentParser.cpp"
#include "SecurityContext.cpp"
#include "SelectorQuery.cpp"
#include "ShadowRoot.cpp"
#include "ShadowTree.cpp"
#include "SpaceSplitString.cpp"
#include "StaticHashSetNodeList.cpp"
#include "StaticNodeList.cpp"
#include "StyleElement.cpp"
#include "StyledElement.cpp"
#include "TagNodeList.cpp"
#include "Text.cpp"
#include "TextEvent.cpp"
#include "Touch.cpp"
#include "TouchEvent.cpp"
#include "TouchList.cpp"
#include "TransformSourceLibxslt.cpp"
#include "Traversal.cpp"
#include "TreeScope.cpp"
#include "TreeScopeAdjuster.cpp"
#include "TreeScopeAdopter.cpp"
#include "TreeWalker.cpp"
#include "UIEvent.cpp"
#include "UIEventWithKeyState.cpp"
#include "UserGestureIndicator.cpp"
#include "UserTypingGestureIndicator.cpp"
#include "ViewportArguments.cpp"
#include "WebKitAnimationEvent.cpp"
#include "WebKitMutationObserver.cpp"
#include "WebKitNamedFlow.cpp"
#include "WebKitTransitionEvent.cpp"
#include "WheelEvent.cpp"
#include "WindowEventContext.cpp"
#include "XMLDocumentParser.cpp"
#include "XMLDocumentParserScope.cpp"