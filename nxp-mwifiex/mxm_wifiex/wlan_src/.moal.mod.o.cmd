cmd_/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/moal.mod.o := clang -Wp,-MMD,/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/.moal.mod.o.d -nostdinc -isystem /opt/prebuilt-android-clang/clang-r450784e/lib64/clang/14.0.7/include -I/home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include -I./arch/arm64/include/generated -I/home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include -I./include -I/home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi -I./arch/arm64/include/generated/uapi -I/home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi -I./include/generated/uapi -include /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/compiler-version.h -include /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kconfig.h -include /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -DKASAN_SHADOW_SCALE_SHIFT= -Qunused-arguments -fmacro-prefix-map=/home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/= -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -fno-PIE -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Wno-format-security -std=gnu89 --target=aarch64-linux-gnu -fintegrated-as -Werror=unknown-warning-option -Werror=ignored-optimization-argument -mgeneral-regs-only -DCONFIG_CC_HAS_K_CONSTRAINT=1 -Wno-psabi -fno-asynchronous-unwind-tables -fno-unwind-tables -mbranch-protection=pac-ret+leaf -Wa,-march=armv8.5-a -DARM64_ASM_ARCH='"armv8.5-a"' -ffixed-x18 -DKASAN_SHADOW_SCALE_SHIFT= -fno-delete-null-pointer-checks -Wno-frame-address -Wno-address-of-packed-member -O2 -Wframe-larger-than=2048 -fstack-protector-strong -Werror -Wno-gnu -mno-global-merge -Wno-unused-but-set-variable -Wno-unused-const-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -ftrivial-auto-var-init=zero -enable-trivial-auto-var-init-zero-knowing-it-will-be-removed-from-clang -fno-stack-clash-protection -g -gdwarf-4 -fsanitize=shadow-call-stack -fno-lto -flto=thin -fsplit-lto-unit -fvisibility=default -Wdeclaration-after-statement -Wvla -Wno-pointer-sign -Wno-array-bounds -fno-strict-overflow -fno-stack-check -Werror=date-time -Werror=incompatible-pointer-types -Wno-initializer-overrides -Wno-format -Wno-sign-compare -Wno-format-zero-length -Wno-pointer-to-enum-cast -Wno-tautological-constant-out-of-range-compare -Wno-unaligned-access -mstack-protector-guard=sysreg -mstack-protector-guard-reg=sp_el0 -mstack-protector-guard-offset=1504 -I/mlan -DLINUX -DIMX_SUPPORT -I/home/uqtony/android_src/out/target/product/eideal_8mm/obj/KERNEL_OBJ/include -DFPNUM='"92"' -DDEBUG_LEVEL1 -DSTA_SUPPORT -DREASSOCIATION -DUAP_SUPPORT -DWIFI_DIRECT_SUPPORT -DMFG_CMD_SUPPORT -DSDIO_SUSPEND_RESUME -DDFS_TESTING_SUPPORT -DSD8978 -DSD8997 -DSD8987 -DSD8801 -DSD9098 -DPCIE8997 -DPCIE9098 -DSDIO -DSDIO_MMC -DPCIE -I/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan -DLINUX -DIMX_SUPPORT -I/home/uqtony/android_src/out/target/product/eideal_8mm/obj/KERNEL_OBJ/include -DFPNUM='"92"' -DDEBUG_LEVEL1 -DMLAN_64BIT -DSTA_SUPPORT -DREASSOCIATION -DUAP_SUPPORT -DWIFI_DIRECT_SUPPORT -DMFG_CMD_SUPPORT -DSDIO_SUSPEND_RESUME -DDFS_TESTING_SUPPORT -DSD8978 -DSD8997 -DSD8987 -DSD8801 -DSD9098 -DPCIE8997 -DPCIE9098 -DSDIO -DSDIO_MMC -DPCIE -DSTA_WEXT -DSTA_CFG80211 -DUAP_WEXT -DUAP_CFG80211 -fsanitize=array-bounds -fsanitize=local-bounds -fsanitize-undefined-trap-on-error -DMODULE -DKBUILD_BASENAME='"moal.mod"' -DKBUILD_MODNAME='"moal"' -D__KBUILD_MODNAME=kmod_moal -c -o /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/moal.mod.o /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/moal.mod.c

source_/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/moal.mod.o := /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/moal.mod.c

deps_/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/moal.mod.o := \
    $(wildcard include/config/MODULE_UNLOAD) \
    $(wildcard include/config/RETPOLINE) \
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
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/module.h \
    $(wildcard include/config/MODULES) \
    $(wildcard include/config/SYSFS) \
    $(wildcard include/config/MODULES_TREE_LOOKUP) \
    $(wildcard include/config/LIVEPATCH) \
    $(wildcard include/config/STACKTRACE_BUILD_ID) \
    $(wildcard include/config/GENERIC_BUG) \
    $(wildcard include/config/KALLSYMS) \
    $(wildcard include/config/SMP) \
    $(wildcard include/config/TRACEPOINTS) \
    $(wildcard include/config/TREE_SRCU) \
    $(wildcard include/config/BPF_EVENTS) \
    $(wildcard include/config/JUMP_LABEL) \
    $(wildcard include/config/TRACING) \
    $(wildcard include/config/EVENT_TRACING) \
    $(wildcard include/config/FTRACE_MCOUNT_RECORD) \
    $(wildcard include/config/KPROBES) \
    $(wildcard include/config/HAVE_STATIC_CALL_INLINE) \
    $(wildcard include/config/PRINTK_INDEX) \
    $(wildcard include/config/CONSTRUCTORS) \
    $(wildcard include/config/FUNCTION_ERROR_INJECTION) \
    $(wildcard include/config/MODULE_SIG) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/list.h \
    $(wildcard include/config/DEBUG_LIST) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/types.h \
    $(wildcard include/config/HAVE_UID16) \
    $(wildcard include/config/UID16) \
    $(wildcard include/config/ARCH_DMA_ADDR_T_64BIT) \
    $(wildcard include/config/PHYS_ADDR_T_64BIT) \
    $(wildcard include/config/64BIT) \
    $(wildcard include/config/ARCH_32BIT_USTAT_F_TINODE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/types.h \
  arch/arm64/include/generated/uapi/asm/types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/int-ll64.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/int-ll64.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi/asm/bitsperlong.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitsperlong.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/bitsperlong.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/posix_types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/stddef.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/stddef.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi/asm/posix_types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/posix_types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/poison.h \
    $(wildcard include/config/ILLEGAL_POINTER_VALUE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/const.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/vdso/const.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/const.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kernel.h \
    $(wildcard include/config/PREEMPT_VOLUNTARY) \
    $(wildcard include/config/PREEMPT_DYNAMIC) \
    $(wildcard include/config/PREEMPT_) \
    $(wildcard include/config/DEBUG_ATOMIC_SLEEP) \
    $(wildcard include/config/MMU) \
    $(wildcard include/config/PROVE_LOCKING) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/stdarg.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/align.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/limits.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/limits.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/vdso/limits.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/linkage.h \
    $(wildcard include/config/ARCH_USE_SYM_ANNOTATIONS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/stringify.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/export.h \
    $(wildcard include/config/MODVERSIONS) \
    $(wildcard include/config/MODULE_REL_CRCS) \
    $(wildcard include/config/HAVE_ARCH_PREL32_RELOCATIONS) \
    $(wildcard include/config/TRIM_UNUSED_KSYMS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/compiler.h \
    $(wildcard include/config/TRACE_BRANCH_PROFILING) \
    $(wildcard include/config/PROFILE_ALL_BRANCHES) \
    $(wildcard include/config/STACK_VALIDATION) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/rwonce.h \
    $(wildcard include/config/LTO) \
    $(wildcard include/config/AS_HAS_LDAPR) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/alternative-macros.h \
  arch/arm64/include/generated/asm/cpucaps.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/insn-def.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/rwonce.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kasan-checks.h \
    $(wildcard include/config/KASAN_GENERIC) \
    $(wildcard include/config/KASAN_SW_TAGS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kcsan-checks.h \
    $(wildcard include/config/KCSAN) \
    $(wildcard include/config/KCSAN_IGNORE_ATOMICS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/linkage.h \
    $(wildcard include/config/ARM64_BTI_KERNEL) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/bitops.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/bits.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/vdso/bits.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/build_bug.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/typecheck.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/kernel.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/sysinfo.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/bitops.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/builtin-__ffs.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/builtin-ffs.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/builtin-__fls.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/builtin-fls.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/ffz.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/fls64.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/find.h \
    $(wildcard include/config/GENERIC_FIND_FIRST_BIT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/sched.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/hweight.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/arch_hweight.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/const_hweight.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/atomic.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/atomic.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/atomic.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/barrier.h \
    $(wildcard include/config/ARM64_PSEUDO_NMI) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/barrier.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/cmpxchg.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/lse.h \
    $(wildcard include/config/ARM64_LSE_ATOMICS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/atomic_ll_sc.h \
    $(wildcard include/config/CC_HAS_K_CONSTRAINT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/jump_label.h \
    $(wildcard include/config/HAVE_ARCH_JUMP_LABEL_RELATIVE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/jump_label.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/insn.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/alternative.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/init.h \
    $(wildcard include/config/STRICT_KERNEL_RWX) \
    $(wildcard include/config/STRICT_MODULE_RWX) \
    $(wildcard include/config/LTO_CLANG) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/atomic_lse.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/atomic/atomic-arch-fallback.h \
    $(wildcard include/config/GENERIC_ATOMIC64) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/atomic/atomic-long.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/atomic/atomic-instrumented.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/instrumented.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/instrumented-atomic.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/lock.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/instrumented-lock.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/non-atomic.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/le.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi/asm/byteorder.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/byteorder/little_endian.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/byteorder/little_endian.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/swab.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/swab.h \
  arch/arm64/include/generated/uapi/asm/swab.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/swab.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/byteorder/generic.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kstrtox.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/log2.h \
    $(wildcard include/config/ARCH_HAS_ILOG2_U32) \
    $(wildcard include/config/ARCH_HAS_ILOG2_U64) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/math.h \
  arch/arm64/include/generated/asm/div64.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/div64.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/minmax.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/panic.h \
    $(wildcard include/config/PANIC_TIMEOUT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/printk.h \
    $(wildcard include/config/MESSAGE_LOGLEVEL_DEFAULT) \
    $(wildcard include/config/CONSOLE_LOGLEVEL_DEFAULT) \
    $(wildcard include/config/CONSOLE_LOGLEVEL_QUIET) \
    $(wildcard include/config/EARLY_PRINTK) \
    $(wildcard include/config/PRINTK) \
    $(wildcard include/config/DYNAMIC_DEBUG) \
    $(wildcard include/config/DYNAMIC_DEBUG_CORE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kern_levels.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/cache.h \
    $(wildcard include/config/ARCH_HAS_CACHE_LINE_SIZE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/cache.h \
    $(wildcard include/config/KASAN_HW_TAGS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/cputype.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/sysreg.h \
    $(wildcard include/config/BROKEN_GAS_INST) \
    $(wildcard include/config/ARM64_PA_BITS_52) \
    $(wildcard include/config/ARM64_4K_PAGES) \
    $(wildcard include/config/ARM64_16K_PAGES) \
    $(wildcard include/config/ARM64_64K_PAGES) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kasan-tags.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/ratelimit_types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/param.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi/asm/param.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/param.h \
    $(wildcard include/config/HZ) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/param.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/spinlock_types.h \
    $(wildcard include/config/PREEMPT_RT) \
    $(wildcard include/config/DEBUG_LOCK_ALLOC) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/spinlock_types_raw.h \
    $(wildcard include/config/DEBUG_SPINLOCK) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/spinlock_types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/qspinlock_types.h \
    $(wildcard include/config/NR_CPUS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/qrwlock_types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/lockdep_types.h \
    $(wildcard include/config/PROVE_RAW_LOCK_NESTING) \
    $(wildcard include/config/PREEMPT_LOCK) \
    $(wildcard include/config/LOCKDEP) \
    $(wildcard include/config/LOCK_STAT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rwlock_types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/once_lite.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/static_call_types.h \
    $(wildcard include/config/HAVE_STATIC_CALL) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/stat.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/stat.h \
    $(wildcard include/config/COMPAT) \
  arch/arm64/include/generated/uapi/asm/stat.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/stat.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/time.h \
    $(wildcard include/config/POSIX_TIMERS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/math64.h \
    $(wildcard include/config/ARCH_SUPPORTS_INT128) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/vdso/math64.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/time64.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/vdso/time64.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/time.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/time_types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/time32.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/timex.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/timex.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/timex.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/arch_timer.h \
    $(wildcard include/config/ARM_ARCH_TIMER_OOL_WORKAROUND) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/hwcap.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi/asm/hwcap.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/cpufeature.h \
    $(wildcard include/config/ARM64_PAN) \
    $(wildcard include/config/ARM64_SW_TTBR0_PAN) \
    $(wildcard include/config/ARM64_SVE) \
    $(wildcard include/config/ARM64_CNP) \
    $(wildcard include/config/ARM64_PTR_AUTH) \
    $(wildcard include/config/ARM64_MTE) \
    $(wildcard include/config/ARM64_DEBUG_PRIORITY_MASKING) \
    $(wildcard include/config/ARM64_BTI) \
    $(wildcard include/config/ARM64_TLB_RANGE) \
    $(wildcard include/config/ARM64_PA_BITS) \
    $(wildcard include/config/ARM64_HW_AFDBM) \
    $(wildcard include/config/ARM64_AMU_EXTN) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/bug.h \
    $(wildcard include/config/BUG_ON_DATA_CORRUPTION) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/bug.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/asm-bug.h \
    $(wildcard include/config/DEBUG_BUGVERBOSE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/brk-imm.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/bug.h \
    $(wildcard include/config/BUG) \
    $(wildcard include/config/GENERIC_BUG_RELATIVE_POINTERS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/instrumentation.h \
    $(wildcard include/config/DEBUG_ENTRY) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/smp.h \
    $(wildcard include/config/UP_LATE_INIT) \
    $(wildcard include/config/DEBUG_PREEMPT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/errno.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/errno.h \
  arch/arm64/include/generated/uapi/asm/errno.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/errno.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/errno-base.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/cpumask.h \
    $(wildcard include/config/CPUMASK_OFFSTACK) \
    $(wildcard include/config/HOTPLUG_CPU) \
    $(wildcard include/config/DEBUG_PER_CPU_MAPS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/threads.h \
    $(wildcard include/config/BASE_SMALL) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/bitmap.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/string.h \
    $(wildcard include/config/BINARY_PRINTF) \
    $(wildcard include/config/FORTIFY_SOURCE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/string.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/string.h \
    $(wildcard include/config/ARCH_HAS_UACCESS_FLUSHCACHE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/smp_types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/llist.h \
    $(wildcard include/config/ARCH_HAVE_NMI_SAFE_CMPXCHG) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/preempt.h \
    $(wildcard include/config/PREEMPT_COUNT) \
    $(wildcard include/config/TRACE_PREEMPT_TOGGLE) \
    $(wildcard include/config/PREEMPTION) \
    $(wildcard include/config/PREEMPT_NOTIFIERS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/preempt.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/thread_info.h \
    $(wildcard include/config/THREAD_INFO_IN_TASK) \
    $(wildcard include/config/GENERIC_ENTRY) \
    $(wildcard include/config/HAVE_ARCH_WITHIN_STACK_FRAMES) \
    $(wildcard include/config/HARDENED_USERCOPY) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/restart_block.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/current.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/thread_info.h \
    $(wildcard include/config/SHADOW_CALL_STACK) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/memory.h \
    $(wildcard include/config/ARM64_VA_BITS) \
    $(wildcard include/config/KASAN_SHADOW_OFFSET) \
    $(wildcard include/config/KASAN) \
    $(wildcard include/config/VMAP_STACK) \
    $(wildcard include/config/DEBUG_VIRTUAL) \
    $(wildcard include/config/EFI) \
    $(wildcard include/config/ARM_GIC_V3_ITS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sizes.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/page-def.h \
    $(wildcard include/config/ARM64_PAGE_SHIFT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/mmdebug.h \
    $(wildcard include/config/DEBUG_VM) \
    $(wildcard include/config/DEBUG_VM_PGFLAGS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/memory_model.h \
    $(wildcard include/config/FLATMEM) \
    $(wildcard include/config/SPARSEMEM_VMEMMAP) \
    $(wildcard include/config/SPARSEMEM) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/pfn.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/stack_pointer.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/smp.h \
    $(wildcard include/config/ARM64_ACPI_PARKING_PROTOCOL) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/percpu.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/percpu.h \
    $(wildcard include/config/HAVE_SETUP_PER_CPU_AREA) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/percpu-defs.h \
    $(wildcard include/config/DEBUG_FORCE_WEAK_PER_CPU) \
    $(wildcard include/config/AMD_MEM_ENCRYPT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/clocksource/arm_arch_timer.h \
    $(wildcard include/config/ARM_ARCH_TIMER) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/timecounter.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/timex.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/vdso/time32.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/vdso/time.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/compat.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/compat.h \
    $(wildcard include/config/COMPAT_FOR_U64_ALIGNMENT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sched.h \
    $(wildcard include/config/VIRT_CPU_ACCOUNTING_NATIVE) \
    $(wildcard include/config/SCHED_INFO) \
    $(wildcard include/config/SCHEDSTATS) \
    $(wildcard include/config/FAIR_GROUP_SCHED) \
    $(wildcard include/config/RT_GROUP_SCHED) \
    $(wildcard include/config/RT_MUTEXES) \
    $(wildcard include/config/UCLAMP_TASK) \
    $(wildcard include/config/UCLAMP_BUCKETS_COUNT) \
    $(wildcard include/config/KMAP_LOCAL) \
    $(wildcard include/config/SCHED_CORE) \
    $(wildcard include/config/CGROUP_SCHED) \
    $(wildcard include/config/BLK_DEV_IO_TRACE) \
    $(wildcard include/config/PREEMPT_RCU) \
    $(wildcard include/config/TASKS_RCU) \
    $(wildcard include/config/TASKS_TRACE_RCU) \
    $(wildcard include/config/PSI) \
    $(wildcard include/config/MEMCG) \
    $(wildcard include/config/LRU_GEN) \
    $(wildcard include/config/COMPAT_BRK) \
    $(wildcard include/config/CGROUPS) \
    $(wildcard include/config/BLK_CGROUP) \
    $(wildcard include/config/PAGE_OWNER) \
    $(wildcard include/config/EVENTFD) \
    $(wildcard include/config/STACKPROTECTOR) \
    $(wildcard include/config/ARCH_HAS_SCALED_CPUTIME) \
    $(wildcard include/config/CPU_FREQ_TIMES) \
    $(wildcard include/config/VIRT_CPU_ACCOUNTING_GEN) \
    $(wildcard include/config/NO_HZ_FULL) \
    $(wildcard include/config/POSIX_CPUTIMERS) \
    $(wildcard include/config/POSIX_CPU_TIMERS_TASK_WORK) \
    $(wildcard include/config/KEYS) \
    $(wildcard include/config/SYSVIPC) \
    $(wildcard include/config/DETECT_HUNG_TASK) \
    $(wildcard include/config/IO_URING) \
    $(wildcard include/config/AUDIT) \
    $(wildcard include/config/AUDITSYSCALL) \
    $(wildcard include/config/DEBUG_MUTEXES) \
    $(wildcard include/config/TRACE_IRQFLAGS) \
    $(wildcard include/config/UBSAN) \
    $(wildcard include/config/UBSAN_TRAP) \
    $(wildcard include/config/BLOCK) \
    $(wildcard include/config/COMPACTION) \
    $(wildcard include/config/TASK_XACCT) \
    $(wildcard include/config/CPUSETS) \
    $(wildcard include/config/X86_CPU_RESCTRL) \
    $(wildcard include/config/FUTEX) \
    $(wildcard include/config/PERF_EVENTS) \
    $(wildcard include/config/NUMA) \
    $(wildcard include/config/NUMA_BALANCING) \
    $(wildcard include/config/RSEQ) \
    $(wildcard include/config/TASK_DELAY_ACCT) \
    $(wildcard include/config/FAULT_INJECTION) \
    $(wildcard include/config/LATENCYTOP) \
    $(wildcard include/config/FUNCTION_GRAPH_TRACER) \
    $(wildcard include/config/KCOV) \
    $(wildcard include/config/UPROBES) \
    $(wildcard include/config/BCACHE) \
    $(wildcard include/config/SECURITY) \
    $(wildcard include/config/BPF_SYSCALL) \
    $(wildcard include/config/GCC_PLUGIN_STACKLEAK) \
    $(wildcard include/config/X86_MCE) \
    $(wildcard include/config/KRETPROBES) \
    $(wildcard include/config/ARCH_HAS_PARANOID_L1D_FLUSH) \
    $(wildcard include/config/RT_SOFTINT_OPTIMIZATION) \
    $(wildcard include/config/ARCH_TASK_STRUCT_ON_STACK) \
    $(wildcard include/config/DEBUG_RSEQ) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/sched.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/pid.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rculist.h \
    $(wildcard include/config/PROVE_RCU_LIST) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rcupdate.h \
    $(wildcard include/config/TINY_RCU) \
    $(wildcard include/config/TASKS_RCU_GENERIC) \
    $(wildcard include/config/RCU_STALL_COMMON) \
    $(wildcard include/config/RCU_NOCB_CPU) \
    $(wildcard include/config/TASKS_RUDE_RCU) \
    $(wildcard include/config/TREE_RCU) \
    $(wildcard include/config/DEBUG_OBJECTS_RCU_HEAD) \
    $(wildcard include/config/PROVE_RCU) \
    $(wildcard include/config/ARCH_WEAK_RELEASE_ACQUIRE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/irqflags.h \
    $(wildcard include/config/IRQSOFF_TRACER) \
    $(wildcard include/config/PREEMPT_TRACER) \
    $(wildcard include/config/DEBUG_IRQFLAGS) \
    $(wildcard include/config/TRACE_IRQFLAGS_SUPPORT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/irqflags.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/ptrace.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi/asm/ptrace.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi/asm/sve_context.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/bottom_half.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/lockdep.h \
    $(wildcard include/config/DEBUG_LOCKING_API_SELFTESTS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/processor.h \
    $(wildcard include/config/KUSER_HELPERS) \
    $(wildcard include/config/ARM64_FORCE_52BIT) \
    $(wildcard include/config/HAVE_HW_BREAKPOINT) \
    $(wildcard include/config/ARM64_PTR_AUTH_KERNEL) \
    $(wildcard include/config/ARM64_TAGGED_ADDR_ABI) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/android_vendor.h \
    $(wildcard include/config/ANDROID_VENDOR_OEM_DATA) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/android_kabi.h \
    $(wildcard include/config/ANDROID_KABI_RESERVE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/vdso/processor.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/vdso/processor.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/hw_breakpoint.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/virt.h \
    $(wildcard include/config/KVM) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/sections.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/sections.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/kasan.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/mte-kasan.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/mte-def.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/pgtable-types.h \
    $(wildcard include/config/PGTABLE_LEVELS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/pgtable-nopud.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/pgtable-nop4d.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/pgtable-hwdef.h \
    $(wildcard include/config/ARM64_CONT_PTE_SHIFT) \
    $(wildcard include/config/ARM64_CONT_PMD_SHIFT) \
    $(wildcard include/config/ARM64_VA_BITS_52) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/pointer_auth.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/prctl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/random.h \
    $(wildcard include/config/ARCH_RANDOM) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/once.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/random.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/ioctl.h \
  arch/arm64/include/generated/uapi/asm/ioctl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/ioctl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/ioctl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/irqnr.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/irqnr.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/prandom.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/percpu.h \
    $(wildcard include/config/NEED_PER_CPU_EMBED_FIRST_CHUNK) \
    $(wildcard include/config/NEED_PER_CPU_PAGE_FIRST_CHUNK) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/archrandom.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/arm-smccc.h \
    $(wildcard include/config/ARM64) \
    $(wildcard include/config/HAVE_ARM_SMCCC) \
    $(wildcard include/config/ARM) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/spectre.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/fpsimd.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi/asm/sigcontext.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rcutree.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/wait.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/spinlock.h \
  arch/arm64/include/generated/asm/mmiowb.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/mmiowb.h \
    $(wildcard include/config/MMIOWB) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/spinlock.h \
  arch/arm64/include/generated/asm/qspinlock.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/qspinlock.h \
  arch/arm64/include/generated/asm/qrwlock.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/qrwlock.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rwlock.h \
    $(wildcard include/config/PREEMPT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/INLINE_SPIN_LOCK) \
    $(wildcard include/config/INLINE_SPIN_LOCK_BH) \
    $(wildcard include/config/INLINE_SPIN_LOCK_IRQ) \
    $(wildcard include/config/INLINE_SPIN_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_SPIN_TRYLOCK) \
    $(wildcard include/config/INLINE_SPIN_TRYLOCK_BH) \
    $(wildcard include/config/UNINLINE_SPIN_UNLOCK) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_BH) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_IRQRESTORE) \
    $(wildcard include/config/GENERIC_LOCKBREAK) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/INLINE_READ_LOCK) \
    $(wildcard include/config/INLINE_WRITE_LOCK) \
    $(wildcard include/config/INLINE_READ_LOCK_BH) \
    $(wildcard include/config/INLINE_WRITE_LOCK_BH) \
    $(wildcard include/config/INLINE_READ_LOCK_IRQ) \
    $(wildcard include/config/INLINE_WRITE_LOCK_IRQ) \
    $(wildcard include/config/INLINE_READ_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_WRITE_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_READ_TRYLOCK) \
    $(wildcard include/config/INLINE_WRITE_TRYLOCK) \
    $(wildcard include/config/INLINE_READ_UNLOCK) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK) \
    $(wildcard include/config/INLINE_READ_UNLOCK_BH) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_BH) \
    $(wildcard include/config/INLINE_READ_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_READ_UNLOCK_IRQRESTORE) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_IRQRESTORE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/wait.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/refcount.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sem.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/sem.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/ipc.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/uidgid.h \
    $(wildcard include/config/MULTIUSER) \
    $(wildcard include/config/USER_NS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/highuid.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rhashtable-types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/mutex.h \
    $(wildcard include/config/MUTEX_SPIN_ON_OWNER) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/osq_lock.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/debug_locks.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/workqueue.h \
    $(wildcard include/config/DEBUG_OBJECTS_WORK) \
    $(wildcard include/config/FREEZER) \
    $(wildcard include/config/WQ_WATCHDOG) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/timer.h \
    $(wildcard include/config/DEBUG_OBJECTS_TIMERS) \
    $(wildcard include/config/NO_HZ_COMMON) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/ktime.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/jiffies.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/vdso/jiffies.h \
  include/generated/timeconst.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/vdso/ktime.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/timekeeping.h \
    $(wildcard include/config/GENERIC_CMOS_UPDATE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/clocksource_ids.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/debugobjects.h \
    $(wildcard include/config/DEBUG_OBJECTS) \
    $(wildcard include/config/DEBUG_OBJECTS_FREE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/ipc.h \
  arch/arm64/include/generated/uapi/asm/ipcbuf.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/ipcbuf.h \
  arch/arm64/include/generated/uapi/asm/sembuf.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/sembuf.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/shm.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/page.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/personality.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/personality.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/getorder.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/shm.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/hugetlb_encode.h \
  arch/arm64/include/generated/uapi/asm/shmbuf.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/shmbuf.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/shmparam.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/shmparam.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/plist.h \
    $(wildcard include/config/DEBUG_PLIST) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/hrtimer.h \
    $(wildcard include/config/HIGH_RES_TIMERS) \
    $(wildcard include/config/TIME_LOW_RES) \
    $(wildcard include/config/TIMERFD) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/hrtimer_defs.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rbtree.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rbtree_types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/seqlock.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/ww_mutex.h \
    $(wildcard include/config/DEBUG_RT_MUTEXES) \
    $(wildcard include/config/DEBUG_WW_MUTEX_SLOWPATH) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rtmutex.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/timerqueue.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/seccomp.h \
    $(wildcard include/config/SECCOMP) \
    $(wildcard include/config/HAVE_ARCH_SECCOMP_FILTER) \
    $(wildcard include/config/SECCOMP_FILTER) \
    $(wildcard include/config/CHECKPOINT_RESTORE) \
    $(wildcard include/config/SECCOMP_CACHE_DEBUG) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/seccomp.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/seccomp.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/unistd.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi/asm/unistd.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/unistd.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/seccomp.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/unistd.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/nodemask.h \
    $(wildcard include/config/HIGHMEM) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/numa.h \
    $(wildcard include/config/NODES_SHIFT) \
    $(wildcard include/config/NUMA_KEEP_MEMINFO) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/resource.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/resource.h \
  arch/arm64/include/generated/uapi/asm/resource.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/resource.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/resource.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/latencytop.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sched/prio.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sched/types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/signal_types.h \
    $(wildcard include/config/OLD_SIGACTION) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/signal.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/signal.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi/asm/signal.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/signal.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/signal.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/signal-defs.h \
  arch/arm64/include/generated/uapi/asm/siginfo.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/siginfo.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/syscall_user_dispatch.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/mm_types_task.h \
    $(wildcard include/config/ARCH_WANT_BATCHED_UNMAP_TLB_FLUSH) \
    $(wildcard include/config/SPLIT_PTLOCK_CPUS) \
    $(wildcard include/config/ARCH_ENABLE_SPLIT_PMD_PTLOCK) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/task_io_accounting.h \
    $(wildcard include/config/TASK_IO_ACCOUNTING) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/posix-timers.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/alarmtimer.h \
    $(wildcard include/config/RTC_CLASS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/task_work.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/rseq.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kcsan.h \
  arch/arm64/include/generated/asm/kmap_size.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/kmap_size.h \
    $(wildcard include/config/DEBUG_KMAP_LOCAL) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sched/task_stack.h \
    $(wildcard include/config/STACK_GROWSUP) \
    $(wildcard include/config/DEBUG_STACK_USAGE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/magic.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/stat.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/buildid.h \
    $(wildcard include/config/CRASH_CORE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/mm_types.h \
    $(wildcard include/config/HAVE_ALIGNED_STRUCT_PAGE) \
    $(wildcard include/config/USERFAULTFD) \
    $(wildcard include/config/SPECULATIVE_PAGE_FAULT) \
    $(wildcard include/config/SWAP) \
    $(wildcard include/config/HAVE_ARCH_COMPAT_MMAP_BASES) \
    $(wildcard include/config/MEMBARRIER) \
    $(wildcard include/config/AIO) \
    $(wildcard include/config/MMU_NOTIFIER) \
    $(wildcard include/config/TRANSPARENT_HUGEPAGE) \
    $(wildcard include/config/HUGETLB_PAGE) \
    $(wildcard include/config/IOMMU_SUPPORT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/auxvec.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/auxvec.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi/asm/auxvec.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kref.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rwsem.h \
    $(wildcard include/config/RWSEM_SPIN_ON_OWNER) \
    $(wildcard include/config/DEBUG_RWSEMS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/err.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/completion.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/swait.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/uprobes.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/uprobes.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/debug-monitors.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/esr.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/probes.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/page-flags-layout.h \
  include/generated/bounds.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/sparsemem.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/mmu.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kmod.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/umh.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/gfp.h \
    $(wildcard include/config/CMA) \
    $(wildcard include/config/ZONE_DMA) \
    $(wildcard include/config/ZONE_DMA32) \
    $(wildcard include/config/ZONE_DEVICE) \
    $(wildcard include/config/PM_SLEEP) \
    $(wildcard include/config/CONTIG_ALLOC) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/mmzone.h \
    $(wildcard include/config/FORCE_MAX_ZONEORDER) \
    $(wildcard include/config/MEMORY_ISOLATION) \
    $(wildcard include/config/LRU_GEN_STATS) \
    $(wildcard include/config/MEMORY_HOTPLUG) \
    $(wildcard include/config/PAGE_EXTENSION) \
    $(wildcard include/config/DEFERRED_STRUCT_PAGE_INIT) \
    $(wildcard include/config/HAVE_MEMORYLESS_NODES) \
    $(wildcard include/config/SPARSEMEM_EXTREME) \
    $(wildcard include/config/HAVE_ARCH_PFN_VALID) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/pageblock-flags.h \
    $(wildcard include/config/HUGETLB_PAGE_SIZE_VARIABLE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/page-flags.h \
    $(wildcard include/config/ARCH_USES_PG_UNCACHED) \
    $(wildcard include/config/MEMORY_FAILURE) \
    $(wildcard include/config/PAGE_IDLE_FLAG) \
    $(wildcard include/config/THP_SWAP) \
    $(wildcard include/config/KSM) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/local_lock.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/local_lock_internal.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/memory_hotplug.h \
    $(wildcard include/config/ARCH_HAS_ADD_PAGES) \
    $(wildcard include/config/HAVE_ARCH_NODEDATA_EXTENSION) \
    $(wildcard include/config/MEMORY_HOTREMOVE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/notifier.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/srcu.h \
    $(wildcard include/config/TINY_SRCU) \
    $(wildcard include/config/SRCU) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rcu_segcblist.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/srcutree.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rcu_node_tree.h \
    $(wildcard include/config/RCU_FANOUT) \
    $(wildcard include/config/RCU_FANOUT_LEAF) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/topology.h \
    $(wildcard include/config/USE_PERCPU_NUMA_NODE_ID) \
    $(wildcard include/config/SCHED_SMT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/arch_topology.h \
    $(wildcard include/config/GENERIC_ARCH_TOPOLOGY) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/topology.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/topology.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sysctl.h \
    $(wildcard include/config/SYSCTL) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/sysctl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/elf.h \
    $(wildcard include/config/ARCH_USE_GNU_PROPERTY) \
    $(wildcard include/config/ARCH_HAVE_ELF_PROT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/elf.h \
    $(wildcard include/config/COMPAT_VDSO) \
  arch/arm64/include/generated/asm/user.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/user.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/elf.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/elf-em.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/fs.h \
    $(wildcard include/config/READ_ONLY_THP_FOR_FS) \
    $(wildcard include/config/FS_POSIX_ACL) \
    $(wildcard include/config/CGROUP_WRITEBACK) \
    $(wildcard include/config/IMA) \
    $(wildcard include/config/FILE_LOCKING) \
    $(wildcard include/config/FSNOTIFY) \
    $(wildcard include/config/FS_ENCRYPTION) \
    $(wildcard include/config/FS_VERITY) \
    $(wildcard include/config/EPOLL) \
    $(wildcard include/config/UNICODE) \
    $(wildcard include/config/QUOTA) \
    $(wildcard include/config/FS_DAX) \
    $(wildcard include/config/MIGRATION) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/wait_bit.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kdev_t.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/kdev_t.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/dcache.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rculist_bl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/list_bl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/bit_spinlock.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/lockref.h \
    $(wildcard include/config/ARCH_USE_CMPXCHG_LOCKREF) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/stringhash.h \
    $(wildcard include/config/DCACHE_WORD_ACCESS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/hash.h \
    $(wildcard include/config/HAVE_ARCH_HASH) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/path.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/list_lru.h \
    $(wildcard include/config/MEMCG_KMEM) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/shrinker.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/radix-tree.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/xarray.h \
    $(wildcard include/config/XARRAY_MULTI) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/capability.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/capability.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/semaphore.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/fcntl.h \
    $(wildcard include/config/ARCH_32BIT_OFF_T) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/fcntl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/uapi/asm/fcntl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/asm-generic/fcntl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/openat2.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/migrate_mode.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/percpu-rwsem.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rcuwait.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sched/signal.h \
    $(wildcard include/config/SCHED_AUTOGROUP) \
    $(wildcard include/config/BSD_PROCESS_ACCT) \
    $(wildcard include/config/TASKSTATS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/signal.h \
    $(wildcard include/config/PROC_FS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sched/jobctl.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sched/task.h \
    $(wildcard include/config/HAVE_EXIT_THREAD) \
    $(wildcard include/config/ARCH_WANTS_DYNAMIC_TASK_STRUCT) \
    $(wildcard include/config/HAVE_ARCH_THREAD_STRUCT_WHITELIST) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/uaccess.h \
    $(wildcard include/config/SET_FS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/fault-inject-usercopy.h \
    $(wildcard include/config/FAULT_INJECTION_USERCOPY) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/uaccess.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/kernel-pgtable.h \
    $(wildcard include/config/RANDOMIZE_BASE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/mte.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/bitfield.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/extable.h \
    $(wildcard include/config/BPF_JIT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/cred.h \
    $(wildcard include/config/DEBUG_CREDENTIALS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/key.h \
    $(wildcard include/config/KEY_NOTIFICATIONS) \
    $(wildcard include/config/NET) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/assoc_array.h \
    $(wildcard include/config/ASSOCIATIVE_ARRAY) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sched/user.h \
    $(wildcard include/config/WATCH_QUEUE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/percpu_counter.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/ratelimit.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rcu_sync.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/delayed_call.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/uuid.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/uuid.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/errseq.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/ioprio.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sched/rt.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/iocontext.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/ioprio.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/fs_types.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/mount.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/fs.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/quota.h \
    $(wildcard include/config/QUOTA_NETLINK_INTERFACE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/dqblk_xfs.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/dqblk_v1.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/dqblk_v2.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/dqblk_qtree.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/projid.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/uapi/linux/quota.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/nfs_fs_i.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kobject.h \
    $(wildcard include/config/UEVENT_HELPER) \
    $(wildcard include/config/DEBUG_KOBJECT_RELEASE) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/sysfs.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kernfs.h \
    $(wildcard include/config/KERNFS) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/idr.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/kobject_ns.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/moduleparam.h \
    $(wildcard include/config/ALPHA) \
    $(wildcard include/config/IA64) \
    $(wildcard include/config/PPC64) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/rbtree_latch.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/error-injection.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/error-injection.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/tracepoint-defs.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/static_key.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/cfi.h \
    $(wildcard include/config/CFI_CLANG_SHADOW) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/module.h \
    $(wildcard include/config/ARM64_MODULE_PLTS) \
    $(wildcard include/config/DYNAMIC_FTRACE) \
    $(wildcard include/config/ARM64_ERRATUM_843419) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/asm-generic/module.h \
    $(wildcard include/config/HAVE_MOD_ARCH_SPECIFIC) \
    $(wildcard include/config/MODULES_USE_ELF_REL) \
    $(wildcard include/config/MODULES_USE_ELF_RELA) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/build-salt.h \
    $(wildcard include/config/BUILD_SALT) \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/elfnote.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/elfnote-lto.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/include/linux/vermagic.h \
  include/generated/utsrelease.h \
  /home/uqtony/android_src/vendor/nxp-opensource/kernel_imx/arch/arm64/include/asm/vermagic.h \

/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/moal.mod.o: $(deps_/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/moal.mod.o)

$(deps_/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/moal.mod.o):
