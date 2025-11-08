//
// Created by bijan on 11/2/2025.
//

#pragma once
#include "juce_gui_basics/juce_gui_basics.h"

namespace neapolitan
{
class PluginProcessor;

class FrequencyVisualizer : public juce::Component, private juce::Timer
{
   public:
   explicit FrequencyVisualizer (PluginProcessor& p, juce::Colour lineColor);
   ~FrequencyVisualizer() override;

   void drawFrame (juce::Graphics& g);

   void paint (juce::Graphics& g) override;

   void resized() override;

   void drawNextFrameOfSpectrum();
   void timerCallback() override;

   private:
   PluginProcessor& processorRef;
   juce::Colour     _lineColor;
};

} // namespace neapolitan
