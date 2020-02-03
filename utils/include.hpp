#define GETSET(type, var)\
    private:\
       type _##var;\
    public:\
       const type& get##var()\
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
    const char *name##Strings[] = { #v1, #v2, #v3, #v4, #v5, #v6, #v7};\
    const char *enum2str(name value) { return name##Strings[(int)value]; }


#define ENUM_MACRO_2(name, v1, v2)\
    enum class name {v1,v2};\
    const char *name##Strings[]={#v1, #v2};\
    const char *enum2str(name value){ return name##Strings[(int)value];}
                
