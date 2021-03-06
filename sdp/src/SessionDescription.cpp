/*****************************************************************************
//	SDP Parser Classes
//
//	Session Description Class
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
#include "Poco/Util/OptionException.h"

#include "FieldFactory.h"
#include "SessionDescription.h"

using std::string;

using Poco::Util::InvalidArgumentException;

namespace SDP {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	SessionDescription class implementation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Public methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SessionDescription :: SessionDescription(const OriginField & originator,
										 const SessionNameField & sessionName,
										 const TimeVec & times)
	: _version(0)
{
	if("" == originator.getValue())
	{
		throw new InvalidArgumentException("SessionDescription ctor() - originator can't be empty!");
	}
	if("" == sessionName.getValue())
	{
		throw new InvalidArgumentException("SessionDescription ctor() - invalid session name!");
	}
	if(times.size() < 1)
	{
		throw new InvalidArgumentException("SessionDescription ctor() - at least one TimeDescription must be included!");
	}

	_originator = originator;
	_name = sessionName;
	_times = times;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SessionDescription :: SessionDescription(const string & sessionDescription)
{
	StringVec lines = split(sessionDescription, "\r\n");

	//	last line seem to be empty, 'cause descriptions have to finish with
	//	"\r\n" sequence; if so, remove it
	if("" == lines.back())
	{
		lines.pop_back();
	}
	
	//	create description fields from strings
	Field * pField = FieldFactory::CreateInstance(lines[0]);
	_version = * dynamic_cast<VersionField *>(pField);
	FieldFactory::DestroyInstance(pField);

	pField = FieldFactory::CreateInstance(lines[1]);
	_originator = * dynamic_cast<OriginField *>(pField);
	FieldFactory::DestroyInstance(pField);

	pField = FieldFactory::CreateInstance(lines[2]);
	_name = * dynamic_cast<SessionNameField *>(pField);
	FieldFactory::DestroyInstance(pField);

	for(size_t i = 3 ; i < lines.size() ; ++i)
	{
		pField = FieldFactory::CreateInstance(lines[i]);
		switch(lines[i][0])
		{
			case 't':
				{
					bool continueSearch = true;
					string timeString = lines[i];
					while(continueSearch)
					{
						if(i + 1 < lines.size())
						{
							if('r' == lines[i + 1][0] || 't' == lines[i + 1][0])
							{
								++i;
								timeString += "\r\n" + lines[i];
							}
							else
							{
								continueSearch = false;
							}
						}
						else
						{
							continueSearch = false;
						}
					}
					_times.push_back(TimeDescription(timeString));
				}

				break;

			case 'm':
				{
					bool continueSearch = true;
					string mediaString = lines[i];
					while(continueSearch)
					{
						if(i + 1 < lines.size())
						{
							if('m' != lines[i + 1][0])
							{
								++i;
								mediaString += "\r\n" + lines[i];
							}
							else
							{
								continueSearch = false;
							}
						}
						else
						{
							continueSearch = false;
						}
					}
					_media.push_back(MediaDescription(mediaString));
				}
				break;

			case 'i':
				_description = * dynamic_cast<InfoField *>(pField);
						
				break;

			case 'u':
				_uri = * dynamic_cast<URIField *>(pField);
						
				break;

			case 'e':
				_email = * dynamic_cast<EMailField *>(pField);
						
				break;

			case 'p':
				_phone = * dynamic_cast<PhoneField *>(pField);
						
				break;

			case 'c':
				_connectionInfo = * dynamic_cast<ConnectionField *>(pField);
						
				break;

			case 'b':
				_bandwidth = * dynamic_cast<BandwidthField *>(pField);
						
				break;

			case 'z':
				_timeZoneAdjustments.push_back(* dynamic_cast<TimeZoneAdjustmentField *>(pField));
						
				break;
			case 'k':
				_encryptionKey = * dynamic_cast<KeyField *>(pField);
						
				break;

			case 'a':
				_attributes.push_back(* dynamic_cast<AttributeField *>(pField));
						
				break;
		}

		FieldFactory::DestroyInstance(pField);
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SessionDescription :: SessionDescription(const SessionDescription & sessionDescription)
	: _version(sessionDescription._version)
	, _originator(sessionDescription._originator)
	, _name(sessionDescription._name)
	, _description(sessionDescription._description)
	, _uri(sessionDescription._uri)
	, _email(sessionDescription._email)
	, _phone(sessionDescription._phone)
	, _connectionInfo(sessionDescription._connectionInfo)
	, _bandwidth(sessionDescription._bandwidth)
	, _times(sessionDescription._times)
	, _timeZoneAdjustments(sessionDescription._timeZoneAdjustments)
	, _encryptionKey(sessionDescription._encryptionKey)
	, _attributes(sessionDescription._attributes)
	, _media(sessionDescription._media)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SessionDescription & SessionDescription :: operator=(const SessionDescription & sessionDescription)
{
	if(&sessionDescription != this)
	{
		_version = sessionDescription._version;
		_originator = sessionDescription._originator;
		_name = sessionDescription._name;
		_description = sessionDescription._description;
		_uri = sessionDescription._uri;
		_email = sessionDescription._email;
		_phone = sessionDescription._phone;
		_connectionInfo = sessionDescription._connectionInfo;
		_bandwidth = sessionDescription._bandwidth;
		_times = sessionDescription._times;
		_timeZoneAdjustments = sessionDescription._timeZoneAdjustments;
		_encryptionKey = sessionDescription._encryptionKey;
		_attributes = sessionDescription._attributes;
		_media = sessionDescription._media;
	}

	return *this;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline VersionField SessionDescription :: getVersion() const
{
	return _version;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline OriginField SessionDescription :: getOriginator() const
{
	return _originator;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setOriginator(const OriginField & originator)
{
	_originator = originator;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline SessionNameField SessionDescription :: getName() const
{
	return _name;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setName(const SessionNameField & name)
{
	_name = name;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline InfoField SessionDescription :: getDescription() const
{
	return _description;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setDescription(const InfoField & description)
{
	_description = description; 
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline URIField SessionDescription :: getURI() const
{
	return _uri;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setURI(const URIField & uri)
{
	_uri = uri;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline EMailField SessionDescription :: getEMail() const
{
	return _email;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setEMail(const EMailField & email)
{
	_email = email;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline PhoneField SessionDescription :: getPhoneNumber() const
{
	return _phone;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setPhoneNumber(const PhoneField & phone)
{
	_phone = phone;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline ConnectionField SessionDescription :: getConnectionInfo() const
{
	return _connectionInfo;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setConnectionInfo(const ConnectionField & connectionInfo)
{
	_connectionInfo = connectionInfo;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline BandwidthField SessionDescription :: getBandwidth() const
{
	return _bandwidth;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setBandwidth(BandwidthField & bandwidth)
{
	_bandwidth = bandwidth;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline TimeVec SessionDescription :: getTimes() const
{
	return _times;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setTimes(const TimeVec & times)
{
	_times = times;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline TimeZoneAdjustmentFieldVec SessionDescription :: getTimeZoneAdjustments() const
{
	return _timeZoneAdjustments;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setTimeZoneAdjustments(const TimeZoneAdjustmentFieldVec & timeZoneAdjustments)
{
	_timeZoneAdjustments = timeZoneAdjustments;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline KeyField SessionDescription :: getEncryptionKey() const
{
	return _encryptionKey;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setEncryptionKey(const KeyField & encryptionKey)
{
	_encryptionKey = encryptionKey;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline AttributeVec SessionDescription :: getAttributes() const
{
	return _attributes;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setAttributes(const AttributeVec & attributes)
{
	_attributes = attributes;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline MediaVec SessionDescription :: getMedia() const
{
	return _media;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SessionDescription :: setMedia(const MediaVec & media)
{
	_media = media;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline size_t SessionDescription :: getMediaCount() const
{
	return _media.size();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

std::string SessionDescription :: toString() const
{
	string str = _version.toString() + "\r\n";
	if("" != _originator.toString())
	{
		str += _originator.toString() + "\r\n";
	}
	if("" != _name.toString())
	{
		str += _name.toString() + "\r\n";
	}
	if("" != _description.toString())
	{
		str += _description.toString() + "\r\n";
	}
	if("" != _uri.toString())
	{
		str += _uri.toString() + "\r\n";
	}
	if("" != _email.toString())
	{
		str += _email.toString() + "\r\n";
	}
	if("" != _phone.toString())
	{
		str += _phone.toString() + "\r\n";
	}
	if("" != _connectionInfo.toString())
	{
		str += _connectionInfo.toString() + "\r\n";
	}
	if("" != _bandwidth.toString())
	{
		str += _bandwidth.toString() + "\r\n";
	}

	for(TimeVec::const_iterator iter = _times.begin() ;
		_times.end() != iter ;
		++iter)
	{
		if("" != iter->toString())
		{
			str += iter->toString() + "\r\n";
		}
	}

	for(TimeZoneAdjustmentFieldVec::const_iterator iter = _timeZoneAdjustments.begin() ;
		_timeZoneAdjustments.end() != iter ;
		++iter)
	{
		if("" != iter->toString())
		{
			str += iter->toString() + "\r\n";
		}
	}

	for(AttributeVec::const_iterator iter = _attributes.begin() ;
		_attributes.end() != iter ;
		++iter)
	{
		if("" != iter->toString())
		{
			str += iter->toString() + "\r\n";
		}
	}

	for(MediaVec::const_iterator iter = _media.begin() ;
		_media.end() != iter ;
		++iter)
	{
		if("" != iter->toString())
		{
			str += iter->toString() + "\r\n";
		}
	}

	return str;
}

} //	namespace SDP
