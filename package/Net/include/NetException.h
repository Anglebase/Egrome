#pragma once

#include "Exception.h"

class ConnectFailed : public Exception {
public:
    ConnectFailed(const std::string& message);
};

