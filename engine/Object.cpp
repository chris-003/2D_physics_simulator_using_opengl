#include "Object.h"
#include <algorithm>

namespace engine {
Object::Object() : slotIndex(0) {
}

Object::~Object() {
}

// template<typename slot_t, typename... Args>
// requires std::is_invocable_v<slot_t, Args...> Object::Slot
// Object::connect(const Signal &signal, const slot_t &func) {
//     // static unsigned int slotIndex = 0;
//     connections.insert(
//         std::make_tuple(signal, Slot(slotIndex), std::any(func)));

//     return Slot(slotIndex++);
// }

void Object::disconnect(const Slot &slot) {
    for (auto iter = connections.begin(); iter != connections.end(); ++iter) {
        if (std::get<1>(*iter).index() == slot.index()) {
            connections.erase(iter);
            return;
        }
    }
}

void Object::disconnect(Object *sender, const Slot &slot) {
    sender->disconnect(slot);
}

// void Object::emit(const Signal &signal) {
//     auto iter = connections.find(
//         std::make_tuple(signal, Slot(0), std::function<void(std::any)>()));
//     if (iter == connections.end()) {
//         return;
//     }
//     // else
//     for (; iter != connections.end() &&
//            std::get<0>(*iter).index() == signal.index();
//          ++iter) {
//         auto func = (std::get<2>(*iter));
//         std::any_cast<const std::function<void(void)>
//         &>(std::get<2>(*iter))();
//     }
// }

} // namespace engine