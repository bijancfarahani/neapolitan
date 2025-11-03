//
// Created by bijan on 11/2/2025.
//

#include "FlavorPanel.h"
#include "PluginProcessor.h"
namespace neapolitan {

     FlavorPanel::FlavorPanel (PluginProcessor& p)
    {
         _knobs.add (std::make_unique<StrawberryKnob> (p));
         _knobs.add (std::make_unique<VanillaKnob> (p));
         _knobs.add (std::make_unique<ChocolateKnob> (p));
    }

    void FlavorPanel::paint (juce::Graphics& g)
    {
         g.setColour(juce::Colours::skyblue);
         g.fillRect (getLocalBounds());
    }

    void FlavorPanel::resized()
    {
         auto area = getLocalBounds();
         const auto third = area.getWidth() / 3;
         for (auto* knob: _knobs)
         {
             addAndMakeVisible (knob);
             // Give each knob 1/3 width and some padding.
             knob->setBounds(area.removeFromLeft(third).reduced(10));
         }
    }

} // neapolitan