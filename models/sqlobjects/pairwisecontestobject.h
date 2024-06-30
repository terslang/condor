#pragma once
#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT PairwiseContestObject : public TSqlObject, public QSharedData {
public:
    int election_id {0};
    QString option_a_id;
    QString option_b_id;
    int option_a_count {0};
    int option_b_count {0};

    enum PropertyIndex {
        ElectionId = 0,
        OptionAId,
        OptionBId,
        OptionACount,
        OptionBCount,
    };

    int primaryKeyIndex() const override { return ElectionId; }
    int autoValueIndex() const override { return -1; }
    QString tableName() const override { return QStringLiteral("pairwise_contest"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int election_id READ getelection_id WRITE setelection_id)
    T_DEFINE_PROPERTY(int, election_id)
    Q_PROPERTY(QString option_a_id READ getoption_a_id WRITE setoption_a_id)
    T_DEFINE_PROPERTY(QString, option_a_id)
    Q_PROPERTY(QString option_b_id READ getoption_b_id WRITE setoption_b_id)
    T_DEFINE_PROPERTY(QString, option_b_id)
    Q_PROPERTY(int option_a_count READ getoption_a_count WRITE setoption_a_count)
    T_DEFINE_PROPERTY(int, option_a_count)
    Q_PROPERTY(int option_b_count READ getoption_b_count WRITE setoption_b_count)
    T_DEFINE_PROPERTY(int, option_b_count)
};

