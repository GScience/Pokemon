
#include "Spirit.h"
#include <algorithm>

void Spirit::draw()
{
	for (auto sp : m_spiritComponentList)
		sp.draw();
}
SpiritComponent* Spirit::addSpiritComponent(unsigned short zOrder)
{
	SpiritComponent newSC = SpiritComponent(this, m_sdlRenderer);
	newSC.m_zOrder = zOrder;

	auto i = m_spiritComponentList.begin();

	for (; i != m_spiritComponentList.end(); i++)
		if (i->isCoveredBy(newSC))
			break;

	return &*m_spiritComponentList.emplace(i, newSC);
}