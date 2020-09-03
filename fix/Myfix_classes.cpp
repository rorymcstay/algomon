//-------------------------------------------------------------------------------------------------
// *** f8c generated file: DO NOT EDIT! Created: 2020-08-31 14:48:54 ***
//-------------------------------------------------------------------------------------------------
/*

Fix8 is released under the GNU LESSER GENERAL PUBLIC LICENSE Version 3.

Fix8 Open Source FIX Engine.
Copyright (C) 2010-20 David L. Dight <fix@fix8.org>

Fix8 is free software: you can  redistribute it and / or modify  it under the  terms of the
GNU Lesser General  Public License as  published  by the Free  Software Foundation,  either
version 3 of the License, or (at your option) any later version.

Fix8 is distributed in the hope  that it will be useful, but WITHOUT ANY WARRANTY;  without
even the  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

You should  have received a copy of the GNU Lesser General Public  License along with Fix8.
If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************************
*                Special note for Fix8 compiler generated source code                     *
*                                                                                         *
* Binary works  that are the results of compilation of code that is generated by the Fix8 *
* compiler  can be released  without releasing your  source code as  long as your  binary *
* links dynamically  against an  unmodified version of the Fix8 library.  You are however *
* required to leave the copyright text in the generated code.                             *
*                                                                                         *
*******************************************************************************************

BECAUSE THE PROGRAM IS  LICENSED FREE OF  CHARGE, THERE IS NO  WARRANTY FOR THE PROGRAM, TO
THE EXTENT  PERMITTED  BY  APPLICABLE  LAW.  EXCEPT WHEN  OTHERWISE  STATED IN  WRITING THE
COPYRIGHT HOLDERS AND/OR OTHER PARTIES  PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY
KIND,  EITHER EXPRESSED   OR   IMPLIED,  INCLUDING,  BUT   NOT  LIMITED   TO,  THE  IMPLIED
WARRANTIES  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS TO
THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE,
YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

IN NO EVENT UNLESS REQUIRED  BY APPLICABLE LAW  OR AGREED TO IN  WRITING WILL ANY COPYRIGHT
HOLDER, OR  ANY OTHER PARTY  WHO MAY MODIFY  AND/OR REDISTRIBUTE  THE PROGRAM AS  PERMITTED
ABOVE,  BE  LIABLE  TO  YOU  FOR  DAMAGES,  INCLUDING  ANY  GENERAL, SPECIAL, INCIDENTAL OR
CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT
NOT LIMITED TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR
THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF SUCH
HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

*/

//-------------------------------------------------------------------------------------------------
#include <fix8/f8config.h>
#if defined FIX8_MAGIC_NUM && FIX8_MAGIC_NUM > 16793600L
#error Myfix_classes.cpp version 1.4.0 is out of date. Please regenerate with f8c.
#endif
//-------------------------------------------------------------------------------------------------
// Myfix_classes.cpp
//-------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <iterator>
#include <algorithm>
#include <cerrno>
#include <string.h>
// f8 includes
#include <fix8/f8exception.hpp>
#include <fix8/hypersleep.hpp>
#include <fix8/mpmc.hpp>
#include <fix8/thread.hpp>
#include <fix8/f8types.hpp>
#include <fix8/f8utils.hpp>
#include <fix8/tickval.hpp>
#include <fix8/logger.hpp>
#include <fix8/traits.hpp>
#include <fix8/field.hpp>
#include <fix8/message.hpp>
#include "Myfix_types.hpp"
#include "Myfix_router.hpp"
#include "Myfix_classes.hpp"
//-------------------------------------------------------------------------------------------------
namespace FIX8 {
namespace FIX4400 {

namespace {

//-------------------------------------------------------------------------------------------------

const char *cn[] // Component names
{
   "",
   "CommissionData", // 1
   "DiscretionInstructions", // 2
   "FinancingDetails", // 3
   "Instrument", // 4
   "InstrumentExtension", // 5
   "InstrumentLeg", // 6
   "LegBenchmarkCurveData", // 7
   "LegStipulations", // 8
   "NestedParties", // 9
   "NestedParties2", // 10
   "NestedParties3", // 11
   "OrderQtyData", // 12
   "Parties", // 13
   "PegInstructions", // 14
   "PositionAmountData", // 15
   "PositionQty", // 16
   "SettlInstructionsData", // 17
   "SettlParties", // 18
   "SpreadOrBenchmarkCurveData", // 19
   "Stipulations", // 20
   "TrdRegTimestamps", // 21
   "UnderlyingInstrument", // 22
   "UnderlyingStipulations", // 23
   "YieldData", // 24
};

} // namespace

//-------------------------------------------------------------------------------------------------
const FIX4400::Myfix_BaseMsgEntry::Pair msgpairs[] 
{
   { "0", { Type2Type<FIX4400::Heartbeat>(), "Heartbeat" } },
   { "1", { Type2Type<FIX4400::TestRequest>(), "TestRequest" } },
   { "2", { Type2Type<FIX4400::ResendRequest>(), "ResendRequest" } },
   { "3", { Type2Type<FIX4400::Reject>(), "Reject" } },
   { "4", { Type2Type<FIX4400::SequenceReset>(), "SequenceReset" } },
   { "5", { Type2Type<FIX4400::Logout>(), "Logout" } },
   { "6", { Type2Type<FIX4400::IOI>(), "IOI" } },
   { "7", { Type2Type<FIX4400::Advertisement>(), "Advertisement" } },
   { "8", { Type2Type<FIX4400::ExecutionReport>(), "ExecutionReport" } },
   { "9", { Type2Type<FIX4400::OrderCancelReject>(), "OrderCancelReject" } },
   { "A", { Type2Type<FIX4400::Logon>(), "Logon" } },
   { "AA", { Type2Type<FIX4400::DerivativeSecurityList>(), "DerivativeSecurityList" } },
   { "AB", { Type2Type<FIX4400::NewOrderMultileg>(), "NewOrderMultileg" } },
   { "AC", { Type2Type<FIX4400::MultilegOrderCancelReplace>(), "MultilegOrderCancelReplace" } },
   { "AD", { Type2Type<FIX4400::TradeCaptureReportRequest>(), "TradeCaptureReportRequest" } },
   { "AE", { Type2Type<FIX4400::TradeCaptureReport>(), "TradeCaptureReport" } },
   { "AF", { Type2Type<FIX4400::OrderMassStatusRequest>(), "OrderMassStatusRequest" } },
   { "AG", { Type2Type<FIX4400::QuoteRequestReject>(), "QuoteRequestReject" } },
   { "AH", { Type2Type<FIX4400::RFQRequest>(), "RFQRequest" } },
   { "AI", { Type2Type<FIX4400::QuoteStatusReport>(), "QuoteStatusReport" } },
   { "AJ", { Type2Type<FIX4400::QuoteResponse>(), "QuoteResponse" } },
   { "AK", { Type2Type<FIX4400::Confirmation>(), "Confirmation" } },
   { "AL", { Type2Type<FIX4400::PositionMaintenanceRequest>(), "PositionMaintenanceRequest" } },
   { "AM", { Type2Type<FIX4400::PositionMaintenanceReport>(), "PositionMaintenanceReport" } },
   { "AN", { Type2Type<FIX4400::RequestForPositions>(), "RequestForPositions" } },
   { "AO", { Type2Type<FIX4400::RequestForPositionsAck>(), "RequestForPositionsAck" } },
   { "AP", { Type2Type<FIX4400::PositionReport>(), "PositionReport" } },
   { "AQ", { Type2Type<FIX4400::TradeCaptureReportRequestAck>(), "TradeCaptureReportRequestAck" } },
   { "AR", { Type2Type<FIX4400::TradeCaptureReportAck>(), "TradeCaptureReportAck" } },
   { "AS", { Type2Type<FIX4400::AllocationReport>(), "AllocationReport" } },
   { "AT", { Type2Type<FIX4400::AllocationReportAck>(), "AllocationReportAck" } },
   { "AU", { Type2Type<FIX4400::ConfirmationAck>(), "ConfirmationAck" } },
   { "AV", { Type2Type<FIX4400::SettlementInstructionRequest>(), "SettlementInstructionRequest" } },
   { "AW", { Type2Type<FIX4400::AssignmentReport>(), "AssignmentReport" } },
   { "AX", { Type2Type<FIX4400::CollateralRequest>(), "CollateralRequest" } },
   { "AY", { Type2Type<FIX4400::CollateralAssignment>(), "CollateralAssignment" } },
   { "AZ", { Type2Type<FIX4400::CollateralResponse>(), "CollateralResponse" } },
   { "B", { Type2Type<FIX4400::News>(), "News" } },
   { "BA", { Type2Type<FIX4400::CollateralReport>(), "CollateralReport" } },
   { "BB", { Type2Type<FIX4400::CollateralInquiry>(), "CollateralInquiry" } },
   { "BC", { Type2Type<FIX4400::NetworkCounterpartySystemStatusRequest>(), "NetworkCounterpartySystemStatusRequest" } },
   { "BD", { Type2Type<FIX4400::NetworkCounterpartySystemStatusResponse>(), "NetworkCounterpartySystemStatusResponse" } },
   { "BE", { Type2Type<FIX4400::UserRequest>(), "UserRequest" } },
   { "BF", { Type2Type<FIX4400::UserResponse>(), "UserResponse" } },
   { "BG", { Type2Type<FIX4400::CollateralInquiryAck>(), "CollateralInquiryAck" } },
   { "BH", { Type2Type<FIX4400::ConfirmationRequest>(), "ConfirmationRequest" } },
   { "C", { Type2Type<FIX4400::Email>(), "Email" } },
   { "D", { Type2Type<FIX4400::NewOrderSingle>(), "NewOrderSingle" } },
   { "E", { Type2Type<FIX4400::NewOrderList>(), "NewOrderList" } },
   { "F", { Type2Type<FIX4400::OrderCancelRequest>(), "OrderCancelRequest" } },
   { "G", { Type2Type<FIX4400::OrderCancelReplaceRequest>(), "OrderCancelReplaceRequest" } },
   { "H", { Type2Type<FIX4400::OrderStatusRequest>(), "OrderStatusRequest" } },
   { "J", { Type2Type<FIX4400::AllocationInstruction>(), "AllocationInstruction" } },
   { "K", { Type2Type<FIX4400::ListCancelRequest>(), "ListCancelRequest" } },
   { "L", { Type2Type<FIX4400::ListExecute>(), "ListExecute" } },
   { "M", { Type2Type<FIX4400::ListStatusRequest>(), "ListStatusRequest" } },
   { "N", { Type2Type<FIX4400::ListStatus>(), "ListStatus" } },
   { "P", { Type2Type<FIX4400::AllocationInstructionAck>(), "AllocationInstructionAck" } },
   { "Q", { Type2Type<FIX4400::DontKnowTrade>(), "DontKnowTrade" } },
   { "R", { Type2Type<FIX4400::QuoteRequest>(), "QuoteRequest" } },
   { "S", { Type2Type<FIX4400::Quote>(), "Quote" } },
   { "T", { Type2Type<FIX4400::SettlementInstructions>(), "SettlementInstructions" } },
   { "V", { Type2Type<FIX4400::MarketDataRequest>(), "MarketDataRequest" } },
   { "W", { Type2Type<FIX4400::MarketDataSnapshotFullRefresh>(), "MarketDataSnapshotFullRefresh" } },
   { "X", { Type2Type<FIX4400::MarketDataIncrementalRefresh>(), "MarketDataIncrementalRefresh" } },
   { "Y", { Type2Type<FIX4400::MarketDataRequestReject>(), "MarketDataRequestReject" } },
   { "Z", { Type2Type<FIX4400::QuoteCancel>(), "QuoteCancel" } },
   { "a", { Type2Type<FIX4400::QuoteStatusRequest>(), "QuoteStatusRequest" } },
   { "b", { Type2Type<FIX4400::MassQuoteAcknowledgement>(), "MassQuoteAcknowledgement" } },
   { "c", { Type2Type<FIX4400::SecurityDefinitionRequest>(), "SecurityDefinitionRequest" } },
   { "d", { Type2Type<FIX4400::SecurityDefinition>(), "SecurityDefinition" } },
   { "e", { Type2Type<FIX4400::SecurityStatusRequest>(), "SecurityStatusRequest" } },
   { "f", { Type2Type<FIX4400::SecurityStatus>(), "SecurityStatus" } },
   { "g", { Type2Type<FIX4400::TradingSessionStatusRequest>(), "TradingSessionStatusRequest" } },
   { "h", { Type2Type<FIX4400::TradingSessionStatus>(), "TradingSessionStatus" } },
   { "header", { Type2Type<FIX4400::header, bool>(), "header" } },
   { "i", { Type2Type<FIX4400::MassQuote>(), "MassQuote" } },
   { "j", { Type2Type<FIX4400::BusinessMessageReject>(), "BusinessMessageReject" } },
   { "k", { Type2Type<FIX4400::BidRequest>(), "BidRequest" } },
   { "l", { Type2Type<FIX4400::BidResponse>(), "BidResponse" } },
   { "m", { Type2Type<FIX4400::ListStrikePrice>(), "ListStrikePrice" } },
   { "o", { Type2Type<FIX4400::RegistrationInstructions>(), "RegistrationInstructions" } },
   { "p", { Type2Type<FIX4400::RegistrationInstructionsResponse>(), "RegistrationInstructionsResponse" } },
   { "q", { Type2Type<FIX4400::OrderMassCancelRequest>(), "OrderMassCancelRequest" } },
   { "r", { Type2Type<FIX4400::OrderMassCancelReport>(), "OrderMassCancelReport" } },
   { "s", { Type2Type<FIX4400::NewOrderCross>(), "NewOrderCross" } },
   { "t", { Type2Type<FIX4400::CrossOrderCancelReplaceRequest>(), "CrossOrderCancelReplaceRequest" } },
   { "trailer", { Type2Type<FIX4400::trailer, bool>(), "trailer" } },
   { "u", { Type2Type<FIX4400::CrossOrderCancelRequest>(), "CrossOrderCancelRequest" } },
   { "v", { Type2Type<FIX4400::SecurityTypeRequest>(), "SecurityTypeRequest" } },
   { "w", { Type2Type<FIX4400::SecurityTypes>(), "SecurityTypes" } },
   { "x", { Type2Type<FIX4400::SecurityListRequest>(), "SecurityListRequest" } },
   { "y", { Type2Type<FIX4400::SecurityList>(), "SecurityList" } },
   { "z", { Type2Type<FIX4400::DerivativeSecurityListRequest>(), "DerivativeSecurityListRequest" } }
}; // 94

extern const Myfix_BaseEntry::Pair fldpairs[];

/// Compiler generated metadata object, accessed through this function.
const F8MetaCntx& ctx() // avoid SIOF
{
   static const Myfix_BaseMsgEntry bme(msgpairs, 94);
   static const Myfix_BaseEntry be(fldpairs, 910);
   static const F8MetaCntx _ctx(4400, bme, be, cn, "FIX.4.4");
   return _ctx;
}

} // namespace FIX4400

// Compiler generated metadata object accessible outside namespace through this function.
extern "C"
{
   const F8MetaCntx& FIX4400_ctx() { return FIX4400::ctx(); }
}

} // namespace FIX8
