#pragma once
#include "PluginProcessor.h"
#include "juce_gui_basics/juce_gui_basics.h"
namespace neapolitan
{

struct AttachedSlider
{
    AttachedSlider(
        juce::RangedAudioParameter& rangedAudioParameter)
        : slider(), attachment(rangedAudioParameter, slider, nullptr)
    {
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    }

    juce::Slider slider;
    juce::SliderParameterAttachment attachment;
};
class FlavorKnob : public juce::Component
{
   public:
    explicit FlavorKnob(PluginProcessor& p, juce::StringRef flavorName, juce::RangedAudioParameter& rangedAudioParameter);
    ~FlavorKnob() override = default;

    void paint(juce::Graphics& g) override;

    void resized() override;

   protected:
    virtual juce::Colour getBackgroundColor() const = 0;
    virtual juce::String getFlavorName() const = 0;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    // juce::Slider gainSlider;
    AttachedSlider gainSlider;

   private:
    PluginProcessor& _processor;
    juce::Label gainLabel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlavorKnob)
};

    class VanillaKnob final : public FlavorKnob
    {
        public:
        explicit VanillaKnob(PluginProcessor& p);

        void paint(juce::Graphics& g) override
        {
            FlavorKnob::paint(g);
            return;
        }

        juce::Colour getBackgroundColor() const override
        {
            return juce::Colour::fromRGB(245, 225, 209);
            return juce::Colours::navajowhite;
        }
        juce::String getFlavorName() const override {return "Vanilla";}

    };

    class StrawberryKnob final : public FlavorKnob
    {
    public:
        explicit StrawberryKnob (PluginProcessor& p);
        juce::String getFlavorName() const override {return "Strawberry";}

        juce::Colour getBackgroundColor() const override
        {
            return juce::Colour::fromRGB(210, 167, 162);
            return juce::Colours::indianred;
        }
    };

    class ChocolateKnob final : public FlavorKnob
    {
    public:
        explicit ChocolateKnob (PluginProcessor& p);
        juce::String getFlavorName() const override {return "Chocolate";}

        juce::Colour getBackgroundColor() const override
        {
            return juce::Colour::fromRGB(108, 79, 61);
            return juce::Colours::chocolate;
        }
    };

} // namespace neapolitan