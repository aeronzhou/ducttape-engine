
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Scene/Vector3.hpp>

namespace dt {
    Vector3::Vector3() : mVec(0.0f, 0.0f, 0.0f) {}

    Vector3::Vector3(const Vector3 &other) : mVec(other.mVec) {}

    Vector3::Vector3(const float x, const float y, const float z)
        : mVec(x, y, z) {}

    Vector3::Vector3(const Ogre::Vector3 &ogre_vector)
        : mVec(ogre_vector) {}

    Vector3::Vector3(const btVector3 &bt_vector)
        : mVec(bt_vector.getX(), bt_vector.getY(), bt_vector.getZ()) {}

    Ogre::Vector3 & Vector3::getOgreVector3() {
        return mVec;
    }

    const Ogre::Vector3 & Vector3::getOgreVector3() const {
        return mVec;
    }

    btVector3 Vector3::getBulletVector3() const {
        return btVector3(mVec.x, mVec.y, mVec.z);
    }

    const Vector3 Vector3::ZERO( 0, 0, 0 );
    const Vector3 Vector3::UNIT_X( 1, 0, 0 );
    const Vector3 Vector3::UNIT_Y( 0, 1, 0 );
    const Vector3 Vector3::UNIT_Z( 0, 0, 1 );
    const Vector3 Vector3::NEGATIVE_UNIT_X( -1,  0,  0 );
    const Vector3 Vector3::NEGATIVE_UNIT_Y(  0, -1,  0 );
    const Vector3 Vector3::NEGATIVE_UNIT_Z(  0,  0, -1 );
    const Vector3 Vector3::UNIT_SCALE(1, 1, 1);

    void Vector3::swap(Vector3& other) {
        mVec.swap(other.mVec);
    }

    Ogre::Real Vector3::getDistance(const Vector3& other) const {
        return mVec.distance(other.mVec);
    }

    Ogre::Real Vector3::dotProduct(const Vector3& other) const {
        return mVec.dotProduct(other.mVec);
    }

    bool Vector3::operator == (const Vector3& other) const {
        return mVec == other.mVec;
    }

    bool Vector3::operator != (const Vector3& other) const {
        return mVec != other.mVec;
    }

    Vector3 Vector3::crossProduct(const Vector3& other) const {
        return mVec.crossProduct(other.mVec);
    }

    QScriptValue Vector3::toQtScriptObject() {
        return ScriptManager::get()->getScriptEngine()->newQObject(this);
    }

    Vector3 Vector3::getRandomDeviant(float angle_range) const {
        return Vector3(mVec.randomDeviant(Ogre::Degree(angle_range)));
    }

    Ogre::Real Vector3::getAngleBetween(const Vector3& other) {
        return mVec.angleBetween(other.mVec).valueRadians();
    }

    Ogre::Quaternion Vector3::getRotationTo(const Vector3& other) const {
        return mVec.getRotationTo(other.mVec);
    }

    Vector3 Vector3::getReflection(Vector3& normal) const {
        return Vector3(mVec.reflect(normal.mVec));
    }

    Vector3 Vector3::operator + (const Vector3& other) const {
        return Vector3(mVec + other.mVec);
    }

    Vector3 Vector3::operator - (const Vector3& other) const {
        return Vector3(mVec - other.mVec);
    }

    Vector3 Vector3::operator - () const {
        return Vector3(-mVec);
    }

    Vector3 Vector3::operator * (const float multiplier) const {
        return Vector3(mVec * multiplier);
    }

    Vector3 Vector3::operator * (const Vector3& multiplier) const {
        return Vector3(mVec.crossProduct(multiplier.mVec));
    }

    Vector3 Vector3::operator = (const Vector3& other) {
        mVec = other.mVec;
        return *this;
    }

    void Vector3::normalise() {
        mVec.normalise();
    }

    bool Vector3::isZero() const {
        return mVec.isZeroLength();
    }

    float Vector3::getX() const {
        return mVec.x;
    }

    float Vector3::getY() const {
        return mVec.y;
    }

    float Vector3::getZ() const {
        return mVec.z;
    }

    void Vector3::setX(const float x) {
        if(mVec.x != x)
            mVec.x = x;
    }

    void Vector3::setY(const float y) {
        if(mVec.y != y)
            mVec.y = y;
    }

    void Vector3::setZ(const float z) {
        if(mVec.z != z)
            mVec.z = z;
    }

    float Vector3::getLength() const {
        return mVec.length();
    }

    void Vector3::scriptSwap(QScriptValue other) {
        if(other.isQObject()) {
            Vector3* p_vec = (Vector3*)other.toQObject();

            if(p_vec != nullptr) {
                swap(*p_vec);
            }
            else {
                Logger::get().debug("The Vector3 you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Vector3 object.");
        }
    }

    float Vector3::scriptGetDistance(QScriptValue other) const {
        if(other.isQObject()) {
            Vector3* p_vec = (Vector3*)other.toQObject();

            if(p_vec != nullptr) {
                return getDistance(*p_vec);
            }
            else {
                Logger::get().debug("The Vector3 you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Vector3 object.");
        }

        return 0.0f;
    }

    float Vector3::scriptDotProduct(QScriptValue other) const {
        if(other.isQObject()) {
            Vector3* p_vec = (Vector3*)other.toQObject();

            if(p_vec != nullptr) {
                return dotProduct(*p_vec);
            }
            else {
                Logger::get().debug("The Vector3 you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Vector3 object.");
        }

        return 0.0f;
    }

    QScriptValue Vector3::scriptCrossProduct(QScriptValue other) const {
        if(other.isQObject()) {
            Vector3* p_vec = (Vector3*)other.toQObject();

            if(p_vec != nullptr) {
                return crossProduct(*p_vec).toQtScriptObject();
            }
            else {
                Logger::get().debug("The Vector3 you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Vector3 object.");
        }

        return QScriptValue::UndefinedValue;
    }

    QScriptValue Vector3::scriptGetRandomDeviant(float angle_range) const {
        return getRandomDeviant(angle_range).toQtScriptObject();
    }

    float Vector3::scriptGetAngleBetween(QScriptValue other) {
        if(other.isQObject()) {
            Vector3* p_vec = (Vector3*)other.toQObject();

            if(p_vec != nullptr) {
                return this->getAngleBetween(*p_vec);
            }
            else {
                Logger::get().debug("The Vector3 you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Vector3 object.");
        }

        return 0.0f;
    }

    QScriptValue Vector3::scriptGetRotationTo(QScriptValue other) const {
        if(other.isQObject()) {
            Vector3* p_vec = (Vector3*)other.toQObject();

            if(p_vec != nullptr) {
                return QScriptValue::UndefinedValue;//(this->getRotationTo(*p_vec)).toQtScriptObject();
            }
            else {
                Logger::get().debug("The Vector3 you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Vector3 object.");
        }

        return QScriptValue::UndefinedValue;
    }

    QScriptValue Vector3::scriptGetReflection(QScriptValue normal) const {
        if(normal.isQObject()) {
            Vector3* p_norvec = (Vector3*)normal.toQObject();

            if(p_norvec != nullptr) {
                return (this->getReflection(*p_norvec)).toQtScriptObject();
            }
            else {
                Logger::get().debug("The Vector3 you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Vector3 object.");
        }

        return QScriptValue::UndefinedValue;
    }

    QScriptValue Vector3::scriptAdd(QScriptValue other) const {
        if(other.isQObject()) {
            Vector3* p_vec = (Vector3*)other.toQObject();

            if(p_vec != nullptr) {
                return (*this + *p_vec).toQtScriptObject();
            }
            else {
                Logger::get().debug("The Vector3 you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Vector3 object.");
        }

        return QScriptValue::UndefinedValue;
    }

    QScriptValue Vector3::scriptSubtract(QScriptValue other) const {
        if(other.isQObject()) {
            Vector3* p_vec = (Vector3*)other.toQObject();

            if(p_vec != nullptr) {
                return (*this - *p_vec).toQtScriptObject();
            }
            else {
                Logger::get().debug("The Vector3 you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Vector3 object.");
        }

        return QScriptValue::UndefinedValue;
    }

    QScriptValue Vector3::scriptMultiply(float multiplier) const {
        return ((*this) * multiplier).toQtScriptObject();
    }
}