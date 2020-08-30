#include <string>
#include <memory>

class ConfigManager
{
public:
    void initialise(std::string& configfile_);
    using Ptr = std::shared_ptr<ConfigManager>;

};
