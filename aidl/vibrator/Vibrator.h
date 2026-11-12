/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/android/hardware/vibrator/BnVibrator.h>
#include <array>
#include <map>

namespace aidl {
namespace android {
namespace hardware {
namespace vibrator {

const std::string kVibratorState = "/sys/class/leds/vibrator_single/state";
const std::string kVibratorDuration = "/sys/class/leds/vibrator_single/duration";
const std::string kVibratorActivate = "/sys/class/leds/vibrator_single/activate";
const std::string kVibratorSeq = "/sys/class/leds/vibrator_single/seq";

#ifdef VIBRATOR_SUPPORTS_EFFECTS
const std::string kVibratorStrength = "/sys/class/leds/vibrator_single/gain";
/* Unity gain is 0x80 */
const int kVibratorStrengthMax = 0xB0;
#endif

static std::map<EffectStrength, float> vibStrengths = {
        {EffectStrength::LIGHT, 0.5}, {EffectStrength::MEDIUM, 0.75}, {EffectStrength::STRONG, 1}};

/* Waveforms in aw8622x_haptic.bin */
const int32_t kWaveNone = 0;
const int32_t kWaveStrongClick = 1; /* 28 ms, full scale */
const int32_t kWaveClick = 3;       /* 30 ms, 2/3 scale */
const int32_t kWaveTick = 4;        /* 4 ms, 2/3 scale */
const int32_t kWaveSoftTick = 5;    /* 4 ms, 1/4 scale */

/* Shorter requests get stretched to the 30 ms click by the driver */
const int32_t kVibratorMinDurationMs = 15;

struct VibEffect {
    std::array<int32_t, 2> waves; /* played back to back */
    int32_t durationMs;
};

class Vibrator : public BnVibrator {
  public:
#ifdef VIBRATOR_SUPPORTS_EFFECTS
    Vibrator();
#endif
    ndk::ScopedAStatus getCapabilities(int32_t* _aidl_return) override;
    ndk::ScopedAStatus off() override;
    ndk::ScopedAStatus on(int32_t timeoutMs,
                          const std::shared_ptr<IVibratorCallback>& callback) override;
    ndk::ScopedAStatus perform(Effect effect, EffectStrength strength,
                               const std::shared_ptr<IVibratorCallback>& callback,
                               int32_t* _aidl_return) override;
    ndk::ScopedAStatus getSupportedEffects(std::vector<Effect>* _aidl_return) override;
    ndk::ScopedAStatus setAmplitude(float amplitude) override;
    ndk::ScopedAStatus setExternalControl(bool enabled) override;
    ndk::ScopedAStatus getCompositionDelayMax(int32_t* maxDelayMs);
    ndk::ScopedAStatus getCompositionSizeMax(int32_t* maxSize);
    ndk::ScopedAStatus getSupportedPrimitives(std::vector<CompositePrimitive>* supported) override;
    ndk::ScopedAStatus getPrimitiveDuration(CompositePrimitive primitive,
                                            int32_t* durationMs) override;
    ndk::ScopedAStatus compose(const std::vector<CompositeEffect>& composite,
                               const std::shared_ptr<IVibratorCallback>& callback) override;
    ndk::ScopedAStatus getSupportedAlwaysOnEffects(std::vector<Effect>* _aidl_return) override;
    ndk::ScopedAStatus alwaysOnEnable(int32_t id, Effect effect, EffectStrength strength) override;
    ndk::ScopedAStatus alwaysOnDisable(int32_t id) override;
    ndk::ScopedAStatus getResonantFrequency(float* resonantFreqHz) override;
    ndk::ScopedAStatus getQFactor(float* qFactor) override;
    ndk::ScopedAStatus getFrequencyResolution(float* freqResolutionHz) override;
    ndk::ScopedAStatus getFrequencyMinimum(float* freqMinimumHz) override;
    ndk::ScopedAStatus getBandwidthAmplitudeMap(std::vector<float>* _aidl_return) override;
    ndk::ScopedAStatus getPwlePrimitiveDurationMax(int32_t* durationMs) override;
    ndk::ScopedAStatus getPwleCompositionSizeMax(int32_t* maxSize) override;
    ndk::ScopedAStatus getSupportedBraking(std::vector<Braking>* supported) override;
    ndk::ScopedAStatus composePwle(const std::vector<PrimitivePwle>& composite,
                                   const std::shared_ptr<IVibratorCallback>& callback) override;

  private:
    static ndk::ScopedAStatus setNode(const std::string path, const int32_t value);
    static ndk::ScopedAStatus setNode(const std::string path, const std::string value);
    std::map<Effect, VibEffect> vibEffects = {
            {Effect::TEXTURE_TICK, {{kWaveSoftTick, kWaveNone}, 5}},
            {Effect::TICK, {{kWaveTick, kWaveNone}, 5}},
            {Effect::POP, {{kWaveTick, kWaveSoftTick}, 9}},
            {Effect::CLICK, {{kWaveClick, kWaveNone}, 30}},
            {Effect::HEAVY_CLICK, {{kWaveStrongClick, kWaveNone}, 28}},
            {Effect::THUD, {{kWaveStrongClick, kWaveClick}, 58}},
    };
#ifdef VIBRATOR_SUPPORTS_EFFECTS
    static bool exists(const std::string path);
    bool mVibratorStrengthSupported;
#endif
    ndk::ScopedAStatus play(const std::array<int32_t, 2>& waves);
    ndk::ScopedAStatus activate(int32_t timeoutMs);
};

}  // namespace vibrator
}  // namespace hardware
}  // namespace android
}  // namespace aidl
