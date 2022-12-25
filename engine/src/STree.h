#pragma once
#include <deque>

namespace engine {
template<typename Data_t>
class STree {
public:
    typedef Data_t                    Data;
    typedef STree<Data>               Self;
    typedef std::deque<Self *>        Container;
    typedef Container::iterator       iterator;
    typedef Container::const_iterator const_iterator;

protected:
    Data      m_data;
    Container m_children;
    Self     *m_parent;

public:
    STree(const Data &data = Data(), Self *parent = nullptr);
    STree(Data &&data, Self *parent = nullptr);
    ~STree();

public:
    Self       *parent() const;
    void        setParent(Self *parent);
    Data       &data();
    const Data &data() const;
    void        setData(const Data &data);
    void        setData(Data &&data);
    template<typename... Arg>
    void emplace(Arg &...arg...);

public:
    iterator       begin();
    iterator       end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    void           addChild(Self *const &chlid);
    iterator       erase(const iterator &pos);
};

template<>
class STree<void> : public STree<STree<void> *> {
public:
    typedef STree<void> *const  Data;
    typedef STree<void>         Self;
    typedef std::deque<Self *>  Container;
    typedef Container::iterator iterator;

    // protected:
    //     Data      m_data;
    //     Container m_children;
    //     Self     *m_parent;

public:
    STree(Self *parent = nullptr) : STree<STree<void> *>(this, parent) {
    }
    STree(STree<void> *&data, STree<STree<void> *> *parent)  = delete;
    STree(STree<void> *&&data, STree<STree<void> *> *parent) = delete;

public:
    // Self *parent();
    // void  setParent(Self *parent);
    // Data &data();

    void setData(STree<void> *&data)  = delete;
    void setData(STree<void> *&&data) = delete;
    template<typename... Arg>
    void emplace(Arg &...arg...) = delete;

    // public:
    //     iterator begin();
    //     iterator end();
    //     void     addChild(Self *const &chlid);
    //     iterator erase(const iterator &pos);
};
} // namespace engine

#include "STree.hpp"