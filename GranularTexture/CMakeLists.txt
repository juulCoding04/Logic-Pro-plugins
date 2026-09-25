juce_add_plugin(GranularTexture
    COMPANY_NAME "Juul C."
    PLUGIN_MANUFACTURER_CODE Juul
    PLUGIN_CODE Gtex
    FORMATS AU Standalone
    COPY_PLUGIN_AFTER_BUILD TRUE
    PRODUCT_NAME "Granular Texture")

target_sources(GranularTexture PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
    Source/Scheduler.cpp
    Source/Grain.cpp)

target_link_libraries(GranularTexture PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp)

target_compile_definitions(GranularTexture PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0)
