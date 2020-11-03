#include "GameObject.h"
#include "SDLSystem.h"

void GameObject::turnObjOn()
{
	m_bIsOn = true;
}

void GameObject::turnObjOff()
{
	m_bIsOn = false;
	m_bInView = false;
	m_bUpdating = false;	
	m_velocity = Vector2Df(0, 0);

	//sends the object offscreen
	m_position.getYRef() = -(m_height + 10);
}


void GameObject::inViewCheck()
{
	int screenWidth = TheSDLSystem::Instance().getScreenWidth();
	int screenHeight = TheSDLSystem::Instance().getScreenHeight();

	int objRightEdge = m_position.getX() + m_width;
	int objButtomEdge = m_position.getY() + m_height;


	if (m_position.getX() > screenWidth || objRightEdge < 0 ||
		m_position.getY() > screenHeight || objButtomEdge < 0)
	{
		m_bInView = false;
	}
	else
	{
		m_bInView = true;
	}
}

void GameObject::scroll(float scrollSpeed)
{
	m_position.getXRef() -= scrollSpeed;
}
