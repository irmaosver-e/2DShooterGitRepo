#ifndef __Glider__
#define __Glider__

#include "Enemy.h"

class Glider :	public Enemy
{
public:
	
	Glider();
	virtual ~Glider() {}
	
	virtual void load(const LoaderParams& rParams);
	virtual void update();
	virtual void clean() { std::cout << "Enemy::clean() EMPTY \n"; }

	virtual void collision();

private:
	int m_maxHeight;
	int m_minHeight;
	int m_gap;
};

#endif /*defined(__Enemy__)*/

