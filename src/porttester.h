#ifndef PACKAGEDOWNLOADER_PORTTESTER_H
#define PACKAGEDOWNLOADER_PORTTESTER_H

class PortTester : public Poco::Task
{
public:
    PortTester(std::string& hostName, const unsigned int& portNumber)
            : Task("porttester"),  _portNumber(portNumber), _hostName(hostName) { };
    ~PortTester() { };

    void runTask();

private:
    const std::string _hostName ;
    const unsigned int _portNumber;
};

#endif //PACKAGEDOWNLOADER_PORTTESTER_H
