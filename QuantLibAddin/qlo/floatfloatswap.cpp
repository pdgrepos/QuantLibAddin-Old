/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2006, 2011, 2015 Ferdinando Ametrano
 Copyright (C) 2005 Aurelien Chanudet
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2006 Katiuscia Manzoni

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#if defined(HAVE_CONFIG_H)
    #include <qlo/config.hpp>
#endif

#include <ql/instruments/floatfloatswap.hpp>
#include <qlo/floatfloatswap.hpp>

using ObjectHandler::ValueObject;
using ObjectHandler::property_t;

namespace QuantLibAddin {
	
	        FloatFloatSwap::FloatFloatSwap(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::VanillaSwap::Type type, const QuantLib::Real nominal1,
            const QuantLib::Real nominal2, const boost::shared_ptr<QuantLib::Schedule> &schedule1,
            const boost::shared_ptr<QuantLib::InterestRateIndex> &index1,
            const QuantLib::DayCounter &dayCount1, const boost::shared_ptr<QuantLib::Schedule> &schedule2,
            const boost::shared_ptr<QuantLib::InterestRateIndex> &index2,
            const QuantLib::DayCounter &dayCount2,
            const bool intermediateCapitalExchange,
            const bool finalCapitalExchange, const QuantLib::Real gearing1,
            const QuantLib::Real spread1, bool permanent)
			 : Swap(properties, permanent)
			{
        libraryObject_ = boost::shared_ptr<QuantLib::Instrument>(new
            QuantLib::FloatFloatSwap(type, nominal1, nominal2, *schedule1, index1, dayCount1,
										*schedule2, index2, dayCount2, intermediateCapitalExchange,
										finalCapitalExchange, gearing1, spread1));
			}

			FloatFloatSwap::FloatFloatSwap(
			const boost::shared_ptr<ValueObject>& properties,
			const boost::shared_ptr<QuantLib::FloatFloatSwapRateHelper>& swapRH,
			bool permanent)
			: Swap(properties, permanent)
			{
				libraryObject_ = swapRH->basisSwap();
			}
}
