#ifndef __ParserManager__
#define __ParserManager__

#include "Singleton.h"

#include "SystemParser.h"
#include "StateParser.h"
#include "LevelParser.h"

class ParserManager :  public Singleton<ParserManager>
{
public:
	ParserManager(token) :
		m_rootPath(""),
		m_imagesFolder(""),
		m_audioFolder(""),
		m_fontsFolder(""),
		m_mapsFolder(""),
		m_tilesetsFolder(""),
		m_sysParser(SystemParser()),
		m_stateParser(StateParser()),
		m_levelParser(LevelParser()) {}

	SystemParser& getSystemParserRef() { return m_sysParser; }
	StateParser& getStateParserRef() { return m_stateParser; }
	LevelParser& getLevelParserRef() { return m_levelParser; }

	friend class SystemParser;
	friend class StateParser;
	friend class LevelParser;

private:

	SystemParser m_sysParser;
	StateParser m_stateParser;
	LevelParser m_levelParser;

	std::string m_rootPath;
	std::string m_imagesFolder;
	std::string m_audioFolder;
	std::string m_fontsFolder;
	std::string m_mapsFolder;
	std::string m_tilesetsFolder;

};

typedef ParserManager TheParserManager;

#endif /* defined(__ParserManager__) */

