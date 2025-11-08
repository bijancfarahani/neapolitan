#include "FrequencyVisualizer.h"
#include "PluginProcessor.h"
namespace neapolitan
{
FrequencyVisualizer::FrequencyVisualizer (PluginProcessor& p)
    : processorRef (p),
      _lineColors {
          juce::Colour::fromRGB (200, 200, 200),
          juce::Colour::fromRGB (255, 150, 80),
          juce::Colour::fromRGB (194, 145, 111)
      }
{
   startTimerHz (60);
}

FrequencyVisualizer::~FrequencyVisualizer() = default;

void FrequencyVisualizer::drawFrame (juce::Graphics& g)
{
   auto width = getLocalBounds().getWidth();
   auto height = getLocalBounds().getHeight();
   for (int i = 0; i < 3; i++)
   {
      g.setColour (_lineColors[i]);
      const auto& flavorNoiseData = processorRef.getFlavorNoiseData()[i];
      for (int i = 1; i < scopeSize; ++i)
      {
         g.drawLine (
             {(float) juce::jmap (i - 1, 0, scopeSize - 1, 0, width),
              juce::jmap (flavorNoiseData.scopeData[i - 1], 0.0f, 1.0f, (float) (height), 0.0f),
              (float) juce::jmap (i, 0, scopeSize - 1, 0, width),
              juce::jmap (flavorNoiseData.scopeData[i], 0.0f, 1.0f, (float) (height), 0.0f)}
         );
      }
   }
}

void FrequencyVisualizer::paint (juce::Graphics& g)
{
   g.setColour (juce::Colours::black);
   g.fillRect (getLocalBounds());
   drawFrame (g);
}

void FrequencyVisualizer::resized() {}

void FrequencyVisualizer::drawNextFrameOfSpectrum (FftData& flavorNoiseData)
{
   // first apply a windowing function to our data
   flavorNoiseData.window.multiplyWithWindowingTable (flavorNoiseData.fftData, fftSize); // [1]

   // then render our FFT data..
   flavorNoiseData.forwardFFT.performFrequencyOnlyForwardTransform (flavorNoiseData.fftData); // [2]

   auto mindB = -100.0f;
   auto maxdB = 0.0f;

   for (int i = 0; i < scopeSize; ++i) // [3]
   {
      auto skewedProportionX =
          1.0f - std::exp (std::log (1.0f - (float) i / (float) scopeSize) * 0.2f);
      auto fftDataIndex =
          juce::jlimit (0, fftSize / 2, (int) (skewedProportionX * (float) fftSize * 0.5f));
      auto level = juce::jmap (
          juce::jlimit (
              mindB,
              maxdB,
              juce::Decibels::gainToDecibels (flavorNoiseData.fftData[fftDataIndex])
                  - juce::Decibels::gainToDecibels ((float) fftSize)
          ),
          mindB,
          maxdB,
          0.0f,
          1.0f
      );

      flavorNoiseData.scopeData[i] = level; // [4]
   }
}
void FrequencyVisualizer::timerCallback()
{
   // Here you can repaint or update animated components
   for (auto& flavorNoiseData : processorRef.getFlavorNoiseData())
   {
      if (flavorNoiseData.nextFFTBlockReady)
      {
         drawNextFrameOfSpectrum (flavorNoiseData);
         flavorNoiseData.nextFFTBlockReady = false;
      }
   }
}

} // namespace neapolitan