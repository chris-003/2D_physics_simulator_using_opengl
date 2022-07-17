#pragma once
#include <any>
#include <functional>
#include <set>
#include <tuple>

namespace engine {
class Object {
public:
    class Signal {
    public:
        Signal(unsigned int index = -1) : _index(index) {
        }
        unsigned int index() const {
            return _index;
        }
        std::strong_ordering operator<=>(const Signal &b) const {
            return index() <=> b.index();
        }

    protected:
        unsigned int _index;
    };
    class Slot {
    public:
        Slot(unsigned int index = -1) : _index(index) {
        }
        unsigned int index() const {
            return _index;
        }
        std::strong_ordering operator<=>(const Slot &b) const {
            return index() <=> b.index();
        }

    protected:
        unsigned int _index;
    };
    Object();
    ~Object();
    Slot        connect(const Signal                                &signal,
                        const std::function<void(const std::any &)> &func);
    static Slot connect(Object *sender, const Signal &signal,
                        const std::function<void(const std::any &)> &func);
    void        disconnect(const Slot &slot);
    static void disconnect(Object *sender, const Slot &slot);
    void        emit(const Signal &signal, const std::any &param = std::any());

private:
    struct Cmp {
        template<typename T>
        bool operator()(const T &a, const T &b) const {
            return std::get<0>(a).index() < std::get<0>(b).index();
        }
    };
    std::multiset<
        std::tuple<Signal, Slot, std::function<void(const std::any &)>>, Cmp>
                 connections;
    unsigned int slotIndex;
};
} // namespace engine