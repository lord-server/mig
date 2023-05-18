#pragma once

#include <lua.h>

namespace mig {
class script_env {
public:
    script_env();
    ~script_env();

    script_env(const script_env&) = delete;
    script_env& operator=(const script_env&) = delete;

private:
    lua_State* L;
};
}
