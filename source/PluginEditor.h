#pragma once

#include "BinaryData.h"
#include "FlavorKnob.h"
#include "PluginProcessor.h"
#include "melatonin_inspector/melatonin_inspector.h"
namespace neapolitan
{
//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor, private juce::Timer
{
   public:
    explicit PluginEditor(PluginProcessor&);
    ~PluginEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

   private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor& processorRef;
    std::unique_ptr<melatonin::Inspector> inspector;
    juce::TextButton inspectButton{"Inspect the UI"};

    // === UI Elements ===
    FlavorKnob flavorKnobs;

    juce::TextButton footer;
    juce::Rectangle<int> visualizer;

    juce::Label gainLabel;
    juce::Slider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
} // namespace neapolitan