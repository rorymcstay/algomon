#ifndef UTILS_INCLUDE
#define UTILS_INCLUDE

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
        
#endif
