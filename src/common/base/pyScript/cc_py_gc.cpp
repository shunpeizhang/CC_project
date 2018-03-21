#include "cc_py_gc.h"


using namespace CC::pyScript;



bool PyGC::m_bIsInit = false;


bool PyGC::initialize()
{
	PyObject *pModule = PyImport_ImportModule("gc");
	if(NULL === pModule)
	{
		
	}



	return true;
}

bool PyGC::finalise()
{



}



void PyGC::collect(int8 generations)
{


}

void PyGC::setDebug(uint32 flags)
{



}


























