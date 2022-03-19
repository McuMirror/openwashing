#ifndef dia_runtime_registry_h
#define dia_runtime_registry_h

#include "dia_functions.h"
#include "dia_network.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "LuaBridge.h"
#include <string>
#include <jansson.h>
#include <list>
#include <stdexcept>

using namespace luabridge;

// Main object for Client-Server communication.


class DiaRuntimeRegistry {
private:
    DiaNetwork * network;
public:
    int curPostID;
    DiaRuntimeRegistry(DiaNetwork * newNetwork) {
        curPostID = 0;
        network = newNetwork;
    }
    
    std::string Value(std::string key) {
        return network->GetRegistryValueByKey(key);
    }

    std::string ValueFromStation(int id, std::string key){
        return network->GetRegistryValueFromStationByKey(id, key);
    }
    
    int ValueInt(std::string key) {
	    int result = 0;
	    try {
	        result = std::stoi(values[key]);
	    }
        catch (std::invalid_argument &err) {
            fprintf(stderr, "Key for registry is invalid, returning 0...\n");
            return 0;
        }
        return result;
    }

    int SetPostID(int newPostID) {
        curPostID = newPostID;
        return 0;
    }

    int GetPostID() {
        return curPostID;
    }

    int SetValue(std::string key,std::string value) {
        values[key]= value;
        return 0;
    }

    std::string SetValueByKeyIfNotExists(std::string key, std::string value) {
        return network->SetRegistryValueByKeyIfNotExists(key, value);
    }

    std::string SetValueByKey(std::string key, std::string value){
        return network->SetRegistryValueByKey(key,value);
    }

    int (*get_price_function)(int button);
    int GetPrice(int button) {
        if(get_price_function) {
            return get_price_function(button);
        } else {
            printf("error: NIL object or function GetPrice\n");
        }
        return 0;
    }

    int (*get_discount_function)(int button);
    int GetDiscount(int button) {
        if(get_discount_function) {
            return get_discount_function(button);
        } else {
            printf("error: NIL object or function GetDiscount\n");
        }
        return 0;
    }

    int (*get_is_finishing_program_function)(int button);
    int GetIsFinishingProgram(int button){
        if (get_is_finishing_program_function){
            return get_is_finishing_program_function(button);
        }else {
            printf("error: NIL object or function GetIsFinishingProgram\n");
        }
        return 0;
    }
private:
    std::map<std::string, std::string> values;
};

#endif
