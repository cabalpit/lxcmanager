#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QSqlQuery>

#include "datalayer/distributionmodel.h"
#include "datalayer/imagemodel.h"


namespace businesslayer {
    class Controller;
}

class Controller: public QObject
{
        Q_OBJECT
    public:
         Controller(QObject *parent = nullptr);
         ~Controller();

        QStringList distributions();
        QStringList release(QString distrib);
        QStringList architectures(QString release);
        QStringList variants(QString arch);

    public slots:
        void clear();

    protected:

    private:
        model::DistributionModel *m_distribModel;
        model::ImageModel *m_imageModel;

         QHash<QString, QVariant> m_distribution;
         QHash<QString, QVariant> m_release;
         QHash<QString, QVariant> m_architecture;
         QHash<QString, QVariant> m_variant;

         QString m_idxDistrib;
         QString m_idxRelease;
         QString m_idxArch;
};

#endif // CONTROLLER_H
