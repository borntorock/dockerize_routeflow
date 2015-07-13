#include "IPC.h"

IPCMessage::~IPCMessage() {
    /* Virtual destructor quells compiler warnings about undefined behaviour */
}

string IPCMessageService::get_id() {
    return this->id;
}

void IPCMessageService::set_id(string id) {
    this->id = id;
}
