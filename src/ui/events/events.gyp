# Copyright 2013 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'variables': {
    'chromium_code': 1,
  },
  'targets': [
    {
      # GN version: //ui/events:dom4_keycode_converter
      'target_name': 'dom4_keycode_converter',
      'type': 'static_library',
      'dependencies': [
        '<(DEPTH)/base/base.gyp:base',
      ],
      'sources': [
        # Note: sources list duplicated in GN build.
        'keycodes/dom4/keycode_converter.cc',
        'keycodes/dom4/keycode_converter.h',
        'keycodes/dom4/keycode_converter_data.h',
      ],
    },
    {
      # GN version: //ui/events:events_base
      'target_name': 'events_base',
      'type': '<(component)',
      'dependencies': [
        '<(DEPTH)/base/base.gyp:base',
        '<(DEPTH)/base/third_party/dynamic_annotations/dynamic_annotations.gyp:dynamic_annotations',
        '<(DEPTH)/skia/skia.gyp:skia',
        '../gfx/gfx.gyp:gfx',
        '../gfx/gfx.gyp:gfx_geometry',
        'dom4_keycode_converter',
      ],
      'defines': [
        'EVENTS_BASE_IMPLEMENTATION',
      ],
      'sources': [
        # Note: sources list duplicated in GN build.
        'device_data_manager.cc',
        'device_data_manager.h',
        'device_hotplug_event_observer.h',
        'event_constants.h',
        'event_switches.cc',
        'event_switches.h',
        'events_base_export.h',
        'gesture_event_details.cc',
        'gesture_event_details.h',
        'gestures/fling_curve.cc',
        'gestures/fling_curve.h',
        'gestures/gesture_configuration.cc',
        'gestures/gesture_configuration.h',
        'keycodes/keyboard_code_conversion.cc',
        'keycodes/keyboard_code_conversion.h',
        'keycodes/keyboard_code_conversion_android.cc',
        'keycodes/keyboard_code_conversion_android.h',
        'keycodes/keyboard_code_conversion_mac.h',
        'keycodes/keyboard_code_conversion_mac.mm',
        'keycodes/keyboard_code_conversion_win.cc',
        'keycodes/keyboard_code_conversion_win.h',
        'keycodes/keyboard_code_conversion_x.cc',
        'keycodes/keyboard_code_conversion_x.h',
        'keycodes/keyboard_codes.h',
        'latency_info.cc',
        'latency_info.h',
        'touchscreen_device.cc',
        'touchscreen_device.h',
        'x/device_data_manager_x11.cc',
        'x/device_data_manager_x11.h',
        'x/device_list_cache_x.cc',
        'x/device_list_cache_x.h',
        'x/hotplug_event_handler_x11.cc',
        'x/hotplug_event_handler_x11.h',
        'x/keysym_to_unicode.cc',
        'x/keysym_to_unicode.h',
        'x/touch_factory_x11.cc',
        'x/touch_factory_x11.h',
      ],
      'export_dependent_settings': [
        '../../ui/gfx/gfx.gyp:gfx',
      ],
      'conditions': [
        ['use_x11==1', {
          'dependencies': [
            '../../build/linux/system.gyp:x11',
            '../gfx/x/gfx_x11.gyp:gfx_x11',
          ],
        }],
      ],
    },
    {
      # GN version: //ui/events
      'target_name': 'events',
      'type': '<(component)',
      'dependencies': [
        '<(DEPTH)/base/base.gyp:base',
        '<(DEPTH)/base/third_party/dynamic_annotations/dynamic_annotations.gyp:dynamic_annotations',
        '<(DEPTH)/skia/skia.gyp:skia',
        '../gfx/gfx.gyp:gfx',
        '../gfx/gfx.gyp:gfx_geometry',
        'events_base',
        'gesture_detection',
      ],
      'defines': [
        'EVENTS_IMPLEMENTATION',
      ],
      'sources': [
        # Note: sources list duplicated in GN build.
        'cocoa/cocoa_event_utils.h',
        'cocoa/cocoa_event_utils.mm',
        'cocoa/events_mac.mm',
        'event.cc',
        'event.h',
        'event_dispatcher.cc',
        'event_dispatcher.h',
        'event_handler.cc',
        'event_handler.h',
        'event_processor.cc',
        'event_processor.h',
        'event_rewriter.h',
        'event_source.cc',
        'event_source.h',
        'event_target.cc',
        'event_target.h',
        'event_target_iterator.h',
        'event_targeter.cc',
        'event_targeter.h',
        'event_utils.cc',
        'event_utils.h',
        'events_export.h',
        'events_stub.cc',
        'gestures/gesture_provider_aura.cc',
        'gestures/gesture_provider_aura.h',
        'gestures/gesture_recognizer.h',
        'gestures/gesture_recognizer_impl.cc',
        'gestures/gesture_recognizer_impl.h',
        'gestures/gesture_recognizer_impl_mac.cc',
        'gestures/gesture_types.h',
        'gestures/motion_event_aura.cc',
        'gestures/motion_event_aura.h',
        'ozone/events_ozone.cc',
        'win/events_win.cc',
        'x/events_x.cc',
        'linux/text_edit_command_auralinux.cc',
        'linux/text_edit_command_auralinux.h',
        'linux/text_edit_key_bindings_delegate_auralinux.cc',
        'linux/text_edit_key_bindings_delegate_auralinux.h',
      ],
      'conditions': [
        ['use_x11==1', {
          'dependencies': [
            '../../build/linux/system.gyp:x11',
          ],
        }],
        ['use_aura==0', {
          'sources!': [
            'gestures/gesture_provider_aura.cc',
            'gestures/gesture_provider_aura.h',
            'gestures/gesture_recognizer.h',
            'gestures/gesture_recognizer_impl.cc',
            'gestures/gesture_recognizer_impl.h',
            'gestures/gesture_types.h',
            'gestures/motion_event_aura.cc',
            'gestures/motion_event_aura.h',
          ],
        }],
        # We explicitly enumerate the platforms we _do_ provide native cracking
        # for here.
        ['OS=="win" or OS=="mac" or use_x11==1 or use_ozone==1', {
          'sources!': [
            'events_stub.cc',
          ],
        }],
        ['chromeos==1', {
          'sources!': [
            'linux/text_edit_command_auralinux.cc',
            'linux/text_edit_command_auralinux.h',
            'linux/text_edit_key_bindings_delegate_auralinux.cc',
            'linux/text_edit_key_bindings_delegate_auralinux.h',
          ],
        }],
      ],
    },
    {
      # GN version: //ui/events:gesture_detection
      'target_name': 'gesture_detection',
      'type': '<(component)',
      'dependencies': [
        '<(DEPTH)/base/base.gyp:base',
        '<(DEPTH)/base/third_party/dynamic_annotations/dynamic_annotations.gyp:dynamic_annotations',
        '../gfx/gfx.gyp:gfx',
        '../gfx/gfx.gyp:gfx_geometry',
        'events_base',
      ],
      'defines': [
        'GESTURE_DETECTION_IMPLEMENTATION',
      ],
      'sources': [
        # Note: sources list duplicated in GN build.
        'gesture_detection/bitset_32.h',
        'gesture_detection/filtered_gesture_provider.cc',
        'gesture_detection/filtered_gesture_provider.h',
        'gesture_detection/gesture_config_helper.h',
        'gesture_detection/gesture_config_helper_android.cc',
        'gesture_detection/gesture_config_helper_aura.cc',
        'gesture_detection/gesture_detection_export.h',
        'gesture_detection/gesture_detector.cc',
        'gesture_detection/gesture_detector.h',
        'gesture_detection/gesture_event_data.cc',
        'gesture_detection/gesture_event_data.h',
        'gesture_detection/gesture_event_data_packet.cc',
        'gesture_detection/gesture_event_data_packet.h',
        'gesture_detection/gesture_provider.cc',
        'gesture_detection/gesture_provider.h',
        'gesture_detection/gesture_touch_uma_histogram.cc',
        'gesture_detection/gesture_touch_uma_histogram.h',
        'gesture_detection/motion_event.cc',
        'gesture_detection/motion_event.h',
        'gesture_detection/motion_event_buffer.cc',
        'gesture_detection/motion_event_buffer.h',
        'gesture_detection/motion_event_generic.cc',
        'gesture_detection/motion_event_generic.h',
        'gesture_detection/scale_gesture_detector.cc',
        'gesture_detection/scale_gesture_detector.h',
        'gesture_detection/snap_scroll_controller.cc',
        'gesture_detection/snap_scroll_controller.h',
        'gesture_detection/touch_disposition_gesture_filter.cc',
        'gesture_detection/touch_disposition_gesture_filter.h',
        'gesture_detection/velocity_tracker_state.cc',
        'gesture_detection/velocity_tracker_state.h',
        'gesture_detection/velocity_tracker.cc',
        'gesture_detection/velocity_tracker.h',
      ],
      'conditions': [
        ['use_aura!=1 and OS!="android"', {
          'sources': [
            'gesture_detection/gesture_config_helper.cc',
          ],
        }],
      ],
    },
    {
      # GN version: //ui/events:test_support
      'target_name': 'events_test_support',
      'type': 'static_library',
      'dependencies': [
        '<(DEPTH)/base/base.gyp:base',
        '<(DEPTH)/skia/skia.gyp:skia',
        '../gfx/gfx.gyp:gfx_geometry',
        'events',
        'events_base',
        'gesture_detection',
        'platform/events_platform.gyp:events_platform',
      ],
      'sources': [
        # Note: sources list duplicated in GN build.
        'test/cocoa_test_event_utils.h',
        'test/cocoa_test_event_utils.mm',
        'test/event_generator.cc',
        'test/event_generator.h',
        'test/events_test_utils.cc',
        'test/events_test_utils.h',
        'test/events_test_utils_x11.cc',
        'test/events_test_utils_x11.h',
        'test/mock_motion_event.cc',
        'test/mock_motion_event.h',
        'test/platform_event_waiter.cc',
        'test/platform_event_waiter.h',
        'test/test_event_handler.cc',
        'test/test_event_handler.h',
        'test/test_event_processor.cc',
        'test/test_event_processor.h',
        'test/test_event_target.cc',
        'test/test_event_target.h',
      ],
      'conditions': [
        ['OS=="ios"', {
          # The cocoa files don't apply to iOS.
          'sources/': [['exclude', 'cocoa']],
        }],
      ],
    },
    {
      # GN version: //ui/events:events_unittests
      'target_name': 'events_unittests',
      'type': '<(gtest_target_type)',
      'dependencies': [
        '<(DEPTH)/base/base.gyp:base',
        '<(DEPTH)/skia/skia.gyp:skia',
        '../gfx/gfx.gyp:gfx',
        '../gfx/gfx.gyp:gfx_geometry',
        '../gfx/gfx.gyp:gfx_test_support',
        'dom4_keycode_converter',
        'events',
        'events_base',
        'events_test_support',
        'gesture_detection',
        'platform/events_platform.gyp:events_platform',
      ],
      'sources': [
        # Note: sources list duplicated in GN build.
        'cocoa/events_mac_unittest.mm',
        'event_dispatcher_unittest.cc',
        'event_processor_unittest.cc',
        'event_rewriter_unittest.cc',
        'event_unittest.cc',
        'gesture_detection/bitset_32_unittest.cc',
        'gesture_detection/gesture_event_data_packet_unittest.cc',
        'gesture_detection/gesture_provider_unittest.cc',
        'gesture_detection/motion_event_buffer_unittest.cc',
        'gesture_detection/motion_event_generic_unittest.cc',
        'gesture_detection/touch_disposition_gesture_filter_unittest.cc',
        'gesture_detection/velocity_tracker_unittest.cc',
        'gestures/fling_curve_unittest.cc',
        'gestures/gesture_provider_aura_unittest.cc',
        'gestures/motion_event_aura_unittest.cc',
        'keycodes/dom4/keycode_converter_unittest.cc',
        'latency_info_unittest.cc',
        'platform/platform_event_source_unittest.cc',
        'x/events_x_unittest.cc',
      ],
      'conditions': [
        ['use_x11==1', {
          'dependencies': [
            '../../build/linux/system.gyp:x11',
            '../gfx/x/gfx_x11.gyp:gfx_x11',
          ],
        }],
        ['use_ozone==1', {
          'sources': [
            'ozone/evdev/key_event_converter_evdev_unittest.cc',
            'ozone/evdev/touch_event_converter_evdev_unittest.cc',
          ],
          'dependencies': [
            'ozone/events_ozone.gyp:events_ozone',
            'ozone/events_ozone.gyp:events_ozone_evdev',
          ]
        }],
        ['use_aura==0', {
          'sources!': [
            'gestures/gesture_provider_aura_unittest.cc',
            'gestures/motion_event_aura_unittest.cc',
          ],
        }],
        ['OS=="linux" and use_allocator!="none"', {
          'dependencies': [
            '<(DEPTH)/base/allocator/allocator.gyp:allocator',
          ],
        }],
        # Exclude tests that rely on event_utils.h for platforms that do not
        # provide native cracking, i.e., platforms that use events_stub.cc.
        ['OS!="win" and use_x11!=1 and use_ozone!=1', {
          'sources!': [
            'event_unittest.cc',
          ],
        }],
        ['OS == "android"', {
          'dependencies': [
            '../../testing/android/native_test.gyp:native_test_native_code',
          ],
        }],
      ],
    },
  ],
  'conditions': [
  ],
}
