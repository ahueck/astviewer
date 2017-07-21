/*
 * Command.h
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_COMMAND_H_
#define INCLUDE_CORE_COMMAND_H_

#include <QString>
#include <QDebug>

namespace astviewer {

using cmd_id = size_t;

class Command final {
public:
  enum class CommandType
    : size_t {
      file_load = 1, file_store = 2, query = 4, selection = 8
  };

  cmd_id id;
  CommandType t { CommandType::query };
  QString input { "" };
  size_t row_start { 0 };
  size_t row_end { 0 };
  size_t column_start { 0 };
  size_t column_end { 0 };
  QString result { "" };

  Command() {
    static cmd_id id_ = 0;
    id = ++id_;
  }
};

inline QString commandType2Str(const Command::CommandType type) {
  switch (type) {
  case Command::CommandType::file_load:
    return "File Load";
    break;
  case Command::CommandType::file_store:
    return "File Store";
    break;
  case Command::CommandType::query:
    return "Query";
    break;
  case Command::CommandType::selection:
    return "Selection";
    break;
  default:
    return "UNKNOWN";
  }
}

inline QDebug operator<<(QDebug out_dbg, const Command& cmd) {
  out_dbg << "[" << cmd.id << ":" << commandType2Str(cmd.t) << ":\""
      << cmd.input << "\"]";

  return out_dbg;
}

}

#endif /* INCLUDE_CORE_COMMAND_H_ */
