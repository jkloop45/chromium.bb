// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_ACCESSIBILITY_BLINK_AX_TREE_SOURCE_H_
#define CONTENT_RENDERER_ACCESSIBILITY_BLINK_AX_TREE_SOURCE_H_

#include "third_party/WebKit/public/web/WebAXObject.h"
#include "ui/accessibility/ax_node_data.h"
#include "ui/accessibility/ax_tree_source.h"

namespace content {

class RenderFrameImpl;

class BlinkAXTreeSource
    : public ui::AXTreeSource<blink::WebAXObject> {
 public:
  BlinkAXTreeSource(RenderFrameImpl* render_frame);
  virtual ~BlinkAXTreeSource();

  // Call this to have BlinkAXTreeSource collect a mapping from
  // node ids to the frame routing id for an out-of-process iframe during
  // calls to SerializeNode.
  void CollectChildFrameIdMapping(
      std::map<int32, int>* node_to_frame_routing_id_map,
      std::map<int32, int>* node_to_browser_plugin_instance_id_map);

  // Walks up the ancestor chain to see if this is a descendant of the root.
  bool IsInTree(blink::WebAXObject node) const;

  // AXTreeSource implementation.
  virtual blink::WebAXObject GetRoot() const OVERRIDE;
  virtual blink::WebAXObject GetFromId(int32 id) const OVERRIDE;
  virtual int32 GetId(blink::WebAXObject node) const OVERRIDE;
  virtual void GetChildren(
      blink::WebAXObject node,
      std::vector<blink::WebAXObject>* out_children) const OVERRIDE;
  virtual blink::WebAXObject GetParent(blink::WebAXObject node) const
      OVERRIDE;
  virtual void SerializeNode(blink::WebAXObject node,
                             ui::AXNodeData* out_data) const OVERRIDE;
  virtual bool IsValid(blink::WebAXObject node) const OVERRIDE;
  virtual bool IsEqual(blink::WebAXObject node1,
                       blink::WebAXObject node2) const OVERRIDE;
  virtual blink::WebAXObject GetNull() const OVERRIDE;

  blink::WebDocument GetMainDocument() const;

 private:
  RenderFrameImpl* render_frame_;
  std::map<int32, int>* node_to_frame_routing_id_map_;
  std::map<int32, int>* node_to_browser_plugin_instance_id_map_;
};

}  // namespace content

#endif  // CONTENT_RENDERER_ACCESSIBILITY_BLINK_AX_TREE_SOURCE_H_
