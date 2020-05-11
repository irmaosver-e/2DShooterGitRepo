#ifndef __Enemy__
#define __Enemy__

#include "ShooterObject.h"

class Enemy : public ShooterObject
{
public:
	virtual std::string objType() { return "Enemy"; }

protected:
	int m_health;

	Enemy() : ShooterObject() {}
	virtual ~Enemy() {}
};

#endif /*defined(__Enemy__)*/