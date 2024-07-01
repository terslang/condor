#pragma once
#include <QSharedData>
#include <TSqlObject>

class T_MODEL_EXPORT BallotObject
  : public TSqlObject
  , public QSharedData
{
public:
  QString id;
  int election_id{ 0 };

  enum PropertyIndex
  {
    Id = 0,
    ElectionId,
  };

  int primaryKeyIndex() const override { return Id; }
  int autoValueIndex() const override { return -1; }
  QString tableName() const override { return QStringLiteral("ballot"); }

private: /*** Don't modify below this line ***/
  Q_OBJECT
  Q_PROPERTY(QString id READ getid WRITE setid)
  T_DEFINE_PROPERTY(QString, id)
  Q_PROPERTY(int election_id READ getelection_id WRITE setelection_id)
  T_DEFINE_PROPERTY(int, election_id)
};
