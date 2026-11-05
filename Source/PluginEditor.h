#pragma once

#include "PluginProcessor.h"

//==============================================================================
class SoraLookAndFeel : public juce::LookAndFeel_V4
{
public:
    SoraLookAndFeel();

    void drawRotarySlider (juce::Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, juce::Slider&) override;
};

//==============================================================================
class SoraKickAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit SoraKickAudioProcessorEditor (SoraKickAudioProcessor&);
    ~SoraKickAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using APVTS = juce::AudioProcessorValueTreeState;

    struct Knob
    {
        juce::Slider slider { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxBelow };
        juce::Label label;
        std::unique_ptr<APVTS::SliderAttachment> attachment;
    };

    void addKnob (const char* paramID, const char* title);

    SoraKickAudioProcessor& proc;
    SoraLookAndFeel laf;

    juce::Image heroineImage;   // необязательная картинка из Resources/heroine.png

    juce::ComboBox characterBox, driveTypeBox, layerWaveBox;
    std::vector<std::unique_ptr<Knob>> knobs;

    std::unique_ptr<APVTS::ComboBoxAttachment> characterAtt, driveTypeAtt, layerWaveAtt;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoraKickAudioProcessorEditor)
};
