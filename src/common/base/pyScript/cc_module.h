#pragma once




class CC_pyModule
{
public:
	CC_pyModule();
	~CC_pyModule();


	virtual bool install(const wchar_t* pythonHomeDir, std::wstring pyPaths, 
		const char* moduleName);

	
	



};

















