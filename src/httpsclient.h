#ifndef PACKAGEDOWNLOADER_HTTPSCLIENT_H
#define PACKAGEDOWNLOADER_HTTPSCLIENT_H

#include <Poco/FileStream.h>

class HTTPSClient : public Poco::Task
{
public:
    HTTPSClient(const Poco::URI& fullURL, std::string fileName)
            : Task("httpsclient"), _URI(fullURL), _fileName(fileName) { };
    ~HTTPSClient() { };

    void runTask();

private:
    const Poco::URI _URI;
    const std::string _fileName;
};

#endif //PACKAGEDOWNLOADER_HTTPSCLIENT_H
