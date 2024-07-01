#pragma once
#include <QDateTime>
#include <QSharedDataPointer>
#include <QStringList>
#include <QVariant>
#include <TAbstractModel>
#include <TGlobal>

class TModelObject;
class PairwiseContestObject;
class QJsonArray;

class T_MODEL_EXPORT PairwiseContest : public TAbstractModel
{
public:
  PairwiseContest();
  PairwiseContest(const PairwiseContest& other);
  PairwiseContest(const PairwiseContestObject& object);
  ~PairwiseContest();

  int electionId() const;
  QString optionAId() const;
  void setOptionAId(const QString& optionAId);
  QString optionBId() const;
  void setOptionBId(const QString& optionBId);
  int optionACount() const;
  void setOptionACount(int optionACount);
  int optionBCount() const;
  void setOptionBCount(int optionBCount);
  PairwiseContest& operator=(const PairwiseContest& other);

  bool create() override { return TAbstractModel::create(); }
  bool update() override { return TAbstractModel::update(); }
  bool save() override { return TAbstractModel::save(); }
  bool remove() override { return TAbstractModel::remove(); }

  static PairwiseContest create(int electionId,
                                const QString& optionAId,
                                const QString& optionBId,
                                int optionACount,
                                int optionBCount);
  static PairwiseContest create(const QVariantMap& values);
  static QList<PairwiseContest> get(int electionId);
  static int count();
  static QList<PairwiseContest> getAll();
  static QJsonArray getAllJson(const QStringList& properties = QStringList());

private:
  QSharedDataPointer<PairwiseContestObject> d;

  TModelObject* modelData() override;
  const TModelObject* modelData() const override;
  friend T_MODEL_EXPORT QDataStream& operator<<(QDataStream& ds,
                                                const PairwiseContest& model);
  friend T_MODEL_EXPORT QDataStream& operator>>(QDataStream& ds,
                                                PairwiseContest& model);
};

Q_DECLARE_METATYPE(PairwiseContest)
Q_DECLARE_METATYPE(QList<PairwiseContest>)
