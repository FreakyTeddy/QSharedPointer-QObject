/*
 * MyModel.h
 *
 *  Created on: 12/03/2014
 *      Author: vidueirof
 */

#ifndef MYMODEL_H_
#define MYMODEL_H_

#include <qobject.h>

#include <QSharedPointer>
#include <QDebug>

/**
 * This class becomes a wrapper for the dynamic data..
 * this object can be copied around and data will be safely guarded by the shared pointer
 * it can also be sent to the qml view
 */
class MyModel: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY ageChanged FINAL)

public:
    MyModel(QObject* parent = 0) : QObject(parent), m_attr(new __MyModel()) {}
    MyModel(QString name, int age, QObject* parent = 0) : QObject(parent), m_attr(new __MyModel())
    {
        m_attr->name = name;
        m_attr->age = age;
    }
    MyModel(const MyModel& other) : QObject(other.parent()), m_attr(other.m_attr) {}

    virtual ~MyModel()
    {
        qDebug()<<"Model destroyed: " << m_attr->name;
    }

    QString getName() const
    {
        return m_attr->name;
    }

    int getAge() const
    {
        return m_attr->age;
    }

    Q_SLOT void setAge(int age)
    {
        if(age>=0)
        {
            m_attr->age = age;
            emit ageChanged(age);
        }
    }

    Q_SLOT void setName(const QString& name)
    {
        if(!name.isNull())
        {
            m_attr->name = name;
            emit nameChanged(name);
        }
    }

    MyModel& operator=(const MyModel& other)
    {
        this->m_attr = other.m_attr;
        return *this;
    }

    Q_INVOKABLE void changeParent(QObject* parent=0)
    {
        this->setParent(parent);
    }

Q_SIGNALS:
    void ageChanged(const int newAge);
    void nameChanged(const QString &newName);

private:

    struct __MyModel{
        QString name;
        int     age;
    };

    QSharedPointer<__MyModel> m_attr;
};


#endif /* MYMODEL_H_ */
