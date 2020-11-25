#ifndef __Object_Spawner__
#define __Object_Spawner__

#include "Singleton.h"
#include "LoaderParams.h"
#include "ObjectLayer.h"

class ObjectSpawner : public Singleton<ObjectSpawner>
{
public:
    ObjectSpawner(token) {}
    ~ObjectSpawner() {}

    void spawnObject(ObjectLayer& objLayer, ObjectMarker& objMarker);

    void registerObjParams(std::string& objSubType, LoaderParams& params);

    bool checkObjParamsMap(std::string& objSubType);

    LoaderParams& getParameter(std::string& objSubType) { return m_objParams[objSubType]; }

private:

    std::map<std::string, LoaderParams> m_objParams;
};

typedef ObjectSpawner TheObjectSpawner;

#endif /* defined ( __Object_Spawner__ ) */
