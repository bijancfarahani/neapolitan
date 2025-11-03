//
// Created by bijan on 11/2/2025.
//

#include "FlavorPanel.h"
#include "PluginProcessor.h"
namespace neapolitan {

     FlavorPanel::FlavorPanel (PluginProcessor& p) //: _knobs { VanillaKnob (p), FlavorKnob (p), FlavorKnob (p) }
    {
         auto area = getLocalBounds();
         _knobs.add(std::unique_ptr<FlavorKnob>(new VanillaKnob(p)));
         _knobs.add(std::unique_ptr<FlavorKnob>(new StrawberryKnob(p)));
         _knobs.add(std::unique_ptr<FlavorKnob>(new ChocolateKnob(p)));  //_knobs.emplace_back (std::make_unique<FlavorKnob> (new VanillaKnob(p)));
        /* _knobs[0]->setBounds(area.removeFromLeft(area.getWidth() / 3));
         _knobs[1]->setBounds(area.removeFromLeft(area.getWidth() / 2)); // half of remaining area
         _knobs[2]->setBounds(area); // whatever remains
        */
         auto third = area.getWidth() / 3;
         for (auto& knob: _knobs)
         {
             addAndMakeVisible (knob);
             knob->setBounds(area.removeFromLeft(third).reduced(10));  // give each knob 1/3 width and some padding
         }
         //_knobs[0]->setBounds (50, 50, getWidth() * 0.33, getHeight());

    }
    void FlavorPanel::paint (juce::Graphics& g)
    {
        // g.setColour(juce::Colours::skyblue);
        // g.fillRect (getLocalBounds());
    }
    void FlavorPanel::resized()
    {
         auto area = getLocalBounds();

        //Component::resized();
         auto third = area.getWidth() / 3;
         for (auto& knob: _knobs)
         {
             addAndMakeVisible (knob);
             knob->setBounds(area.removeFromLeft(third).reduced(10));  // give each knob 1/3 width and some padding
         }
    }

} // neapolitan