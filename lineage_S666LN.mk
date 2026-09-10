#
# Copyright (C) 2024 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit some common Lineage stuff.
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

-include vendor/lineage-priv/keys/keys.mk

# Inherit from S666LN device
$(call inherit-product, device/itel/S666LN/device.mk)

BOARD_VENDOR := Itel
PRODUCT_NAME := lineage_S666LN
PRODUCT_DEVICE := S666LN
PRODUCT_MANUFACTURER := ITEL
PRODUCT_BRAND := Itel
PRODUCT_MODEL := itel S666LN

PRODUCT_GMS_CLIENTID_BASE := android-transsion

# Build Fingerprint
BUILD_FINGERPRINT := Itel/S666LN-OP/itel-S666LN:13/TP1A.220624.014/251212V1661:user/release-keys
TARGET_BUILD_FINGERPRINT := $(BUILD_FINGERPRINT)

PRODUCT_BUILD_PROP_OVERRIDES += \
    BUILD_FINGERPRINT=$(BUILD_FINGERPRINT) \
    PRIVATE_BUILD_DESC="sys_tssi_64_armv82_itel-user 13 TP1A.220624.014 974711 release-keys" \
    PRODUCT_NAME=S666LN-OP \
    TARGET_DEVICE=itel-S666LN \
    BuildDesc="sys_tssi_64_armv82_itel-user 13 TP1A.220624.014 974711 release-keys" \
    BuildFingerprint=$(BUILD_FINGERPRINT) \
    DeviceProduct=S666LN-OP \
    DeviceName=itel-S666LN

