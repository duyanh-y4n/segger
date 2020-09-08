/**
 * File            : debug_output.h
 * Author          : Duy Anh Pham <duyanh.y4n.pham@gmail.com>
 * Date            : 08.09.2020
 * Last Modified By: Duy Anh Pham <duyanh.y4n.pham@gmail.com>
 */
#ifndef DEBUG_OUTPUT_H
#define DEBUG_OUTPUT_H

#if defined(SEMIHOSTING_ACTIVE)
#define debug_printf(x, y, ...) ((x) ? trace_printf(y, ##__VA_ARGS__) : 0)

#elif defined(SYSVIEWPRINT_ACTIVE)
#define debug_printf(x, y, ...)                                                \
  ((x) ? SEGGER_SYSVIEW_printf(0, y, ##__VA_ARGS__) : 0)

#elif defined(RTT_ACTIVE)
#include "SEGGER_RTT.h"

#define RTT_Init() (SEGGER_RTT_Init())

#define debug_printf(x, y, ...)                                                \
  ((x) ? SEGGER_RTT_printf(0, y, ##__VA_ARGS__) : 0)

#undef TRACE // resolve warning

#define TRACE(x, y, ...) ((x) ? SEGGER_RTT_printf(0, y, ##__VA_ARGS__) : 0)

#define INFO(x, y, ...) ((x) ? SEGGER_RTT_printf(0, y, ##__VA_ARGS__) : 0)

#define ERROR(y, ...) SEGGER_RTT_printf(0, y, ##__VA_ARGS__)
#endif

#endif /* DEBUG_OUTPUT_H */
