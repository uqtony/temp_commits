cmd_/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan.mod := echo   mlan/mlan_shim.o mlan/mlan_init.o mlan/mlan_txrx.o mlan/mlan_cmdevt.o mlan/mlan_misc.o mlan/mlan_cfp.o mlan/mlan_module.o mlan/mlan_wmm.o mlan/mlan_sdio.o mlan/mlan_pcie.o mlan/mlan_11n_aggr.o mlan/mlan_11n_rxreorder.o mlan/mlan_11n.o mlan/mlan_11ac.o mlan/mlan_11ax.o mlan/mlan_11d.o mlan/mlan_11h.o mlan/mlan_meas.o mlan/mlan_scan.o mlan/mlan_sta_ioctl.o mlan/mlan_sta_rx.o mlan/mlan_sta_tx.o mlan/mlan_sta_event.o mlan/mlan_sta_cmd.o mlan/mlan_sta_cmdresp.o mlan/mlan_join.o mlan/mlan_uap_ioctl.o mlan/mlan_uap_cmdevent.o mlan/mlan_uap_txrx.o | awk -v RS='( |\n)' '!x[$$0]++ { print("/home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/"$$0) }' > /home/uqtony/android_src/vendor/nxp-opensource/nxp-mwifiex/mxm_wifiex/wlan_src/mlan.mod
