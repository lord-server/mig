#include <lualib.h>

#include "script.h"

namespace mig {
script_env::script_env()
{
    L = luaL_newstate();
}

script_env::~script_env()
{
    lua_close(L);
}
}
