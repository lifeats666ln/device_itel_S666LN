# Clone Device Kernel Tree
git clone https://github.com/dns24/kernel_itel_s666ln device/itel/S666LN-kernel

# Clone Device Vendor Tree
git clone -b lineage-20.0 https://github.com/lifeats666ln/vendor_itel_S666LN vendor/itel/S666LN

# Clone Device Hardware
git clone -b lineage-20.0 https://github.com/swaraloka-lab/hardware_millennium hardware/transsion

# Clone Device Hardware Mediatek
rm -rf hardware/mediatek
git clone -b lineage-20 https://github.com/LineageOS/android_hardware_mediatek hardware/mediatek

# Clone Device Mediatek Sepolicy Vendor
git clone -b lineage-20 https://github.com/LineageOS/android_device_mediatek_sepolicy_vndr device/mediatek/sepolicy_vndr
