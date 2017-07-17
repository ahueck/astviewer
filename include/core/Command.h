/*
 * Command.h
 *
 *  Created on: Jul 17, 2017
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_COMMAND_H_
#define INCLUDE_CORE_COMMAND_H_


using cmd_id = size_t;

class Command final {
public:
  enum class CommandType : size_t {
    file_load = 0,
    file_store,
    query,
    selection
  };

  cmd_id id;
  CommandType t{CommandType::query};
  QString input{""};
  size_t row_start{0};
  size_t row_end{0};
  size_t column_start{0};
  size_t column_end{0};
  QString result{""};

  Command() {
    static cmd_id id_ = 0;
    id = ++id_;
  }
};



#endif /* INCLUDE_CORE_COMMAND_H_ */
