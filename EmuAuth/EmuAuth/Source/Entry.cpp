#include "Global.h"

int main()
{
    Console::Title("EmuAuth", "https://github.com/SamuelTulach/EmuAuth");

    Global::Secret = Console::ReadInput("Application secret: ");
    printf("\n");

    if (Global::Secret.length() != 64)
    {
        Console::Error("Entered application secret has invalid length");
        getchar();
    }

    Console::Info("Starting fake auth server...");
    httplib::SSLServer svr("./certs/keyauth.win.crt", "./certs/keyauth.win.key");

    svr.Get("/ping", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("pong", "text/plain");
        });

    svr.Post("/api/1.2/", Handler::Process);

    svr.set_logger([](const httplib::Request& req, const httplib::Response& res) {
        Console::Debug("Request from %s at %s", req.remote_addr.c_str(), req.path.c_str());
        });

    bool status = svr.listen("0.0.0.0", 443);
    if (!status)
    {
        Console::Error("Failed to start fake auth server");
        getchar();
    }

    getchar();
}