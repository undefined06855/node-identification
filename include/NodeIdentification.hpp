#pragma once
#include <vector>
#include <Geode/cocos/base_nodes/CCNode.h>

namespace ni {

struct Identification {
    std::string m_nodeID;
    int m_nodeChildIndex;
};

std::vector<Identification> identifyNode(cocos2d::CCNode* node);
cocos2d::CCNode* findNode(std::vector<Identification> identification);
cocos2d::CCNode* findNode(std::vector<Identification> identification, cocos2d::CCNode* parent);

namespace utils {

int getNodeChildIndex(cocos2d::CCNode* node);

}

}
