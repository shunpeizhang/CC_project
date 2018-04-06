#pragma once



class PyStruct
{						
public:	
	/** 
		���� struct.pack
	*/
	static std::string pack(PyObject* fmt, PyObject* args);

	/** 
		���� struct.unpack
	*/
	static PyObject* unpack(PyObject* fmt, PyObject* args);

	/** 
		��ʼ��pickler 
	*/
	static bool initialize(void);
	static void finalise(void);
	
private:
	static PyObject* pack_;									// struct.pack����ָ��
	static PyObject* unpack_;								// struct.unpack����ָ��

	static bool	isInit;										// �Ƿ��Ѿ�����ʼ��
} ;













