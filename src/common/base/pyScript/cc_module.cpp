#include "cc_module.h"
#include "cc_py_log.h"
#include "pystruct.h"


CC_pyModule::CC_pyModule()
{
	module_ = NULL;
	extraModule_ = NULL;
}


CC_pyModule::~CC_pyModule()
{


}


bool CC_pyModule::install(const wchar_t* pythonHomeDir, std::wstring pyPaths, 
	const char* moduleName)
{
	Py_SetPythonHome(const_cast<wchar_t*>(pythonHomeDir));

	// python解释器的初始化  
	Py_Initialize();
    if (!Py_IsInitialized())
    {
    	CC_PY_LOG_ERROR("Script::install(): Py_Initialize is failed!\n");
        return false;
    } 

	PyObject *m = PyImport_AddModule("__main__");

	// 添加一个脚本基础模块
	module_ = PyImport_AddModule(moduleName);
	if (module_ == NULL)
		return false;

	// 将模块对象加入main
	PyObject_SetAttrString(m, moduleName, module_); 
	PyObject_SetAttrString(module_, "__doc__", PyUnicode_FromString("This module is created by KBEngine!"));
	
	PyStruct::initialize();
	Copy::initialize();


	SCRIPT_ERROR_CHECK();

	return installExtraModule("KBExtra");
}

bool CC_pyModule::uninstall(void)
{
	PyStruct::finalise();
	Copy::finalise();
	SCRIPT_ERROR_CHECK();

	PyGC::initialize();

	// 卸载python解释器
	Py_Finalize();

	return true;
}

bool CC_pyModule::installExtraModule(const char* moduleName)
{
	PyObject *m = PyImport_AddModule("__main__");

	// 添加一个脚本扩展模块
	extraModule_ = PyImport_AddModule(moduleName);
	if (extraModule_ == NULL)
		return false;
	
	// 初始化扩展模块
	PyObject *module = PyImport_AddModule(moduleName);
	if (module == NULL)
		return false;

	// 将扩展模块对象加入main
	PyObject_SetAttrString(m, moduleName, extraModule_);

	INFO_MSG(fmt::format("Script::install(): {} is successfully!\n", moduleName));
	return true;
}

bool CC_pyModule::registerExtraMethod(const char* attrName, PyMethodDef* pyFunc)
{
	return PyModule_AddObject(extraModule_, attrName, PyCFunction_New(pyFunc, NULL)) != -1;
}

bool CC_pyModule::registerExtraObject(const char* attrName, PyObject* pyObj)
{
	return PyObject_SetAttrString(extraModule_, attrName, pyObj) != -1;
}

int CC_pyModule::registerToModule(const char* attrName, PyObject* pyObj)
{
	return PyObject_SetAttrString(module_, attrName, pyObj);
}

int CC_pyModule::unregisterToModule(const char* attrName)
{
	if(module_ == NULL || attrName == NULL)
		return 0;

	return PyObject_DelAttrString(module_, attrName);
}

PyObject* CC_pyModule::getModule(void) const
{
	return module_;
}

PyObject* CC_pyModule::getExtraModule(void) const
{
	return extraModule_;
}

int CC_pyModule::run_simpleString(const char* command, std::string* retBufferPtr)
{
	if(command == NULL)
	{
		CC_PY_LOG_ERROR("Script::Run_SimpleString: command is NULL!\n");
		return 0;
	}

	if(retBufferPtr != NULL)
	{
		PyObject *m, *d, *v;
		m = PyImport_AddModule("__main__");
		if (m == NULL)
		{
			SCRIPT_ERROR_CHECK();
			return -1;
		}

		d = PyModule_GetDict(m);

		v = PyRun_String(command, Py_single_input, d, d);
		if (v == NULL) 
		{
			return -1;
		}

		Py_DECREF(v);
		SCRIPT_ERROR_CHECK();
		
		return 0;
	}

	PyRun_SimpleString(command);

	SCRIPT_ERROR_CHECK();
	return 0;
}




