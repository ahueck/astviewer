/*
 * LlvmIRHighlighter.cpp
 *
 *  Created on: Feb 2, 2026
 *      Author: ahueck
 */

#include <gui/LlvmIRHighlighter.h>

#include <QRegularExpression>

namespace astviewer {

LlvmIRHighlighter::LlvmIRHighlighter(QObject* parent) : Highlighter(parent) {}

void LlvmIRHighlighter::highlightBlock(const QString& text) {
  Highlighter::highlightBlock(text);

  // clang-format off
  static const QRegularExpression local_var("[%][a-zA-Z0-9._]+");
  static const QRegularExpression global_var("[@][a-zA-Z0-9._]+");
  static const QRegularExpression keyword("\\b(define|declare|type|target|datalayout|attributes|module|asm|linkage|visibility|dll_storage_class|cconv|inbounds|inrange|tail|musttail|notail|noundef|nonnull|align|dereferenceable)\\b");
  static const QRegularExpression instruction("\\b(ret|br|switch|indirectbr|invoke|resume|unreachable|cleanupret|catchret|catchswitch|catchpad|cleanuppad|fadd|fsub|fmul|fdiv|frem|add|sub|mul|udiv|sdiv|urem|srem|shl|lshr|ashr|and|or|xor|extractelement|insertelement|shufflevector|extractvalue|insertvalue|alloca|load|store|fence|cmpxchg|atomicrmw|getelementptr|trunc|zext|sext|fptrunc|fpext|fptoui|fptosi|uitofp|sitofp|ptrtoint|inttoptr|bitcast|addrspacecast|icmp|fcmp|phi|select|call|va_arg|landingpad|catchpad|cleanuppad|freeze)\\b");
  static const QRegularExpression type("\\b(void|half|float|double|x86_fp80|fp128|ppc_fp128|i[0-9]+|ptr|label|metadata|opaque|token|type|any|vararg)\\b");
  static const QRegularExpression metadata("![a-zA-Z0-9._]+");
  static const QRegularExpression comment(";.*");
  static const QRegularExpression label("^\\s*[a-zA-Z0-9._]+:");
  // clang-format on
  const auto apply_color = [&](const QRegularExpression& regex, const QColor& color) {
    auto matches = regex.globalMatch(text);
    while (matches.hasNext()) {
      const auto match = matches.next();
      setFormat(match.capturedStart(), match.capturedLength(), color);
    }
  };

  apply_color(instruction, {"#5691f3"});
  apply_color(keyword, {"#1290c3"});
  apply_color(type, {"#138c5a"});
  apply_color(local_var, {"#e06c3a"});
  apply_color(global_var, {"#e06c3a"});
  apply_color(metadata, Qt::gray);
  apply_color(label, Qt::darkMagenta);
  apply_color(comment, Qt::darkGreen);
}

LlvmIRHighlighter::~LlvmIRHighlighter() = default;

} /* namespace astviewer */
