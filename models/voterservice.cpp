#include "voterservice.h"
#include "objects/voter.h"
#include <TreeFrogModel>

void
VoterService::index()
{
  auto voterList = Voter::getAll();
  texport(voterList);
}

void
VoterService::show(const QString& email, int electionId)
{
  auto voter = Voter::get(email, electionId);
  texport(voter);
}

QString
VoterService::create(THttpRequest& request)
{
  auto voter = request.formItems("voter");
  auto model = Voter::create(voter);

  if (model.isNull()) {
    QString error = "Failed to create.";
    texport(error);
    texport(voter);
    return QString();
  }

  QString notice = "Created successfully.";
  tflash(notice);
  return model.email();
}

QString
VoterService::create(const QString& email, int electionId)
{
  auto model = Voter::create(email, electionId);

  if (model.isNull()) {
    QString error = "Failed to create voting record for " + email;
    texport(error);
    return QString();
  }

  return model.email();
}

void
VoterService::edit(TSession& session, const QString& email, int electionId)
{
  auto model = Voter::get(email, electionId);
  if (!model.isNull()) {
    auto voter = model.toVariantMap();
    texport(voter);
  }
}

int
VoterService::save(THttpRequest& request,
                   TSession& session,
                   const QString& email,
                   int electionId)
{
  auto model = Voter::get(email, electionId);

  if (model.isNull()) {
    QString error = "Original data not found. It may have been updated/removed "
                    "by another transaction.";
    tflash(error);
    return 0;
  }

  auto voter = request.formItems("voter");
  model.setProperties(voter);
  if (!model.save()) {
    texport(voter);
    QString error = "Failed to update.";
    texport(error);
    return -1;
  }

  QString notice = "Updated successfully.";
  tflash(notice);
  return 1;
}

bool
VoterService::remove(const QString& email, int electionId)
{
  auto voter = Voter::get(email, electionId);
  return voter.remove();
}

bool
VoterService::hasVoted(const QString& email, int electionId)
{
  bool votedAlready = !Voter::get(email, electionId).isNull();

  if (votedAlready) {
    QString error = email + " has already voted";
    texport(error);
    return true;
  }

  return false;
}
