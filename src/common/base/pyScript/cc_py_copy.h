#pragma once



class Copy
{						
public:	
	/** ���� copy.copy */
	static PyObject* copy(PyObject* pyobj);
	static PyObject* deepcopy(PyObject* pyobj);

	/** ��ʼ��pickler */
	static bool initialize(void);
	static void finalise(void);

private:
	static PyObject* copyMethod_;							// cPicket.dumps����ָ��
	static PyObject* deepcopyMethod_;						// cPicket.loads����ָ��
	static bool	isInit;										// �Ƿ��Ѿ�����ʼ��
} ;






