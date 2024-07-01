#include "ballotchoiceservice.h"
#include "objects/ballot.h"
#include "objects/ballotchoice.h"
#include "objects/option.h"
#include <TreeFrogModel>
#include <algorithm>

void
BallotChoiceService::index()
{
  auto ballotChoiceList = BallotChoice::getAll();
  texport(ballotChoiceList);
}

void
BallotChoiceService::show(const QString& ballotId)
{
  auto ballotChoice = BallotChoice::get(ballotId);
  texport(ballotChoice);
}

int
BallotChoiceService::createMany(THttpRequest& request,
                                TSession& session,
                                const QString& ballotId)
{
  auto model = Ballot::get(ballotId);

  if (model.isNull()) {
    QString error = "Original ballot not found. It may have been "
                    "updated/removed by another transaction.";
    tflash(error);
    return 0;
  }

  auto choices = request.formItems("choices");
  auto options = Option::getByElectionId(model.electionId());
  auto visited = QList<bool>(options.size(), false);
  qsizetype maxRank = options.size();

  for (QVariantMap::const_iterator iter = choices.begin();
       iter != choices.end();
       ++iter) {
    // check if option is valid
    auto optionIter =
      std::find_if(options.begin(), options.end(), [&iter](Option opt) {
        return opt.id() == iter.key();
      });
    if (optionIter == options.end()) {
      QString error = "Option not valid for current ballot";
      tflash(error);
      return -1;
    }

    // remove the option to prevent recasting
    options.erase(optionIter);
    bool intParseOk = false;
    int rank = iter.value().toInt(&intParseOk);
    if (!intParseOk) {
      QString error = "Error parsing int " + iter.value().toString();
      tflash(error);
      return -1;
    }

    if (rank > maxRank || rank < 1 || visited[rank]) {
      QString error =
        "Invalid rank preference provided " + iter.value().toString();
      tflash(error);
      return -1;
    }

    auto choice = BallotChoice::create(ballotId, iter.key(), rank);
    if (choice.isNull()) {
      QString error = "Error inserting ballot choice for ballot " + ballotId +
                      "and option " + iter.key();
      tflash(error);
      return -1;
    }

    visited[rank] = true;
  }

  QString notice = "Updated successfully.";
  tflash(notice);
  return 1;
}

QString
BallotChoiceService::create(THttpRequest& request)
{
  auto ballotChoice = request.formItems("ballotChoice");
  auto model = BallotChoice::create(ballotChoice);

  if (model.isNull()) {
    QString error = "Failed to create.";
    texport(error);
    texport(ballotChoice);
    return QString();
  }

  QString notice = "Created successfully.";
  tflash(notice);
  return model.ballotId();
}

void
BallotChoiceService::edit(TSession& session, const QString& ballotId)
{
  auto model = BallotChoice::get(ballotId);
  if (!model.isNull()) {
    auto ballotChoice = model.toVariantMap();
    texport(ballotChoice);
  }
}

void
BallotChoiceService::showOptions(TSession& session, const QString& ballotId)
{
  auto model = Ballot::get(ballotId);
  auto optionList = Option::getByElectionId(model.electionId());

  if (!model.isNull()) {
    auto ballot = model.toVariantMap();
    texport(ballot);
    texport(optionList);
  }
}

int
BallotChoiceService::save(THttpRequest& request,
                          TSession& session,
                          const QString& ballotId)
{
  auto model = BallotChoice::get(ballotId);

  if (model.isNull()) {
    QString error = "Original data not found. It may have been updated/removed "
                    "by another transaction.";
    tflash(error);
    return 0;
  }

  auto ballotChoice = request.formItems("ballotChoice");
  model.setProperties(ballotChoice);
  if (!model.save()) {
    texport(ballotChoice);
    QString error = "Failed to update.";
    texport(error);
    return -1;
  }

  QString notice = "Updated successfully.";
  tflash(notice);
  return 1;
}

bool
BallotChoiceService::remove(const QString& ballotId)
{
  auto ballotChoice = BallotChoice::get(ballotId);
  return ballotChoice.remove();
}
