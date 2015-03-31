#include "Logger.h"

Logger::Logger()
{
	google::InitGoogleLogging("/");

	FLAGS_logtostderr = false;
	FLAGS_colorlogtostderr = true;
	FLAGS_alsologtostderr = true;

	LOG(INFO) << "log system initalize success";
}

Logger::~Logger()
{
	google::ShutdownGoogleLogging();
}
