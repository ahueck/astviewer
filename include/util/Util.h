/*
 * uTIL.H
 *
 *  Created on: Jul 13, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_UTIL_UTIL_H_
#define INCLUDE_UTIL_UTIL_H_

#include <QString>
#include <QFile>
#include <QTextStream>

#include <memory>

namespace astviewer {

inline QString readTxtFile(QString file_path) {
  QFile file(file_path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return {""};
  }
  QTextStream in(&file);
  return in.readAll();
}

template<class T>
struct _Unique_if {
  using _Single_object = std::unique_ptr<T>;
};

template<class T>
struct _Unique_if<T[]> {
  using _Unknown_bound = std::unique_ptr<T []>;
};

template<class T, size_t N>
struct _Unique_if<T[N]> {
  using _Known_bound = void;
};

template<class T, class ... Args>
typename _Unique_if<T>::_Single_object make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
typename _Unique_if<T>::_Unknown_bound make_unique(size_t n) {
  using U = typename std::remove_extent<T>::type;
  return std::unique_ptr<T>(new U[n]());
}

template<class T, class ... Args>
typename _Unique_if<T>::_Known_bound make_unique(Args&&...) = delete;

}

#endif /* INCLUDE_UTIL_UTIL_H_ */
