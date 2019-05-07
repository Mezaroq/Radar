#ifndef RAIL_H
#define RAIL_H

#include <QObject>

class Rail : public QObject
{
    Q_OBJECT
public:
    explicit Rail(QObject *parent = nullptr);

signals:

public slots:
};

#endif // RAIL_H