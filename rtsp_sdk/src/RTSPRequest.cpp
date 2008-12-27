/*****************************************************************************
//	RTSP SDK Base Classes
//
//	RTSP Request Message class
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


#include <cctype>

#include "Poco/Net/HTTPSession.h"
#include "Poco/Net/NetException.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/NumberFormatter.h"

#include "RTSPRequest.h"


using Poco::NumberFormatter;
using Poco::Net::NotAuthenticatedException;
using Poco::Net::NoMessageException;
using Poco::Net::MessageException;

namespace RTSP {

const std::string RTSPRequest::RTSP_NONE;
const std::string RTSPRequest::RTSP_DESCRIBE		= "DESCRIBE";
const std::string RTSPRequest::RTSP_ANNOUNCE		= "ANNOUNCE";
const std::string RTSPRequest::RTSP_GET_PARAMETER	= "GET_PARAMETER";
const std::string RTSPRequest::RTSP_OPTIONS			= "OPTIONS";
const std::string RTSPRequest::RTSP_PAUSE			= "PAUSE";
const std::string RTSPRequest::RTSP_PLAY			= "PLAY";
const std::string RTSPRequest::RTSP_RECORD			= "RECORD";
const std::string RTSPRequest::RTSP_REDIRECT		= "REDIRECT";
const std::string RTSPRequest::RTSP_SETUP			= "SETUP";
const std::string RTSPRequest::RTSP_SET_PARAMETER	= "SET_PARAMETER";
const std::string RTSPRequest::RTSP_TEARDOWN		= "TEARDOWN";

const std::string RTSPRequest::AUTHORIZATION = "Authorization";


RTSPRequest::RTSPRequest():
	_method(RTSP_NONE),
	_uri("/")
{
}

	
RTSPRequest::RTSPRequest(const std::string& version):
	RTSPMessage(version),
	_method(RTSP_NONE),
	_uri("/")
{
}

	
RTSPRequest::RTSPRequest(const std::string& method, const std::string& uri):
	_method(method),
	_uri(uri)
{
}


RTSPRequest::RTSPRequest(const std::string& method, const std::string& uri, const std::string& version):
	RTSPMessage(version),
	_method(method),
	_uri(uri)
{
}


RTSPRequest::~RTSPRequest()
{
}


void RTSPRequest::setMethod(const std::string& method)
{
	_method = method;
}


void RTSPRequest::setURI(const std::string& uri)
{
	_uri = uri;
}


bool RTSPRequest::hasCredentials() const
{
	return has(AUTHORIZATION);
}

	
void RTSPRequest::getCredentials(std::string& scheme, std::string& authInfo) const
{
	scheme.clear();
	authInfo.clear();
	if (has(AUTHORIZATION))
	{
		const std::string& auth = get(AUTHORIZATION);
		std::string::const_iterator it  = auth.begin();
		std::string::const_iterator end = auth.end();
		while (it != end && std::isspace(*it)) ++it;
		while (it != end && !std::isspace(*it)) scheme += *it++;
		while (it != end && std::isspace(*it)) ++it;
		while (it != end) authInfo += *it++;
	}
	else throw NotAuthenticatedException();
}

	
void RTSPRequest::setCredentials(const std::string& scheme, const std::string& authInfo)
{
	std::string auth(scheme);
	auth.append(" ");
	auth.append(authInfo);
	set(AUTHORIZATION, auth);
}


void RTSPRequest::write(std::ostream& ostr) const
{
	ostr << _method << " " << _uri << " " << getVersion() << "\r\n";
	RTSPMessage::write(ostr);
	ostr << "\r\n";
}


void RTSPRequest::read(std::istream& istr)
{
	static const int eof = std::char_traits<char>::eof();

	std::string method;
	std::string uri;
	std::string version;
	int ch = istr.get();
	if (ch == eof) throw NoMessageException();
	while (std::isspace(ch)) ch = istr.get();
	if (ch == eof) throw MessageException("No RTSP request header");
	while (!std::isspace(ch) && ch != eof && method.length() < MAX_METHOD_LENGTH) { method += (char) ch; ch = istr.get(); }
	if (!std::isspace(ch)) throw MessageException("RTSP request method invalid or too long");
	while (std::isspace(ch)) ch = istr.get();
	while (!std::isspace(ch) && ch != eof && uri.length() < MAX_URI_LENGTH) { uri += (char) ch; ch = istr.get(); }
	if (!std::isspace(ch)) throw MessageException("RTSP request URI invalid or too long");
	while (std::isspace(ch)) ch = istr.get();
	while (!std::isspace(ch) && ch != eof && version.length() < MAX_VERSION_LENGTH) { version += (char) ch; ch = istr.get(); }
	if (!std::isspace(ch)) throw MessageException("Invalid RTSP version string");
	while (ch != '\n' && ch != eof) { ch = istr.get(); }
	RTSPMessage::read(istr);
	ch = istr.get();
	while (ch != '\n' && ch != eof) { ch = istr.get(); }
	setMethod(method);
	setURI(uri);
	setVersion(version);
}

} // namespace RTSP

