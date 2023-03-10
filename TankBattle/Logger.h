#pragma once
#include <string>
#include <fstream>
#include <sstream>

class Logger {

public:
    Logger();
    Logger(Logger& other) = delete;
    void operator=(const Logger&) = delete;

	static Logger* GetInstance();
	void Log();
    Logger* AppendToLog(std::string val);
    Logger* NewLine();
    void Clear();

    ~Logger();

private:

    static Logger* singleton_;
    std::string val;
};