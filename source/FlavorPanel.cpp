//
// Created by bijan on 11/2/2025.
//

#include "FlavorPanel.h"
#include "PluginProcessor.h"
#include <ranges>
namespace neapolitan {

     FlavorPanel::FlavorPanel (PluginProcessor& p)
    {
        _knobs.add (std::make_unique<VanillaKnob> (p));
        _knobs.add (std::make_unique<StrawberryKnob> (p));
        _knobs.add (std::make_unique<ChocolateKnob> (p));
        for (auto* knob : _knobs)
        {
            addAndMakeVisible (*knob);
        }
    }

    void FlavorPanel::paint (juce::Graphics& g)
    {
         g.setColour(juce::Colours::skyblue);
         g.fillRect (getLocalBounds());
    }

    void FlavorPanel::resized()
    {
         auto area = getLocalBounds();
         int thirdWidth = area.getWidth() / 3;
         int side = area.getHeight(); // height stays proportional, so this is fine

         // Center each square horizontally in its third
         //  knob[0]->setBounds (thirdWidth * 0, 0, thirdWidth, side);
         //  square2.setBounds (thirdWidth * 1, 0, thirdWidth, side);
         //  square3.setBounds (thirdWidth * 2, 0, thirdWidth, side);

         for (auto* knob: _knobs)
             for (const auto idx : std::views::iota (0, 3))
             {
                 _knobs[idx]->setBounds (thirdWidth * idx, 0, thirdWidth, side);

                 // Give each knob 1/3 width and some padding.
                 //  knob->setBounds(area.removeFromLeft(third).reduced(10));
             }
    }

} // neapolitan