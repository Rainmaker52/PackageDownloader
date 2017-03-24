#include <iostream>

#include <Poco/Util/Application.h>
#include <Poco/Task.h>
#include <Poco/Net/StreamSocket.h>

#include "porttester.h"

void PortTester::runTask() {
    Poco::Util::Application &application = Poco::Util::Application::instance();

    try {
        Poco::Net::SocketAddress socketAddress(this->_hostName, Poco::UInt16(this->_portNumber));
        Poco::Net::StreamSocket streamSocket;

        // Throws if something happens
        streamSocket.connect(socketAddress, Poco::Timespan(0, 0, 0, std::stoi(application.config().getString("tcptimeout")), 0));
        application.config().setString("selectedserver", this->_hostName);
        std::cout << "Selected server " << this->_hostName << " for download" << std::endl;

    } catch(const Poco::RuntimeException &e) {
        //std::cout << "Server " << this->_hostName << " encountered a network error: " << e.message() << std::endl;
    }   catch(const std::exception &e){
            std::cout << this->_hostName << " failed: " << e.what() << ". Exception type " << typeid(e).name() << std::endl;
    }

}
