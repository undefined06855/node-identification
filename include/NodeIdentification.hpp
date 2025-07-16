#pragma once
#include <vector>
#include <Geode/cocos/base_nodes/CCNode.h>

namespace ni {
    
struct Identification {
    Identification(cocos2d::CCNode* node);

    std::string m_nodeID;
    std::string m_nodeTypeInfo;
    int m_nodeChildIndex;

    bool operator==(const Identification& rhs) const;
};
using FullIdentification = std::vector<Identification>;

FullIdentification identifyNode(cocos2d::CCNode* node);
cocos2d::CCNode* findNode(FullIdentification identification);

namespace utils {

int getNodeChildIndex(cocos2d::CCNode* node);
std::string getNodeTypeInfo(cocos2d::CCNode* node);

}

}
