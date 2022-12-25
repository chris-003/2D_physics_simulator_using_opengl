#pragma once
#include "STree.h"
#include <algorithm>

namespace engine {
template<typename Data_t>
STree<Data_t>::STree(const Data &data, Self *parent)
    : m_data(data), m_parent(parent) {
    if (m_parent != nullptr) {
        m_parent->m_children.push_back(this);
    }
}

template<typename Data_t>
STree<Data_t>::STree(Data &&data, Self *parent)
    : m_data(std::move(data)), m_parent(parent) {
    if (m_parent != nullptr) {
        m_parent->m_children.push_back(this);
    }
}

template<typename Data_t>
STree<Data_t>::~STree() {
    if (m_parent != nullptr) {
        { // setParent(nullptr);
            Container &parentContainer = m_parent->m_children;
            parentContainer.erase(std::find(parentContainer.begin(),
                                            parentContainer.end(), this));
            m_parent = nullptr;
        }
        {
            for (auto *i : m_children) {
                i->m_parent = nullptr;
            }
        }
    }
}

template<typename Data_t>
STree<Data_t>::Self *STree<Data_t>::parent() const {
    return m_parent;
}

template<typename Data_t>
void STree<Data_t>::setParent(Self *parent) {
    if (parent == m_parent) {
        return;
    }
    if (m_parent != nullptr) {
        Container &parentContainer = m_parent->m_children;
        parentContainer.erase(
            std::find(parentContainer.begin(), parentContainer.end(), this));
        m_parent = nullptr;
    }
    // else
    m_parent = parent;
    m_parent->m_children.push_back(this);
}

template<typename Data_t>
STree<Data_t>::Data &STree<Data_t>::data() {
    return m_data;
}

template<typename Data_t>
const STree<Data_t>::Data &STree<Data_t>::data() const {
    return m_data;
}

template<typename Data_t>
void STree<Data_t>::setData(const Data &data) {
    m_data = data;
}

template<typename Data_t>
void STree<Data_t>::setData(Data &&data) {
    m_data = std::move(data);
}

template<typename Data_t>
template<typename... Arg>
void STree<Data_t>::emplace(Arg &...arg...) {
    m_data = std::move(Data(std::forward(arg)...));
}

template<typename Data_t>
STree<Data_t>::iterator STree<Data_t>::begin() {
    return m_children.begin();
}

template<typename Data_t>
STree<Data_t>::iterator STree<Data_t>::end() {
    return m_children.end();
}

template<typename Data_t>
STree<Data_t>::const_iterator STree<Data_t>::begin() const {
    return m_children.begin();
}

template<typename Data_t>
STree<Data_t>::const_iterator STree<Data_t>::end() const {
    return m_children.end();
}

template<typename Data_t>
STree<Data_t>::const_iterator STree<Data_t>::cbegin() const {
    return m_children.begin();
}

template<typename Data_t>
STree<Data_t>::const_iterator STree<Data_t>::cend() const {
    return m_children.end();
}

template<typename Data_t>
void STree<Data_t>::addChild(Self *const &child) {
    if (iterator i = std::find(begin(), end(), child); i != end()) {
        return;
    }
    if (child->m_parent != nullptr) {
        Container &c = child->m_parent->m_children;
        c.erase(std::find(c.begin(), c.end(), child));
        // child->m_parent = nullptr;
    }
    child->m_parent = this;
    m_children.push_back(child);
}

template<typename Data_t>
STree<Data_t>::iterator STree<Data_t>::erase(const iterator &pos) {
    if (begin() <= pos && pos < end()) {
        Self *child     = (*pos);
        child->m_parent = nullptr;
        return m_children.erase(pos);
    }
    return m_children.end();
}
} // namespace engine