#!/bin/bash

RET=0
echo "- Applying fenrir compatiblity patches"
cd system/core
curl https://raw.githubusercontent.com/MillenniumOSS/patches/refs/heads/seventeen-yaap/system/core/0002-fastbootd-Always-return-false-for-GetDeviceLockStatu.patch | git am || {
  RET=1
  git am --abort >/dev/null 2>&1
}
cd ../
cd fs/fs_mgr
curl https://raw.githubusercontent.com/MillenniumOSS/patches/refs/heads/seventeen-yaap/system/fs/fs_mgr/0001-libfs_avb-Allow-LKs-patched-with-fenrir-to-boot-on-A.patch | git am || {
  RET=1
  git am --abort >/dev/null 2>&1
}
cd ../../../

if [ $RET -ne 0 ]; then
  echo "ERROR: Patch is not applied! Maybe it's already patched, or you'll have to adapt it to this specific rom source?"
else
  echo "OK: All patched"
fi
