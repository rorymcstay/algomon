#include <string>
#include <map>
#include "Strategy.h"


class StrategyEngine
{

public:
    StrategyEngine();
    ~StrategyEngine();
    void initialise();
    Strategy::Ptr getOrCreateStrategy(const std::string& key);
private:
    std::map<std::string, Strategy::Ptr>;
    
};
