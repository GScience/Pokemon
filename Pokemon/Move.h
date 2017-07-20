#pragma once

#include "ActionBase.h"
#include "RenderableObject.h"

namespace Action
{
	template <int speed, int toX, int toY> class MoveTo :public ActionBase
	{
		//location in float
		float m_x;
		float m_y;

		int m_changedX;
		int m_changedY;

	public:
		MoveTo(std::shared_ptr<RenderableObject> obj) :ActionBase(obj)
		{
			m_x = (float)m_obj->getX();
			m_y = (float)m_obj->getY();

			m_changedX = toX - m_obj->getX();
			m_changedY = toY - m_obj->getY();
		}

		void update(double passedTime) override
		{
			m_x += (float)((speed * m_changedX / sqrt(m_changedX * m_changedX + m_changedY * m_changedY)) * passedTime);
			m_y += (float)((speed * m_changedY / sqrt(m_changedX * m_changedX + m_changedY * m_changedY)) * passedTime);

			if (hasFinished())
				m_obj->setLocation((int)toX, (int)toY);
			else
				m_obj->setLocation((int)m_x, (int)m_y);
		}
		bool hasFinished() const override
		{
			return (toX - (int)m_x) * m_changedX <= 0 && (toY - (int)m_y) * m_changedY <= 0;
		}
	};
}