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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "TaquitoAudioProcessorEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TaquitoAudioProcessorEditor::TaquitoAudioProcessorEditor (TaquitoAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter),
      midiKeyboard(ownerFilter->keyboardState, MidiKeyboardComponent::horizontalKeyboard),
      label (0),
      breathSlider (0),
      label2 (0),
      positionSlider (0),
      label3 (0),
      pressureSlider (0),
      label4 (0),
      channelSlider (0),
      label5 (0),
      octaveSlider (0),
      label6 (0)
{
    addAndMakeVisible (label = new Label (L"new label",
                                          L"TAQUITO"));
    label->setFont (Font (L"Gill Sans", 26.2000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colour (0xff1b1b86));
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (breathSlider = new Slider (L"breathSlider"));
    breathSlider->setRange (0, 10, 0);
    breathSlider->setSliderStyle (Slider::LinearVertical);
    breathSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    breathSlider->addListener (this);

    addAndMakeVisible (label2 = new Label (L"new label",
                                           L"Breath"));
    label2->setFont (Font (L"Gill Sans", 15.0000f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (positionSlider = new Slider (L"positionSlider"));
    positionSlider->setRange (0, 10, 0);
    positionSlider->setSliderStyle (Slider::LinearVertical);
    positionSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    positionSlider->addListener (this);

    addAndMakeVisible (label3 = new Label (L"new label",
                                           L"Position"));
    label3->setFont (Font (L"Gill Sans", 15.0000f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (pressureSlider = new Slider (L"pressureSlider"));
    pressureSlider->setRange (0, 10, 0);
    pressureSlider->setSliderStyle (Slider::LinearVertical);
    pressureSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    pressureSlider->addListener (this);

    addAndMakeVisible (label4 = new Label (L"new label",
                                           L"Pressure"));
    label4->setFont (Font (L"Gill Sans", 15.0000f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (channelSlider = new Slider (L"channelSlider"));
    channelSlider->setRange (1, 16, 1);
    channelSlider->setSliderStyle (Slider::Rotary);
    channelSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    channelSlider->addListener (this);

    addAndMakeVisible (label5 = new Label (L"new label",
                                           L"channel"));
    label5->setFont (Font (L"Gill Sans", 15.0000f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (octaveSlider = new Slider (L"octaveSlider"));
    octaveSlider->setRange (-2, 6, 1);
    octaveSlider->setSliderStyle (Slider::Rotary);
    octaveSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    octaveSlider->addListener (this);

    addAndMakeVisible (label6 = new Label (L"new label",
                                           L"octave"));
    label6->setFont (Font (L"Gill Sans", 15.0000f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]

    // add the midi keyboard component..
    addAndMakeVisible (&midiKeyboard);

    // add the triangular resizer component for the bottom-right of the UI
    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    resizeLimits.setSizeLimits (150, 150, 800, 300);

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

    // set our component's initial size to be the last one that was stored in the filter's settings
//     setSize (ownerFilter->lastUIWidth,
//              ownerFilter->lastUIHeight);

    startTimer (50);

    //[/Constructor]
}

TaquitoAudioProcessorEditor::~TaquitoAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (label);
    deleteAndZero (breathSlider);
    deleteAndZero (label2);
    deleteAndZero (positionSlider);
    deleteAndZero (label3);
    deleteAndZero (pressureSlider);
    deleteAndZero (label4);
    deleteAndZero (channelSlider);
    deleteAndZero (label5);
    deleteAndZero (octaveSlider);
    deleteAndZero (label6);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TaquitoAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TaquitoAudioProcessorEditor::resized()
{
    label->setBounds (0, 80, 112, 24);
    breathSlider->setBounds (0, 0, 48, 48);
    label2->setBounds (0, 48, 48, 24);
    positionSlider->setBounds (56, 0, 48, 48);
    label3->setBounds (56, 48, 48, 24);
    pressureSlider->setBounds (112, 0, 48, 48);
    label4->setBounds (112, 48, 48, 24);
    channelSlider->setBounds (224, 0, 64, 32);
    label5->setBounds (168, 0, 48, 32);
    octaveSlider->setBounds (224, 32, 64, 32);
    label6->setBounds (168, 32, 48, 32);
    //[UserResized] Add your own custom resize handling here..

    const int keyboardHeight = 70;
    midiKeyboard.setBounds (4, getHeight() - keyboardHeight - 4, getWidth() - 8, keyboardHeight);
    resizer->setBounds (getWidth() - 16, getHeight() - 16, 16, 16);
    getProcessor()->lastUIWidth = getWidth();
    getProcessor()->lastUIHeight = getHeight();

    //[/UserResized]
}

void TaquitoAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == breathSlider)
    {
        //[UserSliderCode_breathSlider] -- add your slider handling code here..
        // It's vital to use setParameterNotifyingHost to change any parameters that are automatable
        // by the host, rather than just modifying them directly, otherwise the host won't know
        // that they've changed.
      getProcessor()->setParameterNotifyingHost (TaquitoAudioProcessor::breathParam,
						 (float) breathSlider->getValue());
        //[/UserSliderCode_breathSlider]
    }
    else if (sliderThatWasMoved == positionSlider)
    {
        //[UserSliderCode_positionSlider] -- add your slider handling code here..
      getProcessor()->setParameterNotifyingHost (TaquitoAudioProcessor::positionParam,
						 (float) positionSlider->getValue());
        //[/UserSliderCode_positionSlider]
    }
    else if (sliderThatWasMoved == pressureSlider)
    {
        //[UserSliderCode_pressureSlider] -- add your slider handling code here..
      getProcessor()->setParameterNotifyingHost (TaquitoAudioProcessor::pressureParam,
						 (float) pressureSlider->getValue());
        //[/UserSliderCode_pressureSlider]
    }
    else if (sliderThatWasMoved == channelSlider)
    {
        //[UserSliderCode_channelSlider] -- add your slider handling code here..
      getProcessor()->channel = (int)channelSlider->getValue();
        //[/UserSliderCode_channelSlider]
    }
    else if (sliderThatWasMoved == octaveSlider)
    {
        //[UserSliderCode_octaveSlider] -- add your slider handling code here..
      getProcessor()->octave = (int)octaveSlider->getValue()+2;
        //[/UserSliderCode_octaveSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
// This timer periodically checks whether any of the filter's parameters have changed...
void TaquitoAudioProcessorEditor::timerCallback()
{
    TaquitoAudioProcessor* ourProcessor = getProcessor();
    breathSlider->setValue (ourProcessor->breath, false);
    positionSlider->setValue (ourProcessor->position, false);
    pressureSlider->setValue (ourProcessor->pressure, false);

    channelSlider->setValue (ourProcessor->channel, false);
    octaveSlider->setValue (ourProcessor->octave-2, false);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TaquitoAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public SliderListener, public Timer"
                 constructorParams="TaquitoAudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor (ownerFilter),&#13;midiKeyboard(ownerFilter-&gt;keyboardState, MidiKeyboardComponent::horizontalKeyboard)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="new label" id="beabe49b2939e37f" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 80 112 24" textCol="ff1b1b86" edTextCol="ff000000"
         edBkgCol="0" labelText="TAQUITO" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Gill Sans" fontsize="26.2"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="breathSlider" id="6d801a488d546892" memberName="breathSlider"
          virtualName="" explicitFocusOrder="0" pos="0 0 48 48" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="666e31a033fa0ba" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="0 48 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Breath" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Gill Sans" fontsize="15" bold="0"
         italic="0" justification="33"/>
  <SLIDER name="positionSlider" id="83260369d1e46d19" memberName="positionSlider"
          virtualName="" explicitFocusOrder="0" pos="56 0 48 48" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="5be6cb193832ed62" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="56 48 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Position" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Gill Sans" fontsize="15" bold="0"
         italic="0" justification="33"/>
  <SLIDER name="pressureSlider" id="b01149a604eb479e" memberName="pressureSlider"
          virtualName="" explicitFocusOrder="0" pos="112 0 48 48" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="2626b073c736fda1" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="112 48 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pressure" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Gill Sans" fontsize="15" bold="0"
         italic="0" justification="33"/>
  <SLIDER name="channelSlider" id="6d94148a95b4b5d7" memberName="channelSlider"
          virtualName="" explicitFocusOrder="0" pos="224 0 64 32" min="1"
          max="16" int="1" style="Rotary" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="8ec0ca3320c50609" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="168 0 48 32" edTextCol="ff000000"
         edBkgCol="0" labelText="channel" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Gill Sans" fontsize="15" bold="0"
         italic="0" justification="33"/>
  <SLIDER name="octaveSlider" id="4440f675e984475" memberName="octaveSlider"
          virtualName="" explicitFocusOrder="0" pos="224 32 64 32" min="-2"
          max="6" int="1" style="Rotary" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="c86365b659d51d6d" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="168 32 48 32" edTextCol="ff000000"
         edBkgCol="0" labelText="octave" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Gill Sans" fontsize="15" bold="0"
         italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
