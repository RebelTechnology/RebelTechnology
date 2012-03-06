/*
  ==============================================================================

    This file was auto-generated by the Jucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_63194A6D__
#define __PLUGINPROCESSOR_H_63194A6D__

#include "../JuceLibraryCode/JuceHeader.h"
#include "TaquitoClient.h"


//==============================================================================
/**
*/
class TaquitoAudioProcessor  : public AudioProcessor,
			       public Timer

{
public:
    //==============================================================================
    TaquitoAudioProcessor();
    ~TaquitoAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const            { return JucePlugin_Name; }

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
    //==============================================================================

    void timerCallback();
    MidiKeyboardState keyboardState;
    int lastUIWidth, lastUIHeight;

    enum Parameters
    {
      breathParam = 0,
      positionParam,
      pressureParam,
      totalNumParams
    };

  float breath, position, pressure;

private:
    TaquitoClient taquito;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TaquitoAudioProcessor);
};

#endif  // __PLUGINPROCESSOR_H_63194A6D__
