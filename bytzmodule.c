#include <Python.h>

#include "bytz.h"

static PyObject *bytz_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    bytz_hash((char *)PyBytes_AsString((PyObject*) input), (int)PyBytes_Size((PyObject*) input), output);
#else
    bytz_hash((char *)PyString_AsString((PyObject*) input), (int)PyString_Size((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef DashMethods[] = {
    { "getPoWHash", bytz_getpowhash, METH_VARARGS, "Returns the proof of work hash using bytz hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef DashModule = {
    PyModuleDef_HEAD_INIT,
    "bytz_hash",
    "...",
    -1,
    DashMethods
};

PyMODINIT_FUNC PyInit_bytz_hash(void) {
    return PyModule_Create(&DashModule);
}

#else

PyMODINIT_FUNC initbytz_hash(void) {
    (void) Py_InitModule("bytz_hash", DashMethods);
}
#endif
