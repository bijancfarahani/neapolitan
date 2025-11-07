#pragma once

#include "BinaryData.h"
#include "FlavorPanel.h"
#include "FrequencyVisualizer.h"
#include "PluginProcessor.h"
#include "melatonin_inspector/melatonin_inspector.h"

namespace neapolitan
{
//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor, private juce::Timer
{
   public:
   explicit PluginEditor (PluginProcessor&);
   ~PluginEditor() override;

   //==============================================================================
   void paint (juce::Graphics&) override;
   void resized() override;
   void drawFrame (juce::Graphics& g);
   void drawNextFrameOfSpectrum();
   void timerCallback() override;

   private:
   // This reference is provided as a quick way for your editor to
   // access the processor object that created it.
   PluginProcessor&                      processorRef;
   std::unique_ptr<melatonin::Inspector> inspector;
   juce::TextButton                      inspectButton {"Inspect the UI"};

   // === UI Elements ===
   FlavorPanel flavorPanel;

   juce::TextButton     footer;
   juce::Rectangle<int> visualizer;
   //FrequencyVisualizer  _frequencyVisualizer;

   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
} // namespace neapolitan