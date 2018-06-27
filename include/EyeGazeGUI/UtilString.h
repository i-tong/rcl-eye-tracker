#ifndef UTILSTRING_H
#define UTILSTRING_H

#include <cstring>
#include <qstring.h>
#include <qregexp.h>
#include <QStringList>
#include <vector>

std::vector<float> getNumberFromString(QString inStr);
bool checkEndWith(const char* inputStr, const char* endStr);

#endif // utilstring_h
