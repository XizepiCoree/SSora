#include "PluginEditor.h"

#ifndef SORA_HAS_IMAGE
 #define SORA_HAS_IMAGE 0
#endif

#if SORA_HAS_IMAGE
 #include <BinaryData.h>
#endif

namespace
{
    const juce::Colour skyTop    (0xff6db6ea);
    const juce::Colour skyMid    (0xffa9d8f5);
    const juce::Colour skyBottom (0xffeaf6fd);
    const juce::Colour inkBlue   (0xff35506b);   // основной цвет текста
    const juce::Colour skyAccent (0xff3d9be0);   // дуга значения на ручках
    const juce::Colour pinkAccent(0xfff0708f);   // указатель ручки
    const juce::Colour trackCol  (0xffc5dff2);

    //--------------------------------------------------------------------------
    void drawCloud (juce::Graphics& g, float x, float y, float s, float alpha)
    {
        g.setColour (juce::Colours::white.withAlpha (alpha));
        g.fillEllipse (x,            y + 14.f * s, 90.f * s, 34.f * s);
        g.fillEllipse (x + 14.f * s, y,            44.f * s, 40.f * s);
        g.fillEllipse (x + 40.f * s, y + 6.f * s,  40.f * s, 34.f * s);
        g.fillRoundedRectangle (x + 8.f * s, y + 26.f * s, 80.f * s, 22.f * s, 11.f * s);
    }

    // Оригинальная героиня, нарисованная векторами (не персонаж какой-либо игры)
    void drawHeroine (juce::Graphics& g, juce::Rectangle<float> a)
    {
        const float cx = a.getCentreX();
        const float R  = a.getWidth() * 0.27f;
        const float cy = a.getY() + a.getHeight() * 0.38f;

        const juce::Colour hair    (0xff9a8ae0);
        const juce::Colour hairDark(0xff7766c4);
        const juce::Colour skin    (0xfffde3d2);
        const juce::Colour blouse  (0xfff9fcff);
        const juce::Colour collar  (0xff5aa9e6);
        const juce::Colour ribbon  (0xfff0708f);
        const juce::Colour iris    (0xff3f8fd6);
        const juce::Colour dark    (0xff3b3350);

        // длинные волосы сзади
        g.setColour (hairDark);
        g.fillRoundedRectangle (cx - R * 1.3f, cy - R * 1.2f, R * 2.6f, R * 4.0f, R * 1.1f);

        // тело (блузка)
        juce::Path body;
        body.startNewSubPath (cx - R * 1.6f, a.getBottom());
        body.quadraticTo (cx - R * 1.6f, cy + R * 1.5f, cx - R * 0.5f, cy + R * 1.25f);
        body.lineTo (cx + R * 0.5f, cy + R * 1.25f);
        body.quadraticTo (cx + R * 1.6f, cy + R * 1.5f, cx + R * 1.6f, a.getBottom());
        body.closeSubPath();
        g.setColour (blouse);
        g.fillPath (body);

        // шея
        g.setColour (skin);
        g.fillRoundedRectangle (cx - R * 0.22f, cy + R * 0.85f, R * 0.44f, R * 0.6f, R * 0.15f);

        // матросский воротник
        juce::Path col;
        col.startNewSubPath (cx - R * 0.5f,  cy + R * 1.25f);
        col.lineTo (cx,                     cy + R * 2.05f);
        col.lineTo (cx + R * 0.5f,           cy + R * 1.25f);
        col.lineTo (cx + R * 0.95f,          cy + R * 1.45f);
        col.lineTo (cx,                     cy + R * 2.75f);
        col.lineTo (cx - R * 0.95f,          cy + R * 1.45f);
        col.closeSubPath();
        g.setColour (collar);
        g.fillPath (col);

        // бантик
        juce::Path bow;
        bow.addTriangle (cx, cy + R * 2.05f, cx - R * 0.42f, cy + R * 1.85f, cx - R * 0.42f, cy + R * 2.3f);
        bow.addTriangle (cx, cy + R * 2.05f, cx + R * 0.42f, cy + R * 1.85f, cx + R * 0.42f, cy + R * 2.3f);
        g.setColour (ribbon);
        g.fillPath (bow);
        g.fillEllipse (cx - R * 0.11f, cy + R * 1.94f, R * 0.22f, R * 0.22f);

        // лицо
        g.setColour (skin);
        g.fillEllipse (cx - R, cy - R * 1.05f, R * 2.f, R * 2.15f);

        // румянец
        g.setColour (juce::Colour (0x55f48fb1));
        g.fillEllipse (cx - R * 0.78f, cy + R * 0.34f, R * 0.34f, R * 0.18f);
        g.fillEllipse (cx + R * 0.44f, cy + R * 0.34f, R * 0.34f, R * 0.18f);

        // глаза
        for (int s = -1; s <= 1; s += 2)
        {
            const float ex = cx + (float) s * R * 0.42f;
            const float ey = cy + R * 0.12f;

            g.setColour (juce::Colours::white);
            g.fillEllipse (ex - R * 0.2f, ey - R * 0.28f, R * 0.4f, R * 0.56f);
            g.setColour (iris);
            g.fillEllipse (ex - R * 0.17f, ey - R * 0.22f, R * 0.34f, R * 0.5f);
            g.setColour (dark);
            g.fillEllipse (ex - R * 0.09f, ey - R * 0.08f, R * 0.18f, R * 0.28f);
            g.setColour (juce::Colours::white);
            g.fillEllipse (ex - R * 0.1f, ey - R * 0.2f, R * 0.1f, R * 0.1f);

            juce::Path lash;
            lash.startNewSubPath (ex - R * 0.22f, ey - R * 0.12f);
            lash.quadraticTo (ex, ey - R * 0.4f, ex + R * 0.22f, ey - R * 0.12f);
            g.setColour (dark);
            g.strokePath (lash, juce::PathStrokeType (R * 0.06f, juce::PathStrokeType::curved,
                                                      juce::PathStrokeType::rounded));
        }

        // улыбка
        juce::Path mouth;
        mouth.startNewSubPath (cx - R * 0.13f, cy + R * 0.62f);
        mouth.quadraticTo (cx, cy + R * 0.76f, cx + R * 0.13f, cy + R * 0.62f);
        g.setColour (juce::Colour (0xffd9777f));
        g.strokePath (mouth, juce::PathStrokeType (R * 0.05f, juce::PathStrokeType::curved,
                                                   juce::PathStrokeType::rounded));

        // чёлка
        juce::Path bangs;
        bangs.startNewSubPath (cx - R * 1.1f, cy - R * 0.2f);
        bangs.quadraticTo (cx - R * 1.25f, cy - R * 1.45f, cx, cy - R * 1.3f);
        bangs.quadraticTo (cx + R * 1.25f, cy - R * 1.45f, cx + R * 1.1f, cy - R * 0.2f);
        bangs.quadraticTo (cx + R * 0.95f, cy - R * 0.7f, cx + R * 0.6f,  cy - R * 0.35f);
        bangs.quadraticTo (cx + R * 0.3f,  cy - R * 0.8f, cx + R * 0.05f, cy - R * 0.3f);
        bangs.quadraticTo (cx - R * 0.3f,  cy - R * 0.8f, cx - R * 0.55f, cy - R * 0.35f);
        bangs.quadraticTo (cx - R * 0.95f, cy - R * 0.7f, cx - R * 1.1f,  cy - R * 0.2f);
        bangs.closeSubPath();
        g.setColour (hair);
        g.fillPath (bangs);

        // боковые пряди
        g.fillRoundedRectangle (cx - R * 1.12f, cy - R * 0.5f, R * 0.26f, R * 1.5f, R * 0.13f);
        g.fillRoundedRectangle (cx + R * 0.86f, cy - R * 0.5f, R * 0.26f, R * 1.5f, R * 0.13f);

        // заколка-бантик на волосах
        juce::Path clip;
        const float bx = cx + R * 0.82f, by = cy - R * 0.98f;
        clip.addTriangle (bx, by, bx - R * 0.34f, by - R * 0.2f, bx - R * 0.34f, by + R * 0.22f);
        clip.addTriangle (bx, by, bx + R * 0.34f, by - R * 0.2f, bx + R * 0.34f, by + R * 0.22f);
        g.setColour (juce::Colours::white);
        g.fillPath (clip);
        g.setColour (collar);
        g.fillEllipse (bx - R * 0.08f, by - R * 0.08f, R * 0.16f, R * 0.16f);
    }
}

//==============================================================================
SoraLookAndFeel::SoraLookAndFeel()
{
    setColour (juce::Slider::textBoxTextColourId, inkBlue);
    setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    setColour (juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    setColour (juce::Label::textColourId, inkBlue);

    setColour (juce::ComboBox::backgroundColourId, juce::Colours::white.withAlpha (0.85f));
    setColour (juce::ComboBox::textColourId, inkBlue);
    setColour (juce::ComboBox::outlineColourId, juce::Colour (0xff7fb8e6));
    setColour (juce::ComboBox::arrowColourId, skyAccent);

    setColour (juce::PopupMenu::backgroundColourId, juce::Colour (0xfff4faff));
    setColour (juce::PopupMenu::textColourId, inkBlue);
    setColour (juce::PopupMenu::highlightedBackgroundColourId, skyAccent);
    setColour (juce::PopupMenu::highlightedTextColourId, juce::Colours::white);
}

void SoraLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                                        float pos, float startAngle, float endAngle, juce::Slider&)
{
    auto bounds = juce::Rectangle<float> ((float) x, (float) y, (float) width, (float) height).reduced (6.f);
    const float radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) * 0.5f;
    const auto centre = bounds.getCentre();
    const float angle = startAngle + pos * (endAngle - startAngle);

    g.setColour (juce::Colours::white.withAlpha (0.9f));
    g.fillEllipse (centre.x - radius, centre.y - radius, radius * 2.f, radius * 2.f);

    juce::Path track;
    track.addCentredArc (centre.x, centre.y, radius - 3.f, radius - 3.f, 0.f, startAngle, endAngle, true);
    g.setColour (trackCol);
    g.strokePath (track, juce::PathStrokeType (4.f));

    juce::Path value;
    value.addCentredArc (centre.x, centre.y, radius - 3.f, radius - 3.f, 0.f, startAngle, angle, true);
    g.setColour (skyAccent);
    g.strokePath (value, juce::PathStrokeType (4.f));

    juce::Path pointer;
    pointer.addRoundedRectangle (-1.5f, -radius + 9.f, 3.f, radius * 0.36f, 1.5f);
    pointer.applyTransform (juce::AffineTransform::rotation (angle).translated (centre.x, centre.y));
    g.setColour (pinkAccent);
    g.fillPath (pointer);
}

//==============================================================================
SoraKickAudioProcessorEditor::SoraKickAudioProcessorEditor (SoraKickAudioProcessor& p)
    : AudioProcessorEditor (&p), proc (p)
{
    setLookAndFeel (&laf);

#if SORA_HAS_IMAGE
    heroineImage = juce::ImageCache::getFromMemory (BinaryData::heroine_png, BinaryData::heroine_pngSize);
#endif

    characterBox.addItemList (SoraKickAudioProcessor::getCharacterNames(), 1);
    driveTypeBox.addItemList (SoraKickAudioProcessor::getDriveTypeNames(), 1);
    layerWaveBox.addItemList (SoraKickAudioProcessor::getWaveNames(), 1);
    addAndMakeVisible (characterBox);
    addAndMakeVisible (driveTypeBox);
    addAndMakeVisible (layerWaveBox);

    characterAtt = std::make_unique<APVTS::ComboBoxAttachment> (proc.apvts, "character", characterBox);
    driveTypeAtt = std::make_unique<APVTS::ComboBoxAttachment> (proc.apvts, "driveType", driveTypeBox);
    layerWaveAtt = std::make_unique<APVTS::ComboBoxAttachment> (proc.apvts, "layerWave", layerWaveBox);

    // порядок = раскладка сетки 6 x 4
    addKnob ("attack",      "ATTACK");
    addKnob ("sustain",     "SUSTAIN");
    addKnob ("length",      "LENGTH");
    addKnob ("sub",         "SUB");
    addKnob ("click",       "CLICK");
    addKnob ("lowCut",      "LOW CUT");

    addKnob ("drive",       "DRIVE");
    addKnob ("bits",        "BITS");
    addKnob ("rate",        "RATE");
    addKnob ("screech",     "SCREECH");
    addKnob ("screechFreq", "SCREECH HZ");
    addKnob ("highCut",     "HIGH CUT");

    addKnob ("layer",       "SUB LAYER");
    addKnob ("layerFreq",   "LAYER HZ");
    addKnob ("layerDecay",  "LAYER DECAY");
    addKnob ("layerDrop",   "PITCH DROP");
    addKnob ("dropTime",    "DROP TIME");
    addKnob ("trigger",     "TRIGGER");

    addKnob ("rumble",      "RUMBLE");
    addKnob ("rumbleFreq",  "RUMBLE HZ");
    addKnob ("mix",         "MIX");
    addKnob ("output",      "OUTPUT");

    setSize (940, 660);
}

SoraKickAudioProcessorEditor::~SoraKickAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
}

void SoraKickAudioProcessorEditor::addKnob (const char* paramID, const char* title)
{
    auto k = std::make_unique<Knob>();

    k->slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 90, 16);
    k->label.setText (title, juce::dontSendNotification);
    k->label.setJustificationType (juce::Justification::centred);
    k->label.setFont (juce::Font (juce::FontOptions (11.f, juce::Font::bold)));
    k->attachment = std::make_unique<APVTS::SliderAttachment> (proc.apvts, paramID, k->slider);

    addAndMakeVisible (k->slider);
    addAndMakeVisible (k->label);
    knobs.push_back (std::move (k));
}

void SoraKickAudioProcessorEditor::paint (juce::Graphics& g)
{
    // небо
    juce::ColourGradient sky (skyTop, 0.f, 0.f, skyBottom, 0.f, (float) getHeight(), false);
    sky.addColour (0.45, skyMid);
    g.setGradientFill (sky);
    g.fillAll();

    // облака
    drawCloud (g, 300.f, 6.f,   1.3f, 0.55f);
    drawCloud (g, 760.f, 20.f,  1.0f, 0.5f);
    drawCloud (g, 560.f, 610.f, 1.2f, 0.6f);
    drawCloud (g,  20.f, 560.f, 1.5f, 0.55f);
    drawCloud (g, 820.f, 560.f, 0.9f, 0.5f);

    // левая панель с героиней
    const auto heroPanel = juce::Rectangle<float> (16.f, 16.f, 240.f, 628.f);
    g.setColour (juce::Colours::white.withAlpha (0.35f));
    g.fillRoundedRectangle (heroPanel, 20.f);

    g.saveState();
    juce::Path clipPath;
    clipPath.addRoundedRectangle (heroPanel, 20.f);
    g.reduceClipRegion (clipPath, juce::AffineTransform());

    if (heroineImage.isValid())
        g.drawImageWithin (heroineImage, (int) heroPanel.getX(), (int) heroPanel.getY(),
                           (int) heroPanel.getWidth(), (int) heroPanel.getHeight(),
                           juce::RectanglePlacement::centred);
    else
        drawHeroine (g, heroPanel);

    g.restoreState();

    // заголовок
    g.setColour (inkBlue.withAlpha (0.35f));
    g.setFont (juce::Font (juce::FontOptions (40.f, juce::Font::bold)));
    g.drawText ("SORA KICK", 290, 16, 340, 46, juce::Justification::centredLeft);
    g.setColour (juce::Colours::white);
    g.drawText ("SORA KICK", 288, 14, 340, 46, juce::Justification::centredLeft);

    g.setColour (inkBlue);
    g.setFont (juce::Font (juce::FontOptions (12.f, juce::Font::bold)));
    g.drawText ("kick processor  -  blue sky edition", 290, 56, 340, 16, juce::Justification::centredLeft);

    g.setFont (juce::Font (juce::FontOptions (11.f, juce::Font::bold)));
    g.drawText ("CHARACTER",  288, 78, 200, 14, juce::Justification::centredLeft);
    g.drawText ("DRIVE TYPE", 512, 78, 120, 14, juce::Justification::centredLeft);
    g.drawText ("LAYER WAVE", 646, 78, 120, 14, juce::Justification::centredLeft);

    // панель с ручками
    g.setColour (juce::Colours::white.withAlpha (0.45f));
    g.fillRoundedRectangle (268.f, 132.f, 656.f, 512.f, 20.f);
}

void SoraKickAudioProcessorEditor::resized()
{
    characterBox.setBounds (288, 94, 210, 28);
    driveTypeBox.setBounds (512, 94, 120, 28);
    layerWaveBox.setBounds (646, 94, 120, 28);

    const juce::Rectangle<int> area (276, 140, 640, 500);
    const int cols = 6, rows = 4;
    const int cw = area.getWidth() / cols;
    const int ch = area.getHeight() / rows;

    for (size_t i = 0; i < knobs.size(); ++i)
    {
        const int row = (int) i / cols;
        const int col = (int) i % cols;
        auto cell = juce::Rectangle<int> (area.getX() + col * cw, area.getY() + row * ch, cw, ch).reduced (3);
        knobs[i]->label.setBounds (cell.removeFromTop (16));
        knobs[i]->slider.setBounds (cell);
    }
}
