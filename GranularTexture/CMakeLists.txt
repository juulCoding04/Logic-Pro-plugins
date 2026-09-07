juce_add_plugin(GranularTexture
    COMPANY_NAME "Juul"
    PLUGIN_MANUFACTURER_CODE Juul
    PLUGIN_CODE Gtex
    FORMATS AU Standalone
    PRODUCT_NAME "Granular Texture")

target_sources(GranularTexture PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp)

target_link_libraries(GranularTexture PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp)

target_compile_definitions(GranularTexture PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0)

add_custom_command(TARGET GranularTexture_AU POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_BUNDLE_DIR:GranularTexture_AU>"
        "$ENV{HOME}/Library/Audio/Plug-Ins/Components/$<TARGET_BUNDLE_FILE_NAME:GranularTexture_AU>")
