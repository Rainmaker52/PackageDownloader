#include <iostream>

#include <Poco/Util/Application.h>
#include <Poco/Task.h>

#include "summary.h"
#include "util.h"

void Summary::runTask() {
    Poco::Util::Application &application = Poco::Util::Application::instance();

    std::cout << std::endl << "Summary" << std::endl << std::string(7, '-') << std::endl;
    std::cout << "Download path: " << application.config().getString("packagepath") << std::endl;
    std::cout << "TCP Timeout: " << application.config().getString("tcptimeout") << " second(s)" << std::endl;
    std::cout << "Overwrite existing file: " << (application.config().getBool("overwrite") ? "true": "false") << std::endl;
    std::cout << std::endl;

    for(auto server : Util::splitString(application.config().getString("servers"))){
        std::cout << "Server: " << server << std::endl;
    }
    std::cout << std::endl;

}
