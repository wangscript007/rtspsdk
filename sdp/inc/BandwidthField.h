/*****************************************************************************
//	SDP Parser Classes
//
//	Bandwidth Field Class
//
//	description:
//		represents SDP description bandwidth field
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

#ifndef __BANDWIDTH_FIELD__H__
#define __BANDWIDTH_FIELD__H__

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "sdp_parser.h"
#include "common.h"
#include "Field.h"

namespace SDP {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	BandwidthField class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class SDP_PARSER_API BandwidthField : public Field
    /// A Bandwidth represents the b= field within MediaDescription and SessionDescription.
    /// 
    /// This specifies the proposed bandwidth to be used by the session or media, and is optional.
    /// Multiple bandwidth specifiers of different types may be associated with the same
    /// SessionDescription. Each consists of a token type and an integer value measuring the
    /// bandwidth in kilobits per second.
{
public:

	BandwidthField();
	/// Creates an empty BandwidthField.

	BandwidthField(const std::string & value);
	/// Creates a new BandwidthField according to the specified value string.

	BandwidthField(const std::string & modifier, int bandwidth);
	/// Creates a new BandwidthField with the specified bandwidth modifier 
	/// (usually either "CT" or "AS") and the maximum bandwidth in kbps.

	BandwidthField(const BandwidthField & bandwidthField);
	/// Creates a copy of specified BandwidthField object.

	BandwidthField & operator=(const BandwidthField & bandwidthField);
	/// Copies the specified BandwidthField object.

	std::string getModifier() const;
	/// Gets the bandwidth modifier.

	int getBandwidth() const;
	/// Gets the bandwidth value in kbps.

	virtual std::string getValue() const;
	/// Gets the value portion of this field.

private:

	std::string			_modifier;
	int					_bandwidth;

};

} //	namespace SDP

#endif	//	__BANDWIDTH_FIELD__H__

