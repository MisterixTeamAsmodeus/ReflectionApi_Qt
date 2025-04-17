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
class Converter<QDateTime> final
{
    static constexpr auto mask = "yyyy-MM-dd HH:mm:ss.zzz";

public:
    ~Converter() = default;

    void fillFromString(QDateTime& value, const std::string& str) const
    {
        value = QDateTime::fromString(QString::fromStdString(str), mask);
    }

    std::string convertToString(const QDateTime& value) const
    {
        return value.toString(mask).toStdString();
    }
};

template<>
class Converter<QDate> final
{
    static constexpr auto mask = "yyyy-MM-dd";

public:
    ~Converter() = default;

    void fillFromString(QDate& value, const std::string& str) const
    {
        value = QDate::fromString(QString::fromStdString(str), mask);
    }

    std::string convertToString(const QDate& value) const
    {
        return value.toString(mask).toStdString();
    }
};

template<>
class Converter<QString> final
{
public:
    ~Converter() = default;

    void fillFromString(QString& value, const std::string& str) const
    {
        value = QString::fromStdString(str);
    }

    std::string convertToString(const QString& value) const
    {
        return value.toStdString();
    }
};

template<>
class Converter<QByteArray> final
{
public:
    ~Converter() = default;

    void fillFromString(QByteArray& value, const std::string& str) const
    {
        value = QByteArray::fromStdString(str);
    }

    std::string convertToString(const QByteArray& value) const
    {
        return value.toStdString();
    }
};

} // namespace ReflectionApi