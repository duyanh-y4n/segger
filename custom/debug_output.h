/**
 * File            : debug_output.h
 * Author          : Duy Anh Pham <duyanh.y4n.pham@gmail.com>
 * Date            : 08.09.2020
 * Last Modified By: Duy Anh Pham <duyanh.y4n.pham@gmail.com>
 */
#ifndef DEBUG_OUTPUT_H
#define DEBUG_OUTPUT_H

/*
 * SEMIHOSTING_ACTIVE
 * */
#if defined(SEMIHOSTING_ACTIVE)
#define debug_printf(x, y, ...) ((x) ? trace_printf(y, ##__VA_ARGS__) : 0)

/*
 * SYSVIEWPRINT_ACTIVE
 * */
#elif defined(SYSVIEWPRINT_ACTIVE)
#define debug_printf(x, y, ...)                                                \
  ((x) ? SEGGER_SYSVIEW_printf(0, y, ##__VA_ARGS__) : 0)

/*
 * RTT_ACTIVE
 * */
#elif defined(RTT_ACTIVE)
#include "SEGGER_RTT.h"

#define RTT_Init() (SEGGER_RTT_Init())

#define debug_printf(x, y, ...)                                                \
  ((x) ? SEGGER_RTT_printf(0, y, ##__VA_ARGS__) : 0)

#undef TRACE // resolve warning

#define TRACE(x, y, ...) ((x) ? SEGGER_RTT_printf(0, y, ##__VA_ARGS__) : 0)

#define INFO(x, y, ...) ((x) ? SEGGER_RTT_printf(0, y, ##__VA_ARGS__) : 0)

#define ERROR(y, ...) SEGGER_RTT_printf(0, y, ##__VA_ARGS__)

/*
 * -DEBUG_OUTPUT disable
 * */
#else
#define RTT_Init() (0)

#define debug_printf(x, y, ...) (0)

#undef TRACE // resolve warning

#define TRACE(x, y, ...) (0)

#define INFO(x, y, ...) (0)

#define ERROR(y, ...) (0)
#endif

#endif /* DEBUG_OUTPUT_H */
