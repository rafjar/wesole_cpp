#ifndef _rozklad_hpp_
#define _rozklad_hpp_

#include <map>
#include <vector>
#include <memory>

typedef std::map<std::string, float> ParametryRozkladu;

class Rozklad {
    public:
        explicit Rozklad(const std::vector<float> &dane);
        virtual ~Rozklad() {}
        virtual std::unique_ptr<ParametryRozkladu> oblicz() const = 0;

    protected:
        const std::vector<float> &dane_;
};

class RozkladGaussa : public Rozklad {
    public:
        explicit RozkladGaussa(const std::vector<float> &dane);
        virtual ~RozkladGaussa();
        virtual std::unique_ptr<ParametryRozkladu> oblicz() const;
        static Rozklad* kreator(const std::vector<float> &dane);
};

typedef Rozklad* (*KreatorRozkladu)(const std::vector<float> &);

class FabrykaRozkladow {
    private:
        static std::map<unsigned, KreatorRozkladu> rozklady;
        static std::map<unsigned, std::string> nazwy;

    public:
        static void rejestruj(KreatorRozkladu kr, const std::string &nazwa);
        static Rozklad *utworz(unsigned id, const std::vector<float> &dane);
        static std::string nazwa(unsigned id);
        static unsigned ilosc();
};

#endif