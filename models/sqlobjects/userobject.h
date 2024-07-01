#pragma once
#include <QSharedData>
#include <TSqlObject>

class T_MODEL_EXPORT UserObject
  : public TSqlObject
  , public QSharedData
{
public:
  QString email;
  QString password;

  enum PropertyIndex
  {
    Email = 0,
    Password,
  };

  int primaryKeyIndex() const override { return Email; }
  int autoValueIndex() const override { return -1; }
  QString tableName() const override { return QStringLiteral("user"); }

private: /*** Don't modify below this line ***/
  Q_OBJECT
  Q_PROPERTY(QString email READ getemail WRITE setemail)
  T_DEFINE_PROPERTY(QString, email)
  Q_PROPERTY(QString password READ getpassword WRITE setpassword)
  T_DEFINE_PROPERTY(QString, password)
};
