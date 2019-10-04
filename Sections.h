#ifndef SECTIONS_H
#define SECTIONS_H

#include <QStringList>
#include <QDebug>
#include <iostream>

class ParamsList: public QStringList
{
public:
  std::ostream& operator<<(std::ostream& os);
  ParamsList& operator<<(ParamsList paramsList);
  friend std::ostream& operator<<(std::ostream& os, const ParamsList& paramsList);
};

struct Location
{
  Location();
  Location(ParamsList params);
  ParamsList path(QString p = "") const;
  Location &operator<<(const QString &str);

private:
  ParamsList params;
};

struct Section
{
  Section(QString name);
  ParamsList& operator<<(ParamsList paramsList);
  friend ParamsList& operator<<(std::ostream& os, Section& section);

private:
  QString name;
  ParamsList params;
};



////////////
ParamsList getLog(QString path);
ParamsList server (QStringList serverNames);
ParamsList root (QString path, QString index = "index.php");
ParamsList includes (QStringList include);
ParamsList location(QString path, QStringList params);

#endif // SECTIONS_H
