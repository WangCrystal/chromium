// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_POWER_SAVE_BLOCKER_H_
#define CONTENT_BROWSER_POWER_SAVE_BLOCKER_H_
#pragma once

#include "base/basictypes.h"

// A RAII-style class to block the system from entering low-power (sleep) mode.
class PowerSaveBlocker {
 public:
  explicit PowerSaveBlocker(bool enabled);
  ~PowerSaveBlocker();

  bool enabled() const { return enabled_; }

  // Puts the sleep mode block into effect.
  void Enable();
  // Disables the sleep block.
  void Disable();

 private:
  // Platform-specific function called when enable state is changed.
  // Guaranteed to be called only from the UI thread.
  static void ApplyBlock(bool blocked);

  // Called only from UI thread.
  static void AdjustBlockCount(int delta);

  // Invokes AdjustBlockCount on the UI thread.
  static void PostAdjustBlockCount(int delta);

  bool enabled_;

  static int blocker_count_;

  DISALLOW_COPY_AND_ASSIGN(PowerSaveBlocker);
};

#endif  // CONTENT_BROWSER_POWER_SAVE_BLOCKER_H_
