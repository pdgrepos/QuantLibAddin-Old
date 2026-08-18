#include "ohpy/py_shared_state.hpp"
#include "pyql_defines.hpp" //py_quantlib_methods definition
#include "py_local_enumerations.hpp"

extern "C" {

     static PyModuleDef py_quantlib_module = {
        PyModuleDef_HEAD_INIT,
        "py_quantlib",
        "Python export of quantlib functions",
        -1, // Usiamo la PyCapsule invece dello stato locale
        py_quantlib_methods,
        NULL, NULL, NULL, NULL
    };

    PyMODINIT_FUNC PyInit_py_quantlib(void) {

        PyObject *module = PyModule_Create(&py_quantlib_module);
        if (!module) {
            return NULL;
        }
        SharedState *st = get_shared_state_from_oh();

        if (!st) {
            Py_DECREF(module);
            return NULL;
        }
        registerLocalEnums();

        if (st->PyOHError) {
            Py_INCREF(st->PyOHError);
            if (PyModule_AddObject(module, "PyOH_error", st->PyOHError) < 0) {
                Py_DECREF(st->PyOHError);
                Py_DECREF(module);
                return NULL;
            }
        }
        return module;
    }

} // extern "C"
