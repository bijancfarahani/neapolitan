#include "PluginEditor.h"
namespace neapolitan
{
    PluginEditor::PluginEditor (PluginProcessor& p)
        : AudioProcessorEditor (&p), processorRef (p), visualizer (10, 10, 40, 40)
    {
        juce::ignoreUnused (processorRef);

        addAndMakeVisible (inspectButton);

        // this chunk of code instantiates and opens the melatonin inspector
        inspectButton.onClick = [&] {
            if (!inspector)
            {
                inspector = std::make_unique<melatonin::Inspector> (*this);
                inspector->onClose = [this]() { inspector.reset(); };
            }

            inspector->setVisible (true);
        };

        // Make sure that before the constructor has finished, you've set the
        // editor's size to whatever you need it to be.
        setSize (1280, 720);

        // --- Gain Slider ---
        gainSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
        gainSlider.setColour (juce::Slider::thumbColourId, juce::Colours::mediumseagreen);
        gainSlider.setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::seagreen);
        // BIJAN: How to move it in GUI?
        gainLabel.setText ("TESTING", juce::dontSendNotification);
        gainLabel.setJustificationType (juce::Justification::centred);
        gainLabel.setColour (juce::Label::textColourId, juce::Colours::white);
        gainSlider.setBounds (400, 400, 400, 400);

        addAndMakeVisible (gainSlider);
        addAndMakeVisible (gainLabel);

        // === Attach to processor parameter ===
        gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
            processorRef.apvts, "gain", gainSlider);

        footer.setColour (juce::TextButton::buttonColourId, juce::Colours::limegreen);
        footer.setButtonText ("Studio B, https://github.com/bijancfarahani/neapolitan");
        auto area = getLocalBounds();

        int headerFooterHeight = 36;
        footer.setBounds (area.removeFromBottom (headerFooterHeight));
        footer.setBounds (area.removeFromBottom (headerFooterHeight));
        addAndMakeVisible (footer);
        //visualizer.setBounds (40, 300, 300, 300);

        int x_start = area.getWidth() * 0.25;
        int width = area.getWidth() * 0.5;
        int y_start = area.getHeight() * 0.15;
        int height = area.getHeight() * 0.55;
        visualizer.setBounds (x_start, y_start, width, height);
        // === Start animation refresh (e.g., for meters or visual motion) ===
        startTimerHz (60);
    }

    PluginEditor::~PluginEditor()
    {
    }

    void PluginEditor::paint (juce::Graphics& g)
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (juce::Colours::lightpink);

        auto area = getLocalBounds();
        g.setColour (juce::Colours::white);
        g.setFont (36.0f);
        auto helloWorld = juce::String ("Hello from ") + PRODUCT_NAME_WITHOUT_VERSION + " v" VERSION + " running in " + CMAKE_BUILD_TYPE;
        g.drawText (helloWorld, area.removeFromTop (150), juce::Justification::centred, false);
        g.setColour (juce::Colours::black);
        g.fillRect (visualizer);
        g.drawRect (visualizer);
        // Example: animated pulsing ring (visual hook)
        const auto bounds = gainSlider.getBounds().toFloat();
        const float time = static_cast<float> (juce::Time::getMillisecondCounter() % 1000) / 1000.0f;
        const float pulse = 0.5f + 0.5f * std::sin (juce::MathConstants<float>::twoPi * time);

        g.setColour (juce::Colours::mediumseagreen.withAlpha (0.2f + 0.3f * pulse));
        g.drawEllipse (bounds.expanded (10.0f), 2.0f);
    }

    void PluginEditor::resized()
    {
        // layout the positions of your child components here
        auto area = getLocalBounds();
        area.removeFromBottom (50);
        inspectButton.setBounds (getLocalBounds().withSizeKeepingCentre (100, 50));
    }

    void PluginEditor::timerCallback()
    {
        // Here you can repaint or update animated components
        repaint();
    }
} // namespace neapolitan