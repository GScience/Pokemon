
#include "SpiritComponent.h"
#include "Spirit.h"

void SpiritComponent::update(double passedTime)
{
	SDL_Rect scRect = m_dRect;

	scRect.x += m_spiritRect.x;
	scRect.y += m_spiritRect.y;

	scRect.h = (int)((float)scRect.h / 512.0f * (float)m_spiritRect.h);
	scRect.w = (int)((float)scRect.w / 512.0f * (float)m_spiritRect.w);

	SDL_RenderCopy(m_sdlRenderer, m_texture, &m_sRect, &scRect);
}