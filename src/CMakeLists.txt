cmake_minimum_required(VERSION 3.27)

include(nrf5/nrf5)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    main.cpp
    sys.cpp

    freertos/hooks.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    etl
    freertos_kernel
)

### START FREERTOS ###
target_include_directories(freertos_config SYSTEM INTERFACE freertos)
### END FREERTOS ###

### START NRF5 SDK ###
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${NRF5_SDK_PATH}/components/drivers_nrf/radio_config/radio_config.c
    ${NRF5_SDK_PATH}/components/drivers_nrf/nrf_soc_nosd/nrf_soc.c
    ${NRF5_SDK_PATH}/components/drivers_nrf/nrf_soc_nosd/nrf_nvic.c

    ${NRF5_SDK_PATH}/modules/nrfx/mdk/gcc_startup_nrf52840.S
    ${NRF5_SDK_PATH}/modules/nrfx/mdk/system_nrf52840.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_adc.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_clock.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_comp.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_dppi.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_gpiote.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_i2s.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_lpcomp.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_nfct.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_nvmc.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_pdm.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_power.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_ppi.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_pwm.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_qdec.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_qspi.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_rng.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_rtc.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_saadc.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_spi.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_spim.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_spis.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_swi.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_systick.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_temp.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_timer.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_twi_twim.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_twi.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_twim.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_twis.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_uart.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_uarte.c
    # ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_usbd.c
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_wdt.c

    # ${NRF5_SDK_PATH}/components/libraries/block_dev/qspi/nrf_block_dev_qspi.c
    # ${NRF5_SDK_PATH}/components/libraries/block_dev/empty/nrf_block_dev_empty.c
    # ${NRF5_SDK_PATH}/components/libraries/balloc/nrf_balloc.c
    # ${NRF5_SDK_PATH}/components/libraries/atomic_flags/nrf_atflags.c
    # ${NRF5_SDK_PATH}/components/libraries/atomic_fifo/nrf_atfifo.c
    # ${NRF5_SDK_PATH}/components/libraries/atomic/nrf_atomic.c
    # ${NRF5_SDK_PATH}/components/libraries/util/sdk_mapped_flags.c
    # ${NRF5_SDK_PATH}/components/libraries/util/nrf_assert.c
    # ${NRF5_SDK_PATH}/components/libraries/util/app_util_platform.c
    # ${NRF5_SDK_PATH}/components/libraries/util/app_error_weak.c
    # ${NRF5_SDK_PATH}/components/libraries/util/app_error_handler_gcc.c
    # ${NRF5_SDK_PATH}/components/libraries/util/app_error.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/class/nrf_dfu_trigger/app_usbd_nrf_dfu_trigger.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/class/msc/app_usbd_msc.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/class/hid/mouse/app_usbd_hid_mouse.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/class/hid/kbd/app_usbd_hid_kbd.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/class/hid/generic/app_usbd_hid_generic.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/class/hid/app_usbd_hid.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/class/dummy/app_usbd_dummy.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/class/cdc/acm/app_usbd_cdc_acm.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/class/audio/app_usbd_audio.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/app_usbd_string_desc.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/app_usbd_serial_num.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/app_usbd_core.c
    # ${NRF5_SDK_PATH}/components/libraries/usbd/app_usbd.c
    # ${NRF5_SDK_PATH}/components/libraries/uart/retarget.c
    # ${NRF5_SDK_PATH}/components/libraries/uart/app_uart_fifo.c
    # ${NRF5_SDK_PATH}/components/libraries/uart/app_uart.c
    # ${NRF5_SDK_PATH}/components/libraries/twi_sensor/nrf_twi_sensor.c
    # ${NRF5_SDK_PATH}/components/libraries/twi_mngr/nrf_twi_mngr.c
    # ${NRF5_SDK_PATH}/components/libraries/timer/drv_rtc.c
    # ${NRF5_SDK_PATH}/components/libraries/timer/app_timer_rtx.c
    # ${NRF5_SDK_PATH}/components/libraries/timer/app_timer_freertos.c
    # ${NRF5_SDK_PATH}/components/libraries/timer/app_timer2.c
    # ${NRF5_SDK_PATH}/components/libraries/timer/app_timer.c
    # ${NRF5_SDK_PATH}/components/libraries/svc/nrf_svc_handler.c
    # ${NRF5_SDK_PATH}/components/libraries/strerror/nrf_strerror.c
    # ${NRF5_SDK_PATH}/components/libraries/stack_guard/nrf_stack_guard.c
    # ${NRF5_SDK_PATH}/components/libraries/spi_mngr/nrf_spi_mngr.c
    # ${NRF5_SDK_PATH}/components/libraries/sortlist/nrf_sortlist.c
    # ${NRF5_SDK_PATH}/components/libraries/slip/slip.c
    # ${NRF5_SDK_PATH}/components/libraries/simple_timer/app_simple_timer.c
    # ${NRF5_SDK_PATH}/components/libraries/sha256/sha256.c
    # ${NRF5_SDK_PATH}/components/libraries/sensorsim/sensorsim.c
    # ${NRF5_SDK_PATH}/components/libraries/sdcard/app_sdcard.c
    # ${NRF5_SDK_PATH}/components/libraries/scheduler/app_scheduler_serconn.c
    # ${NRF5_SDK_PATH}/components/libraries/scheduler/app_scheduler.c
    # ${NRF5_SDK_PATH}/components/libraries/ringbuf/nrf_ringbuf.c
    # ${NRF5_SDK_PATH}/components/libraries/queue/nrf_queue.c
    # ${NRF5_SDK_PATH}/components/libraries/pwr_mgmt/nrf_pwr_mgmt.c
    # ${NRF5_SDK_PATH}/components/libraries/pwm/app_pwm.c
    # ${NRF5_SDK_PATH}/components/libraries/mpu/nrf_mpu_lib.c
    # ${NRF5_SDK_PATH}/components/libraries/mem_manager/mem_manager.c
    # ${NRF5_SDK_PATH}/components/libraries/memobj/nrf_memobj.c
    # ${NRF5_SDK_PATH}/components/libraries/low_power_pwm/low_power_pwm.c
    # ${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_str_formatter.c
    # ${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_frontend.c
    # ${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_default_backends.c
    # ${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_backend_uart.c
    # ${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_backend_serial.c
    # ${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_backend_rtt.c
    # ${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_backend_flash.c
    # ${NRF5_SDK_PATH}/components/libraries/libuarte/nrf_libuarte_drv.c
    # ${NRF5_SDK_PATH}/components/libraries/libuarte/nrf_libuarte_async.c
    # ${NRF5_SDK_PATH}/components/libraries/led_softblink/led_softblink.c
    # ${NRF5_SDK_PATH}/components/libraries/hci/hci_transport.c
    # ${NRF5_SDK_PATH}/components/libraries/hci/hci_slip.c
    # ${NRF5_SDK_PATH}/components/libraries/hci/hci_mem_pool.c
    # ${NRF5_SDK_PATH}/components/libraries/hardfault/nrf52/handler/hardfault_handler_keil.c
    # ${NRF5_SDK_PATH}/components/libraries/hardfault/nrf52/handler/hardfault_handler_iar.c
    # ${NRF5_SDK_PATH}/components/libraries/hardfault/nrf52/handler/hardfault_handler_gcc.c
    # ${NRF5_SDK_PATH}/components/libraries/hardfault/nrf51/handler/hardfault_handler_keil.c
    # ${NRF5_SDK_PATH}/components/libraries/hardfault/nrf51/handler/hardfault_handler_iar.c
    # ${NRF5_SDK_PATH}/components/libraries/hardfault/nrf51/handler/hardfault_handler_gcc.c
    # ${NRF5_SDK_PATH}/components/libraries/hardfault/hardfault_implementation.c
    # ${NRF5_SDK_PATH}/components/libraries/gpiote/app_gpiote.c
    # ${NRF5_SDK_PATH}/components/libraries/gfx/nrf_gfx.c
    # ${NRF5_SDK_PATH}/components/libraries/fstorage/nrf_fstorage_sd.c
    # ${NRF5_SDK_PATH}/components/libraries/fstorage/nrf_fstorage_nvmc.c
    # ${NRF5_SDK_PATH}/components/libraries/fstorage/nrf_fstorage.c
    # ${NRF5_SDK_PATH}/components/libraries/fifo/app_fifo.c
    # ${NRF5_SDK_PATH}/components/libraries/fds/fds.c
    # ${NRF5_SDK_PATH}/components/libraries/experimental_task_manager/task_manager.c
    # ${NRF5_SDK_PATH}/components/libraries/experimental_section_vars/nrf_section_iter.c
    # ${NRF5_SDK_PATH}/components/libraries/ecc/ecc.c
    # ${NRF5_SDK_PATH}/components/libraries/csense_drv/nrf_drv_csense.c
    # ${NRF5_SDK_PATH}/components/libraries/csense/nrf_csense.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/optiga/optiga_backend_utils.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/optiga/optiga_backend_rng.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/optiga/optiga_backend_init.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/optiga/optiga_backend_ecdsa.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/optiga/optiga_backend_ecdh.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/optiga/optiga_backend_ecc.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/oberon/oberon_backend_hmac.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/oberon/oberon_backend_hash.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/oberon/oberon_backend_eddsa.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/oberon/oberon_backend_ecdsa.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/oberon/oberon_backend_ecdh.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/oberon/oberon_backend_ecc.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/oberon/oberon_backend_chacha_poly_aead.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/nrf_sw/nrf_sw_backend_hash.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/nrf_hw/nrf_hw_backend_rng_mbedtls.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/nrf_hw/nrf_hw_backend_rng.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/nrf_hw/nrf_hw_backend_init.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/micro_ecc/micro_ecc_backend_ecdsa.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/micro_ecc/micro_ecc_backend_ecdh.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/micro_ecc/micro_ecc_backend_ecc.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/mbedtls/mbedtls_backend_init.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/mbedtls/mbedtls_backend_hmac.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/mbedtls/mbedtls_backend_hash.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/mbedtls/mbedtls_backend_ecdsa.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/mbedtls/mbedtls_backend_ecdh.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/mbedtls/mbedtls_backend_ecc.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/mbedtls/mbedtls_backend_aes_aead.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/mbedtls/mbedtls_backend_aes.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cifra/cifra_backend_aes_aead.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310_bl/cc310_bl_backend_shared.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310_bl/cc310_bl_backend_init.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310_bl/cc310_bl_backend_hash.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310_bl/cc310_bl_backend_ecdsa.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310_bl/cc310_bl_backend_ecc.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_shared.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_rng.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_mutex.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_init.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_hmac.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_hash.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_eddsa.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_ecdsa.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_ecdh.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_ecc.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_chacha_poly_aead.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_aes_aead.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/backend/cc310/cc310_backend_aes.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_shared.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_rng.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_init.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_hmac.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_hkdf.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_hash.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_error.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_eddsa.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_ecdsa.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_ecdh.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_ecc.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_aes_shared.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_aes.c
    # ${NRF5_SDK_PATH}/components/libraries/crypto/nrf_crypto_aead.c
    # ${NRF5_SDK_PATH}/components/libraries/crc32/crc32.c
    # ${NRF5_SDK_PATH}/components/libraries/crc16/crc16.c
    # ${NRF5_SDK_PATH}/components/libraries/cli/uart/nrf_cli_uart.c
    # ${NRF5_SDK_PATH}/components/libraries/cli/rtt/nrf_cli_rtt.c
    # ${NRF5_SDK_PATH}/components/libraries/cli/libuarte/nrf_cli_libuarte.c
    # ${NRF5_SDK_PATH}/components/libraries/cli/cdc_acm/nrf_cli_cdc_acm.c
    # ${NRF5_SDK_PATH}/components/libraries/cli/ble_uart/nrf_cli_ble_uart.c
    # ${NRF5_SDK_PATH}/components/libraries/cli/nrf_cli.c
    # ${NRF5_SDK_PATH}/components/libraries/cli/cli_utils_cmds.c
    # ${NRF5_SDK_PATH}/components/libraries/button/app_button.c
    # ${NRF5_SDK_PATH}/components/libraries/bsp/bsp_nfc.c
    # ${NRF5_SDK_PATH}/components/libraries/bsp/bsp_cli.c
    # ${NRF5_SDK_PATH}/components/libraries/bsp/bsp_btn_ble.c
    # ${NRF5_SDK_PATH}/components/libraries/bsp/bsp_btn_ant.c
    # ${NRF5_SDK_PATH}/components/libraries/bsp/bsp.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/serial_dfu/nrf_dfu_serial_usb.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/serial_dfu/nrf_dfu_serial_uart.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/serial_dfu/nrf_dfu_serial.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_ver_validation.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_validation.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_utils.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_trigger_usb.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_transport.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_svci_handler.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_svci.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_settings_svci.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_settings.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_req_handler.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_mbr.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_handling_error.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu_flash.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/nrf_dfu.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/dfu/dfu-cc.pb.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/ble_dfu/nrf_dfu_ble.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/ant_dfu/nrf_dfu_ant.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/nrf_bootloader_wdt.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/nrf_bootloader_info.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/nrf_bootloader_fw_activation.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/nrf_bootloader_dfu_timers.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/nrf_bootloader_app_start_final.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/nrf_bootloader_app_start.c
    # ${NRF5_SDK_PATH}/components/libraries/bootloader/nrf_bootloader.c
    # ${NRF5_SDK_PATH}/components/libraries/block_dev/sdc/nrf_block_dev_sdc.c
    # ${NRF5_SDK_PATH}/components/libraries/block_dev/ram/nrf_block_dev_ram.c
    # ${NRF5_SDK_PATH}/components/libraries/block_dev/qspi/nrf_serial_flash_params.c
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${NRF5_SDK_PATH}/config/nrf52840/config
    ${NRF5_SDK_PATH}/modules/nrfx
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/include
    ${NRF5_SDK_PATH}/modules/nrfx/drivers/src
    ${NRF5_SDK_PATH}/modules/nrfx/hal
    ${NRF5_SDK_PATH}/modules/nrfx/mdk
    # ${NRF5_SDK_PATH}/modules/nrfx/templates
    ${NRF5_SDK_PATH}/integration/nrfx
    ${NRF5_SDK_PATH}/components/toolchain/cmsis/include
    ${NRF5_SDK_PATH}/components/drivers_nrf
    ${NRF5_SDK_PATH}/components/drivers_nrf/nrf_soc_nosd
    ${NRF5_SDK_PATH}/components/libraries/atomic
    ${NRF5_SDK_PATH}/components/libraries/atomic_fifo
    ${NRF5_SDK_PATH}/components/libraries/atomic_flags
    ${NRF5_SDK_PATH}/components/libraries/balloc
    ${NRF5_SDK_PATH}/components/libraries/block_dev
    ${NRF5_SDK_PATH}/components/libraries/bootloader
    ${NRF5_SDK_PATH}/components/libraries/bsp
    ${NRF5_SDK_PATH}/components/libraries/button
    ${NRF5_SDK_PATH}/components/libraries/cli
    ${NRF5_SDK_PATH}/components/libraries/crc16
    ${NRF5_SDK_PATH}/components/libraries/crc32
    ${NRF5_SDK_PATH}/components/libraries/crypto
    ${NRF5_SDK_PATH}/components/libraries/csense
    ${NRF5_SDK_PATH}/components/libraries/csense_drv
    ${NRF5_SDK_PATH}/components/libraries/delay
    ${NRF5_SDK_PATH}/components/libraries/ecc
    ${NRF5_SDK_PATH}/components/libraries/experimental_section_vars
    ${NRF5_SDK_PATH}/components/libraries/experimental_task_manager
    ${NRF5_SDK_PATH}/components/libraries/fds
    ${NRF5_SDK_PATH}/components/libraries/fifo
    ${NRF5_SDK_PATH}/components/libraries/fstorage
    ${NRF5_SDK_PATH}/components/libraries/gfx
    ${NRF5_SDK_PATH}/components/libraries/gpiote
    ${NRF5_SDK_PATH}/components/libraries/hardfault
    ${NRF5_SDK_PATH}/components/libraries/hci
    ${NRF5_SDK_PATH}/components/libraries/led_softblink
    ${NRF5_SDK_PATH}/components/libraries/libuarte
    ${NRF5_SDK_PATH}/components/libraries/log
    ${NRF5_SDK_PATH}/components/libraries/log/src
    ${NRF5_SDK_PATH}/components/libraries/low_power_pwm
    ${NRF5_SDK_PATH}/components/libraries/mem_manager
    ${NRF5_SDK_PATH}/components/libraries/memobj
    ${NRF5_SDK_PATH}/components/libraries/mpu
    ${NRF5_SDK_PATH}/components/libraries/mutex
    ${NRF5_SDK_PATH}/components/libraries/pwm
    ${NRF5_SDK_PATH}/components/libraries/pwr_mgmt
    ${NRF5_SDK_PATH}/components/libraries/queue
    ${NRF5_SDK_PATH}/components/libraries/ringbuf
    ${NRF5_SDK_PATH}/components/libraries/scheduler
    ${NRF5_SDK_PATH}/components/libraries/sdcard
    ${NRF5_SDK_PATH}/components/libraries/sensorsim
    ${NRF5_SDK_PATH}/components/libraries/sha256
    ${NRF5_SDK_PATH}/components/libraries/simple_timer
    ${NRF5_SDK_PATH}/components/libraries/slip
    ${NRF5_SDK_PATH}/components/libraries/sortlist
    ${NRF5_SDK_PATH}/components/libraries/spi_mngr
    ${NRF5_SDK_PATH}/components/libraries/stack_guard
    ${NRF5_SDK_PATH}/components/libraries/stack_info
    ${NRF5_SDK_PATH}/components/libraries/strerror
    ${NRF5_SDK_PATH}/components/libraries/svc
    ${NRF5_SDK_PATH}/components/libraries/timer
    ${NRF5_SDK_PATH}/components/libraries/twi_mngr
    ${NRF5_SDK_PATH}/components/libraries/twi_sensor
    ${NRF5_SDK_PATH}/components/libraries/uart
    ${NRF5_SDK_PATH}/components/libraries/usbd
    ${NRF5_SDK_PATH}/components/libraries/util
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
    NRF52840_XXAA
    S113
    S140
)
### END NRF5 SDK ###

target_link_options(${CMAKE_PROJECT_NAME} PUBLIC
    "LINKER:-Map=${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}.map,--cref"
    -T ${CMAKE_CURRENT_LIST_DIR}/generic_gcc_nrf52.ld
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/generic_gcc_nrf52.ld)
