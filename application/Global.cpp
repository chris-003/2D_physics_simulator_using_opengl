#include "Global.h"

Global::Global() {
}

Global::~Global() {
}

Global &Global::getInstance() {
    static Global instance;
    return instance;
}