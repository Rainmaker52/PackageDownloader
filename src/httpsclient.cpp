#include <iostream>

#include <Poco/Util/Application.h>
#include <Poco/Task.h>
#include <Poco/URI.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>

#include "httpsclient.h"

void HTTPSClient::runTask() {
    Poco::Util::Application &application = Poco::Util::Application::instance();

    std::cout << "Downloading from URL " << _URI.toString() << " to " << _fileName << std::endl;

    // Accept all certificates
    Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> pInvalidCertificateHandler = new Poco::Net::AcceptCertificateHandler(false);
    Poco::Net::Context::Ptr pContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "",
                                                              Poco::Net::Context::VERIFY_NONE);
    Poco::Net::SSLManager::instance().initializeClient(0, pInvalidCertificateHandler, pContext);

    Poco::Net::HTTPSClientSession httpsClientSession(this->_URI.getHost(), this->_URI.getPort());
    Poco::Net::HTTPRequest httpRequest(Poco::Net::HTTPRequest::HTTP_GET, this->_URI.getPath());
    httpsClientSession.sendRequest(httpRequest);
    Poco::Net::HTTPResponse httpResponse;
    std::istream& httpStream = httpsClientSession.receiveResponse(httpResponse);

    // Valid response?
    if (httpResponse.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
        std::cerr << "Error while downloading. Server response " << httpResponse.getStatus() << " reason given: "
                  << httpResponse.getReason() << std::endl;
        return;
    }

    Poco::FileOutputStream fileOutputStream(this->_fileName);

    Poco::StreamCopier::copyStream(httpStream, fileOutputStream);
    std::cout << "Download complete" << std::endl;
}
