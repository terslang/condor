#pragma once
#include <QDateTime>
#include <QSharedDataPointer>
#include <QStringList>
#include <QVariant>
#include <TAbstractModel>
#include <TGlobal>

class TModelObject;
class BallotObject;
class QJsonArray;

class T_MODEL_EXPORT Ballot : public TAbstractModel
{
public:
  Ballot();
  Ballot(const Ballot& other);
  Ballot(const BallotObject& object);
  ~Ballot();

  QString id() const;
  void setId(const QString& id);
  int electionId() const;
  void setElectionId(int electionId);
  Ballot& operator=(const Ballot& other);

  bool create() override { return TAbstractModel::create(); }
  bool update() override { return TAbstractModel::update(); }
  bool save() override { return TAbstractModel::save(); }
  bool remove() override { return TAbstractModel::remove(); }

  static Ballot create(const QString& id, int electionId);
  static Ballot create(const QVariantMap& values);
  static Ballot get(const QString& id);
  static int count();
  static QList<Ballot> getAll();
  static QJsonArray getAllJson(const QStringList& properties = QStringList());

private:
  QSharedDataPointer<BallotObject> d;

  TModelObject* modelData() override;
  const TModelObject* modelData() const override;
  friend T_MODEL_EXPORT QDataStream& operator<<(QDataStream& ds,
                                                const Ballot& model);
  friend T_MODEL_EXPORT QDataStream& operator>>(QDataStream& ds, Ballot& model);
};

Q_DECLARE_METATYPE(Ballot)
Q_DECLARE_METATYPE(QList<Ballot>)
