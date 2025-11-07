#include "FlavorKnob.h"

namespace neapolitan
{
FlavorKnob::FlavorKnob (
    PluginProcessor&            p,
    const juce::StringRef       flavorName,
    juce::RangedAudioParameter& rangedAudioParameter
)
    : _processor (p)
{
   // --- Gain Slider ---
   gainSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
   gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, getWidth(), getHeight() * 0.2);
   gainSlider.setColour (juce::Slider::thumbColourId, juce::Colours::blue);
   gainSlider.setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::brown);
   addAndMakeVisible (gainSlider);

   // === Attach to processor parameter ===
   gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
       _processor.apvts, "gain_" + flavorName, gainSlider
   );
}

FlavorKnob::~FlavorKnob() = default;

void FlavorKnob::paint (juce::Graphics& g)
{
   g.setColour (getBackgroundColor());
   g.fillRect (getLocalBounds());
   // Example: animated pulsing ring (visual hook)
   const auto  bounds = gainSlider.getBounds().toFloat();
   const float time = static_cast<float> (juce::Time::getMillisecondCounter() % 1000) / 1000.0f;
   const float pulse = 0.5f + 0.5f * std::sin (juce::MathConstants<float>::twoPi * time);

   g.setColour (juce::Colours::mediumseagreen.withAlpha (0.2f + 0.3f * pulse));
   g.drawEllipse (bounds.expanded (10.0f), 2.0f);
}
void FlavorKnob::resized()
{
   auto childBounds = juce::Rectangle<int> (getWidth(), getHeight());
   gainSlider.setBounds (childBounds);
}

VanillaKnob::VanillaKnob (PluginProcessor& p)
    : FlavorKnob (p, getFlavorName(), *(p._pluginParameters[0]))
{
}

juce::Colour VanillaKnob::getBackgroundColor() const
{
   return juce::Colour::fromRGB (246, 226, 179);
}
juce::String VanillaKnob::getFlavorName() const { return "vanilla"; }

StrawberryKnob::StrawberryKnob (PluginProcessor& p)
    : FlavorKnob (p, getFlavorName(), *(p._pluginParameters[1]))
{
}
juce::String StrawberryKnob::getFlavorName() const { return "strawberry"; }

juce::Colour StrawberryKnob::getBackgroundColor() const
{
   return juce::Colour::fromRGB (253, 174, 174);
}

ChocolateKnob::ChocolateKnob (PluginProcessor& p)
    : FlavorKnob (p, getFlavorName(), *(p._pluginParameters[2]))
{
}
juce::String ChocolateKnob::getFlavorName() const { return "chocolate"; }

juce::Colour ChocolateKnob::getBackgroundColor() const
{
   return juce::Colour::fromRGB (126, 102, 81);
}
} // namespace neapolitan
