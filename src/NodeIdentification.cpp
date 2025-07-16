#include "NodeIdentification.hpp"
#include <Geode/utils/cocos.hpp>

ni::Identification::Identification(cocos2d::CCNode* node)
    : m_nodeID(node->getID())
    , m_nodeTypeInfo(ni::utils::getNodeTypeInfo(node))
    , m_nodeChildIndex(ni::utils::getNodeChildIndex(node)) {}

bool ni::Identification::operator==(const ni::Identification& rhs) const {
    // maybe this isnt the best place to put this?
    // if node id is empty, use child index, else use node id
    if (m_nodeID == "" && rhs.m_nodeID == "") {
        return m_nodeChildIndex == rhs.m_nodeChildIndex
            && m_nodeTypeInfo == rhs.m_nodeTypeInfo;
    } else {
        return m_nodeID == rhs.m_nodeID
            && m_nodeTypeInfo == rhs.m_nodeTypeInfo;
    }
}


ni::FullIdentification ni::identifyNode(cocos2d::CCNode* node) {
    if (!node) return {};
    
    std::vector<ni::Identification> ret = {};

    ret.push_back(ni::Identification(node));

    if (node->getParent()) {
        auto parentInfo = ni::identifyNode(node->getParent());
        ret.insert(ret.end(), parentInfo.begin(), parentInfo.end());
    }

    return ret;
}

cocos2d::CCNode* findNodeInternal(ni::FullIdentification identification, cocos2d::CCNode* parent) {
    if (identification.size() == 0) return parent;
    if (!parent) return nullptr;

    auto id = identification.back();

    for (auto node : geode::cocos::CCArrayExt<cocos2d::CCNode*>(parent->getChildren())) {
        if (ni::Identification(node) == id) {
            identification.pop_back();
            return findNodeInternal(identification, node);
        }
    }

    return nullptr;
}

cocos2d::CCNode* ni::findNode(ni::FullIdentification identification) {
    if (identification.size() == 0) return nullptr;
    identification.pop_back(); // remove ccscene since thats always first
    return findNodeInternal(identification, cocos2d::CCScene::get());
}

// utils:

int ni::utils::getNodeChildIndex(cocos2d::CCNode* node) {
    if (!node || !node->getParent()) return -1;

    auto index = node->getParent()->getChildren()->indexOfObject(node);
    if (index == UINT_MAX) return -1;

    return index;
}

std::string ni::utils::getNodeTypeInfo(cocos2d::CCNode* node) {
    if (!node) return "";

    std::string ret;

#ifdef GEODE_IS_WINDOWS
    ret = typeid(*node).name() + 6;
#else 
    int status = 0;
    auto demangle = abi::__cxa_demangle(typeid(*node).name(), 0, 0, &status);
    if (status == 0) {
        ret = demangle;
    }
    free(demangle);
#endif

    return ret;
}
