#include <Python.h>
#include <string>


using namespace std;


void test()
{
	PyRun_SimpleString("print 'test'");

	PyObject *m, *d, *v;
		m = PyImport_AddModule("__main__");
		if (m == NULL)
		{
			return;
		}

		d = PyModule_GetDict(m);

	PyRun_String("print 'test'", Py_single_input, d,d);
}


class CTestObject: public PyObject
{
public:
	CTestObject()
	{
		if (PyType_Ready(&_scriptType) < 0)
		{
			printf("CTestObject: Type {} is not ready\n");
		}
		
		PyObject_INIT(static_cast<PyObject*>(this), &_scriptType);		
	}

	~CTestObject()
	{
		assert(this->ob_refcnt == 0);
	}

	static void _tp_dealloc(PyObject* self)								
	{																						
		delete static_cast<CTestObject*>(self);									
	}

	static PyObject* tp_repr(PyObject* self)
	{		
		return PyUnicode_FromFormat("%s object at %p.", "CTestObject", static_cast<CTestObject*>(self));
	}
																					
	static PyObject* _tp_getattro(PyObject* self, PyObject* name)							
	{
		return PyObject_GenericGetAttr(static_cast<CTestObject*>(self), name);
	}																						
																																												
	static int _tp_setattro(PyObject* self, PyObject* name, PyObject* value)				
	{																						
		return (value != NULL) ?									
				PyObject_GenericSetAttr(static_cast<CTestObject*>(self), name, value):
				PyObject_GenericSetAttr(static_cast<CTestObject*>(self), name, NULL);
	}

	static int _tp_init(PyObject* self, PyObject *args, PyObject* kwds)						\
	{																						
		return 0;					
	}	

	static PyObject* _tp_new(PyTypeObject* type, PyObject* args, PyObject* kwds)			
	{																						
		return type->tp_alloc(type, 0);											
	}

public:
	static PyTypeObject _scriptType;
};


PyTypeObject CTestObject::_scriptType =														
{																						
	PyVarObject_HEAD_INIT(&PyType_Type, 0)														\
	"CTestObject",											/* tp_name            */	\
	sizeof(CTestObject),									/* tp_basicsize 	  */	\
	0,														/* tp_itemsize		  */	\
	(destructor)CTestObject::_tp_dealloc, 					/* tp_dealloc		  */	\
	0,														/* tp_print 		  */	\
	0,														/* tp_getattr		  */	\
	0,														/* tp_setattr		  */	\
	0,														/* void *tp_reserved  */	\
	CTestObject::tp_repr,									/* tp_repr			  */	\
	0,														/* tp_as_number 	  */	\
	0,													    /* tp_as_sequence	  */	\
	0,													    /* tp_as_mapping	  */	\
	0,														/* tp_hash			  */	\
	0,													    /* tp_call			  */	\
	CTestObject::tp_repr, 									/* tp_str			  */	\
	(getattrofunc)CTestObject::_tp_getattro,				/* tp_getattro		  */	\
	(setattrofunc)CTestObject::_tp_setattro,				/* tp_setattro		  */	\
	0,														/* tp_as_buffer 	  */	\
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,				/* tp_flags 		  */	\
	"test new module",										/* tp_doc			  */	\
	0,														/* tp_traverse		  */	\
	0,														/* tp_clear 		  */	\
	0,														/* tp_richcompare	  */	\
	0,														/* tp_weaklistoffset  */	\
	0,													    /* tp_iter			  */	\
	0,												        /* tp_iternext		  */	\
	0,														/* tp_methods		  */	\
	0,														/* tp_members		  */	\
	0,														/* tp_getset		  */	\
	0, 							                            /* tp_base			  */	\
	0,														/* tp_dict			  */	\
	0,														/* tp_descr_get 	  */	\
	0,														/* tp_descr_set 	  */	\
	0,								                        /* tp_dictoffset	  */	\
	(initproc)CTestObject::_tp_init,						/* tp_init			  */	\
	0,														/* tp_alloc 		  */	\
	CTestObject::_tp_new,									/* tp_new			  */	\
	PyObject_GC_Del,										/* tp_free			  */	\
};



void test1()
{
	Py_SetPythonHome("/root/test/python/");
	PyRun_SimpleString("import sys"); 
	PyRun_SimpleString("sys.path.append('./')"); 

	if (PyType_Ready(&CTestObject::_scriptType) < 0)
	{
		printf("PyType_Ready failed!\n");
		return;
	}


	PyObject *m = PyImport_AddModule("__main__");

	PyObject *module_ = PyImport_AddModule("CTestObject");
	if (module_ == NULL)
		return;

	// 将模块对象加入main
	//PyObject_SetAttrString(m, "CTestObject", module_); 
	Py_INCREF(&CTestObject::_scriptType);
	PyModule_AddObject(m, "CTestObject", (PyObject *)&CTestObject::_scriptType);
	
	PyObject *pModule = PyImport_ImportModule("modPy");
	if(NULL == pModule)
	{
		printf("PyImport_ImportModule failed!\n");
		return;
	}	

	//CTestObject *pTest = new CTestObject();
	//PyObject_SetAttrString(pModule, "CTestObject", pTest);
	
	PyObject *pFun = PyObject_GetAttrString(pModule, "test");
	if(NULL == pFun || !PyFunction_Check(pFun))
	{
		printf("get fun failed!\n");
		return;
	}

	PyObject *pSeqObject = PyObject_Dir(pModule);
	if(NULL == pSeqObject)
	{
		printf("PyObject_Dir failed!\n");
		return;
	}

	Py_ssize_t len = PySequence_Length(pSeqObject);
	for(int iPos = 0; len > iPos; ++iPos)
	{
		PyObject *pItem = PySequence_GetItem(pSeqObject, iPos);
		if(NULL == pItem)
		{
			printf("PySequence_GetItem failed!\n");
			return;
		}

		printf("item:%s\n", PyString_AsString(pItem));
	}

	
	PyObject_CallFunction(pFun, "");
	
}



int main()
{
	Py_Initialize();

	test1();

	Py_Finalize();

	return 0;
}



