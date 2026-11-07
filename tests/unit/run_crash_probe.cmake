# Phase 06b scope 5: runs the hidden crash probe (test_fail_fast.cpp) and passes only when it ends by
# abort() within LIMIT seconds: on POSIX the process dies from SIGABRT (execute_process reports
# "Subprocess aborted" / "Child aborted"), on Windows the CRT's abort() exits with code 3. A hang hits the
# limit and fails; a normal exit, or any other non-zero code (e.g. Catch2's "no test matched" when the
# probe is missing or renamed), fails too, so the entry cannot pass without the probe actually crashing.
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
elseif(NOT (result MATCHES "^(Subprocess|Child) aborted$" OR result STREQUAL "3"))
    message(FATAL_ERROR "crash probe did not end by abort() (result '${result}')\n${out}\n${err}")
endif()
