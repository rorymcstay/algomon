#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include <string>
#include <memory>
#include <map>

#include <tinyxml2.h>

#include <logger.h>
#include <include.hpp>

#include <Enums.h>

#define CONFIG_ROOT     "AlgomonConfig"
#define ENGINE_CONFIG   "EngineConfig"
#define FEED_CONFIG     "FeedConfigs"

using namespace tinyxml2;
using namespace domain;

namespace cfg
{

class ConfigEntry
{
    XMLElement* _xml;
public:
    using Ptr = std::shared_ptr<ConfigEntry>;
    ConfigEntry(XMLElement* xml)
    :   _xml(xml)
    {}
    ConfigEntry()
    :   _xml(nullptr)
    {}

    std::string getStrValue(const std::string& key_, std::string default_)
    {
        const XMLAttribute* val = _xml->FindAttribute(key_.c_str());
        if (!val)
        {
            LOG_WARN("config entry " << LOG_VAR(key_) << " not found");
            return default_ ;
        }
        return val->Value(); 
    }

    int getIntValue(const std::string& key_, int default_)
    {
        const XMLAttribute* val = _xml->FindAttribute(key_.c_str());
        if (!val)
        {
            LOG_WARN("config entry " << LOG_VAR(key_) << " not found");
            return default_;
        }
        return val->IntValue();
    }

    bool getBoolValue(const std::string& key_, bool default_)
    {
        const XMLAttribute* val = _xml->FindAttribute(key_.c_str());
        if (!val)
        {
            LOG_WARN("config entry " << LOG_VAR(key_) << " not found");
            return default_;
        }
        return val->BoolValue();
    }

    std::string getName()
    {
        return _xml->Name();
    }
};

struct Config
{
    using Ptr = std::shared_ptr<Config>;
    bool    empty;
    std::string name;
    Config()
    :   empty(true)
    ,   name()
    {}
    Config(ConfigEntry::Ptr xml)
    :   empty(false)
    ,   name(xml->getName())
    {
        LOG_DEBUG("Loading config" << LOG_VAR(name));
    }
};

struct PluginConfig : Config
{
    std::string     library;
    std::string     factorymethod;

    PluginConfig(ConfigEntry::Ptr xml)
    :   Config(xml)
    ,   library(xml->getStrValue("library", ""))
    ,   factorymethod(xml->getStrValue("factorymethod", ""))
    {}
    PluginConfig(): Config(){}
};

struct EngineConfig : PluginConfig
{
    using Ptr = std::shared_ptr<EngineConfig>;
    domain::StrategyKey     strategykey;
    uint64_t                strategythreads;
    bool                    enforceSeqCheck;

    EngineConfig(ConfigEntry::Ptr xml)
    :   PluginConfig(xml)
    ,   strategykey(domain::str2enum<domain::StrategyKey>(xml->getStrValue("strategykey", "Instrument").c_str()))
    ,   strategythreads(xml->getIntValue("strategythreads", 2))
    ,   enforceSeqCheck(xml->getBoolValue("enforceSeqCheck", true))
    {}
    EngineConfig(): PluginConfig(){}
    static const char* classname() { return "EngineConfig"; }

};

struct StrategyConfig : Config
{

    using Ptr = std::shared_ptr<StrategyConfig>;
    StrategyConfig(ConfigEntry::Ptr xml)
    :   Config(xml)
    {}
};

struct TopicConfig : Config
{
    using Ptr = std::shared_ptr<TopicConfig>;
    std::string     name;
    std::string     filter;
    TopicConfig(ConfigEntry::Ptr xml)
    :   Config(xml)
    ,   name(xml->getStrValue("name", ""))
    ,   filter(xml->getStrValue("filter", ""))
    {}
    TopicConfig(): Config() {}
    static const char* classname() { return "TopicConfig"; }
};

struct FeedConfig : PluginConfig
{
    using Ptr = std::shared_ptr<FeedConfig>;
    std::string     connectionstring;
    std::string     eventtype;
    std::string     strategykey;
    std::string     topicname;
    bool            enabled;

    FeedConfig(ConfigEntry::Ptr xml)
    :   PluginConfig(xml)
    ,   connectionstring(xml->getStrValue("connectionstring", ""))
    ,   eventtype(xml->getStrValue("eventtype", ""))
    ,   strategykey(xml->getStrValue("strategykey", ""))
    ,   topicname(xml->getStrValue("topicname", ""))
    ,   enabled(xml->getBoolValue("enabled", true))
    {}
    FeedConfig() : PluginConfig(){}
    static const char* classname() { return "FeedConfig"; }
};
typedef std::map<std::string, FeedConfig::Ptr>  FeedConfigs;
typedef std::map<std::string, TopicConfig::Ptr> TopicConfigs;
typedef std::map<std::string, StrategyConfig::Ptr> StrategyConfigs;

class ConfigManager
{
private:
    tinyxml2::XMLDocument           _config;
    GETSET(FeedConfigs,             feedConfigs)
    GETSET(TopicConfigs,            topicConfigs)
    GETSET(EngineConfig::Ptr,       engineConfig)
    GETSET(StrategyConfigs,         strategyConfigs)
    GETSET(std::string,             filelocation)
    GETSET(bool,                    initialised)
    XMLElement*                     _config_root_ptr;

    const ConfigEntry::Ptr getConfigEntry(const std::string& name_); 
public:
    ConfigManager();
    void initialise(const std::string& configfile_);
    using Ptr = std::shared_ptr<ConfigManager>; 
private:
    template<typename T> bool loadConfig(
            typename T::Ptr& config_, 
            std::string path_="", 
            XMLElement* xmlelement=nullptr
            );

    template<typename T> bool loadConfigs(std::map<std::string, typename T::Ptr>& configs_, std::string path_);

public:

    const TopicConfig::Ptr gettopicConfig(const std::string& key_) { 
        return (_topicConfigs.find(key_) != _topicConfigs.end()) ? _topicConfigs.at(key_) : nullptr; 
    }

    const FeedConfig::Ptr getfeedConfig(const std::string& key_) { 
        return (_feedConfigs.find(key_) != _feedConfigs.end()) ? _feedConfigs.at(key_) : nullptr; 
    }

};

} // cfg
#endif
