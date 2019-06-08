#include <cassert>

#include <QFileSystemWatcher>

#include "QtFileWatcher.h"

using namespace FileWatcher;

struct QtFileWatcher::Impl
{
	QFileSystemWatcher watcher;
	std::map<QString, std::function<void()>> callBacks;
};

QtFileWatcher::QtFileWatcher()
	: m_impl(std::make_unique<Impl>())
{
	connect(&m_impl->watcher, &QFileSystemWatcher::fileChanged, this, &QtFileWatcher::OnFileChanged);
}

QtFileWatcher::~QtFileWatcher() = default;

void QtFileWatcher::AddFile(const std::string& file, std::function<void()> callBackFileChanged)
{
	m_impl->callBacks.emplace(QString::fromStdString(file), callBackFileChanged);
	m_impl->watcher.addPath(QString::fromStdString(file));
}

void QtFileWatcher::OnFileChanged(const QString& path)
{
	const auto it = m_impl->callBacks.find(path);

	assert(it != m_impl->callBacks.cend());

	it->second();
}
