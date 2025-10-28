#include "PluginEditor.h"

#include "GuiConfig.h"

namespace neapolitan
{
NeapolitanAudioProcessorEditor::NeapolitanAudioProcessorEditor (NeapolitanAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
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
   setSize (gui::DEFAULT_WINDOW_WIDTH, gui::DEFAULT_WINDOW_HEIGHT);
}

NeapolitanAudioProcessorEditor::~NeapolitanAudioProcessorEditor() = default;

void NeapolitanAudioProcessorEditor::paint (juce::Graphics& g)
{
   // (Our component is opaque, so we must completely fill the background with a solid colour)
   g.fillAll (juce::Colours::lightpink);

   auto area = getLocalBounds();
   g.setColour (juce::Colours::white);
   g.setFont (36.0f);
   auto helloWorld = juce::String ("Hello from ") + PRODUCT_NAME_WITHOUT_VERSION + " v" VERSION + " running in " + CMAKE_BUILD_TYPE;
   g.drawText (helloWorld, area.removeFromTop (150), juce::Justification::centred, false);
}

void NeapolitanAudioProcessorEditor::resized()
{
   // layout the positions of your child components here
   auto area = getLocalBounds();
   area.removeFromBottom (50);
   inspectButton.setBounds (getLocalBounds().withSizeKeepingCentre (100, 50));
}
}