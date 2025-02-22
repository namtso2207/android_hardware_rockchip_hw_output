/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_DRM_CONNECTOR_H_
#define ANDROID_DRM_CONNECTOR_H_

#include "drmencoder.h"
#include "drmmode.h"
#include "drmproperty.h"

#include <stdint.h>
#include <vector>
#include <xf86drmMode.h>

namespace android {

class DrmResources;

class DrmConnector {
 public:
  DrmConnector(DrmResources *drm, drmModeConnectorPtr c,
               DrmEncoder *current_encoder,
               std::vector<DrmEncoder *> &possible_encoders);
  DrmConnector(const DrmProperty &) = delete;
  DrmConnector &operator=(const DrmProperty &) = delete;

  int Init();

  uint32_t id() const;

  int display() const;
  void set_display(int display);

  void set_display_possible(int display_bit);

  bool built_in() const;

  int UpdateModes();

  const std::vector<DrmMode> &modes() const {
    return modes_;
  }
  const DrmMode &best_mode() const;
  const DrmMode &active_mode() const;
  const DrmMode &current_mode() const;
  void set_best_mode(const DrmMode &mode);
  void set_active_mode(const DrmMode &mode);
  void set_current_mode(const DrmMode &mode);
  void SetDpmsMode(uint32_t dpms_mode);

  const DrmProperty &dpms_property() const;
  const DrmProperty &crtc_id_property() const;
  const DrmProperty &hdmi_output_mode_capacity_property() const;
  const DrmProperty &hdmi_output_depth_capacity_property() const;
  const std::vector<DrmEncoder *> &possible_encoders() const {
    return possible_encoders_;
  }

  uint32_t connector_id();
  DrmEncoder *encoder() const;
  void set_encoder(DrmEncoder *encoder);

  drmModeConnection state() const;
  void force_disconnect(bool force);

  uint32_t get_type() { return type_; }
  uint32_t type_id() const { return type_id_; };
  int possible_displays() { return possible_displays_; }

  uint32_t mm_width() const;
  uint32_t mm_height() const;
  drmModeConnectorPtr get_connector() { return connector_; }
  void update_state(drmModeConnection state);
  void update_size(int w, int h);
  void dump_connector(std::ostringstream *out) const;

 private:
  DrmResources *drm_;

  uint32_t id_;
  DrmEncoder *encoder_;
  int display_;



  uint32_t type_;
  uint32_t type_id_;
  drmModeConnection state_;
  bool force_disconnect_;

  uint32_t mm_width_;
  uint32_t mm_height_;

  DrmMode active_mode_;
  DrmMode current_mode_;
  DrmMode best_mode_;
  std::vector<DrmMode> modes_;

  DrmProperty dpms_property_;
  DrmProperty crtc_id_property_;
  DrmProperty connector_id_;

  DrmProperty hdmi_output_mode_capacity_;
  DrmProperty hdmi_color_depth_capacity_;

  std::vector<DrmEncoder *> possible_encoders_;
  uint32_t possible_displays_;

  drmModeConnectorPtr connector_;
};
}

#endif  // ANDROID_DRM_PLANE_H_
