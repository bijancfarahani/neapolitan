#pragma once
#include "PluginProcessor.h"
#include "juce_gui_basics/juce_gui_basics.h"
namespace neapolitan
{

class FlavorKnob : public juce::Component
{
   public:
   explicit FlavorKnob (
       PluginProcessor&            p,
       juce::StringRef             flavorName,
       juce::RangedAudioParameter& rangedAudioParameter
   );
   ~FlavorKnob() override;

   void paint (juce::Graphics& g) override;

   void resized() override;

   protected:
   virtual juce::Colour getBackgroundColor() const = 0;
   virtual juce::String getFlavorName() const = 0;
   juce::Slider         gainSlider;
   std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

   private:
   PluginProcessor& _processor;
   juce::Label      gainLabel;

   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlavorKnob)
};

class VanillaKnob final : public FlavorKnob
{
   public:
   explicit VanillaKnob (PluginProcessor& p);

   juce::Colour getBackgroundColor() const override;
   juce::String getFlavorName() const override;
};

class StrawberryKnob final : public FlavorKnob
{
   public:
   explicit StrawberryKnob (PluginProcessor& p);
   juce::String getFlavorName() const override;

   juce::Colour getBackgroundColor() const override;
};

class ChocolateKnob final : public FlavorKnob
{
   public:
   explicit ChocolateKnob (PluginProcessor& p);
   juce::String getFlavorName() const override;

   juce::Colour getBackgroundColor() const override;
};

} // namespace neapolitan