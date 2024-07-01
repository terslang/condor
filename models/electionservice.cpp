#include "electionservice.h"
#include "objects/election.h"
#include "objects/option.h"
#include <TreeFrogModel>

void
ElectionService::index()
{
  auto electionList = Election::getAll();
  texport(electionList);
}

void
ElectionService::show(int id)
{
  auto election = Election::get(id);
  auto optionList = Option::getByElectionId(id);
  texport(election);
  texport(optionList);
}

int
ElectionService::create(THttpRequest& request)
{
  auto election = request.formItems("election");
  auto model = Election::create(election);

  if (model.isNull()) {
    QString error = "Failed to create.";
    texport(error);
    texport(election);
    return -1;
  }

  QString notice = "Created successfully.";
  tflash(notice);
  return model.id();
}

void
ElectionService::edit(TSession& session, int id)
{
  auto model = Election::get(id);
  if (!model.isNull()) {
    auto election = model.toVariantMap();
    auto optionList = Option::getByElectionId(id);
    texport(election);
    texport(optionList);
  }
}

int
ElectionService::save(THttpRequest& request, TSession& session, int id)
{
  auto model = Election::get(id);

  if (model.isNull()) {
    QString error = "Original data not found. It may have been updated/removed "
                    "by another transaction.";
    tflash(error);
    return 0;
  }

  auto election = request.formItems("election");
  model.setProperties(election);
  if (!model.save()) {
    texport(election);
    QString error = "Failed to update.";
    texport(error);
    return -1;
  }

  QString notice = "Updated successfully.";
  tflash(notice);
  return 1;
}

bool
ElectionService::remove(int id)
{
  auto election = Election::get(id);
  return election.remove();
}
