#pragma once
#include <QDateTime>
#include <QSharedDataPointer>
#include <QStringList>
#include <QVariant>
#include <TAbstractModel>
#include <TGlobal>

class TModelObject;
class VoterObject;
class QJsonArray;

class T_MODEL_EXPORT Voter : public TAbstractModel
{
public:
  Voter();
  Voter(const Voter& other);
  Voter(const VoterObject& object);
  ~Voter();

  QString email() const;
  void setEmail(const QString& email);
  int electionId() const;
  Voter& operator=(const Voter& other);

  bool create() override { return TAbstractModel::create(); }
  bool update() override { return TAbstractModel::update(); }
  bool save() override { return TAbstractModel::save(); }
  bool remove() override { return TAbstractModel::remove(); }

  static Voter create(const QString& email, int electionId);
  static Voter create(const QVariantMap& values);
  static Voter get(const QString& email, int electionId);
  static int count();
  static QList<Voter> getAll();
  static QJsonArray getAllJson(const QStringList& properties = QStringList());

private:
  QSharedDataPointer<VoterObject> d;

  TModelObject* modelData() override;
  const TModelObject* modelData() const override;
  friend T_MODEL_EXPORT QDataStream& operator<<(QDataStream& ds,
                                                const Voter& model);
  friend T_MODEL_EXPORT QDataStream& operator>>(QDataStream& ds, Voter& model);
};

Q_DECLARE_METATYPE(Voter)
Q_DECLARE_METATYPE(QList<Voter>)
