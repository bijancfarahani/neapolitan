//
// Created by bijan on 11/2/2025.
//

#include "FlavorPanel.h"
#include "PluginProcessor.h"
#include <ranges>
namespace neapolitan
{

FlavorPanel::FlavorPanel (PluginProcessor& p)
    : _knobs {
          std::make_unique<VanillaKnob> (p),
          std::make_unique<StrawberryKnob> (p),
          std::make_unique<ChocolateKnob> (p)
      }
{
   for (const auto& knob : _knobs)
   {
      addAndMakeVisible (*knob);
   }
}

FlavorPanel::~FlavorPanel() = default;

void FlavorPanel::paint (juce::Graphics& g)
{
   g.setColour (juce::Colours::skyblue);
   g.fillRect (getLocalBounds());
}

void FlavorPanel::resized()
{
   auto area = getLocalBounds();
   int  thirdWidth = area.getWidth() / 3;
   // height stays proportional, so this is fine
   int  side = area.getHeight();
   for (const auto idx : std::views::iota (0, 3))
   {
      _knobs[idx]->setBounds (thirdWidth * idx, 0, thirdWidth, side);
   }
}

} // namespace neapolitan