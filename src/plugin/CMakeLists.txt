# SpatialScene: the JUCE plugin. Identity values are the AX8 placeholders (docs/BUILD_PLAN.md §2);
# they must be confirmed before the first beta and never changed after users save projects.
#
# This file is include()d from the top-level CMakeLists.txt, so paths use CMAKE_CURRENT_LIST_DIR and the
# JUCE artefacts land in build/<preset>/SpatialScene_artefacts/<Config>/.
set(SPATIAL_PLUGIN_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(SPATIAL_PLUGIN_FORMATS VST3 Standalone)
if(APPLE)
    list(APPEND SPATIAL_PLUGIN_FORMATS AU)
endif()

juce_add_plugin(SpatialScene
                PRODUCT_NAME "SpatialScene"
                COMPANY_NAME "Makroof"                      # AX8
                BUNDLE_ID com.makroof.spatialscene          # AX8
                PLUGIN_MANUFACTURER_CODE Mkrf               # AX8
                PLUGIN_CODE Spsc                            # AX8
                FORMATS ${SPATIAL_PLUGIN_FORMATS}
                IS_SYNTH FALSE
                NEEDS_MIDI_INPUT FALSE
                NEEDS_MIDI_OUTPUT FALSE
                IS_MIDI_EFFECT FALSE
                EDITOR_WANTS_KEYBOARD_FOCUS FALSE
                COPY_PLUGIN_AFTER_BUILD FALSE
                VST3_CATEGORIES Fx Spatial
                AU_MAIN_TYPE kAudioUnitType_Effect)

target_sources(SpatialScene PRIVATE
               "${SPATIAL_PLUGIN_DIR}/PluginProcessor.h"
               "${SPATIAL_PLUGIN_DIR}/PluginProcessor.cpp")

# Anything in src/ is included as "plugin/...", "contract/...", etc.
target_include_directories(SpatialScene PUBLIC "${SPATIAL_PLUGIN_DIR}/..")

target_compile_definitions(SpatialScene PUBLIC
                           JUCE_WEB_BROWSER=0
                           JUCE_USE_CURL=0
                           JUCE_VST3_CAN_REPLACE_VST2=0
                           # JUCE_DISPLAY_SPLASH_SCREEN stays at the JUCE default (licence check in Phase 13).
                           )

# JUCE modules are linked PRIVATE on purpose: their sources are compiled once, into this shared-code
# target. The format wrappers (and spatial_tests) re-export this target's include directories instead of
# linking the modules again, which is what JUCE's own juce_add_plugin does for the wrappers.
target_link_libraries(SpatialScene
                      PUBLIC spatial::contract
                             spatial::sim
                             spatial::module3d
                             spatial::plugin_core
                             juce::juce_recommended_config_flags
                             juce::juce_recommended_warning_flags
                      PRIVATE juce::juce_audio_utils
                              spatial::warnings)
