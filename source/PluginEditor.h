#pragma once

// #include <juce_audio_processors/processors/juce_AudioProcessorEditor.h>
#include "BinaryData.h"
#include "PluginProcessor.h"
#include "melatonin_inspector/melatonin_inspector.h"

//==============================================================================
class NeapolitanAudioProcessorEditor : public juce::AudioProcessorEditor
{
   public:
    explicit NeapolitanAudioProcessorEditor(NeapolitanAudioProcessor&);
    ~NeapolitanAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

   private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NeapolitanAudioProcessor& processorRef;
    std::unique_ptr<melatonin::Inspector> inspector;
    juce::TextButton inspectButton{"Inspect the UI"};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NeapolitanAudioProcessorEditor)
};