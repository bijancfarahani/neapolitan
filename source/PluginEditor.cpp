#include "PluginEditor.h"
namespace neapolitan
{
PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p),
      processorRef (p),
      flavorPanel (p),
      _frequencyVisualizer (p, juce::Colour::fromRGB (200, 200, 200))
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
   setResizable (true, true);
   getConstrainer()->setFixedAspectRatio (16.0 / 9.0);

   footer.setColour (juce::TextButton::buttonColourId, juce::Colours::limegreen);
   footer.setButtonText ("Studio B, https://github.com/bijancfarahani/neapolitan");

   // === Start animation refresh (e.g., for meters or visual motion) ===
   startTimerHz (60);

   addAndMakeVisible (flavorPanel);
   addAndMakeVisible (footer);

   addAndMakeVisible (_frequencyVisualizer);
}

PluginEditor::~PluginEditor() = default;

void PluginEditor::paint (juce::Graphics& g)
{
   // (Our component is opaque, so we must completely fill the background with a solid colour)
   g.fillAll (juce::Colour::fromRGB (255, 141, 170));

   auto area = getLocalBounds();
   g.setColour (juce::Colours::white);
   g.setFont (36.0f);
   auto helloWorld = juce::String ("Hello from ") + PRODUCT_NAME_WITHOUT_VERSION + " v" VERSION
                     + " running in " + CMAKE_BUILD_TYPE;
   g.drawText (helloWorld, area.removeFromTop (150), juce::Justification::centred, false);
   g.setColour (juce::Colours::black);
}

void PluginEditor::resized()
{
   // layout the positions of your child components here
   auto area = getLocalBounds();
   inspectButton.setBounds (area.withSizeKeepingCentre (100, 50));

   int x_start = area.getWidth() * 0.25;
   int width = area.getWidth() * 0.5;
   int y_start = area.getHeight() * 0.15;
   int height = area.getHeight() * 0.55;
   _frequencyVisualizer.setBounds (x_start, y_start, width, height);

   auto childBounds = juce::Rectangle<int> (getWidth() * 0.30, getHeight() * 0.20)
                          .withCentre (area.getCentre())
                          .translated (0, getHeight() * 0.30);
   flavorPanel.setBounds (childBounds);

   int headerFooterHeight = 36;
   footer.setBounds (area.removeFromBottom (headerFooterHeight));
}

void PluginEditor::timerCallback() { repaint(); }
} // namespace neapolitan