/*****************************************************************************
//	SDP Parser Classes
//
//	Time Zone Adjustment Class
//
//	description:
//		represents time zone adjustment
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

#ifndef __TIME_ZONE_ADJUSTMENT__H__
#define __TIME_ZONE_ADJUSTMENT__H__

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//	PoCo headers
#include "Poco/DateTime.h"

#include "sdp_parser.h"
#include "common.h"

namespace SDP {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	TimeZoneAdjustment class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class SDP_PARSER_API TimeZoneAdjustment
    /// From RFC 2327:
    /// To schedule a repeated session which spans a change from daylight-
    /// saving time to standard time or vice-versa, it is necessary to
    /// specify offsets from the base repeat times. This is required
    /// because different time zones change time at different times of day,
    /// different countries change to or from daylight time on different
    /// dates, and some countries do not have daylight saving time at all.
    /// 
    /// Thus in order to schedule a session that is at the same time winter
    /// and summer, it must be possible to specify unambiguously by whose
    /// time zone a session is scheduled.  To simplify this task for
    /// receivers, we allow the sender to specify the NTP time that a time
    /// zone adjustment happens and the offset from the time when the
    /// session was first scheduled.  The "z" field allows the sender to
    /// specify a list of these adjustment times and offsets from the base
    /// time.
{
public:

	TimeZoneAdjustment(const std::string & value);
	/// Creates a new TimeZoneAdjustment according to the value
	///	portion of the field.

	TimeZoneAdjustment(const Poco::DateTime & time, const Poco::Timespan & offset);
	/// Instantiates a new TimeZoneAdjustment with the specified time
	/// the adjustment takes place and the amount of time to adjust.

	TimeZoneAdjustment(const TimeZoneAdjustment & timeZoneAdjustment);
	/// Creates a copy of specified TimeZoneAdjustment object.

	TimeZoneAdjustment & operator=(const TimeZoneAdjustment & timeZoneAdjustment);
	/// Copies the specified TimeZoneAdjustment object.

	Poco::DateTime getAdjustmentTime() const;
	/// Gets the time of the adjustment.

	void setAdjustmentTime(const Poco::DateTime & adjTime);
	/// Sets the time of the adjustment.

	Poco::Timespan getOffset() const;
	/// Gets the amount of time to adjust calculations from the base time.

	void setOffset(const Poco::Timespan & offset);
	/// Sets the amount of time to adjust calculations from the base time.

	std::string toString() const;
	/// Converts TimeZoneAdjustment to a string.

private:

	Poco::DateTime			_adjustmentTime;
	Poco::Timespan			_offset;

};

} //	namespace SDP

#endif	//	__TIME_ZONE_ADJUSTMENT__H__

