#include <iostream>
#include "Logger.h"

using namespace std;

Logger::Logger(string logName, bool console) : lockFile(LOG_FILE), name(logName) {
	this->level = LogLevel::INFO;
	this->console = console;
	this->initializeEnumMapValues();
}

Logger::Logger(LogLevel level, string logName) : lockFile(LOG_FILE), name(logName) {
	this->level = LogLevel::INFO;
	this->initializeEnumMapValues();
}

Logger::~Logger() {
}

void Logger::initializeEnumMapValues() {
	this->logLevelMap[LogLevel::DEBUG] = string("[DEBUG]");
	this->logLevelMap[LogLevel::INFO] = string("[INFO]");
	this->logLevelMap[LogLevel::WARN] = string("[WARN]");
	this->logLevelMap[LogLevel::ERROR] = string("[ERROR]");
}

void Logger::info(const string data) {
	this->logLocking(data, LogLevel::INFO);
}

void Logger::error(const string data) {
	this->logLocking(data, LogLevel::ERROR);
}

void Logger::warn(const string data) {
	this->logLocking(data, LogLevel::WARN);
}

void Logger::debug(const string data) {
	this->logLocking(data, LogLevel::DEBUG);
}

void Logger::logLocking(const string data, LogLevel level) {
	if (this->level <= level){
		log(data, level);
	}
}

void Logger::log(const string data, LogLevel level) {
	string logLine = createLogLine(data, level);
	if (this->console)
		std::cout << logLine;
	lockFile.write(logLine.c_str(), logLine.length());
}

string Logger::createLogLine(const string data, LogLevel level) {
	string logLine;
	logLine.append(getFormattedDateTime());
	logLine.append(LOG_DELIMITER);
	logLine.append(this->name);
	logLine.append(LOG_DELIMITER);
	logLine.append(this->logLevelMap[level]);
	logLine.append(LOG_DELIMITER);
	logLine.append(data);
	logLine.append("\n");
	return logLine;
}

string Logger::getFormattedDateTime() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	return string(buffer);
}

