#pragma once 




/// �����ǰ�ű������Ĵ�����Ϣ	
#define SCRIPT_ERROR_CHECK()																\
{																							\
 	if (PyErr_Occurred())																	\
 	{																						\
		PyErr_PrintEx(0);																	\
	}																						\
}







