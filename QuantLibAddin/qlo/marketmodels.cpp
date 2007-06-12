
/*
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Marco Bianchetti

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

#if defined(HAVE_CONFIG_H)     // Dynamically created by configure
    #include <qlo/config.hpp>
#endif
#include <qlo/marketmodels.hpp>
#include <qlo/products.hpp>
#include <ql/math/matrix.hpp>
#include <ql/models/marketmodels/models/flatvol.hpp>
#include <ql/models/marketmodels/browniangenerators/mtbrowniangenerator.hpp>
#include <ql/models/marketmodels/evolvers/lognormalfwdratepc.hpp>
#include <ql/models/marketmodels/evolvers/lognormalfwdrateipc.hpp>
#include <ql/models/marketmodels/evolvers/normalfwdratepc.hpp>
#include <ql/models/marketmodels/products/onestep/onestepforwards.hpp>
#include <ql/models/marketmodels/products/onestep/onestepoptionlets.hpp>
#include <ql/models/marketmodels/products/multistep/multistepratchet.hpp>
#include <ql/models/marketmodels/correlations/correlations.hpp>
#include <ql/models/marketmodels/marketmodeldifferences.hpp>

namespace QuantLibAddin {

    CapletCoterminalSwaptionCalibration::CapletCoterminalSwaptionCalibration(
            const QuantLib::EvolutionDescription& evolution,
            const boost::shared_ptr<QuantLib::PiecewiseConstantCorrelation>& corr,
            const std::vector<boost::shared_ptr<QuantLib::PiecewiseConstantVariance> >& swapVariances,
            const std::vector<QuantLib::Volatility>& capletVols,
            const boost::shared_ptr<QuantLib::CurveState>& cs,
            QuantLib::Spread displacement)
    {
        libraryObject_ =
            boost::shared_ptr<QuantLib::CapletCoterminalSwaptionCalibration>(
                new QuantLib::CapletCoterminalSwaptionCalibration(
                    evolution, corr, swapVariances, capletVols, cs,
                    displacement));
    }

    CapletCoterminalSwaptionCalibration2::CapletCoterminalSwaptionCalibration2(
            const QuantLib::EvolutionDescription& evolution,
            const boost::shared_ptr<QuantLib::PiecewiseConstantCorrelation>& corr,
            const std::vector<boost::shared_ptr<QuantLib::PiecewiseConstantVariance> >& swapVariances,
            const std::vector<QuantLib::Volatility>& capletVols,
            const boost::shared_ptr<QuantLib::CurveState>& cs,
            QuantLib::Spread displacement)
    {
        libraryObject_ =
            boost::shared_ptr<QuantLib::CapletCoterminalSwaptionCalibration2>(
                new QuantLib::CapletCoterminalSwaptionCalibration2(
                    evolution, corr, swapVariances, capletVols, cs,
                    displacement));
    }

    CapletCoterminalSwaptionCalibration3::CapletCoterminalSwaptionCalibration3(
            const QuantLib::EvolutionDescription& evolution,
            const boost::shared_ptr<QuantLib::PiecewiseConstantCorrelation>& corr,
            const std::vector<boost::shared_ptr<QuantLib::PiecewiseConstantVariance> >& swapVariances,
            const std::vector<QuantLib::Volatility>& capletVols,
            const boost::shared_ptr<QuantLib::CurveState>& cs,
            QuantLib::Spread displacement)
    {
        libraryObject_ =
            boost::shared_ptr<QuantLib::CapletCoterminalSwaptionCalibration3>(
                new QuantLib::CapletCoterminalSwaptionCalibration3(
                    evolution, corr, swapVariances, capletVols, cs,
                    displacement));
    }

    TimeHomogeneousForwardCorrelation::TimeHomogeneousForwardCorrelation(
           const QuantLib::Matrix& fwdCorrelation,
           const std::vector<QuantLib::Time>& rateTimes)
    {
        QL_REQUIRE(!rateTimes.empty(), "rate times vector is empty!");
        libraryObject_ =
            boost::shared_ptr<QuantLib::TimeHomogeneousForwardCorrelation>(
                new QuantLib::TimeHomogeneousForwardCorrelation(
                    fwdCorrelation, rateTimes));
    }

    TimeHomogeneousTimeDependentForwardCorrelation::
        TimeHomogeneousTimeDependentForwardCorrelation(
            const std::vector<QuantLib::Time>& rateTimes,
            QuantLib::Real longTermCorr,
            QuantLib::Real beta,
            QuantLib::Real gamma)
    {
        QL_REQUIRE(!rateTimes.empty(), "rate times vector is empty!");
        libraryObject_ =
            boost::shared_ptr<QuantLib::TimeHomogeneousTimeDependentForwardCorrelation>(
                new QuantLib::TimeHomogeneousTimeDependentForwardCorrelation(
                    rateTimes,longTermCorr,beta,gamma));
    }

    CotSwapFromFwdCorrelation::CotSwapFromFwdCorrelation(
            const QuantLib::Matrix& correlations,
            const QuantLib::CurveState& curveState,
            QuantLib::Real displacement,
            const QuantLib::EvolutionDescription& evolution) {
        libraryObject_ =
            boost::shared_ptr<QuantLib::CotSwapFromFwdCorrelation>(new
                QuantLib::CotSwapFromFwdCorrelation(correlations,
                                                          curveState,
                                                          displacement,
                                                          evolution));
    }

    EvolutionDescription::EvolutionDescription(
            const std::vector<QuantLib::Time>& rateTimes,
            const std::vector<QuantLib::Time>& evolutionTimes)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::EvolutionDescription>(
            new QuantLib::EvolutionDescription(rateTimes, evolutionTimes));
    }

    EvolutionDescription::EvolutionDescription(
            const QuantLib::EvolutionDescription& ev)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::EvolutionDescription>(
            new QuantLib::EvolutionDescription(ev));
    }

    EvolutionDescription::EvolutionDescription(
            const QuantLib::MarketModelMultiProduct& product)
    {
        const QuantLib::EvolutionDescription& ev = product.evolution();
        libraryObject_ =
           boost::shared_ptr< QuantLib::EvolutionDescription>(new QuantLib::EvolutionDescription(ev));
    }

    FlatVol::FlatVol(
            const std::vector<QuantLib::Volatility>& volatilities,
            const boost::shared_ptr<QuantLib::PiecewiseConstantCorrelation>& corr,
            const QuantLib::EvolutionDescription& evolution,
            const QuantLib::Size numberOfFactors,
            const std::vector<QuantLib::Rate>& initialRates,
            const std::vector<QuantLib::Rate>& displacements) {
        libraryObject_ = boost::shared_ptr<QuantLib::MarketModel>(new
            QuantLib::FlatVol(volatilities,
                                     corr,
                                     evolution,
                                     numberOfFactors,
                                     initialRates,
                                     displacements));
    }

    AbcdVol::AbcdVol(
            QuantLib::Real a,
            QuantLib::Real b,
            QuantLib::Real c,
            QuantLib::Real d,
            const std::vector<QuantLib::Real>& ks,
            const boost::shared_ptr<QuantLib::PiecewiseConstantCorrelation>& corr,
            const QuantLib::EvolutionDescription& evolution,
            const QuantLib::Size numberOfFactors,
            const std::vector<QuantLib::Rate>& initialRates,
            const std::vector<QuantLib::Rate>& displacements) {
        libraryObject_ = boost::shared_ptr<QuantLib::MarketModel>(new
            QuantLib::AbcdVol(a, b, c, d, ks,
                                     corr,
                                     evolution,
                                     numberOfFactors,
                                     initialRates,
                                     displacements));
    }

    FlatVolFactory::FlatVolFactory(
        QuantLib::Real longTermCorr,
        QuantLib::Real beta,
        const std::vector<QuantLib::Time>& times,
        const std::vector<QuantLib::Volatility>& vols,
        const QuantLib::Handle<QuantLib::YieldTermStructure>& yieldCurve,
        QuantLib::Spread displacement)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::MarketModelFactory>(
            new QuantLib::FlatVolFactory(longTermCorr,
                                         beta,
                                         times,
                                         vols,
                                         yieldCurve,
                                         displacement));
    }


    LMMDriftCalculator::LMMDriftCalculator(
                                    const QuantLib::Matrix& pseudo,
                                    const std::vector<QuantLib::Rate>& displ,
                                    const std::vector<QuantLib::Time>& taus,
                                    QuantLib::Size numeraire,
                                    QuantLib::Size alive)
    : drifts_(taus.size()) {
        libraryObject_ = boost::shared_ptr<QuantLib::LMMDriftCalculator>(new
            QuantLib::LMMDriftCalculator(pseudo, displ,
                                         taus, numeraire, alive));
    }

    std::vector<QuantLib::Real> LMMDriftCalculator::compute(
                                const QuantLib::LMMCurveState& cs) const {
        libraryObject_->compute(cs, drifts_);
        return drifts_;
    }

    std::vector<QuantLib::Real> LMMDriftCalculator::computePlain(
                                const QuantLib::LMMCurveState& cs) const {
        libraryObject_->computePlain(cs, drifts_);
        return drifts_;
    }

    std::vector<QuantLib::Real> LMMDriftCalculator::computeReduced(
                                const QuantLib::LMMCurveState& cs) const {
        libraryObject_->computeReduced(cs, drifts_);
        return drifts_;
    }

    LMMNormalDriftCalculator::LMMNormalDriftCalculator(
                                const QuantLib::Matrix& pseudo,
                                const std::vector<QuantLib::Time>& taus,
                                QuantLib::Size numeraire,
                                QuantLib::Size alive)
    : drifts_(taus.size()) {
        libraryObject_ = boost::shared_ptr<QuantLib::LMMNormalDriftCalculator>(
            new QuantLib::LMMNormalDriftCalculator(pseudo,
                                                   taus, numeraire, alive));
    }

    std::vector<QuantLib::Real> LMMNormalDriftCalculator::compute(
                                const QuantLib::LMMCurveState& cs) const {
        libraryObject_->compute(cs, drifts_);
        return drifts_;
    }

    std::vector<QuantLib::Real> LMMNormalDriftCalculator::computePlain(
                                const QuantLib::LMMCurveState& cs) const {
        libraryObject_->computePlain(cs, drifts_);
        return drifts_;
    }

    std::vector<QuantLib::Real> LMMNormalDriftCalculator::computeReduced(
                                const QuantLib::LMMCurveState& cs) const {
        libraryObject_->computeReduced(cs, drifts_);
        return drifts_;
    }

    CMSMMDriftCalculator::CMSMMDriftCalculator(
                                const QuantLib::Matrix& pseudo,
                                const std::vector<QuantLib::Rate>& displ,
                                const std::vector<QuantLib::Time>& taus,
                                QuantLib::Size numeraire,
                                QuantLib::Size alive,
                                QuantLib::Size spanningFwds)
    : drifts_(taus.size()) {
        libraryObject_= boost::shared_ptr<QuantLib::CMSMMDriftCalculator>(new
            QuantLib::CMSMMDriftCalculator(pseudo, displ,
                                           taus, numeraire, alive,
                                           spanningFwds));
    }

    std::vector<QuantLib::Real> CMSMMDriftCalculator::compute(
                                const QuantLib::CMSwapCurveState& cs) const {
        libraryObject_->compute(cs, drifts_);
        return drifts_;
    }

    SMMDriftCalculator::SMMDriftCalculator(
                                const QuantLib::Matrix& pseudo,
                                const std::vector<QuantLib::Rate>& displ,
                                const std::vector<QuantLib::Time>& taus,
                                QuantLib::Size numeraire,
                                QuantLib::Size alive)
    : drifts_(taus.size()) {
        libraryObject_= boost::shared_ptr<QuantLib::SMMDriftCalculator>(new
            QuantLib::SMMDriftCalculator(pseudo, displ,
                                         taus, numeraire, alive));
    }

    std::vector<QuantLib::Real> SMMDriftCalculator::compute(
                                const QuantLib::CoterminalSwapCurveState& cs) const {
        libraryObject_->compute(cs, drifts_);
        return drifts_;
    }

    //SwapCovarianceApproximator::SwapCovarianceApproximator(
    //                            const QuantLib::CurveState& initialCurveState,
    //                            QuantLib::Size expiry,
    //                            QuantLib::Size maturity,
    //                            QuantLib::Spread displacement,
    //                            const QuantLib::Matrix& forwardCovarianceMatrix)
    //{
    //    libraryObject_ = boost::shared_ptr<QuantLib::SwapCovarianceApproximator>(
    //        new QuantLib::SwapCovarianceApproximator(
    //                        initialCurveState, expiry,maturity, displacement,
    //                        forwardCovarianceMatrix));
    //}

    //QuantLib::Disposable<QuantLib::Matrix> SwapCovarianceApproximator::swapCovarianceMatrix()
    //    {
    //    QuantLib::Matrix result;
    //    libraryObject_->swapCovarianceMatrix();
    //    return result;
    //}

    MTBrownianGeneratorFactory::MTBrownianGeneratorFactory(unsigned long seed)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::BrownianGeneratorFactory>(
            new QuantLib::MTBrownianGeneratorFactory(seed));
    }

    LogNormalFwdRatePc::LogNormalFwdRatePc(
        const boost::shared_ptr<QuantLib::MarketModel>& pseudoRoot,
        const QuantLib::BrownianGeneratorFactory& generatorFactory,
        const std::vector<QuantLib::Size>& numeraires)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::MarketModelEvolver>(
            new QuantLib::LogNormalFwdRatePc(pseudoRoot,
                                               generatorFactory,
                                               numeraires));
    }

    LogNormalFwdRateIpc::LogNormalFwdRateIpc(
        const boost::shared_ptr<QuantLib::MarketModel>& pseudoRoot,
        const QuantLib::BrownianGeneratorFactory& generatorFactory,
        const std::vector<QuantLib::Size>& numeraires)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::MarketModelEvolver>(
            new QuantLib::LogNormalFwdRateIpc(pseudoRoot,
                                                generatorFactory,
                                                numeraires));
    }

    NormalFwdRatePc::NormalFwdRatePc(
        const boost::shared_ptr<QuantLib::MarketModel>& pseudoRoot,
        const QuantLib::BrownianGeneratorFactory& generatorFactory,
        const std::vector<QuantLib::Size>& numeraires)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::MarketModelEvolver>(
            new QuantLib::NormalFwdRatePc(pseudoRoot,
                                                generatorFactory,
                                                numeraires));
    }

    AccountingEngine::AccountingEngine(
        const boost::shared_ptr<QuantLib::MarketModelEvolver>& evolver,
        const QuantLib::Clone<QuantLib::MarketModelMultiProduct>& product,
        double initialNumeraireValue)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::AccountingEngine>(
            new QuantLib::AccountingEngine(evolver,
                                           //*(product.get()),
                                           product,
                                           initialNumeraireValue));
    }


    PiecewiseConstantAbcdVariance::PiecewiseConstantAbcdVariance(
                            QuantLib::Real a, QuantLib::Real b,
                            QuantLib::Real c, QuantLib::Real d,
                            const QuantLib::Size resetIndex,
                            const std::vector<QuantLib::Time>& rateTimes) {

        libraryObject_ =
            boost::shared_ptr<QuantLib::PiecewiseConstantVariance>(new
                QuantLib::PiecewiseConstantAbcdVariance(a, b, c, d,
                                                        resetIndex,
                                                        rateTimes));

    }

    //Volatility model
    LmExtLinearExponentialVolModel::LmExtLinearExponentialVolModel(
        const std::vector<QuantLib::Time>& fixingTimes,
        QuantLib::Real a,
        QuantLib::Real b,
        QuantLib::Real c,
        QuantLib::Real d) {

            libraryObject_ = boost::shared_ptr<QuantLib::LmExtLinearExponentialVolModel>(
            new QuantLib::LmExtLinearExponentialVolModel(fixingTimes,a,b,c,d));
    }
    //Correlation model
    LmLinearExponentialCorrelationModel::LmLinearExponentialCorrelationModel(
        QuantLib::Size size,
        QuantLib::Real rho,
        QuantLib::Real beta,
        QuantLib::Size factors) {

            libraryObject_ = boost::shared_ptr<QuantLib::LmLinearExponentialCorrelationModel>(
                new QuantLib::LmLinearExponentialCorrelationModel(size,rho,beta,factors));

    }
    
    QuantLib::Matrix qlHistCorrZeroYieldLinear(
               const QuantLib::Date& startDate, 
               const QuantLib::Date& endDate, 
               const QuantLib::Period& step,
               const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
               const QuantLib::Period& initialGap,
               const QuantLib::Period& horizon,
               const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
               const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
               const QuantLib::DayCounter& yieldCurveDayCounter,
               QuantLib::Real yieldCurveAccuracy) {
        
        return QuantLib::historicalCorrelations<QuantLib::ZeroYield, QuantLib::Linear>(
                   startDate, endDate, step,
                   fwdIndex, initialGap, horizon,
                   iborIndexes, swapIndexes,
                   yieldCurveDayCounter, yieldCurveAccuracy);
    }
    
   std::vector<QuantLib::Real> qlRateVolDifferences(
       const QuantLib::MarketModel& marketModel1,
       const QuantLib::MarketModel& marketModel2){
           return QuantLib::rateVolDifferences(marketModel1, marketModel2);
   }

   std::vector<QuantLib::Real> qlRateInstVolDifferences(
                            const QuantLib::MarketModel& marketModel1,
                            const QuantLib::MarketModel& marketModel2, 
                            QuantLib::Size index){
        return QuantLib::rateInstVolDifferences(marketModel1, marketModel2, index);
   }

}
