#include "cc_py_gc.h"
#include "cc_py_log.h"


using namespace CC::pyScript;



bool PyGC::m_bIsInit = false;


bool PyGC::initialize()
{
	PyObject *pModule = PyImport_ImportModule("gc");
	if(NULL === pModule)
	{
		CC_PY_LOG_ERROR("PyImport_ImportModule failed!");
		return false;
	}

	collectMethod_ = PyObject_GetAttrString(pModule, "collect");
	if (!collectMethod_)
	{
		CC_PY_LOG_ERROR("PyGC::initialize: get collect is error!\n");
		return false;
	}

	set_debugMethod_ = PyObject_GetAttrString(pModule, "set_debug");
	if(!set_debugMethod_)
	{
		CC_PY_LOG_ERROR("PyGC::init: get set_debug is error!\n");
		return false;
	}

	PyObject* flag = NULL;
		
	flag = PyObject_GetAttrString(pModule, "DEBUG_STATS");
	if(!flag)
	{
		CC_PY_LOG_ERROR("PyGC::init: get DEBUG_STATS is error!\n");
		return false;
	}
	else
	{
		DEBUG_STATS = PyLong_AsLong(flag);
		Py_DECREF(flag);
		flag = NULL;
	}
	
	flag = PyObject_GetAttrString(pModule, "DEBUG_COLLECTABLE");
	if(!flag)
	{
		CC_PY_LOG_ERROR("PyGC::init: get DEBUG_COLLECTABLE is error!\n");
		return false;
	}
	else
	{
		DEBUG_COLLECTABLE = PyLong_AsLong(flag);
		Py_DECREF(flag);
		flag = NULL;
	}
	
	flag = PyObject_GetAttrString(pModule, "DEBUG_UNCOLLECTABLE");
	if(!flag)
	{
		CC_PY_LOG_ERROR("PyGC::init: get DEBUG_UNCOLLECTABLE is error!\n");
		return false;
	}
	else
	{
		DEBUG_UNCOLLECTABLE = PyLong_AsLong(flag);
		Py_DECREF(flag);
		flag = NULL;
	}
	
	flag = PyObject_GetAttrString(pModule, "DEBUG_SAVEALL");
	if(!flag)
	{
		CC_PY_LOG_ERROR("PyGC::init: get DEBUG_SAVEALL is error!\n");
		return false;
	}
	else
	{
		DEBUG_SAVEALL = PyLong_AsLong(flag);
		Py_DECREF(flag);
		flag = NULL;
	}

	flag = PyObject_GetAttrString(pModule, "DEBUG_LEAK");
	if(!flag)
	{
		CC_PY_LOG_ERROR("PyGC::init: get DEBUG_LEAK is error!\n");
		return false;
	}
	else
	{
		DEBUG_LEAK = PyLong_AsLong(flag);
		Py_DECREF(flag);
		flag = NULL;
	}

	APPEND_SCRIPT_MODULE_METHOD(pModule, debugTracing,	__py_debugTracing,	METH_VARARGS, 0);

	Py_DECREF(pModule);

	m_bIsInit = true;

	return true;
}

bool PyGC::finalise()
{
	Py_XDECREF(collectMethod_);
	Py_XDECREF(set_debugMethod_);
	
	collectMethod_ = NULL;
	set_debugMethod_ = NULL;

	return true;
}



void PyGC::collect(int8 generations)
{
	PyObject* pyRet = NULL;
		
	if(generations != -1)
	{
		pyRet = PyObject_CallFunction(collectMethod_, 
			const_cast<char*>("(i)"), generations);
	}
	else
	{
		pyRet = PyObject_CallFunction(collectMethod_, 
			const_cast<char*>(""));
	}


	if (PyErr_Occurred())																	
 	{																						
		PyErr_PrintEx(0);																
	}

	if(pyRet){																				
		Py_DECREF(pyRet);																
		pyRet = NULL;																	
	}

}

void PyGC::setDebug(uint32 flags)
{
	PyObject* pyRet = PyObject_CallFunction(set_debugMethod_, 
		const_cast<char*>("i"), flags);
	
	SCRIPT_ERROR_CHECK();
	
	if (PyErr_Occurred())																	
 	{																						
		PyErr_PrintEx(0);																
	}

	if(pyRet){																				
		Py_DECREF(pyRet);																
		pyRet = NULL;																	
	}
}


























