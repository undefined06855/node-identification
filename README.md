# node-identification

A simple library to give a unique identification for nodes in a node tree in a
certain layer, to be able to be then found later quickly and easily for a Geode
mod (or I guess just any cocos game if you have node ids but who is doing that)

## Usage

Plonk this in your `CMakeLists.txt` after
`add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)`:
```cmake
CPMAddPackage("gh:undefined06855/node-identification#<commit hash>")
target_link_libraries(${PROJECT_NAME} node-identification)
```

and then use `ni::identifyNode` to get identification for a node:
```cpp
auto identification = ni::identifyNode(myNode);
```
and `ni::findNode` to find it in the node tree:
```cpp
auto node = ni::findNode(identification);
auto node = ni::findNode(identification, CCScene::get());
```
