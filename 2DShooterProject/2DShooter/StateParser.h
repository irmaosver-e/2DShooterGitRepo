#ifndef __StateParser__
#define __StateParser__

#include <iostream>
#include <vector>
#include "Parser.h"
#include "GameObject.h"
#include "GameState.h"

class StateParser : public Parser
{
public:

	StateParser() {}
	~StateParser() {}

	/* redundant
	bool parseState(std::string assetsLocation, std::string stateFile, std::string stateID,
					std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);
					*/
	/* redundant
	void parseTextures(std::string assetsLocation,TiXmlElement* pTextureRoot, std::vector<std::string> *pTextureIDs);
	*/
	/* to be made redundant
	void parseObjects(TiXmlElement* pObjectRoot, std::vector<GameObject*> *pObjects);
	*/

	bool parseState(GameState* pState);

	void setStateFile(std::string& fileName) { m_stateFile = fileName; }

private:

	void parseAudio(TiXmlElement* pAudioElem);

	std::string m_stateFile;



};

#endif /* defined ( __StateParser__ ) */