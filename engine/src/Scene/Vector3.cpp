
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Scene/Vector3.hpp>

namespace dt {
    Vector3::Vector3() : mX(0.0f), mY(0.0f), mZ(0.0f) {}

    Vector3::Vector3(const float x, const float y, const float z)
        : mX(x),
          mY(y),
          mZ(z) {}

    Vector3::Vector3(const Ogre::Vector3& ogre_vector)
        : mX(ogre_vector.x),
          mY(ogre_vector.y),
          mZ(ogre_vector.z) {}

    Ogre::Vector3 Vector3::getOgreVector3() const {
        return Ogre::Vector3(mX, mY, mZ);
    }

    void Vector3::swap(Vector3& other) {
        float x = other.mX;
        float y = other.mY;
        float z = other.mZ;

        other.mX = mX;
        other.mY = mY;
        other.mZ = mZ;

        mX = x;
        mY = y;
        mZ = z;
    }

    float Vector3::getDistance(const Vector3& other) const {
        return sqrt((mX - other.mX) * (mX - other.mX) + (mY - other.mY) * (mY - other.mY) + (mZ - other.mZ) * (mZ - other.mZ));
    }

    float Vector3::dotProduct(const Vector3& other) const {
        return mX * other.mX + mY * other.mY + mZ * other.mZ;
    }

    Vector3 Vector3::crossProduct(const Vector3& other) const {
        Vector3 vec;
        vec.mX = mY * other.mZ - mZ * other.mY;
        vec.mY = mZ * other.mX - mX * other.mZ;
        vec.mZ = mX * other.mY - mY * other.mX;

        return vec;
    }

    QScriptValue Vector3::toQtScriptObject() {
        return ScriptManager::get()->getScriptEngine()->newQObject(this);
    }

    Vector3 Vector3::getRandomDeviant(float angle_range) const {
        Vector3 vec1 = this->crossProduct(Vector3(1.0f, 0.0f, 0.0f));
        Vector3 vec2 = this->crossProduct(vec1);
        Vector3 vec3 = *this;

        // TODO: Fill here with rotation operations.

        return vec3;
    }

    float Vector3::getAngleBetween(const Vector3& other) const {
        float dot_product = this->dotProduct(other);

        return dot_product / (this->getLength() * other.getLength());
    }

    Quaterion Vector3::getRotationTo(const Vector3& other) const {
        return Quaterion();
    }

    Vector3 Vector3::getReflection(const Vector3& normal) const {
        normal.normalise();

        return *this - this->dotProduct(normal).dotProduct(normal) * 2;
    }

    Vector3 Vector3::operator + (const Vector3& other) const {
        return Vector3(mX + other.mX, mY + other.mY, mZ + other.mZ);
    }

    Vector3 Vector3::operator - (const Vector3& other) const {
        return Vector3(mX - other.mX, mY - other.mY, mZ - other.mZ);
    }

    Vector3 Vector3::operator - () const {
        return Vector3(-mX, -mY, -mZ);
    }

    Vector3 Vector3::operator * (const float multiplier) const {
        return Vector3(mX * multiplier, mY * multiplier, mZ * multiplier);
    }

    Vector3 Vector3::operator * (const Vector3& multiplier) const {
        return this->crossProduct(multiplier);
    }

    void Vector3::normalise() {
        float length = this->getLength();

        mX /= length;
        mY /= length;
        mZ /= length;
    }

    bool Vector3::isZero() const {
        return mX == 0.0f && mY == 0.0f && mZ == 0.0f;
    }

    float Vector3::getX() const {
        return mX;
    }

    float Vector3::getY() const {
        return mY;
    }

    float Vector3::getZ() const {
        return mZ;
    }

    void Vector3::setX(const float x) {
        if(mX != x)
            mX = x;
    }

    void Vector3::setY(const float y) {
        if(mY != y)
            mY = y;
    }

    void Vector3::setZ(const float z) {
        if(mZ != z)
            mZ = z;
    }

    float Vector3::getLength() const {
        return sqrt(mX * mX + mY * mY + mZ * mZ);
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
}