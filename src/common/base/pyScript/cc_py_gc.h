#pragma once



#include "cc_py_int_types.h"



namespace CC { 
namespace pyScript {



//python垃圾回收模块封装
class PyGC
{
public:
	//gc可以启动debug方式，在gc运行时会打印一些信息，下面这些标志指定gc打印的信息内容
	static uint32 DEBUG_STATS;
	static uint32 DEBUG_COLLECTABLE;
	static uint32 DEBUG_UNCOLLECTABLE;
	static uint32 DEBUG_SAVEALL;
	static uint32 DEBUG_LEAK;


public:

	//模块初始化
	static bool initialize();
	//模块销毁
	static bool finalise();



	/*
		功能说明：强制回收garbage
		输入参数说明：
			generations： With no arguments, run a full collection.  The optional argument
    			may be an integer specifying which generation to collect.  A ValueError
    			is raised if the generation number is invalid.
	*/
	static void collect(int8 generations = -1);

	//设置调试标志
	static void setDebug(uint32 flags);


private:
	static bool m_bIsInit;//此模块是否初始化
	
	static PyObject* collectMethod_;// cPicket.dumps方法指针
	static PyObject* set_debugMethod_;// cPicket.loads方法指针
};







}
}
















