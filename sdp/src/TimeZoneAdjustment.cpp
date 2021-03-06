/*****************************************************************************
//	SDP Parser Classes
//
//	Time Zone Adjustment Class
//
//	revision of last commit:
//		$Rev$
//	author of last commit:
//		$Author$
//	date of last commit:
//		$Date$
//
//	created by Argenet {argenet@sibears.org}
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
******************************************************************************/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//	PoCo headers
#include "Poco/Timespan.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"

#include "NTPTime.h"
#include "TimeZoneAdjustment.h"

using std::string;

using Poco::Int64;
using Poco::DateTime;
using Poco::Timespan;
using Poco::NumberParser;
using Poco::NumberFormatter;
using Poco::SyntaxException;

namespace SDP {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	TimeZoneAdjustment class implementation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Public methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TimeZoneAdjustment :: TimeZoneAdjustment(const string & value)
{
	StringVec parts = split(value, ' ');

	try
	{
		Int64 ans = NumberParser::parse64(parts[0]);
		_adjustmentTime = NTPTime::getDateTime(ans);

	}
	catch(SyntaxException &)
	{
	}

	try
	{
		Int64 ans = NumberParser::parse64(parts[1]);
		_offset = (0 != ans) ? NTPTime::getTimeSpan(ans) : NTPTime::getTimeSpan(parts[1]);

	}
	catch(SyntaxException &)
	{
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TimeZoneAdjustment :: TimeZoneAdjustment(const DateTime & adjTime, const Timespan & offset)
	: _adjustmentTime(adjTime)
	, _offset(offset)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TimeZoneAdjustment :: TimeZoneAdjustment(const TimeZoneAdjustment & timeZoneAdjustment)
	: _adjustmentTime(timeZoneAdjustment._adjustmentTime)
	, _offset(timeZoneAdjustment._offset)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TimeZoneAdjustment & TimeZoneAdjustment :: operator=(const TimeZoneAdjustment & timeZoneAdjustment)
{
	if(&timeZoneAdjustment != this)
	{
		_adjustmentTime = timeZoneAdjustment._adjustmentTime;
		_offset = timeZoneAdjustment._offset;
	}

	return *this;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline DateTime TimeZoneAdjustment :: getAdjustmentTime() const
{
	return _adjustmentTime;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline void TimeZoneAdjustment :: setAdjustmentTime(const Poco::DateTime & adjTime)
{
	_adjustmentTime = adjTime;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline Timespan TimeZoneAdjustment :: getOffset() const
{
	return _offset;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline void TimeZoneAdjustment :: setOffset(const Poco::Timespan & offset)
{
	_offset = offset;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline std::string TimeZoneAdjustment :: toString() const
{
	return NumberFormatter::format(NTPTime::getNTPTime(_adjustmentTime)) +
		   " " + 
		   NumberFormatter::format(NTPTime::getNTPTime(_offset));
}

} //	namespace SDP
