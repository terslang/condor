#pragma once
#include <TGlobal>

class THttpRequest;
class TSession;


class T_MODEL_EXPORT UserService {
public:
    void index();
    void show(const QString &email);
    QString create(THttpRequest &request);
    void edit(TSession &session, const QString &email);
    int save(THttpRequest &request, TSession &session, const QString &email);
    bool remove(const QString &email);
};

