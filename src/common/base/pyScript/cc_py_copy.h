#pragma once



class Copy
{						
public:	
	/** 代理 copy.copy */
	static PyObject* copy(PyObject* pyobj);
	static PyObject* deepcopy(PyObject* pyobj);

	/** 初始化pickler */
	static bool initialize(void);
	static void finalise(void);

private:
	static PyObject* copyMethod_;							// cPicket.dumps方法指针
	static PyObject* deepcopyMethod_;						// cPicket.loads方法指针
	static bool	isInit;										// 是否已经被初始化
} ;






