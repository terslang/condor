#pragma once
#include <TGlobal>

class THttpRequest;
class TSession;


class T_MODEL_EXPORT BallotService {
public:
    void index();
    void show(const QString &id);
    QString create(THttpRequest &request);
    void edit(TSession &session, const QString &id);
    int save(THttpRequest &request, TSession &session, const QString &id);
    bool remove(const QString &id);
};

