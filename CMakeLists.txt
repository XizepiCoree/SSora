cmake_minimum_required(VERSION 3.22)
project(SoraKick VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.4
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(SoraKick
    COMPANY_NAME "KickLab"
    PLUGIN_MANUFACTURER_CODE Klab
    PLUGIN_CODE Skck
    FORMATS VST3
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    PRODUCT_NAME "Sora Kick"
    COPY_PLUGIN_AFTER_BUILD FALSE)

target_sources(SoraKick PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h)

# Необязательная картинка героини: положите PNG в Resources/heroine.png
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Resources/heroine.png")
    juce_add_binary_data(SoraAssets SOURCES Resources/heroine.png)
    target_link_libraries(SoraKick PRIVATE SoraAssets)
    target_compile_definitions(SoraKick PRIVATE SORA_HAS_IMAGE=1)
endif()

target_compile_definitions(SoraKick PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(SoraKick
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
