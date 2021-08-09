
#include <iostream>
#include <cassert>

#include <Python.h>
#include <numpy/ndarrayobject.h>

// https://docs.python.org/3/extending/embedding.html
// https://github.com/dusty-nv/jetson-utils/issues/44
// export PYTHONPATH=.:$PYTHONPATH

#define FORT(x) x##_

static PyObject *py_module = 0;
static PyObject *py_function = 0;

inline int init_numpy()
{
  if(!PyArray_API) import_array();
  return PyArray_API ? 1 : 0;
}

static void py_test(const char *py_script_, const char *py_function_,
		    double *x, const int &nx, double *y, const int &ny)
{
  if(!Py_IsInitialized()) Py_Initialize();

  assert(Py_IsInitialized());
  
  assert(init_numpy());
  
  if(!py_module) {
    PyObject *py_script = PyUnicode_DecodeFSDefault(py_script_);
    assert(py_script);
    py_module = PyImport_Import(py_script);
    assert(py_module);
    Py_DECREF(py_script);
  }
  
  if(!py_function) {
    assert(py_module);
    py_function = PyObject_GetAttrString(py_module, py_function_);
    assert(py_function);
    assert(PyCallable_Check(py_function));
  }

  const npy_intp dim1 [] = { nx };
  const npy_intp dim2 [] = { ny };
  PyObject *x_py = PyArray_SimpleNewFromData(1, dim1, NPY_DOUBLE, x);
  PyObject *y_py = PyArray_SimpleNewFromData(1, dim2, NPY_DOUBLE, y);

  assert(PyObject_CallFunctionObjArgs(py_function, x_py, y_py, NULL));
  
  Py_DECREF(x_py);
  Py_DECREF(y_py);
  x_py = 0;
  y_py = 0;

  // PyRun_SimpleString("import sys; sys.stdout.flush()");
  
  std::cout.flush();
}

static void py_finalize()
{
  if(py_function) { Py_DECREF(py_function); py_function = 0; }
  if(py_module) { Py_DECREF(py_module); py_module = 0; }
  if(Py_IsInitialized()) assert(!Py_FinalizeEx());
  std::cout.flush();
}

// Fortran interface: PyTest
extern "C" void FORT(pytest)(const char *py_script, const int &len_py_script,
			     const char *py_function, const int &len_py_function,
			     double *x, const int &nx, double *y, const int &ny)
{
  char *py_script_ = new char [len_py_script+1];
  assert(py_script);
  memcpy(py_script_, py_script, len_py_script*sizeof(char));
  py_script_[len_py_script] = '\0';

  char *py_function_ = new char [len_py_function+1];
  assert(py_function_);
  memcpy(py_function_, py_function, len_py_function*sizeof(char));
  py_function_[len_py_function] = '\0';

  py_test(py_script_, py_function_, x, nx, y, ny);

  if(py_script_) { delete [] py_script_; py_script_ = 0; }
  if(py_function_) { delete [] py_function_; py_function_ = 0; }
}

// Fortran interface: PyFinalize 
extern "C" void FORT(pyfinalize)()
{
  py_finalize();
}

