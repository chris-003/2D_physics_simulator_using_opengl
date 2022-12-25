#include "SObject.h"

namespace engine {
SObject::SObject() : slotIndex(0) {
}

SObject::~SObject() {
}

void SObject::disconnect(int slot) {
    for (auto iter = connections.begin(); iter != connections.end(); ++iter) {
        if (std::get<1>(*iter) == slot) {
            connections.erase(iter);
            return;
        }
    }
}

void SObject::disconnect(SObject *sender, int slot) {
    sender->disconnect(slot);
}
} // namespace engine