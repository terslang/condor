#pragma once
#include <QDateTime>
#include <QSharedDataPointer>
#include <QStringList>
#include <QVariant>
#include <TAbstractModel>
#include <TGlobal>

class TModelObject;
class BallotChoiceObject;
class QJsonArray;

class T_MODEL_EXPORT BallotChoice : public TAbstractModel
{
public:
  BallotChoice();
  BallotChoice(const BallotChoice& other);
  BallotChoice(const BallotChoiceObject& object);
  ~BallotChoice();

  QString ballotId() const;
  void setBallotId(const QString& ballotId);
  QString optionId() const;
  void setOptionId(const QString& optionId);
  int rank() const;
  void setRank(int rank);
  BallotChoice& operator=(const BallotChoice& other);

  bool create() override { return TAbstractModel::create(); }
  bool update() override { return TAbstractModel::update(); }
  bool save() override { return TAbstractModel::save(); }
  bool remove() override { return TAbstractModel::remove(); }

  static BallotChoice create(const QString& ballotId,
                             const QString& optionId,
                             int rank);
  static BallotChoice create(const QVariantMap& values);
  static BallotChoice update(const QString& ballotId,
                             const QString& optionId,
                             int rank);
  static BallotChoice get(const QString& ballotId);
  static QList<BallotChoice> getByBallotId(const QString& ballotId);
  static int count();
  static int getOutrankingCount(const QString& optionAId,
                                const QString& optionBId);
  static QList<BallotChoice> getAll();
  static QJsonArray getAllJson(const QStringList& properties = QStringList());

private:
  QSharedDataPointer<BallotChoiceObject> d;

  TModelObject* modelData() override;
  const TModelObject* modelData() const override;
  friend T_MODEL_EXPORT QDataStream& operator<<(QDataStream& ds,
                                                const BallotChoice& model);
  friend T_MODEL_EXPORT QDataStream& operator>>(QDataStream& ds,
                                                BallotChoice& model);
};

Q_DECLARE_METATYPE(BallotChoice)
Q_DECLARE_METATYPE(QList<BallotChoice>)
