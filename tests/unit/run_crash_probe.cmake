# Phase 06b scope 5: runs the hidden crash probe (test_fail_fast.cpp) and passes when it ends
# abnormally (SIGABRT / abort exit code) within LIMIT seconds; a hang hits the limit and fails.
# Usage: cmake -DPROBE=<spatial_tests> -DLIMIT=30 -P run_crash_probe.cmake
if(NOT PROBE OR NOT LIMIT)
    message(FATAL_ERROR "run_crash_probe.cmake: PROBE and LIMIT are required")
endif()
string(TIMESTAMP t0 "%s%f" UTC)
execute_process(COMMAND "${PROBE}" "[crash-probe]"
                RESULT_VARIABLE result
                OUTPUT_VARIABLE out
                ERROR_VARIABLE err
                TIMEOUT ${LIMIT})
string(TIMESTAMP t1 "%s%f" UTC)
math(EXPR elapsed_ms "(${t1} - ${t0}) / 1000")
message(STATUS "crash probe: result '${result}' after ${elapsed_ms} ms (limit ${LIMIT} s)")
if(result MATCHES "timeout")
    message(FATAL_ERROR "crash probe hung: no exit within ${LIMIT} s\n${out}\n${err}")
elseif(result STREQUAL "0")
    message(FATAL_ERROR "crash probe exited normally: it did not crash\n${out}\n${err}")
endif()
