#pragma once
#include <QSharedData>
#include <TSqlObject>

class T_MODEL_EXPORT BallotChoiceObject
  : public TSqlObject
  , public QSharedData
{
public:
  QString ballot_id;
  QString option_id;
  int rank{ 0 };

  enum PropertyIndex
  {
    BallotId = 0,
    OptionId,
    Rank,
  };

  int primaryKeyIndex() const override { return BallotId; }
  int autoValueIndex() const override { return -1; }
  QString tableName() const override { return QStringLiteral("ballot_choice"); }

private: /*** Don't modify below this line ***/
  Q_OBJECT
  Q_PROPERTY(QString ballot_id READ getballot_id WRITE setballot_id)
  T_DEFINE_PROPERTY(QString, ballot_id)
  Q_PROPERTY(QString option_id READ getoption_id WRITE setoption_id)
  T_DEFINE_PROPERTY(QString, option_id)
  Q_PROPERTY(int rank READ getrank WRITE setrank)
  T_DEFINE_PROPERTY(int, rank)
};
