#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <vector>
//para usar o parser json
#include "rapidjson/prettywriter.h" // JSON para string

class Package {
public:
    Package();
    Package(const std::string _ip, const std::string msg);
    Package(const Package& rhs);
    virtual ~Package();

    Package& operator=(const Package& rhs);
    void setip(const std::string _ip);
    std::string getip() const;
    void setmessage(const std::string msg);
    std::string getmessage() const;

    template <typename Writer>
    void Serialize(Writer& writer) const {
        writer.StartObject();  //inicia objeto
        writer.Key("ip");
        writer.String(ip.c_str(), static_cast<size_t>(ip.size()));
        writer.Key("message");
        writer.String(message.c_str(), static_cast<size_t>(message.size()));
        writer.EndObject();
    }
private:

    std::string ip;
    std::string message;
};


#endif
