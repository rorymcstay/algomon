#ifndef UTILS_INCLUDE
#define UTILS_INCLUDE

#include <string>
#include <stdexcept>


#define GETSET(type, var)\
    private:\
       type _##var;\
    public:\
       const type& get##var() const\
       {\
          return _##var;\
       }\
       void set##var(const type& val)\
       {\
          _##var = val;\
       }

#define MVAR(type, var)\
    type _##var;\

#define ENUM_MACRO_7(name, v1, v2, v3, v4, v5, v6, v7)\
    enum class name { v1, v2, v3, v4, v5, v6, v7};\
    inline const char *enum2str(name value) { const char *name##Strings[] = { #v1, #v2, #v3, #v4, #v5, #v6, #v7}; return name##Strings[(int)value]; }


#define ENUM_MACRO_2(name, v1, v2)\
    enum class name {v1,v2};\
    inline const char *enum2str(name value){ const char *name##Strings[]={#v1, #v2}; return name##Strings[(int)value];}
        
#define ENUM_MACRO_3(name, v1, v2, v3)\
    enum class name {v1,v2, v3};\
    inline const char *enum2str(name value){ const char *name##Strings[]={#v1, #v2, #v3}; return name##Strings[(int)value];}


namespace utils
{
    template<typename T>
    inline T fromString(std::string str_);

    template<>
    inline double fromString<double>(std::string str_)
    {
        try
        {
            return std::stod(str_);
        }
        catch (std::invalid_argument& e)
        {
            return double(-1.0);
        }
    }
    
    template<>
    inline int fromString<int>(std::string str_)
    {
        try
        {
            return std::stoi(str_);
        }
        catch (std::invalid_argument& e)
        {
            return int(-1);
        }
    }

}

#endif
