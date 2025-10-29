#pragma once

// #include <juce_audio_processors/processors/juce_AudioProcessorEditor.h>
#include "BinaryData.h"
#include "PluginProcessor.h"
#include "melatonin_inspector/melatonin_inspector.h"
namespace neapolitan
{
//==============================================================================
class NeapolitanAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Timer
{
   public:
   explicit NeapolitanAudioProcessorEditor (NeapolitanAudioProcessor&);
   ~NeapolitanAudioProcessorEditor() override;

   //==============================================================================
   void paint (juce::Graphics&) override;
   void resized() override;

   private:
   // === Animation Timer ===
   void timerCallback() override;

   // This reference is provided as a quick way for your editor to
   // access the processor object that created it.
   NeapolitanAudioProcessor& processorRef;
   std::unique_ptr<melatonin::Inspector> inspector;
   juce::TextButton inspectButton { "Inspect the UI" };
   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NeapolitanAudioProcessorEditor)

   // === UI Elements ===
   juce::Slider gainSlider;
   juce::Label gainLabel;
   std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

   juce::TextButton footer;
   juce::Rectangle<int> visualizer;
};
}