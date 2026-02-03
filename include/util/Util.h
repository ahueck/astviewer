/*
 * uTIL.H
 *
 *  Created on: Jul 13, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_UTIL_UTIL_H_
#define INCLUDE_UTIL_UTIL_H_

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include <memory>

namespace astviewer {

inline QString shortenPath(const QString& path, int components) {
  if (components <= 0) {
    return path;
  }
  QFileInfo info(path);
  const QString native_path = QDir::toNativeSeparators(info.absoluteFilePath());
  const QString separator = QDir::separator();
  const QStringList parts = native_path.split(separator, Qt::SkipEmptyParts);

  if (parts.size() <= components) {
    return native_path;
  }

  QStringList last_parts;
  for (int i = parts.size() - components; i < parts.size(); ++i) {
    last_parts << parts.at(i);
  }

  if (components == 1) {
    return last_parts.join(separator);
  }

  return "..." + separator + last_parts.join(separator);
}

inline QString readTxtFile(QString file_path) {
  QFile file(file_path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return {""};
  }
  QTextStream in(&file);
  return in.readAll();
}

namespace detail {

template <class T>
struct _Unique_if {
  using _Single_object = std::unique_ptr<T>;
};

template <class T>
struct _Unique_if<T[]> {
  using _Unknown_bound = std::unique_ptr<T[]>;
};

template <class T, size_t N>
struct _Unique_if<T[N]> {
  using _Known_bound = void;
};

} /* namespace detail */

template <class T, class... Args>
typename detail::_Unique_if<T>::_Single_object make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
typename detail::_Unique_if<T>::_Unknown_bound make_unique(size_t n) {
  using U = typename std::remove_extent<T>::type;
  return std::unique_ptr<T>(new U[n]());
}

template <class T, class... Args>
typename detail::_Unique_if<T>::_Known_bound make_unique(Args&&...) = delete;

}  // namespace astviewer

#endif /* INCLUDE_UTIL_UTIL_H_ */
