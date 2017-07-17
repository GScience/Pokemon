
#include "SpiritComponent.h"
#include "Spirit.h"
#include "BaseEngine.h"

void SpiritComponent::draw()
{
	SDL_RenderCopy(m_sdlRenderer, m_texture, &m_textureRect, &m_scRect);
}

void SpiritComponent::update(double passedTime)
{
	m_scRect = m_rect;

	m_scRect.x += m_spiritRect.x;
	m_scRect.y += m_spiritRect.y;

	m_scRect.h = (int)((float)m_scRect.h / Setting::windowHeight * (float)m_spiritRect.h);
	m_scRect.w = (int)((float)m_scRect.w / Setting::windowWidth * (float)m_spiritRect.w);
}