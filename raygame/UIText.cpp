#include "UIText.h"
#include <raylib.h>

/// <summary>
/// Draws The Text Box
/// </summary>
void UIText::draw()
{
    Rectangle textBox = Rectangle();
    textBox.x = getTransform()->getLocalPosition().x;
    textBox.y = getTransform()->getLocalPosition().y;
    textBox.width = m_width;
    textBox.height = m_height;
    DrawTextRec(m_font, m_text, textBox, m_fontSize, 1, true, m_fontColor);
}
