set(SEGGER_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
set(SEGGER_SRC ${CMAKE_CURRENT_SOURCE_DIR}/SEGGER CACHE INTERNAL "")
set(SEGGER_CONF ${CMAKE_CURRENT_SOURCE_DIR}/Config CACHE INTERNAL "")
set(SEGGER_SAMPLE ${CMAKE_CURRENT_SOURCE_DIR}/Sample CACHE INTERNAL "")

add_library(SEGGER 
    #${CMAKE_CURRENT_SOURCE_DIR}/HardFault/SEGGER_HardFault_Handler.c

    # RTT
    ${SEGGER_SRC}/SEGGER_RTT.c
    ${SEGGER_SRC}/SEGGER_RTT.h
    ${SEGGER_CONF}/SEGGER_RTT_Conf.h
    ${SEGGER_SRC}/SEGGER_RTT_printf.c

    # syscall
    ${SEGGER_SRC}/Syscalls/SEGGER_RTT_Syscalls_GCC.c
    #${SEGGER_SRC}/Syscalls/SEGGER_RTT_Syscalls_IAR.c
    #${SEGGER_SRC}/Syscalls/SEGGER_RTT_Syscalls_KEIL.c
    #${SEGGER_SRC}/Syscalls/SEGGER_RTT_Syscalls_SES.c

    # system view
    ${SEGGER_SRC}/SEGGER_SYSVIEW.c
    ${SEGGER_SRC}/SEGGER_SYSVIEW.h
    ${SEGGER_SRC}/SEGGER_SYSVIEW_ConfDefaults.h
    ${SEGGER_SRC}/SEGGER_SYSVIEW_Int.h
    ${SEGGER_CONF}/SEGGER_SYSVIEW_Conf.h

    # armv7 (for cormtex m3, m4)
    ${SEGGER_SRC}/SEGGER_RTT_ASM_ARMv7M.S
    )

target_include_directories(SEGGER PUBLIC
    ${SEGGER_SRC}
    ${SEGGER_CONF}
    ${SEGGER_PATH}/custom # e.g: debug_output.h
    )

if(DEFINED FREERTOS_INC)
    target_include_directories(SEGGER PUBLIC
        # FreeRTOS includes
        ${FREERTOS_INC}
        ${FREERTOS_GCC}
        # path for FreeRTOSConfig.h
        ${APP_INC}
        )
else()
    message(ERROR "Can't find FreeRTOS includes header")
endif(DEFINED FREERTOS_INC)


if(DEFINED FREERTOSV10)
    message("FreeRTOSV10 for SEGGER System View set")
    target_sources(SEGGER PUBLIC
        ${SEGGER_SAMPLE}/FreeRTOSV10/SEGGER_SYSVIEW_FreeRTOS.c
        ${SEGGER_SAMPLE}/FreeRTOSV10/SEGGER_SYSVIEW_FreeRTOS.h
        ${SEGGER_SAMPLE}/FreeRTOSV10/Config/Cortex-M/SEGGER_SYSVIEW_Config_FreeRTOS.c
        )
    target_include_directories(SEGGER PUBLIC
        ${SEGGER_SAMPLE}/FreeRTOSV10
        )
else()
    message(ERROR "FreeRTOS for System View not set")
endif(DEFINED FREERTOSV10)
