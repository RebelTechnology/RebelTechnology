#ifndef INCLUDED_DEBUG_H
#define INCLUDED_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

  void debug_message(const char* string);
  void debug_printf(const char* fmt, ...);

#undef WPRINT_MACRO
#undef WPRINT_APP_INFO
#undef WPRINT_APP_ERROR

#define WPRINT_MACRO(args) do {debug_printf args;} while(0==1)
#define WPRINT_APP_INFO(args) WPRINT_MACRO(args)
#define WPRINT_APP_ERROR(args) do { WPRINT_MACRO(args); WICED_ASSERTION_FAIL_ACTION(); } while(0)

  void debug_message(const char* string);

#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_DEBUG_H */
