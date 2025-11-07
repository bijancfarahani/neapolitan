//
// Created by bijan on 11/2/2025.
//

#pragma once
#include "FlavorKnob.h"
#include <array>
namespace neapolitan
{

class FlavorPanel : public juce::Component
{
   public:
   explicit FlavorPanel (PluginProcessor& p);
   ~FlavorPanel() override;
   void paint (juce::Graphics& g) override;

   void resized() override;

   private:
   std::array<std::unique_ptr<FlavorKnob>, 3> _knobs;
};

} // namespace neapolitan
