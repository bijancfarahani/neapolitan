//
// Created by bijan on 11/2/2025.
//

#pragma once
#include "PluginProcessor.h"
#include "juce_gui_basics/juce_gui_basics.h"

namespace neapolitan
{

class FrequencyVisualizer : public juce::Component, private juce::Timer
{
   public:
       explicit FrequencyVisualizer (PluginProcessor& p);
       ~FrequencyVisualizer() override;

       void drawFrame (juce::Graphics& g);

       void paint (juce::Graphics& g) override;

       void resized() override;

       void drawNextFrameOfSpectrum (FftData& flavorNoiseData);
       void timerCallback() override;

   private:
   PluginProcessor& processorRef;
   std::array<juce::Colour, 3> _lineColors;
};

} // namespace neapolitan
