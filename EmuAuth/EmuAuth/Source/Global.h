#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <cstdarg>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../Library/httplib.h"
#include "../Library/json.hpp"
#include "../Library/hmac_sha256.h"

#include "Console.h"
#include "Handler.h"
#include "Utils.h"

namespace Global
{
    inline std::string Secret;
    inline std::string EncryptionKey;
}