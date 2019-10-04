#include "Sections.h"



std::ostream &ParamsList::operator<<(std::ostream &os)
{
  qInfo() << __LINE__ << *this;
  for (QString line: *this)
    os << line.toStdString() << std::endl;

  return os;
}

ParamsList &ParamsList::operator<<(ParamsList paramsList)
{
  append("\n");
  for (QString line: paramsList)
    append( line + "\n" );

  return *this;
}

std::ostream &operator<<(std::ostream &os, const ParamsList &paramsList)
{
  qInfo() << __LINE__ << paramsList;
  for (QString param: paramsList)
    os << param.toStdString() << "\n";

  os << std::endl;

  return os;
}

Location::Location(){}

Location::Location(ParamsList params):params(params) {}

ParamsList Location::path(QString p) const {
  ParamsList ret;
  ret.append( "location " + p + " {");
  for (QString param: params)
    ret += "  " + param;
  ret.append( "}" );
  return ret;
}

Location &Location::operator<<(const QString &str)
{
  params.append( str ); return *this;
}

Section::Section(QString name): name(name){}

ParamsList &operator<<(std::ostream &os, Section &section)
{
  std::string n = section.name.toStdString();
  os << n << " {\n";
  for (QString param: section.params)
    os << "  " + param.toStdString();

  os << "}\n";
  return section.params;
}

ParamsList &Section::operator<<(ParamsList paramsList)
{
  for (QString paramStr: paramsList)
    params.append("  " + paramStr + "\n");

  return params;
}

ParamsList getLog(QString path)
{
  ParamsList ret;
  ret.append("access_log " + path + "/access.log;");
  ret.append("error_log " + path + "/error.log;");

  return ret;
}

ParamsList server(QStringList serverNames)
{
  ParamsList ret;
  ret.append("charset UTF-8;");
  ret.append("server_name " + serverNames.join(" ") + ";");

  return ret;
}

ParamsList root(QString path, QString index)
{
  ParamsList ret;
  ret.append("root " + path + ";");
  ret.append("index " + index + ";");

  return ret;
}

ParamsList includes(QStringList include)
{
  ParamsList ret;
  for (QString inc: include)
    ret.append( "include " + inc + ";" );

  return ret;
}

ParamsList location(QString path, QStringList params)
{
  ParamsList ret;
  ret.append("location " + path + " {");
  for (QString param: params)
    ret.append("  " + param);
  ret.append("}\n");
  return ret;
}
