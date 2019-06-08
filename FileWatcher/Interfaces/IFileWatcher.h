#pragma once

#include <functional>

namespace FileWatcher {

class IFileWatcher
{
public:
	virtual ~IFileWatcher() = default;
	virtual void AddFile(const std::string& file, std::function<void()> callBackFileChanged) = 0;
};

}
