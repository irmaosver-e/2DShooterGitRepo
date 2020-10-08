#include "GameObject.h"
#include "SDLSystem.h"

void GameObject::turnObjOn()
{
	m_bIsOn = true;
}

void GameObject::turnObjOff()
{
	m_bIsOn = false;
	//m_bInView = false;
	//m_bUpdating = false;
	//m_position = Vector2D(0, 0);
	m_velocity = Vector2D(0, 0);
}

void GameObject::InViewCheck()
{
	int screenWidth = TheSDLSystem::Instance().getScreenWidth();
	int screenHeight = TheSDLSystem::Instance().getScreenHeight();

	int objRightEdge = m_position.getX() + m_width;
	int objButtomEdge = m_position.getY() + m_height;


	if (m_position.getX() > screenWidth || objRightEdge < 0 ||
		m_position.getY() > screenHeight || objButtomEdge < 0)
	{
		turnObjOff();
	}
	else
	{
		turnObjOn();
	}
}
