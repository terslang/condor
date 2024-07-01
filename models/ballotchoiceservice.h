#pragma once
#include <TGlobal>

class THttpRequest;
class TSession;

class T_MODEL_EXPORT BallotChoiceService
{
public:
  void index();
  void show(const QString& ballotId);
  int createMany(THttpRequest& request, TSession& session, const QString& id);
  QString create(THttpRequest& request);
  void edit(TSession& session, const QString& ballotId);
  void showOptions(TSession& session, const QString& ballotId);
  int save(THttpRequest& request, TSession& session, const QString& ballotId);
  bool remove(const QString& ballotId);
};
