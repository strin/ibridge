//
//  BridgeException.h
//  iBridge
//
//  Created by Tianlin Shi on 11/28/12.
//
//

#ifndef __iBridge__BridgeException__
#define __iBridge__BridgeException__

#include <iostream>
#include <string>

using namespace std;

class BridgeException {
public:
        BridgeException();
        BridgeException(string message);
        string getMessage();
private:
        string message;
};
#endif /* defined(__iBridge__BridgeException__) */
