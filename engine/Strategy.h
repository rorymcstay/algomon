#include <memory>

class Strategy
{
public:
    Strategy();
    ~Strategy();
    using Ptr = std::shared_ptr<Strategy>;
};
