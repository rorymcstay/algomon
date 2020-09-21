#include "FixServer.h"

namespace testfwk
{
    // Router
    TestServerRouter::TestServerRouter(TestFixServer& session) : _session(session) 
    {
        LOG_INFO("Initiated FIX session!");
    }
 
    // Server
    /*
bool TestServerRouter::operator() (const FIX8::FIX44::NewOrderSingle *msg) const
{        
    FIX44::ExecutionReport *er(new FIX44::ExecutionReport);
    msg->copy_legal(er);

    std::ostringstream oistr;
    static unsigned oid(0), eoid(0);
    FIX44::OrderQty qty;
    msg->get(qty);
    oistr << "ord" << ++oid;
    *er << new FIX44::OrderID(oistr.str())
        << new FIX44::ExecType(FIX44::ExecType_NEW)
        << new FIX44::OrdStatus(FIX44::OrdStatus_NEW)
        << new FIX44::LeavesQty(qty())
        << new FIX44::CumQty(0.)
        << new FIX44::AvgPx(0.)
        << new FIX44::LastCapacity('5')
        << new FIX44::ReportToExch('Y')
        << new FIX44::ExecID(oistr.str());
    msg->push_unknown(er);
    _session.send(er);

    unsigned remaining_qty(qty()), cum_qty(0);
    while (remaining_qty > 0)
    {
        unsigned trdqty(getrandom(remaining_qty));
        if (!trdqty)
            trdqty = 1;
        er = new FIX44::ExecutionReport;
        msg->copy_legal(er);
        std::ostringstream eistr;
        eistr << "exec" << ++eoid;
        remaining_qty -= trdqty;
        cum_qty += trdqty;
        *er << new FIX44::OrderID(oistr.str())
            << new FIX44::ExecID(eistr.str())
            << new FIX44::ExecType(FIX44::ExecType_NEW)
            << new FIX44::OrdStatus(remaining_qty == trdqty ? FIX44::OrdStatus_FILLED : FIX44::OrdStatus_PARTIAL)
            << new FIX44::LeavesQty(remaining_qty)
            << new FIX44::CumQty(cum_qty)
            << new FIX44::LastQty(trdqty)
            << new FIX44::AvgPx(price());
        _session.send(er);
    }

    return true;
}*/

}
