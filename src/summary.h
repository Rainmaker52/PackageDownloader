#ifndef PACKAGEDOWNLOADER_SUMMARY_H
#define PACKAGEDOWNLOADER_SUMMARY_H

class Summary : public Poco::Task
{
public:
    Summary() : Task("summary") { };
    ~Summary() { };

    void runTask();
};

#endif //PACKAGEDOWNLOADER_SUMMARY_H
