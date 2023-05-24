# mig

Scriptable map migrations

## building

Assuming you have gcc, libpq and ninja installed:

```sh
git clone --recurse-submodules https://github.com/lord-server/mig.git
mkdir build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
ninja
```
