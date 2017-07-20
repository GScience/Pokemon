
#include "Spirit.h"
#include <algorithm>

void Spirit::update(double passedTime)
{
	for (auto sp = m_spiritComponentList.begin(); sp != m_spiritComponentList.end();)
	{
		if ((*sp)->isRemoved())
			sp = m_spiritComponentList.erase(sp);
		else
		{
			(*sp)->update(passedTime);
			sp++;
		}
	}
}

std::shared_ptr<SpiritComponent> Spirit::addSpiritComponent(unsigned short zOrder)
{
	std::shared_ptr<SpiritComponent> newSC = std::make_shared<SpiritComponent>(this, m_rect, m_sdlRenderer);
	newSC->m_zOrder = zOrder;

	auto i = m_spiritComponentList.begin();

	for (; i != m_spiritComponentList.end(); i++)
		if (!(*i)->isCoveredBy(*newSC))
			break;

	return *m_spiritComponentList.emplace(i, newSC);
}

void Spirit::draw()
{
	for (auto sp : m_spiritComponentList)
		if (sp->isVisiable())
			sp->draw();
}