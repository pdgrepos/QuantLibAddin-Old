#ifndef __PY_OH_UTILITIES_
#define __PY_OH_UTILITIES_

#include <Python.h>

#include <exception>
#include <string>
#include <cmath>
#include <vector>

#include <boost/optional.hpp>

#include "oh\repository.hpp"
#include <oh\objecthandler.hpp>

#include <Python.h>
#include <string>

// PyObject -> Scalar

template <class T>
T convertValue(PyObject *value) {
	throw std::logic_error("convertValue not implemented");
}

template <class T>
std::vector<T> convertVector(PyObject *vect) {
	throw std::logic_error("convertVector not implemented");
}

template<> inline double convertValue(PyObject *value) {
    return PyFloat_AsDouble(value);
}

template<> inline long convertValue(PyObject *value) {
    if (PyLong_Check(value)) {
        long val = PyLong_AsLong(value);
        if (val == -1 && PyErr_Occurred()) {
            PyErr_Clear();
            throw std::runtime_error("Overflow converting PyLong to C++ long.");
        }
        return val;
    }
    else if (PyFloat_Check(value)) {
        return static_cast<long>(PyFloat_AsDouble(value));
    }
    else {
        PyObject* type_obj = PyObject_Type(value);
        PyObject* repr = PyObject_Repr(type_obj);
        const char* type_name = PyUnicode_AsUTF8(repr);
        std::string err_msg = "Unsupported PyObject type in convertValue<long>: ";
        err_msg += (type_name ? type_name : "unknown");

        Py_XDECREF(repr);
        Py_XDECREF(type_obj);
        throw std::runtime_error(err_msg);
    }
}

template<> inline std::string convertValue(PyObject *value) {
    return PyUnicode_AsUTF8(value);
}
template<> inline bool convertValue(PyObject *value) {
    int res = PyObject_IsTrue(value);
    if (res == -1)
        throw std::logic_error("Passed PyObject pointer was not a boolean!");
    return res != 0;
}
template <> inline ObjectHandler::property_t convertValue<ObjectHandler::property_t>(PyObject* value) {
    if (!value || value == Py_None) {
        return ObjectHandler::property_t(); // empty_property_tag
    }
    // Bool
    if (PyBool_Check(value)) {
        return ObjectHandler::property_t(value == Py_True);
    }
    // Int
    if (PyLong_Check(value)) {
        return ObjectHandler::property_t(convertValue<long>(value));
    }
    // Floating point
    if (PyFloat_Check(value)) {
        return ObjectHandler::property_t(PyFloat_AsDouble(value));
    }
    // String
    if (PyUnicode_Check(value)) {
        return ObjectHandler::property_t(convertValue<std::string>(value));
    }
    // Byte string
    if (PyBytes_Check(value)) {
        return ObjectHandler::property_t(std::string(PyBytes_AsString(value), PyBytes_Size(value)));
    }
    std::string typeName = Py_TYPE(value)->tp_name;
    std::string reprStr = "<errore nel calcolo del repr>";

    PyObject* pyRepr = PyObject_Repr(value);
    if (pyRepr) {
        Py_ssize_t size;
        const char* utf8 = PyUnicode_AsUTF8AndSize(pyRepr, &size);
        if (utf8) {
            reprStr = std::string(utf8, size);
        }
        Py_DECREF(pyRepr); // Required: PyObject_Repr returns a new reference
    }
    else {
        PyErr_Clear(); // Clears potential errors raised by __repr__()
    }

    throw std::invalid_argument(
        "convertValue : Unsupported PyObject type when converting to property_t : " +
        typeName + "' with value: " + reprStr
    );
}

template <class T>
boost::optional<T> convertOptionalValue(PyObject* value)
{
    if (value == Py_None)
        return boost::none;

    return boost::optional<T>(convertValue<T>(value));
}

template <class T>
T convertOptionalValue(PyObject* value, const T& defValue)
{
    if (value == Py_None)
        return defValue;

    return convertValue<T>(value);
}

// PyObject -> Vector

template <class T>
std::vector<T> listTupleToVector_T(PyObject* incoming) {
	std::vector<T> data;
	if (PyTuple_Check(incoming)) {
		for (Py_ssize_t i = 0; i < PyTuple_Size(incoming); i++) {
			PyObject *value = PyTuple_GetItem(incoming, i);
			data.push_back(convertValue<T>(value));
		}
	}
	else {
		if (PyList_Check(incoming)) {
			for (Py_ssize_t i = 0; i < PyList_Size(incoming); i++) {
				PyObject *value = PyList_GetItem(incoming, i);
				data.push_back(convertValue<T>(value));
			}
		}
		else {
			throw std::logic_error("Passed PyObject pointer was not a list or tuple!");
		}
	}
	return data;
}

template<> inline std::vector<double> convertVector(PyObject *vect) {
    return listTupleToVector_T<double>(vect);
}
template<> inline std::vector<long> convertVector(PyObject *vect) {
    return listTupleToVector_T<long>(vect);
}
template<> inline std::vector<std::string> convertVector(PyObject *vect) {
    return listTupleToVector_T<std::string>(vect);
}
template<> inline std::vector<bool> convertVector(PyObject *vect) {
    return listTupleToVector_T<bool>(vect);
}
template<> inline std::vector<ObjectHandler::property_t> convertVector(PyObject *vect) {
    return listTupleToVector_T<ObjectHandler::property_t>(vect);
}

// PyObject -> Matrix

template <class T>
std::vector<std::vector<T> > listTupleToMatrix_T(PyObject* incoming) {
    std::vector<std::vector<T> > data;
    if (PyTuple_Check(incoming)) {
        for (Py_ssize_t i = 0; i < PyTuple_Size(incoming); i++) {
            PyObject *value = PyTuple_GetItem(incoming, i);
            data.push_back(convertVector<T>(value));
        }
    }
    else {
        if (PyList_Check(incoming)) {
            for (Py_ssize_t i = 0; i < PyList_Size(incoming); i++) {
                PyObject *value = PyList_GetItem(incoming, i);
                data.push_back(convertVector<T>(value));
            }
        }
        else {
            throw std::logic_error("Passed PyObject pointer was not a list or tuple!");
        }
    }
    return data;
}

template<> inline std::vector<std::vector<double> > convertVector(PyObject *vect) {
    return listTupleToMatrix_T<double>(vect);
}
template<> inline std::vector<std::vector<long> > convertVector(PyObject *vect) {
    return listTupleToMatrix_T<long>(vect);
}
template<> inline std::vector<std::vector<std::string> > convertVector(PyObject *vect) {
    return listTupleToMatrix_T<std::string>(vect);
}
template<> inline std::vector<std::vector<bool> > convertVector(PyObject *vect) {
    return listTupleToMatrix_T<bool>(vect);
}
template<> inline std::vector<std::vector<ObjectHandler::property_t> > convertVector(PyObject *vect) {
    return listTupleToMatrix_T<ObjectHandler::property_t>(vect);
}

// Scalar -> PyObject

template <class T>
PyObject* toPyObject(const T& value) {
    throw std::logic_error("toPyObject not implemented");
}

template<> inline PyObject* toPyObject(const double& value) {
    return PyFloat_FromDouble(value);
}
template<> inline PyObject* toPyObject(const long& value) {
    return PyLong_FromLong(value);
}
template<> inline PyObject* toPyObject(const std::string& value) {
    return PyUnicode_FromString(value.c_str());
}
template<> inline PyObject* toPyObject(const bool& value) {
    return PyBool_FromLong(value);
}

template <class T>
PyObject* toPyObject(const std::vector<T>& values) {
	PyObject* result = PyList_New(0);
	for(size_t i = 0; i < values.size(); i++) {
		PyList_Append(result, toPyObject(values[i]));
	}
	return result;
}

inline std::vector<PyObject*> splitArgs(PyObject* args, const size_t nPars){
	std::vector<PyObject*> objects;
	size_t argc = PyTuple_GET_SIZE(args);

    if(argc != nPars)
        throw std::logic_error("splitArgs: mismatching arguments size. Expected("
            + std::to_string(nPars) + ") != provided(" + std::to_string(argc) + ")");

	objects.resize(argc);

	for (int i = 0; i<argc; i++) {
		objects[i] = PyTuple_GET_ITEM(args, i);
	}
	return objects;
}

#endif //__PY_OH_UTILITIES_
