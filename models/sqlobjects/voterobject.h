#pragma once
#include <QSharedData>
#include <TSqlObject>

class T_MODEL_EXPORT VoterObject
  : public TSqlObject
  , public QSharedData
{
public:
  QString email;
  int election_id{ 0 };

  enum PropertyIndex
  {
    Email = 0,
    ElectionId,
  };

  int primaryKeyIndex() const override { return Email; }
  int autoValueIndex() const override { return -1; }
  QString tableName() const override { return QStringLiteral("voter"); }

private: /*** Don't modify below this line ***/
  Q_OBJECT
  Q_PROPERTY(QString email READ getemail WRITE setemail)
  T_DEFINE_PROPERTY(QString, email)
  Q_PROPERTY(int election_id READ getelection_id WRITE setelection_id)
  T_DEFINE_PROPERTY(int, election_id)
};
