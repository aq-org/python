#include <Python.h>

int main() {
    Py_Initialize();

    // 1. 导入模块
    PyObject *pModule = PyImport_ImportModule("math");
    if (!pModule) {
        PyErr_Print();
        return 1;
    }

    // 2. 获取函数对象
    PyObject *pFunc = PyObject_GetAttrString(pModule, "sqrt");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        PyErr_Print();
        Py_DECREF(pModule);
        return 1;
    }

    // 3. 调用函数（直接传递参数）
    PyObject *pResult = PyObject_CallFunction(pFunc, "f", 2.0);  // 调用 sqrt(2.0)
    if (pResult) {
        double result = PyFloat_AsDouble(pResult);
        printf("Result: %f\n", result);
        Py_DECREF(pResult);
    } else {
        PyErr_Print();
    }

    // 4. 清理资源
    Py_DECREF(pFunc);
    Py_DECREF(pModule);
    Py_FinalizeEx();
    return 0;
}