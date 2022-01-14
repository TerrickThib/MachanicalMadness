#pragma once
#include "Actor.h"
#include "raylib.h"
class UIText :
    public Actor
{
public:
    UIText(float x, float y, const char* name, Color color, int width, int height, int fontSize, const char* text = "") : Actor(x, y, name)
    {
        m_text = text;
        m_width = width;
        m_height = height;
        m_font = LoadFont("resources/fonts/alagard.png");
        m_fontSize = fontSize;
        m_fontColor = color;
    }

    void draw() override;

private:
    const char* m_text;
    int m_width;
    int m_height;
    int m_fontSize;
    Font m_font;
    Color m_fontColor;
};

