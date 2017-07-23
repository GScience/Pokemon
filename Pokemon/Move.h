#pragma once

#include "ActionBase.h"
#include "RenderableObject.h"

constexpr double PI = 3.141592653589793238462;

namespace Action
{
	template <int speed, int toX, int toY> class MoveTo :public ActionBase
	{
	private:
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
			return (toX - (int)m_x) * m_changedX <= 0 && (toY - (int)m_y) * m_changedY <= 0 || m_isStop;
		}
	};

	template <int speed, int degree, int step> class MoveWithStep :public ActionBase
	{
	private:
		//location in float
		float m_x;
		float m_y;

		int		m_oldX;
		int		m_oldY;

		float	m_moved = 0;
		int		m_stepCount;
		bool	m_hasFinished = false;

		double m_cos = cos(degree / 180.0 * PI);
		double m_sin = sin(degree / 180.0 * PI);

	public:
		MoveWithStep(std::shared_ptr<RenderableObject> obj) :ActionBase(obj)
		{
			m_oldX = obj->getX();
			m_oldY = obj->getY();

			m_x = (float)m_oldX;
			m_y = (float)m_oldY;
		}

		void update(double passedTime) override
		{
			if (m_hasFinished)
				return;

			if (m_isStop)
			{
				if ((m_moved + (float)(speed * passedTime)) / (float)step < m_stepCount)
				{
					if (speed * passedTime > m_stepCount * step - m_moved)
					{
						m_x += (float)(m_cos * (m_stepCount * step - m_moved));
						m_y += (float)(m_sin * (m_stepCount * step - m_moved));

						m_moved += (float)(m_stepCount * step - m_moved);
					}
					else
					{
						m_x += (float)(speed * m_cos * passedTime);
						m_y += (float)(speed * m_sin * passedTime);

						m_moved += (float)passedTime * speed;
					}
				}
				else
				{
					m_hasFinished = true;
					m_obj->setLocation(m_oldX + (int)(m_cos * m_stepCount * step), m_oldY + (int)(m_sin * m_stepCount * step));
					return;
				}
			}
			else
			{
				m_x += (float)(speed * m_cos * passedTime);
				m_y += (float)(speed * m_sin * passedTime);

				m_moved += (float)passedTime * speed;
			}

			m_obj->setLocation((int)m_x, (int)m_y);
		}

		bool hasFinished() const override
		{
			return m_hasFinished;
		}

		void stop() override
		{
			ActionBase::stop();

			m_stepCount = (int)m_moved / step + 1;
		}
	};

	template <int speed, int xChanged, int yChanged> class Move :public ActionBase
	{
	private:
		//location in float
		float m_x;
		float m_y;

		int oldX;
		int oldY;

	public:
		Move(std::shared_ptr<RenderableObject> obj) :ActionBase(obj)
		{
			oldX = m_obj->getX();
			oldY = m_obj->getY();

			m_x = (float)oldX;
			m_y = (float)oldY;
		}

		void update(double passedTime) override
		{
			m_x += (float)((speed * xChanged / sqrt(xChanged * xChanged + yChanged * yChanged)) * passedTime);
			m_y += (float)((speed * yChanged / sqrt(xChanged * xChanged + yChanged * yChanged)) * passedTime);

			if (hasFinished())
				m_obj->setLocation((int)oldX + xChanged, (int)oldY + yChanged);
			else
				m_obj->setLocation((int)m_x, (int)m_y);
		}
		bool hasFinished() const override
		{
			return abs(oldX - m_x) >= abs(xChanged) && abs(oldY - m_y) >= abs(yChanged) || m_isStop;
		}
	};
}