#ifndef dia_runtime_h
#define dia_runtime_h

#include "dia_functions.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "LuaBridge.h"
#include <string>
#include <jansson.h>
#include <list>

#include "dia_runtime_screen.h"
#include "dia_runtime_hardware.h"
#include "dia_runtime_registry.h"
#include "dia_runtime_svcweather.h"

using namespace luabridge;


class DiaRuntime {
public:
    std::string src;
    std::string incl;
    lua_State* Lua;
    int Setup();
    int Loop();
    DiaRuntime(DiaRuntimeRegistry *newDiaRuntimeRegistry);
    ~DiaRuntime();
    LuaRef * SetupFunction;
    LuaRef * LoopFunction;
    std::list<DiaRuntimeScreen *> all_screens;
    DiaRuntimeHardware * hardware;
    DiaRuntimeRegistry * Registry;
    int Init(std::string folder, json_t * src_json, json_t * include_json);
    int InitStr(std::string folder, std::string src_str, std::string incl_str);
    int AddScreen(DiaRuntimeScreen * screen);
    int AddHardware(DiaRuntimeHardware * hw);
    int AddRegistry(DiaRuntimeRegistry * hw);
    int AddSvcWeather(DiaRuntimeSvcWeather * svc);
    int AddAnimations();
    int AddPrograms(std::map<std::string, int> *programs);
    int SetPostID(int newPostID);
};

void printMessage(const std::string& s);

 
#endif
