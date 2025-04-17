#include <ReflectionApi_Qt/reflectionapi-qt.h>

#include <QDateTime>
#include <QUuid>

#include <iostream>

template<typename Type>
void test_type(const Type& start_value)
{
    auto type_converter = ReflectionApi::Converter<Type>();
    auto type_s = type_converter.convertToString(start_value);
    Type type_c;
    type_converter.fillFromString(type_c, type_s);

    assert(start_value == type_c);
}

int main()
{
    test_type(QDateTime::currentDateTime());
    test_type(QDate::currentDate());
    test_type(QUuid::createUuid());
    test_type(QString("test_value"));
    test_type(QByteArray("test_value"));
}
