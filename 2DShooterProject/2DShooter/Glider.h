#ifndef __Glider__
#define __Glider__

#include "Enemy.h"
#include "BaseCreator.h"
#include "SoundManager.h"

class Glider :	public Enemy
{
public:
	
	Glider();
	virtual ~Glider() {}
	
	virtual void load(std::unique_ptr<LoaderParams>& pParams);
	virtual void update();
	virtual void clean() { std::cout << "Enemy::clean() EMPTY \n"; }

	virtual void collision();

private:
	int m_maxHeight;
	int m_minHeight;
	int m_gap;
};

class GliderCreator : public BaseCreator
{
	GameObject* createGameObject() const { return new Glider(); }
};


#endif /*defined(__Enemy__)*/

