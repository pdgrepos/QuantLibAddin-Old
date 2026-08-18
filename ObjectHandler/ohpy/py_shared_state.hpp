#pragma once

#include <Python.h>

#include <oh/ohdefines.hpp>
#include <oh/object.hpp>
#include <oh/libraryobject.hpp>
#include <oh/repository.hpp>
#include <oh/utilities.hpp>
#include <oh/exception.hpp>
#include <oh/property.hpp>
#include <oh/group.hpp>
#include <oh/range.hpp>
#include <oh/serializationfactory.hpp>
#include <oh/processor.hpp>

// Identificatore univoco per la PyCapsule
#define CAPSULE_NAME "shared_oh_state"

// Struttura che contiene le risorse da condividere tra i moduli
struct SharedState {
    PyObject *PyOHError;
};

// Funzione usata da ciascuna delle librerie foglia
inline SharedState* get_shared_state_from_oh() {
    // 1. Importa il modulo core (deve coincidere col nome registrato in PyInit_py_oh)
    PyObject *common_mod = PyImport_ImportModule("py_oh");
    if (!common_mod) {
        // Preserva l'errore originale di Python (es. ModuleNotFoundError, DLL load failed)
        return NULL;
    }

    // 2. Estrai la PyCapsule dall'attributo "_shared_state"
    PyObject *capsule = PyObject_GetAttrString(common_mod, "_shared_state");
    Py_DECREF(common_mod); // Non serve piu' il modulo common

    if (!capsule) {
        // PyObject_GetAttrString imposta gia' un AttributeError. Non sovrascriverlo a meno che non sia necessario.
        return NULL;
    }

    // 3. Verifica che sia effettivamente una Capsule
    if (!PyCapsule_CheckExact(capsule)) {
        Py_DECREF(capsule);
        PyErr_SetString(PyExc_TypeError, "L'attributo '_shared_state' in 'py_oh' non e' una PyCapsule valida.");
        return NULL;
    }

    // 4. Estrai il puntatore C++
    SharedState *st = (SharedState*)PyCapsule_GetPointer(capsule, CAPSULE_NAME);

    // Rilascia la capsule DOPO aver verificato se GetPointer ha avuto successo
    Py_DECREF(capsule);

    if (!st) {
        // PyCapsule_GetPointer imposta automaticamente l'errore in Python se CAPSULE_NAME non combacia
        return NULL;
    }

    return st;
}

// Distruttore invocato da Python quando la PyCapsule viene distrutta dal Garbage Collector
static void destroy_shared_state(PyObject *capsule) {
    SharedState *st = (SharedState*)PyCapsule_GetPointer(capsule, CAPSULE_NAME);
    if (st) {
        Py_XDECREF(st->PyOHError);
        delete st;
    }
}

// Funzione per recuperare lo stato condiviso da un modulo esistente o crearne uno nuovo
inline SharedState* get_or_create_shared_state(PyObject *target_module, PyObject *source_module = NULL) {
    // 1. Se ci viene passato un source_module (es. il sotto-modulo che eredita dal padre)
    if (source_module) {
        PyObject *capsule = PyObject_GetAttrString(source_module, "_shared_state");
        if (capsule && PyCapsule_CheckExact(capsule)) {
            SharedState *st = (SharedState*)PyCapsule_GetPointer(capsule, CAPSULE_NAME);
            Py_DECREF(capsule);
            if (st) {
                // Collega la stessa capsule anche al nuovo modulo
                PyObject *cap_obj = PyObject_GetAttrString(source_module, "_shared_state");
                PyModule_AddObject(target_module, "_shared_state", cap_obj);
                return st;
            }
        }
        PyErr_Clear();
    }

    // 2. Altrimenti, crea un nuovo SharedState
    SharedState *st = new SharedState();
    st->PyOHError = PyErr_NewException("py_quantlib.PyOH_error", NULL, NULL);

    // Invio dello stato in una PyCapsule
    PyObject *capsule = PyCapsule_New(st, CAPSULE_NAME, destroy_shared_state);
    if (capsule == NULL) {
        delete st;
        return NULL;
    }

    // Registra l'attributo nascosto "_shared_state" nel modulo
    PyModule_AddObject(target_module, "_shared_state", capsule);
    return st;
}

// Macro helper per estrarre lo SharedState dalla PyCapsule del modulo 'm'
#define GET_SHARED_STATE(m) [] (PyObject *module_obj) -> SharedState* { \
    PyObject *capsule = PyObject_GetAttrString(module_obj, "_shared_state"); \
    if (!capsule) return NULL; \
    SharedState *st = (SharedState*)PyCapsule_GetPointer(capsule, CAPSULE_NAME); \
    Py_DECREF(capsule); \
    return st; \
}(m)


static PyObject * return_error(PyObject *m, const std::string& msg) {
    SharedState *st = GET_SHARED_STATE(m);
    if (!st || !st->PyOHError) {
        // Fallback di sicurezza nel caso lo stato non sia reperibile
        PyErr_SetString(PyExc_RuntimeError, msg.c_str());
        return NULL;
    }

    // Costruiamo il messaggio completo
    std::string full_msg = "PyOHError: " + msg;

    // PyUnicode_FromString interpreta correttamente stringhe UTF-8 con caratteri speciali (es. "è", "à")
    PyObject *py_msg = PyUnicode_FromString(full_msg.c_str());
    if (py_msg) {
        PyErr_SetObject(st->PyOHError, py_msg);
        Py_DECREF(py_msg); // PyErr_SetObject incrementa la ref count, quindi rilasciamo la nostra
    }
    else {
        // Fallback in caso di errore nella creazione della stringa Python
        PyErr_SetString(st->PyOHError, "Error occurred (and failed to format error message)");
    }

    return NULL;
}

static PyObject *error_out(PyObject *m) {
    SharedState *st = GET_SHARED_STATE(m);
    if (!st || !st->PyOHError) {
        PyErr_SetString(PyExc_RuntimeError, "something bad happened");
        return NULL;
    }
    PyObject *py_msg = PyUnicode_FromString("something bad happened");
    if (py_msg) {
        PyErr_SetObject(st->PyOHError, py_msg);
        Py_DECREF(py_msg);
    }
    else {
        PyErr_SetString(st->PyOHError, "something bad happened");
    }
    return NULL;
}