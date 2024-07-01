#include "optionservice.h"
#include "objects/option.h"
#include <TreeFrogModel>

void
OptionService::index()
{
  auto optionList = Option::getAll();
  texport(optionList);
}

void
OptionService::show(const QString& id)
{
  auto option = Option::get(id);
  texport(option);
}

QString
OptionService::create(THttpRequest& request)
{
  auto option = request.formItems("option");
  option["id"] = QUuid::createUuid().toString(QUuid::WithoutBraces);
  auto model = Option::create(option);
  if (model.isNull()) {
    QString error = "Failed to create.";
    texport(error);
    texport(option);
    return QString();
  }

  QString notice = "Created successfully.";
  tflash(notice);
  return model.id();
}

void
OptionService::edit(TSession& session, const QString& id)
{
  auto model = Option::get(id);
  if (!model.isNull()) {
    auto option = model.toVariantMap();
    texport(option);
  }
}

int
OptionService::save(THttpRequest& request, TSession& session, const QString& id)
{
  auto model = Option::get(id);

  if (model.isNull()) {
    QString error = "Original data not found. It may have been updated/removed "
                    "by another transaction.";
    tflash(error);
    return 0;
  }

  auto option = request.formItems("option");
  model.setProperties(option);
  if (!model.save()) {
    texport(option);
    QString error = "Failed to update.";
    texport(error);
    return -1;
  }

  QString notice = "Updated successfully.";
  tflash(notice);
  return 1;
}

bool
OptionService::remove(const QString& id)
{
  auto option = Option::get(id);
  return option.remove();
}
