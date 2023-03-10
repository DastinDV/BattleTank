#include "Logger.h"

Logger::Logger() {

}

Logger* Logger::GetInstance()
{
    if (singleton_ == nullptr) {
        singleton_ = new Logger();
    }
    return singleton_;
}

Logger* Logger::AppendToLog(std::string val) {
    this->val += val;
    return this;
}

Logger* Logger::NewLine() {
    this->val += "\n";
    return this;
}

void Logger::Log() {
    std::ofstream out;
    out.open("log.txt", std::ios::app);
    if (out.is_open()) {
        out << this->val << "\n";
    }
}

void Logger::Clear() {
    this->val.clear();
}

Logger::~Logger() {
}

Logger* Logger::singleton_ = nullptr;