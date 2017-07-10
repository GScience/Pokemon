
#include "SpiritComponent.h"

void SpiritComponent::draw()
{
	SDL_RenderCopy(m_sdlRenderer, m_texture, &m_sRect, &m_dRect);
}