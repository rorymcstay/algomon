#include "ConfigManager.h"

namespace cfg
{
ConfigManager::ConfigManager()
:   _config()
,   _feedConfigs()
,   _topicConfigs()
,   _engineConfig()
,   _filelocation()
,   _initialised(false)
,   _config_root_ptr(nullptr)
{
    
}

void ConfigManager::initialise(std::string& configfile_)
{
    _config.LoadFile(configfile_.c_str());
    _config_root_ptr = _config.FirstChildElement();
    _initialised = true;
    if (!_config_root_ptr)
    {
        LOG_WARN("Couldn't find root of config.");
    }

    loadConfig<EngineConfig>(_engineConfig, ENGINE_CONFIG);
    loadConfigs<FeedConfig>(_feedConfigs, FEED_CONFIG);
}

const ConfigEntry::Ptr ConfigManager::getConfigEntry(const std::string& name_) {
    // TODO: ability to pass a path.
    XMLElement* xmlPtr = _config_root_ptr->FirstChildElement(name_.c_str());
    if (!xmlPtr)
    {
        LOG_WARN("Config entry " << LOG_VAR(name_) << " not found");
        return nullptr;
    }
    return std::make_shared<ConfigEntry>(xmlPtr);
}

template<typename T>
bool ConfigManager::loadConfig(typename T::Ptr& config_, std::string path_, XMLElement* xmlelement)
{
    LOG_DEBUG("Loading config.");
    ConfigEntry::Ptr configEntry;
    if (!xmlelement)
    {
        configEntry = getConfigEntry(path_);
    }
    else
    {
        configEntry = std::make_shared<ConfigEntry>(xmlelement);
    }
    if (!configEntry)
    {
        LOG_WARNING("Could not load engine file config.");
        return false;
    }
    std::shared_ptr<T> en = std::make_shared<T>(configEntry);
    LOG_INFO("Loaded engine config " << LOG_VAR(en->strategykey));
    config_ = en;
    return true; 
}

template<typename T>
bool ConfigManager::loadConfigs(std::map<std::string, typename T::Ptr>& configs_, std::string path_)
{
    XMLNode* configs = _config_root_ptr->FirstChildElement(path_.c_str());
    if (!configs)
    {
        LOG_WARN("Failed to load " << LOG_VAR(path_) << " config.");
        return false;
    }
    uint64_t i(0);
    XMLNode* child = configs->FirstChild();
    while (child != nullptr)
    {
        LOG_DEBUG("Loading config " << std::string(typeid(T).name()) << ": " << ++i <<  " from " << path_);
        XMLElement* element = child->ToElement();
        if (!element)
        {
            LOG_WARN("Child config in position " << i << " is not an element." << LOG_VAR(path_));
            continue;
        }
        std::string name = element->Attribute("name");
        typename T::Ptr  configRef = configs_[name];
        loadConfig<T>(configRef, "", element);
        child = child->NextSiblingElement();
    }
    LOG_INFO("Finished loading " << LOG_VAR(path_) << " config " << LOG_VAR(configs_.size()));
    return true;
}

} // cfg
