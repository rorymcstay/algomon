#define GETSET(type, var)\
    private:\
       type _##var;\
    public:\
       type get##var()\
       {\
          return _##var;\
       }\
       void set##var(type val)\
       {\
          _##var = val;\
       }

#define MVAR(type, var)\
    type _##var;\

#define QUOTECOMPARISON(op, memVar)\
    public:\
        bool operator ##op(const Quote &a, const Quote &b)\
        {\
            return a._##memVar == b.get##memVar;\
        }\

#define LOG(message)
