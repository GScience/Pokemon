
#include "Spirit.h"
#include <algorithm>

void Spirit::draw()
{
	//sort spirit component first
	m_spiritComponentList.sort([](const SpiritComponent sc1, const SpiritComponent sc2) { return sc1.isCoveredBy(sc2); });

	for (auto sp : m_spiritComponentList)
		sp.draw();
}
SpiritComponent* Spirit::addSpiritComponent()
{
	m_spiritComponentList.emplace_back(SpiritComponent(this, m_sdlRenderer));

	return &m_spiritComponentList.back();
}