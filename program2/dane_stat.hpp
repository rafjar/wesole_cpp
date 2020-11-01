#ifndef _dane_stat_hpp_
#define _dane_stat_hpp_

#include <string>
#include <vector>
#include <fstream>

class DaneStat {
    public:
        DaneStat(const std::string &nazwa);
        virtual const std::vector<float> &dane() const = 0;
        virtual ~DaneStat() {};
        virtual const std::string &nazwa() const;

    protected:
        std::string nazwa_;
};

class DaneStatReal : public DaneStat {
    public:
        DaneStatReal(const std::string &nazwa);
        const std::vector<float> &dane() const;

    private:
        std::vector<float> data_;
};

class DaneStatProxy : public DaneStat {
    public:
        DaneStatProxy(const std::string &nazwa);
        ~DaneStatProxy();
        virtual const std::vector<float> &dane() const;

    private:
        mutable DaneStat *real_obj_;
};

#endif