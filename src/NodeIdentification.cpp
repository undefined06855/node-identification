#include "NodeIdentification.hpp"
#include <Geode/utils/cocos.hpp>

ni::FullIdentification ni::identifyNode(cocos2d::CCNode* node) {
    if (!node) return {};
    
    std::vector<Identification> ret = {};

    ret.push_back({
        .m_nodeID = node->getID(),
        .m_nodeChildIndex = ni::utils::getNodeChildIndex(node)
    });

    if (node->getParent()) {
        auto parentInfo = ni::identifyNode(node->getParent());
        ret.insert(ret.end(), parentInfo.begin(), parentInfo.end());
    }

    return ret;
}

cocos2d::CCNode* ni::findNode(ni::FullIdentification identification) {
    return ni::findNode(identification, cocos2d::CCScene::get());
}

cocos2d::CCNode* ni::findNode(ni::FullIdentification identification, cocos2d::CCNode* parent) {
    if (identification.size() == 0) return parent;
    if (!parent) return nullptr;

    auto id = identification.back();

    for (auto node : geode::cocos::CCArrayExt<cocos2d::CCNode*>(parent->getChildren())) {
        if (node->getID() == id.m_nodeID && ni::utils::getNodeChildIndex(node) == id.m_nodeChildIndex) {
            identification.pop_back();
            return ni::findNode(identification, node);
        }
    }

    return nullptr;
}

int ni::utils::getNodeChildIndex(cocos2d::CCNode* node) {
    if (!node || !node->getParent()) return -1;

    auto index = node->getParent()->getChildren()->indexOfObject(node);
    if (index == UINT_MAX) return -1;

    return index;
}
