namespace domain
{
class TradeMessage: Data
{
    typedef int orderid_t;
    GETSET(MessageType, type);
    GETSET(orderid_t, oid);
    GETSET(double, timestamp);
    GETSET(Quote, quote);

public:
    TradeMessage(std::vector<std::string> data_);

    std::ostream& operator<<(std::ostream& out)
    {
        out << "Message type: " << enum2str(_type);
    }
};
}
