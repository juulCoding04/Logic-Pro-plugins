juce_add_plugin(HelloWorldPlugin
    COMPANY_NAME "Juul C."
    PLUGIN_MANUFACTURER_CODE Juul
    PLUGIN_CODE Hwld
    FORMATS VST3 AU Standalone
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT TRUE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PRODUCT_NAME "Hello World Plugin")

target_sources(HelloWorldPlugin PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp)

target_link_libraries(HelloWorldPlugin PRIVATE
    juce::juce_audio_utils)

target_compile_definitions(HelloWorldPlugin PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_IGNORE_VST3_MISMATCHED_PARAMETER_ID_WARNING=1)
