/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  7 Mar 2012 5:06:34pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_TAQUITOAUDIOPROCESSOREDITOR_TAQUITOAUDIOPROCESSOREDITOR_519C23AA__
#define __JUCER_HEADER_TAQUITOAUDIOPROCESSOREDITOR_TAQUITOAUDIOPROCESSOREDITOR_519C23AA__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TaquitoAudioProcessorEditor  : public AudioProcessorEditor,
                                     public SliderListener,
                                     public Timer
{
public:
    //==============================================================================
    TaquitoAudioProcessorEditor (TaquitoAudioProcessor* ownerFilter);
    ~TaquitoAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();

    TaquitoAudioProcessor* getProcessor() const {
      return static_cast <TaquitoAudioProcessor*> (getAudioProcessor());
    }
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
  ScopedPointer<ResizableCornerComponent> resizer;
  ComponentBoundsConstrainer resizeLimits;
  MidiKeyboardComponent midiKeyboard;
    //[/UserVariables]

    //==============================================================================
    Label* label;
    Slider* breathSlider;
    Label* label2;
    Slider* positionSlider;
    Label* label3;
    Slider* pressureSlider;
    Label* label4;
    Slider* channelSlider;
    Label* label5;
    Slider* octaveSlider;
    Label* label6;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    TaquitoAudioProcessorEditor (const TaquitoAudioProcessorEditor&);
    const TaquitoAudioProcessorEditor& operator= (const TaquitoAudioProcessorEditor&);
};


#endif   // __JUCER_HEADER_TAQUITOAUDIOPROCESSOREDITOR_TAQUITOAUDIOPROCESSOREDITOR_519C23AA__
