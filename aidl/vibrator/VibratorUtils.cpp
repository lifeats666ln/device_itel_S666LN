/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Vibrator.h"

#include <android-base/logging.h>
#include <fstream>

namespace aidl {
namespace android {
namespace hardware {
namespace vibrator {

ndk::ScopedAStatus Vibrator::setNode(const std::string path, const int32_t value) {
    return setNode(path, std::to_string(value));
}

ndk::ScopedAStatus Vibrator::setNode(const std::string path, const std::string value) {
    std::ofstream file(path);

    if (!file.is_open()) {
        LOG(ERROR) << "Failed to write " << value << " to " << path;
        return ndk::ScopedAStatus(AStatus_fromExceptionCode(EX_SERVICE_SPECIFIC));
    }

    file << value << std::endl;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Vibrator::play(const std::array<int32_t, 2>& waves) {
    ndk::ScopedAStatus status;

    status = setNode(kVibratorState, 1);
    if (!status.isOk()) return status;

    /* A duration below 30 ms selects one-shot RAM playback and clears the sequence */
    status = setNode(kVibratorDuration, 1);
    if (!status.isOk()) return status;

    for (size_t i = 0; i < waves.size(); i++) {
        status = setNode(kVibratorSeq, std::to_string(i) + " " + std::to_string(waves[i]));
        if (!status.isOk()) return status;
    }

    return setNode(kVibratorActivate, 1);
}

ndk::ScopedAStatus Vibrator::activate(int32_t timeoutMs) {
    ndk::ScopedAStatus status;

    if (timeoutMs > 0 && timeoutMs < kVibratorMinDurationMs) return play({kWaveTick, kWaveNone});

    /* The driver replaces these durations with its own presets */
    switch (timeoutMs) {
        case 65:
        case 95:
        case 200:
            timeoutMs++;
            break;
    }

    /* timeoutMs under 1 = turn off vibrator */
    if (timeoutMs < 1) {
        return off();
    }

    status = setNode(kVibratorState, 1);
    if (!status.isOk()) return status;

    status = setNode(kVibratorDuration, timeoutMs);
    if (!status.isOk()) return status;

    status = setNode(kVibratorActivate, 1);
    if (!status.isOk()) return status;

    return ndk::ScopedAStatus::ok();
}

#ifdef VIBRATOR_SUPPORTS_EFFECTS
bool Vibrator::exists(const std::string path) {
    std::ofstream file(path);
    return file.is_open();
}
#endif

}  // namespace vibrator
}  // namespace hardware
}  // namespace android
}  // namespace aidl
