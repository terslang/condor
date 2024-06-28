#include "ballotservice.h"
#include "objects/ballot.h"
#include "objects/ballotchoice.h"
#include "objects/option.h"
#include "thttprequest.h"
#include <TreeFrogModel>
#include <algorithm>
#include <iterator>
#include <quuid.h>


void BallotService::index()
{
    auto ballotList = Ballot::getAll();
    texport(ballotList);
}

void BallotService::show(const QString &id)
{
    auto ballot = Ballot::get(id);
    if(ballot.isNull())
    {
      return;
    }
    auto ballotchoice = BallotChoice::getByBallotId(id);
    auto options = Option::getByElectionId(ballot.electionId());

    QList<QVariantMap> choices {};

    // must use back_inserter. choices.begin() won't work
    std::transform(ballotchoice.begin(), ballotchoice.end(), std::back_inserter(choices),
                   [](BallotChoice b){ return b.toVariantMap(); });
    
    for(auto it = choices.begin(); it != choices.end(); it++)
    {
        auto optionIter = std::find_if(options.begin(), options.end(),
                                   [&it](const Option& o){ return o.id() == (*it)["optionId"]; });
        if(optionIter != options.end())
        {
            (*it)["name"] = (*optionIter).name();
            (*it)["body"] = (*optionIter).body();
        }
        else
        {
          qDebug() << "Failed to find option" << *it;
        }
    }

    texport(ballot);
    texport(choices);
}

QString BallotService::create(THttpRequest &request)
{
    auto ballot = request.formItems("ballot");
    ballot["id"] = QUuid::createUuid().toString(QUuid::WithoutBraces);
    auto model = Ballot::create(ballot);

    if (model.isNull()) {
        QString error = "Failed to create.";
        texport(error);
        texport(ballot);
        return QString();
    }
    
    QString notice = "Created successfully.";
    tflash(notice);
    return model.id();
}

void BallotService::edit(TSession& session, const QString &id)
{
    auto model = Ballot::get(id);
    auto choices = BallotChoice::getByBallotId(id);

    if (!model.isNull()) {
        auto ballot = model.toVariantMap();
        texport(ballot);
        texport(choices);
    }
}

int BallotService::save(THttpRequest &request, TSession &session, const QString &id)
{
    auto model = Ballot::get(id);
    
    if (model.isNull()) {
        QString error = "Original data not found. It may have been updated/removed by another transaction.";
        tflash(error);
        return 0;
    }

    auto ballot = request.formItems("ballot");
    model.setProperties(ballot);
    
    if (!model.save()) {
        texport(ballot);
        QString error = "Failed to update.";
        texport(error);
        return -1;
    }

    auto choices = ballot["choices"].value<QVariantMap>();

    QString notice = "Updated successfully.";
    tflash(notice);
    return 1;
}

bool BallotService::remove(const QString &id)
{
    auto ballot = Ballot::get(id);
    return ballot.remove();
}

