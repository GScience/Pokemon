
#include "SpiritComponent.h"
#include "Spirit.h"
#include "BaseEngine.h"

void SpiritComponent::update(double passedTime)
{
	SDL_Rect scRect = m_rect;

	scRect.x += m_spiritRect.x;
	scRect.y += m_spiritRect.y;

	scRect.h = (int)((float)scRect.h / Setting::windowHeight * (float)m_spiritRect.h);
	scRect.w = (int)((float)scRect.w / Setting::windowWidth * (float)m_spiritRect.w);

	SDL_RenderCopy(m_sdlRenderer, m_texture, &m_textureRect, &scRect);
}