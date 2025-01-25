cmd_/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_sta_cmd.o := clang -Wp,-MMD,/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/.mlan_sta_cmd.o.d  -nostdinc -isystem /opt/prebuilt-android-clang/clang-r450784e/lib64/clang/14.0.7/include -I/home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include -I./arch/arm64/include/generated -I/home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include -I./include -I/home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi -I./arch/arm64/include/generated/uapi -I/home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi -I./include/generated/uapi -include /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/compiler-version.h -include /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kconfig.h -include /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -DKASAN_SHADOW_SCALE_SHIFT= -Qunused-arguments -fmacro-prefix-map=/home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/= -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -fno-PIE -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Wno-format-security -std=gnu89 --target=aarch64-linux-gnu -fintegrated-as -Werror=unknown-warning-option -Werror=ignored-optimization-argument -mgeneral-regs-only -DCONFIG_CC_HAS_K_CONSTRAINT=1 -Wno-psabi -fno-asynchronous-unwind-tables -fno-unwind-tables -mbranch-protection=pac-ret+leaf -Wa,-march=armv8.5-a -DARM64_ASM_ARCH='"armv8.5-a"' -ffixed-x18 -DKASAN_SHADOW_SCALE_SHIFT= -fno-delete-null-pointer-checks -Wno-frame-address -Wno-address-of-packed-member -O2 -Wframe-larger-than=2048 -fstack-protector-strong -Werror -Wno-gnu -mno-global-merge -Wno-unused-but-set-variable -Wno-unused-const-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -ftrivial-auto-var-init=zero -enable-trivial-auto-var-init-zero-knowing-it-will-be-removed-from-clang -fno-stack-clash-protection -g -gdwarf-4 -fsanitize=shadow-call-stack -fno-lto -flto=thin -fsplit-lto-unit -fvisibility=default -fsanitize=cfi -fsanitize-cfi-cross-dso -fno-sanitize-cfi-canonical-jump-tables -fno-sanitize-trap=cfi -fno-sanitize-blacklist -Wdeclaration-after-statement -Wvla -Wno-pointer-sign -Wno-array-bounds -fno-strict-overflow -fno-stack-check -Werror=date-time -Werror=incompatible-pointer-types -Wno-initializer-overrides -Wno-format -Wno-sign-compare -Wno-format-zero-length -Wno-pointer-to-enum-cast -Wno-tautological-constant-out-of-range-compare -Wno-unaligned-access -mstack-protector-guard=sysreg -mstack-protector-guard-reg=sp_el0 -mstack-protector-guard-offset=1504 -I/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan -DLINUX -DIMX_SUPPORT -I/home/uqtony/android_src/out/target/product/eideal_8mm/obj/KERNEL_OBJ/include -DFPNUM='"92"' -DDEBUG_LEVEL1 -DMLAN_64BIT -DSTA_SUPPORT -DREASSOCIATION -DUAP_SUPPORT -DWIFI_DIRECT_SUPPORT -DMFG_CMD_SUPPORT -DSDIO_SUSPEND_RESUME -DDFS_TESTING_SUPPORT -DSD8978 -DSD8997 -DSD8987 -DSD8801 -DSD9098 -DPCIE8997 -DPCIE9098 -DSDIO -DSDIO_MMC -DPCIE -DSTA_WEXT -DSTA_CFG80211 -DUAP_WEXT -DUAP_CFG80211  -fsanitize=array-bounds -fsanitize=local-bounds -fsanitize-undefined-trap-on-error  -DMODULE  -DKBUILD_BASENAME='"mlan_sta_cmd"' -DKBUILD_MODNAME='"mlan"' -D__KBUILD_MODNAME=kmod_mlan -c -o /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_sta_cmd.o /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_sta_cmd.c

source_/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_sta_cmd.o := /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_sta_cmd.c

deps_/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_sta_cmd.o := \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/compiler_types.h \
    $(wildcard include/config/HAVE_ARCH_COMPILER_H) \
    $(wildcard include/config/CC_HAS_ASM_INLINE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/compiler_attributes.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/compiler-clang.h \
    $(wildcard include/config/ARCH_USE_BUILTIN_BSWAP) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/compiler.h \
    $(wildcard include/config/CFI_CLANG) \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_decl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_ioctl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_ieee.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_join.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_util.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_fw.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_main.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_wmm.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_11n.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_11n_aggr.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_11n_rxreorder.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_11ac.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_11ax.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_11h.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_sdio.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_meas.h \
  /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_pcie.h \

/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_sta_cmd.o: $(deps_/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_sta_cmd.o)

$(deps_/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan/mlan_sta_cmd.o):
