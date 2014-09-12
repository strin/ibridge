//
//  BridgeException.cpp
//  iBridge
//
//  Created by Tianlin Shi on 11/28/12.
//
//

#include "BridgeException.h"

BridgeException::BridgeException() {
        this->message = "(No Message)";
}

BridgeException::BridgeException(string message) {
        this->message = message;
}

string BridgeException::getMessage() {
        return this->message;
}