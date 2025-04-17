#pragma once

#include "helper/sfinae.h"

#include <ReflectionApi/converterhelper.h>

#include <QDateTime>
#include <QString>

namespace ReflectionApi {
namespace Impl {

template<typename T, std::enable_if_t<SFINAE::has_from_string_v<T>, bool> = true>
void fillFromString(T& value, const std::string& str, int)
{
    value = T::fromString(QString::fromStdString(str));
}

template<typename T, std::enable_if_t<SFINAE::has_to_string_v<T>, bool> = true>
std::string convertToString(const T& value, int)
{
    return value.toString().toStdString();
}

} // namespace Impl

template<>
class Converter<QDateTime>
{
    static constexpr auto mask = "yyyy-MM-dd HH:mm:ss.zzz";

public:
    virtual ~Converter() = default;

    virtual void fillFromString(QDateTime& value, const std::string& str) const
    {
        value = QDateTime::fromString(QString::fromStdString(str), mask);
    }

    virtual std::string convertToString(const QDateTime& value) const
    {
        return value.toString(mask).toStdString();
    }
};

template<>
class Converter<QDate>
{
    static constexpr auto mask = "yyyy-MM-dd";

public:
    virtual ~Converter() = default;

    virtual void fillFromString(QDate& value, const std::string& str) const
    {
        value = QDate::fromString(QString::fromStdString(str), mask);
    }

    virtual std::string convertToString(const QDate& value) const
    {
        return value.toString(mask).toStdString();
    }
};

template<>
class Converter<QString>
{
public:
    virtual ~Converter() = default;

    virtual void fillFromString(QString& value, const std::string& str) const
    {
        value = QString::fromStdString(str);
    }

    virtual std::string convertToString(const QString& value) const
    {
        return value.toStdString();
    }
};

template<>
class Converter<QByteArray>
{
public:
    virtual ~Converter() = default;

    virtual void fillFromString(QByteArray& value, const std::string& str) const
    {
        value = QByteArray::fromStdString(str);
    }

    virtual std::string convertToString(const QByteArray& value) const
    {
        return value.toStdString();
    }
};

} // namespace ReflectionApi