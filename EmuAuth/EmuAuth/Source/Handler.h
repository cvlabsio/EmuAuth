#pragma once

namespace Handler
{
    void HandleInit(const httplib::Params& data, const httplib::Request&, httplib::Response& res);
    void HandleLogin(const httplib::Params& data, const httplib::Request&, httplib::Response& res);

    void Process(const httplib::Request&, httplib::Response& res);
}