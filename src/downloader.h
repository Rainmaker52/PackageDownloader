#ifndef PACKAGEDOWNLOADER_DOWNLOADER_H
#define PACKAGEDOWNLOADER_DOWNLOADER_H

class Downloader : public Poco::Util::Application
{
public:
    Downloader() {};
    ~Downloader() {};

private:

protected:
    void    initialize(Poco::Util::Application&);
    void    uninitialize();
    void    reinitialize(Poco::Util::Application&);

    void    defineOptions(Poco::Util::OptionSet&);
    void    handleArgument(const std::string &, const std::string &);
    void    handleHelp(const std::string&, const std::string&);

    int     main(const std::vector<std::string>&);

};

#endif //PACKAGEDOWNLOADER_DOWNLOADER_H
