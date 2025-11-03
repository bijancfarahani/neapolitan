#include "FlavorKnob.h"

namespace neapolitan{
    FlavorKnob::FlavorKnob (PluginProcessor& p, const juce::StringRef flavorName, juce::RangedAudioParameter& rangedAudioParameter) : _processor (p), gainSlider (rangedAudioParameter)
    {
        // --- Gain Slider ---
        gainSlider.slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        gainSlider.slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
        gainSlider.slider.setColour (juce::Slider::thumbColourId, juce::Colours::blue);
        gainSlider.slider.setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::brown);
        // BIJAN: How to move it in GUI?
        //.setText("TESTING", juce::dontSendNotification);
        //  gainLabel.setJustificationType(juce::Justification::centred);
        //  gainLabel.setColour(juce::Label::textColourId, juce::Colours::white);

        addAndMakeVisible (gainSlider.slider);
        // addAndMakeVisible (gainLabel);

        // === Attach to processor parameter ===
        gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
            _processor.apvts, juce::String ("gain_") + flavorName, gainSlider.slider);
    }

    void FlavorKnob::paint (juce::Graphics& g)
    {
        g.setColour (getBackgroundColor());
        g.fillRect (getLocalBounds());
        // Example: animated pulsing ring (visual hook)
        const auto bounds = gainSlider.slider.getBounds().toFloat();
        const float time = static_cast<float> (juce::Time::getMillisecondCounter() % 1000) / 1000.0f;
        const float pulse = 0.5f + 0.5f * std::sin (juce::MathConstants<float>::twoPi * time);

        g.setColour (juce::Colours::mediumseagreen.withAlpha (0.2f + 0.3f * pulse));
        g.drawEllipse (bounds.expanded (10.0f), 2.0f);
    }
    void FlavorKnob::resized()
    {
        gainSlider.slider.setBounds (getWidth() * 0.5, getHeight() * 0.5, 100, 100);
    }

    VanillaKnob::VanillaKnob (PluginProcessor& p) : FlavorKnob (p, getFlavorName(), *(p._pluginParameters[0]))
    {

    }
    StrawberryKnob::StrawberryKnob (PluginProcessor& p) : FlavorKnob (p, getFlavorName(), *(p._pluginParameters[1]))
    {
    }
    ChocolateKnob::ChocolateKnob (PluginProcessor& p) : FlavorKnob (p, getFlavorName(), *(p._pluginParameters[2]))
    {
    }
}
