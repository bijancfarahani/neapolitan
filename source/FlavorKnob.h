#pragma once
#include "PluginProcessor.h"
#include "juce_gui_basics/juce_gui_basics.h"
namespace neapolitan
{

class FlavorKnob : public juce::Component
{
   public:
    FlavorKnob(PluginProcessor& p);
    ~FlavorKnob() override = default;

    void paint(juce::Graphics& g) override;

    void resized() override
    {
        // Required if you have child components
        // Set bounds for subcomponents here
        // gainSlider.setBoundsRelative()
    }

   private:
    PluginProcessor& _processor;
    juce::Label gainLabel;
    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlavorKnob)
};

} // namespace neapolitan