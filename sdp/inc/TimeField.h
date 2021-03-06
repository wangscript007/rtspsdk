/*****************************************************************************
//	SDP Parser Classes
//
//	Time Field Class
//
//	description:
//		represents SDP description time field
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

#ifndef __TIME_FIELD__H__
#define __TIME_FIELD__H__

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//	PoCo headers
#include "Poco/DateTime.h"

#include "sdp_parser.h"
#include "common.h"
#include "Field.h"

namespace SDP {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	TimeField class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class SDP_PARSER_API TimeField : public Field
    /// A Time represents a t= field contained within a TimeDescription. 
    /// 
    /// A Time specifies the start and stop times for a SessionDescription.
{
public:

	TimeField();
	/// Creates an empty TimeField.

	TimeField(const std::string & value);
	/// Creates a new TimeField according to the specified value string.

	TimeField(const Poco::DateTime & start, const Poco::DateTime & stop);
	/// Creates a new TimeField with the specified start and stop times.

	TimeField(const TimeField & timeField);
	/// Creates a copy of specified TimeField object.

	TimeField & operator=(const TimeField & timeField);
	/// Copies the specified TimeField object.

	Poco::DateTime getStartTime() const;
	/// Gets the start time.

	Poco::DateTime getStopTime() const;
	/// Gets the stop time.

	virtual std::string toString() const;
	/// Converts a Field to it's string representation.

private:

	void Init();
	/// Initializes internal object fields.

	Poco::DateTime		_start;
	Poco::DateTime		_stop;

};

} //	namespace SDP

#endif	//	__TIME_FIELD__H__

