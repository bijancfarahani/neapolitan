//
// Created by bijan on 11/2/2025.
//

#pragma once
#include <array>
#include <vector>
#include "FlavorKnob.h"
namespace neapolitan {

class FlavorPanel : public juce::Component
    {
public:
    explicit FlavorPanel (PluginProcessor& p);
    ~FlavorPanel() override = default;
    void paint(juce::Graphics& g) override;

    void resized() override;
private:
    //std::array<FlavorKnob, 3> _knobs;
    juce::OwnedArray<FlavorKnob> _knobs;
  //  std::vector<std::unique_ptr<FlavorKnob>> _knobs;
};

} // neapolitan


