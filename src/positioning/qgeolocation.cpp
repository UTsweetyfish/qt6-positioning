/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtPositioning module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qgeolocation.h"
#include "qgeolocation_p.h"

QT_BEGIN_NAMESPACE

QGeoLocationPrivate::QGeoLocationPrivate()
    : QSharedData()
{
}

QGeoLocationPrivate::QGeoLocationPrivate(const QGeoLocationPrivate &other)
    : QSharedData()
{
    this->address = other.address;
    this->coordinate = other.coordinate;
    this->viewport = other.viewport;
    this->extendedAttributes = other.extendedAttributes;
}

QGeoLocationPrivate::~QGeoLocationPrivate()
{
}

bool QGeoLocationPrivate::operator==(const QGeoLocationPrivate &other) const
{
    return  (this->address == other.address
            && this->coordinate == other.coordinate
            && this->viewport == other.viewport
            && this->extendedAttributes == other.extendedAttributes);

}

bool QGeoLocationPrivate::isEmpty() const
{
    return (address.isEmpty()
            && !coordinate.isValid()
            && viewport.isEmpty()
            && extendedAttributes.isEmpty());
}

/*!
    \class QGeoLocation
    \inmodule QtPositioning
    \ingroup QtPositioning-positioning
    \ingroup QtLocation-places
    \ingroup QtLocation-places-data
    \since 5.2

    \brief The QGeoLocation class represents basic information about a location.

    A QGeoLocation consists of a coordinate and corresponding address, along with an optional
    bounding shape, which is the recommended region to be displayed when viewing the location.
*/

/*!
    Constructs an new location object.
*/
QGeoLocation::QGeoLocation()
    : d(new QGeoLocationPrivate)
{
}

/*!
    Constructs a copy of \a other
*/
QGeoLocation::QGeoLocation(const QGeoLocation &other)
    :d(other.d)
{
}

/*!
    \fn QGeoLocation::QGeoLocation(QGeoLocation &&other)
    \since 6.2

    Constructs a geo location object by moving from \a other.

    \note The moved-from QGeoLocation object can only be destroyed or
    assigned to. The effect of calling other functions than the destructor
    or one of the assignment operators is undefined.
*/

/*!
    Destroys the location object.
*/
QGeoLocation::~QGeoLocation()
{
}

QT_DEFINE_QSDP_SPECIALIZATION_DTOR(QGeoLocationPrivate)

/*!
    Assigns \a other to this location and returns a reference to this location.
*/
QGeoLocation &QGeoLocation::operator =(const QGeoLocation &other)
{
    if (this == &other)
        return *this;

    d = other.d;
    return *this;
}

/*!
    \fn QGeoLocation &QGeoLocation::operator=(QGeoLocation &&other)
    \since 6.2

    Move-assings \a other to this location and returns a reference to this
    location.

    \note The moved-from QGeoLocation object can only be destroyed or
    assigned to. The effect of calling other functions than the destructor
    or one of the assignment operators is undefined.
*/

/*!
    \fn bool QGeoLocation::operator==(const QGeoLocation &lhs, const QGeoLocation &rhs)

    Returns \c true if the \a lhs location is equal to \a rhs, otherwise
    returns \c false.
*/

/*!
    \fn bool QGeoLocation::operator!=(const QGeoLocation &lhs, const QGeoLocation &rhs)

    Returns \c true if the \a lhs location is not equal to \a rhs, otherwise
    returns \c false.
*/

/*!
    Returns the address of the location.
*/
QGeoAddress QGeoLocation::address() const
{
    return d->address;
}

/*!
    Sets the \a address of the location.
*/
void QGeoLocation::setAddress(const QGeoAddress &address)
{
    d->address = address;
}

/*!
    Returns the coordinate of the location.
*/
QGeoCoordinate QGeoLocation::coordinate() const
{
    return d->coordinate;
}

/*!
    Sets the \a coordinate of the location.
*/
void QGeoLocation::setCoordinate(const QGeoCoordinate &coordinate)
{
    d->coordinate = coordinate;
}

/*!
    \since 6.2

    Returns a bounding shape which represents the recommended region
    to display when viewing this location.

    For example, a building's location may have a region centered around the
    building, but the region is large enough to show it's immediate surrounding
    geographical context.

    \note This method was introduced in Qt6 instead of boundingBox() method.
    It returns a QGeoShape instead of a QGeoRectangle.
    Use \l QGeoShape::boundingGeoRectangle() to obtain a bounding QGeoRectangle
    for the shape.
*/
QGeoShape QGeoLocation::boundingShape() const
{
    return d->viewport;
}

/*!
    \since 6.2

    Sets the \a boundingShape of the location.
*/
void QGeoLocation::setBoundingShape(const QGeoShape &boundingShape)
{
    d->viewport = boundingShape;
}

/*!
    Returns the extended attributes associated to this location.
    Extended attributes are backend-dependent and can be location-dependent.

    \since 5.13
*/
QVariantMap QGeoLocation::extendedAttributes() const
{
    return d->extendedAttributes;
}

/*!
    Sets the extended attributes of the location with the
    parameters specified in \a data.

    \since 5.13
*/
void QGeoLocation::setExtendedAttributes(const QVariantMap &data)
{
    d->extendedAttributes = data;
}

/*!
    Returns \c true if the location coordinate is \l {QGeoCoordinate::isValid}
    {invalid}, and all the other location fields are empty. Otherwise returns
    \c false.
*/
bool QGeoLocation::isEmpty() const
{
    return d->isEmpty();
}

bool QGeoLocation::equals(const QGeoLocation &lhs, const QGeoLocation &rhs)
{
    return (*(lhs.d.constData()) == *(rhs.d.constData()));
}

/*!
    \relates QGeoLocation

    Returns the hash value for the \a location, using \a seed for the
    calculation.

    \note The hash does not take extended attributes into account. This means
    that two geo location objects that differ only in the extended attributes
    will provide similar hashes.
*/
size_t qHash(const QGeoLocation &location, size_t seed) noexcept
{
    return qHashMulti(seed, location.coordinate(), location.boundingShape(), location.address());
}

QT_END_NAMESPACE
