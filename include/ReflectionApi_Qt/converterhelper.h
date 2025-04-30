#pragma once

#include "helper/sfinae.h"

#include <ReflectionApi/converterhelper.h>

#include <QDateTime>
#include <QString>

namespace reflection_api {
namespace impl {

///Реализация для классов имеющих оператор fromString
template<typename T, std::enable_if_t<sfinae::has_from_string_v<T>, bool> = true>
void fill_from_string(T& value, const std::string& str, int)
{
    value = T::fromString(QString::fromStdString(str));
}

///Реализация для классов имеющих оператор toString
template<typename T, std::enable_if_t<sfinae::has_to_string_v<T>, bool> = true>
std::string convert_to_string(const T& value, int)
{
    return value.toString().toStdString();
}

} // namespace impl

template<>
class converter<QDateTime>
{
    static constexpr auto mask = "yyyy-MM-dd HH:mm:ss.zzz";

public:
    virtual ~converter() = default;

    virtual void fill_from_string(QDateTime& value, const std::string& str) const
    {
        value = QDateTime::fromString(QString::fromStdString(str), mask);
    }

    virtual std::string convert_to_string(const QDateTime& value) const
    {
        return value.toString(mask).toStdString();
    }
};

template<>
class converter<QDate>
{
    static constexpr auto mask = "yyyy-MM-dd";

public:
    virtual ~converter() = default;

    virtual void fill_from_string(QDate& value, const std::string& str) const
    {
        value = QDate::fromString(QString::fromStdString(str), mask);
    }

    virtual std::string convert_to_string(const QDate& value) const
    {
        return value.toString(mask).toStdString();
    }
};

template<>
class converter<QString>
{
public:
    virtual ~converter() = default;

    virtual void fill_from_string(QString& value, const std::string& str) const
    {
        value = QString::fromStdString(str);
    }

    virtual std::string convert_to_string(const QString& value) const
    {
        return value.toStdString();
    }
};

template<>
class converter<QByteArray>
{
public:
    virtual ~converter() = default;

    virtual void fill_from_string(QByteArray& value, const std::string& str) const
    {
        value = QByteArray::fromStdString(str);
    }

    virtual std::string convert_to_string(const QByteArray& value) const
    {
        return value.toStdString();
    }
};

} // namespace reflection_api