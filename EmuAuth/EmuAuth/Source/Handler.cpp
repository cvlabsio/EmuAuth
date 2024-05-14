#include "Global.h"

void Handler::HandleInit(const httplib::Params& data, const httplib::Request&, httplib::Response& res)
{
    Console::Info("Handling API INIT request...");

    std::string clientKey = data.find("enckey")->second;
    Console::Debug("Encryption key: %s", clientKey.c_str());

    Global::EncryptionKey = clientKey + "-" + Global::Secret;

    nlohmann::json output = {
      {"success", true},
      {"message", "Initialized"},
      {"sessionid", "deadfeed"},
      {"appinfo", {
        {"numUsers", "N/A"},
        {"numOnlineUsers", "N/A"},
        {"numKeys", "N/A"},
        {"version", "2.0"},
        {"customerPanelLink", "https://keyauth.cc/panel/xxx"},
      }},
      {"newSession", true},
      {"nonce", "feeddead"}
    };

    std::string json = output.dump();
    std::string checksum = Utils::GenerateHMAC(Global::Secret, json);

    Console::Debug("Using signature: %s", checksum.c_str());
    Console::Debug("JSON: %s", json.c_str());

    res.set_header("signature", checksum);
    res.set_content(json, "application/json");

    Console::Success("INIT request handled");
}

void Handler::HandleLogin(const httplib::Params& data, const httplib::Request&, httplib::Response& res)
{
    Console::Info("Handling API LOGIN request...");

    std::string username = data.find("username")->second;
    Console::Debug("Username: %s", username.c_str());

    nlohmann::json output = {
    {"success", true},
    {"message", "Logged in!"},
    {"info", {
        {"username", "emulator"},
        {"subscriptions", {{
            {"subscription", "default"},
            {"key", "AAAAAAA-AAAAAAA-AAAAAAA-AAAAAAA-AAAAAAA-AAAAAAA-AAAAAAA"},
            {"expiry", "2031259554"},
            {"timeleft", 315569071}
        }}},
        {"ip", "88.88.88.88"},
        {"hwid", "emulator"},
        {"createdate", "1715690294"},
        {"lastlogin", "1715690483"}
    }},
    {"nonce", "feeddead"}
    };

    std::string json = output.dump();
    std::string checksum = Utils::GenerateHMAC(Global::EncryptionKey, json);

    Console::Debug("Using signature: %s", checksum.c_str());
    Console::Debug("JSON: %s", json.c_str());

    res.set_header("signature", checksum);
    res.set_content(json, "application/json");

    Console::Success("LOGIN request handled");
}

void Handler::Process(const httplib::Request& req, httplib::Response& res)
{
    httplib::Params data;
    httplib::detail::parse_query_text(req.body, data);

    Console::Debug("Request has %i parameters with body %s", data.size(), req.body.c_str());

    std::string type = data.find("type")->second;

    if (type == "init")
    {
        HandleInit(data, req, res);
        return;
    }

    if (type == "login")
    {
        HandleLogin(data, req, res);
        return;
    }

    Console::Error("Unknown API request type");
}