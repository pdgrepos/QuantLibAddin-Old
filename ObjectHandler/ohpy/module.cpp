#include <Python.h>
#include "py_shared_state.hpp"
#include "pyoh_defines.hpp"

static ObjectHandler::Repository repo;

extern "C" {

    static PyModuleDef oh_module_def = {
        PyModuleDef_HEAD_INIT,
        "py_oh", // Deve coincidere con il nome del modulo Python
        "Modulo Core per la gestione delle risorse condivise OH",
        -1,
        py_oh_methods,
        NULL, NULL, NULL, NULL
    };

    PyMODINIT_FUNC PyInit_py_oh(void) {
        PyObject *module = PyModule_Create(&oh_module_def);
        if (!module) return NULL;

        // Allocazione unica e creazione della PyCapsule
        SharedState *st = new SharedState();
        st->PyOHError = PyErr_NewException("py_oh.PyOH_error", NULL, NULL);

        PyObject *capsule = PyCapsule_New(st, CAPSULE_NAME, destroy_shared_state);
        if (!capsule) {
            delete st;
            Py_DECREF(module);
            return NULL;
        }

        // Registra la capsule come attributo nel modulo oh
        PyModule_AddObject(module, "_shared_state", capsule);
        PyModule_AddObject(module, "PyOH_error", st->PyOHError);

        return module;
    }

} // extern "C"}