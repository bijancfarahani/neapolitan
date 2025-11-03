#include "PluginEditor.h"
namespace neapolitan
{
    PluginEditor::PluginEditor (PluginProcessor& p)
        : AudioProcessorEditor (&p), processorRef (p), flavorPanel (p), visualizer (10, 10, 40, 40)
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
        gainSlider.setColour (juce::Slider::thumbColourId, juce::Colours::blue);
        gainSlider.setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::brown);
        // BIJAN: How to move it in GUI?
        gainLabel.setText ("TESTING", juce::dontSendNotification);
        gainLabel.setJustificationType (juce::Justification::centred);
        gainLabel.setColour (juce::Label::textColourId, juce::Colours::white);
        gainSlider.setBounds (400, 100, 400, 100);

       // addAndMakeVisible (gainSlider);
       // addAndMakeVisible (gainLabel);

        footer.setColour (juce::TextButton::buttonColourId, juce::Colours::limegreen);
        footer.setButtonText ("Studio B, https://github.com/bijancfarahani/neapolitan");
        auto area = getLocalBounds();

        int headerFooterHeight = 36;
        footer.setBounds (area.removeFromBottom (headerFooterHeight));
        footer.setBounds (area.removeFromBottom (headerFooterHeight));
        addAndMakeVisible (footer);
        int x_start = area.getWidth() * 0.25;
        int width = area.getWidth() * 0.5;
        int y_start = area.getHeight() * 0.15;
        int height = area.getHeight() * 0.55;
        visualizer.setBounds (x_start, y_start, width, height);
        // === Start animation refresh (e.g., for meters or visual motion) ===
        startTimerHz (60);

        //flavorPanel.setBounds (getWidth() * 0.5, getHeight() * 0.5, getWidth() * 0.30, getHeight() * 0.25);
       // flavorPanel.centreWithSize (getWidth(), getHeight());
        auto childBounds = juce::Rectangle<int>(getWidth() * 0.30, getHeight() * 0.20).withCentre(area.getCentre()).translated(0,getHeight() * 0.30);
        flavorPanel.setBounds(childBounds);
        addAndMakeVisible(flavorPanel);
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
        //g.fillRect (visualizer);
        //g.drawRect (visualizer);
       // flavorPanel.paint (g);
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