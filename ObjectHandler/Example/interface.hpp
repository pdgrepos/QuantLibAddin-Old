/*
 Copyright (C) 2004 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef interface_h
#define interface_h

#include <boost/config.hpp>
#include <ObjectHandler/objecthandler.hpp>
#include <objectwidget.hpp>

using namespace ObjHandler;

Properties WIDGET_MAKE(
	const std::string &handle,
	const std::string &s,
	const int &i);
                                                                                
Properties WIDGET_UPDATE(
	const std::string &handle,
	const std::string &s,
	const int &i);

void QL_LOGFILE(
	const std::string &logFileName);

void QL_LOGMESSAGE(
	const std::string &msg);

#endif
