#include <iostream>
#include <sstream>

#include <Poco/Util/Application.h>

#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/HelpFormatter.h>

#include <Poco/TaskManager.h>
#include <Poco/URI.h>
#include <Poco/Net/SSLManager.h>

#include <Poco/File.h>

#include "downloader.h"
#include "summary.h"
#include "porttester.h"
#include "httpsclient.h"
#include "util.h"

void Downloader::initialize(Poco::Util::Application &application) {
    this->loadConfiguration();
    Poco::Util::Application::initialize(application);

    Poco::Net::initializeSSL();
}

void Downloader::uninitialize() {
    Poco::Net::uninitializeSSL();
    Poco::Util::Application::uninitialize();
}

void Downloader::reinitialize(Poco::Util::Application &application) {
    Poco::Util::Application::reinitialize(application);
    //Customize after
}

void Downloader::defineOptions(Poco::Util::OptionSet &optionSet) {
    Poco::Util::Application::defineOptions(optionSet);

    optionSet.addOption(
            Poco::Util::Option("help", "h", "Display usage information")
                .required(false)
                .repeatable(false)
                .callback(Poco::Util::OptionCallback<Downloader>(this, &Downloader::handleHelp))
    );
    optionSet.addOption(
            Poco::Util::Option("packagepath", "", "Path on server where package is located")
                .required(true)
                .repeatable(false)
                .argument("<path>")
                .callback(Poco::Util::OptionCallback<Downloader>(this, &Downloader::handleArgument))
    );
    optionSet.addOption(
            Poco::Util::Option("servers", "", "Comma seperated list of servers")
                .required(true)
                .repeatable(false)
                .argument("server1,server2,server3...", true)
                .callback(Poco::Util::OptionCallback<Downloader>(this, &Downloader::handleArgument))
    );
    optionSet.addOption(
            Poco::Util::Option("tcptimeout", "", "TCP Timeout when probing servers, in seconds")
                .required(false)
                .repeatable(false)
                .argument("<timeout in seconds>")
                .callback(Poco::Util::OptionCallback<Downloader>(this, &Downloader::handleArgument))
    );
    optionSet.addOption(
            Poco::Util::Option("overwrite", "o", "Overwrite existing file")
                .required(false)
                .repeatable(false)
                .callback(Poco::Util::OptionCallback<Downloader>(this, &Downloader::handleArgument))
    );

    // Default configuration
    this->config().setBool("helpDisplayed", false);
    this->config().setString("tcptimeout", "2");
    this->config().setBool("overwrite", false);
}

void Downloader::handleHelp(const std::string& name, const std::string& value) {
    this->config().setBool("helpDisplayed", true);

    Poco::Util::HelpFormatter helpFormatter(this->options());
    helpFormatter.setCommand(this->commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("Application that downloads a file from one of the given servers");
    helpFormatter.format(std::cout);
    stopOptionsProcessing();
}

//handleOption would be a nicer name, but this is already used by Poco::Util::Application, which would cause an override
void Downloader::handleArgument(const std::string &name, const std::string &value) {
    if(name == "overwrite") {
        this->config().setBool("overwrite", true);
    } else {
        this->config().setString(name, value);
    }
}

int Downloader::main(const std::vector<std::string> &arguments) {
    if(this->config().getBool("helpDisplayed")) { return Poco::Util::Application::EXIT_OK; }

    Poco::TaskManager taskManager;

    // Display summary
    taskManager.start(new Summary);
    taskManager.joinAll();

    std::cout << "Testing servers..." << std::endl;
    for(auto server : Util::splitString(this->config().getString("servers"))){
        taskManager.start(new PortTester(server, 443));
    }
    taskManager.joinAll();

    if(this->config().getString("selectedserver", "noserverfound") == "noserverfound"){
        std::cerr << "No servers eligable for download were found.";
        return Poco::Util::Application::EXIT_NOHOST;
    }

    Poco::URI uri(std::string("https://" +
                          this->config().getString("selectedserver") + "/" +
                          this->config().getString("packagepath")));

    std::vector<std::string> segments;
    uri.getPathSegments(segments);
    auto &fileName = segments.back();
    std::cout << "Downloading to file " << fileName << std::endl;

    if(Poco::File(fileName).exists() && !this->config().getBool("overwrite")){
        std::cerr << "File " << fileName << " exists and overwrite is not enabled" << std::endl;
        return Poco::Util::Application::EXIT_IOERR;
    }

    taskManager.start(new HTTPSClient(uri, fileName));
    taskManager.joinAll();

    return Poco::Util::Application::EXIT_OK;
}

POCO_APP_MAIN(Downloader)