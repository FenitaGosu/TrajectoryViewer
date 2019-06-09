#pragma once

#include <memory>

#include <QObject>

#include "Interfaces/IFileWatcher.h"

class QString;

namespace FileWatcher {

class QtFileWatcher
	: public QObject
	, public IFileWatcher
{
public:
	QtFileWatcher();
	~QtFileWatcher();

	void AddFile(const std::string& file, std::function<void()> callBackFileChanged) override;

private:
	void OnFileChanged(const QString& path);

private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};

}
