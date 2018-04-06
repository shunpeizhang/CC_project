#pragma once




class CC_pyModule
{
public:
	CC_pyModule();
	~CC_pyModule();


	virtual bool install(const wchar_t* pythonHomeDir, std::wstring pyPaths, 
		const char* moduleName);
	
	virtual bool uninstall(void);

	bool installExtraModule(const char* moduleName);	
	bool registerExtraMethod(const char* attrName, PyMethodDef* pyFunc);
	bool registerExtraObject(const char* attrName, PyObject* pyObj);

	int registerToModule(const char* attrName, PyObject* pyObj);
	int unregisterToModule(const char* attrName);
	
	PyObject* getModule(void) const;
	PyObject* getExtraModule(void) const;

	int run_simpleString(const char* command, std::string* retBufferPtr);

	
protected:
	PyObject* 					module_;
	PyObject*					extraModule_;

};

















