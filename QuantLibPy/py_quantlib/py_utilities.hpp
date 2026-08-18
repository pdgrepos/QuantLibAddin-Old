#ifndef __PY_QL_UTILITIES_
#define __PY_QL_UTILITIES_

#include "ohpy/py_oh_utilities.hpp"
#include <ql\time\date.hpp>

template<> inline QuantLib::Date convertValue(PyObject *value) {
    throw std::logic_error("QuantLib::Date convertValue not implemented");
}

template<> inline std::vector<QuantLib::Date> convertVector(PyObject *vect) {
    return listTupleToVector_T<QuantLib::Date>(vect);
}

template<> inline QuantLib::Period convertValue(PyObject *value) {
    const std::string& s = convertValue<std::string>(value);
    return QuantLib::PeriodParser::parse(s);
}

template<> inline std::vector<QuantLib::Period> convertVector(PyObject *vect) {
    return listTupleToVector_T<QuantLib::Period>(vect);
}

template<> inline std::vector<std::vector<QuantLib::Date> > convertVector(PyObject *vect) {
    return listTupleToMatrix_T<QuantLib::Date>(vect);
}

template<> inline PyObject* toPyObject(const QuantLib::Date& value) {
    return PyLong_FromLong(long(value.serialNumber()));
}

template<class LoopFunction, class InputType, class OutputType>
std::vector<OutputType> loop(
    LoopFunction &loopFunction,
    const std::vector<InputType> &vIn) {

    std::vector<OutputType> vOut;
    vOut.reserve(vIn.size());
    typename std::vector<InputType>::const_iterator i;
    for (i = vIn.begin(); i != vIn.end(); ++i) {
        vOut.push_back(loopFunction(*i));
    }
    return vOut;
}

#define CATCH_PYDG_ERRORS(m)\
    catch (const std::exception &e) {\
        return return_error(m, e.what());\
    }\
    catch (...) {\
        return return_error(m, "unkown error type");\
    }


#endif //__PY_QL_UTILITIES_
