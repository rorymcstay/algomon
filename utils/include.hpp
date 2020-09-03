#ifndef UTILS_INCLUDE
#define UTILS_INCLUDE

#include <string>
#include <stdexcept>
#include <fstream>


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
       }\
    private:


#define MVAR(type, var)\
    type _##var;

#define ENUM_MACRO_7(name, v1, v2, v3, v4, v5, v6, v7)\
    enum class name { Unknown##name, v1, v2, v3, v4, v5, v6, v7};\
    inline const char *enum2str(name value) { const char *name##Strings[] = { #v1, #v2, #v3, #v4, #v5, #v6, #v7}; return name##Strings[(int)value]; } \
    inline std::ostream& operator<<(std::ostream& stream_, name val_ ) {return stream_ << enum2str(val_);}    \
    template<> \
    inline name str2enum(const char* value){ return (enum2str(name::v1) == value) ? name::v1 :                     \
                                                    (enum2str(name::v2) == value) ? name::v2 :                     \
                                                    (enum2str(name::v3) == value) ? name::v3 :                     \
                                                    (enum2str(name::v4) == value) ? name::v4:                     \
                                                    (enum2str(name::v5) == value) ? name::v5:                     \
                                                    (enum2str(name::v6) == value) ? name::v6:                     \
                                                    (enum2str(name::v7) == value) ? name::v7 : name::Unknown##name; }  

#define ENUM_MACRO_5(name, v1, v2, v3, v4, v5)\
    enum class name { Unknown##name, v1, v2, v3, v4, v5 };\
    inline const char *enum2str(name value) { const char *name##Strings[] = { #v1, #v2, #v3, #v4, #v5}; return name##Strings[(int)value]; }  \
    inline std::ostream& operator<<(std::ostream& stream_, name val_ ) { return stream_ << enum2str(val_);}                                  \
    template<>                                                                                                                               \
    inline name str2enum(const char * value){ return (enum2str(name::v1) == value) ? name::v1 :                                     \
                                                     (enum2str(name::v2) == value) ? name::v2 :                                              \
                                                     (enum2str(name::v3) == value) ? name::v3 :                                              \
                                                     (enum2str(name::v4) == value) ? name::v4 :                                              \
                                                     (enum2str(name::v5) == value) ? name::v5 : name::Unknown##name; }

#define ENUM_MACRO_4(name, v1, v2, v3, v4 )\
    enum class name {Unknown##name, v1, v2, v3, v4, v5 };\
    inline const char *enum2str(name value) { const char *name##Strings[] = { #v1, #v2, #v3, #v4 }; return name##Strings[(int)value]; } \
    inline std::ostream& operator<<(std::ostream& stream_, name val_ ) { return stream_ << enum2str(val_);}    \
    template<> \
    inline name str2enum(const char * value){ return (enum2str(name::v1) == value) ? name::v1 :                     \
                                                     (enum2str(name::v2) == value) ? name::v2 :                     \
                                                     (enum2str(name::v3) == value) ? name::v3 :                     \
                                                     (enum2str(name::v4) == value) ? name::v4 : name::Unknown##name; }  
#define ENUM_MACRO_2(name, v1, v2)\
    enum class name {Unknown##name, v1,v2}; \
    inline const char *enum2str(name value) { const char *name##Strings[]={#v1, #v2}; return name##Strings[(int)value]; }\
    inline std::ostream& operator<<(std::ostream& stream_, name val_ ) { return stream_ << enum2str(val_);}    \
    template<> \
    inline name str2enum(const char * value) { return (enum2str(name::v1) == value) ? name::v1 :                     \
                                                     (enum2str(name::v2) == value) ? name::v2 : name::Unknown##name; } 
#define ENUM_MACRO_3(name, v1, v2, v3)\
    enum class name {Unknown##name, v1,v2, v3};\
    inline const char *enum2str(name value){ const char *name##Strings[]={#v1, #v2, #v3}; return name##Strings[(int)value];} \
    inline std::ostream& operator<<(std::ostream& stream_, name val_ ) { return stream_ << enum2str(val_);}    \
    template<> \
    inline name str2enum(const char * value){ return (enum2str(name::v1) == value) ? name::v1 :                     \
                                                     (enum2str(name::v2) == value) ? name::v2 :                     \
                                                     (enum2str(name::v3) == value) ? name::v3 : name::Unknown##name; } 
#define ENUM_MACRO_6(name, v1, v2, v3)\
    enum class name { Unknown##name, v1,v2, v3};\
    inline const char *enum2str(name value){ const char *name##Strings[]={#v1, #v2, #v3}; return name##Strings[(int)value];} \
    inline std::ostream& operator<<(std::ostream& stream_, name val_ ) { return stream_ << enum2str(val_);}    \
    template<> \
    inline name str2enum(const char * value){ return (enum2str(v1) == value) ? v1 :                     \
                                                     (enum2str(name::v2) == value) ? name::v2 :                     \
                                                     (enum2str(name::v3) == value) ? name::v3 :                     \
                                                     (enum2str(name::v4) == value) ? name::v4:                     \
                                                     (enum2str(name::v5) == value) ? name::v5:                     \
                                                     (enum2str(name::v6) == value) ? name::v6 : name::Unknown##name; }  
namespace domain
{
    template<typename T> inline const char* enum2str(T value) {return "";}
    template<typename T> inline T str2enum(const char* value) {return enum2str<T>(value);} 
}

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
