#include "PluginProcessor.h"
#include "PluginEditor.h"

// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
   return new neapolitan::PluginProcessor();
}
namespace neapolitan
{
//==============================================================================
PluginProcessor::PluginProcessor()
    : AudioProcessor (
          BusesProperties()
#if !JucePlugin_IsMidiEffect
   #if !JucePlugin_IsSynth
              .withInput ("Input", juce::AudioChannelSet::stereo(), true)
   #endif
              .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
      ),
      apvts (
          *this,
          nullptr,
          "PARAMS",
          {std::make_unique<juce::AudioParameterFloat> (
               juce::ParameterID ("gain_vanilla", 1),
               "Vanilla Gain",
               0.0f,
               1.0f,
               0.3f
           ),
           std::make_unique<juce::AudioParameterFloat> (
               juce::ParameterID ("gain_strawberry", 1),
               "Strawberry Gain",
               0.0f,
               1.0f,
               0.3
           ),
           std::make_unique<juce::AudioParameterFloat> (
               juce::ParameterID ("gain_chocolate", 1),
               "Chocolate Gain",
               0.0f,
               1.0f,
               0.3f
           )}
      ),
      _pluginParameters()
{
   _pluginParameters[0] = apvts.getParameter (("gain_vanilla"));
   _pluginParameters[1] = apvts.getParameter (("gain_strawberry"));
   _pluginParameters[2] = apvts.getParameter (("gain_chocolate"));
}

PluginProcessor::~PluginProcessor() {}

//==============================================================================
const juce::String PluginProcessor::getName() const { return JucePlugin_Name; }

bool PluginProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
   return true;
#else
   return false;
#endif
}

bool PluginProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
   return true;
#else
   return false;
#endif
}

bool PluginProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
   return true;
#else
   return false;
#endif
}

double PluginProcessor::getTailLengthSeconds() const { return 0.0; }

int PluginProcessor::getNumPrograms()
{
   return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
   // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram() { return 0; }

void PluginProcessor::setCurrentProgram (int index) { juce::ignoreUnused (index); }

const juce::String PluginProcessor::getProgramName (int index)
{
   juce::ignoreUnused (index);
   return {};
}

void PluginProcessor::changeProgramName (int index, const juce::String& newName)
{
   juce::ignoreUnused (index, newName);
}

//==============================================================================
void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
   // Use this method as the place to do any pre-playback
   // initialisation that you need..
   juce::ignoreUnused (sampleRate, samplesPerBlock);

   juce::String message;
   message << "Preparing to play audio...\n";
   message << " samplesPerBlock = " << samplesPerBlock << "\n";
   message << " sampleRate = " << sampleRate;
   juce::Logger::getCurrentLogger()->writeToLog (message);
}

void PluginProcessor::releaseResources()
{
   // When playback stops, you can use this as an opportunity to free up any
   // spare memory, etc.
}

bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
   juce::ignoreUnused (layouts);
   return true;
#else
   // This is the place where you check if the layout is supported.
   // In this template code we only support mono or stereo.
   if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
       && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
      return false;

   // This checks if the input layout matches the output layout
   #if !JucePlugin_IsSynth
   if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
      return false;
   #endif

   return true;
#endif
}

void PluginProcessor::processBlock (
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer&         midiMessages
)
{
   juce::ignoreUnused (midiMessages);

   juce::ScopedNoDenormals noDenormals;
   auto                    totalNumInputChannels = getTotalNumInputChannels();
   auto                    totalNumOutputChannels = getTotalNumOutputChannels();

   // In case we have more outputs than inputs, this code clears any output
   // channels that didn't contain input data, (because these aren't
   // guaranteed to be empty - they may contain garbage).
   // This is here to avoid people getting screaming feedback
   // when they first compile a plugin, but obviously you don't need to keep
   // this code if your algorithm always overwrites all the output channels.
   for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
      buffer.clear (i, 0, buffer.getNumSamples());

   // This is the place where you'd normally do the guts of your plugin's
   // audio processing...
   // Make sure to reset the state if your inner loop is processing
   // the samples and the outer loop is handling the channels.
   // Alternatively, you can process the samples with the channels
   // interleaved by keeping the same state.
   auto level = 0.3f;
   auto currentLevel = level;
   auto levelScale = currentLevel * 2.0f;
   for (int channel = 0; channel < totalNumInputChannels; ++channel)
   {
      auto* channelData = buffer.getWritePointer (channel);
      juce::ignoreUnused (channelData);
      // ..do something to the data...

      auto* buf = buffer.getWritePointer (channel);

      // Fill the required number of samples with noise between -0.125 and +0.125
      for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
      {
         // This data is white noise.
         int i = 0;
         buf[sample] = 0;
         for (auto& flavorBuffer : _flavorsFftData)
         {
            auto  currentLevel = _pluginParameters[i]->getValue();
            auto  levelScale = currentLevel * 2.0f;
            float data = 0;
            if (i == 0)
            {
               data = random.nextFloat() * 0.25f - 0.125f;
               data = data * levelScale - currentLevel;
            }
            else if (i == 1)
            {
               data = 0; // pink noise
            }
            else
            {
               // brown noise
               data = random.nextFloat() * 2.0f - 1.0f;
               data = data * levelScale - currentLevel;
            }

            pushNextSampleIntoFifo (flavorBuffer, data);
            buf[sample] += data;
            ++i;
         }
      }
   }
}

//==============================================================================
bool PluginProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* PluginProcessor::createEditor() { return new PluginEditor (*this); }

//==============================================================================
void PluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
   // You should use this method to store your parameters in the memory block.
   // You could do that either as raw data, or use the XML or ValueTree classes
   // as intermediaries to make it easy to save and load complex data.
   juce::ignoreUnused (destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
   // You should use this method to restore your parameters from this memory block,
   // whose contents will have been created by the getStateInformation() call.
   juce::ignoreUnused (data, sizeInBytes);
}

void PluginProcessor::pushNextSampleIntoFifo (FftData& flavorData, float sample) noexcept
{
   // if the fifo contains enough data, set a flag to say
   // that the next frame should now be rendered..
   if (flavorData.fifoIndex == fftSize) // [11]
   {
      if (!flavorData.nextFFTBlockReady) // [12]
      {
         juce::zeromem (flavorData.fftData, sizeof (flavorData.fftData));
         memcpy (flavorData.fftData, flavorData.fifo, sizeof (flavorData.fifo));
         flavorData.nextFFTBlockReady = true;
      }

      flavorData.fifoIndex = 0;
   }

   flavorData.fifo[flavorData.fifoIndex++] = sample; // [12]
}
//==============================================================================

} // namespace neapolitan