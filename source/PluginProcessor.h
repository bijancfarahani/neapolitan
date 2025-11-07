#pragma once

#include "juce_dsp/juce_dsp.h"
#include <juce_audio_processors/juce_audio_processors.h>

namespace neapolitan
{
class PluginProcessor : public juce::AudioProcessor
{
   public:
   PluginProcessor();
   ~PluginProcessor() override;

   void prepareToPlay (double sampleRate, int samplesPerBlock) override;
   void releaseResources() override;

   bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

   void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

   juce::AudioProcessorEditor* createEditor() override;
   bool                        hasEditor() const override;

   const juce::String getName() const override;

   bool   acceptsMidi() const override;
   bool   producesMidi() const override;
   bool   isMidiEffect() const override;
   double getTailLengthSeconds() const override;

   int                getNumPrograms() override;
   int                getCurrentProgram() override;
   void               setCurrentProgram (int index) override;
   const juce::String getProgramName (int index) override;
   void               changeProgramName (int index, const juce::String& newName) override;

   void getStateInformation (juce::MemoryBlock& destData) override;
   void setStateInformation (const void* data, int sizeInBytes) override;

   // Parameter handling
   juce::AudioProcessorValueTreeState         apvts;
   std::array<juce::RangedAudioParameter*, 3> _pluginParameters;
   void                                       pushNextSampleIntoFifo (float sample) noexcept;
   juce::dsp::FFT                             forwardFFT; // [4]
   juce::dsp::WindowingFunction<float>        window; // [5]

   enum {
      fftOrder = 11, // [1]
      fftSize = 1 << fftOrder, // [2]
      scopeSize = 512 // [3]
   };

   float fifo[fftSize]; // [6]
   float fftData[2 * fftSize]; // [7]
   int   fifoIndex = 0; // [8]
   bool  nextFFTBlockReady = false; // [9]
   float scopeData[scopeSize]; // [10]
   private:
   juce::Random random;

   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};
} // namespace neapolitan