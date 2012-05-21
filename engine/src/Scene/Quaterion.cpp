
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Scene/Quaterion.hpp>

namespace dt {
    Quaternion::Quaternion() : mX(.0f), mY(.0f), mZ(.0f), mW(.0f) {}

    Quaternion::Quaternion(const float x, const float y, const float z, const float w)
        : mX(x),
          mY(y),
          mZ(z),
          mW(w) {}

    Quaternion::Quaternion(const Quaternion &other)
        : mX(other.mX),
          mY(other.mY),
          mZ(other.mZ),
          mW(other.mW) {}

    Quaternion::Quaternion(const Ogre::Quaternion &ogre_quaternion)
        : mX(ogre_quaternion.x),
          mY(ogre_quaternion.y),
          mZ(ogre_quaternion.z),
          mW(ogre_quaternion.w) {}

    Ogre::Quaternion Quaternion::getOgreQuaternion() const
    {
        return Ogre::Quaternion(mW, mX, mY, mZ);
    }

    inline float Quaternion::operator [] (const uint32_t i) const
    {
        assert(i < 4);
        return *(&mW+i);
    }

    inline float& Quaternion::operator [] (const uint32_t i)
    {
        assert(i < 4);
        return *(&mW+i);
    }

    inline Quaternion& Quaternion::operator = (const Quaternion &other)
    {
        mX = other.mX;
        mY = other.mY;
        mZ = other.mZ;
        mW = other.mW;
        return *this;
    }

    inline Quaternion Quaternion::operator + (const Quaternion &other) const
    {
        return Quaternion(mX + other.mX, mY + other.mY, mZ + other.mZ, mW + other.mW);
    }

    inline Quaternion Quaternion::operator - (const Quaternion &other) const
    {
        return Quaternion(mX - other.mX, mY - other.mY, mZ - other.mZ, mW - other.mW);
    }

    inline Quaternion Quaternion::operator * (const Quaternion &other) const
    {
        return Quaternion(
            mW * other.mW - mX * other.mX - mY * other.mY - mZ * other.mZ,
            mW * other.mX + mX * other.mW + mY * other.mZ - mZ * other.mY,
            mW * other.mY + mY * other.mW + mZ * other.mX - mX * other.mZ,
            mW * other.mZ + mZ * other.mW + mX * other.mY - mY * other.mX
            );
    }

    inline Quaternion Quaternion::operator * (const float scalar) const
    {
        return Quaternion(mX * scalar, mY * scalar, mZ * scalar, mW * scalar);
    }

    inline Quaternion Quaternion::operator- () const
    {
        return Quaternion(-mX, -mY, -mZ, -mW);
    }

    inline bool Quaternion::operator== (const Quaternion &rhs) const
    {
        return (rhs.mX == mX) && (rhs.mY == mY) &&
            (rhs.mZ == mZ) && (rhs.mW == mW);
    }

    inline bool Quaternion::operator!= (const Quaternion &rhs) const
    {
        return !operator==(rhs);
    }

    Vector3 Quaternion::operator * (const Vector3 &v) const
    {
        // nVidia SDK implementation
        Vector3 uv, uuv;
        Vector3 qvec(mX, mY, mZ);
        uv = qvec.crossProduct(v);
        uuv = qvec.crossProduct(uv);
        uv = uv * (2.0f * mW);
        uuv = uuv * 2.0f;

        return v + uv + uuv;
    }

    inline float Quaternion::getW() { return mW; }
    inline float Quaternion::getX() { return mX; }
    inline float Quaternion::getY() { return mY; }
    inline float Quaternion::getZ() { return mZ; }
    inline void Quaternion::setW(const float w) { mW = w; }
    inline void Quaternion::setX(const float x) { mX = x; }
    inline void Quaternion::setY(const float y) { mY = y; }
    inline void Quaternion::setZ(const float z) { mZ = z; }

    void Quaternion::swap(Quaternion &other)
    {
        std::swap(mX, other.mX);
        std::swap(mY, other.mY);
        std::swap(mZ, other.mZ);
        std::swap(mW, other.mW);
    }

    float Quaternion::dotProduct(const Quaternion &other) const
    {
        return mX * other.mX + mY * other.mY + mZ * other.mZ + mW * other.mW;
    }

    Quaternion Quaternion::crossProduct(const Quaternion &other) const
    {
        return (*this) * other;
    }

    float Quaternion::getLength() const
    {
        return sqrt(mX * mX + mY * mY + mZ * mZ + mW * mW);
    }

    float Quaternion::normalise()
    {
        float length = sqrt(mX * mX + mY * mY + mZ * mZ + mW * mW);
        if (length != 0)
        {
            (*this) = (*this) * (1.0f / length);
        }
        return length;
    }

    float Quaternion::getRoll() const
    {
        return atan2f(2 * (mX * mY + mW * mZ), mW * mW + mX * mX - mY * mY - mZ * mZ);
    }

    float Quaternion::getPitch() const
    {
        return atan2f(2 * (mY * mZ + mW * mX), mW * mW - mX * mX - mY * mY + mZ * mZ);
    }

    float Quaternion::getYaw() const
    {
        return asinf(-2 * (mX * mZ - mW * mY));
    }

    void Quaternion::fromAngleAxis(const float &angle, const Vector3 &axis)
    {
        // from Ogre
        float halfAngle = 0.5f * angle;
        float sin = sinf(halfAngle);
        mW = cos(halfAngle);
        mX = sin * axis.getX();
        mY = sin * axis.getY();
        mZ = sin * axis.getZ();
    }

    void Quaternion::toAngleAxis(float &angle, Vector3 &axis) const
    {
        // from Ogre
        float sqrLength = mX * mX + mY * mY + mZ * mZ;
        if (sqrLength > 0.0f)
        {
            angle = 2.0f * acos(mW);
            float invLength = sqrtf(sqrLength);
            if (invLength != 0.0f)
            {
                invLength = 1.0f / invLength;
            }
            axis.setX(mX * invLength);
            axis.setY(mY * invLength);
            axis.setZ(mZ * invLength);
        }
        else
        {
            // angle is 0 (mod 2*pi), so any axis will do
            angle = 0.0f;
            axis.setX(1.0f);
            axis.setY(0.0f);
            axis.setZ(0.0f);
        }
    }

    void Quaternion::scriptSwap(QScriptValue other)
    {
        if(other.isQObject()) {
            Quaternion* p_qua = (Quaternion*)other.toQObject();
            if(p_qua != nullptr) {
                swap(*p_qua);
            }
            else {
                Logger::get().debug("The Quaternion you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Quaternion object.");
        }
    }

    float Quaternion::scriptDotProduct(QScriptValue other) const
    {
        if(other.isQObject()) {
            Quaternion* p_qua = (Quaternion*)other.toQObject();
            if(p_qua != nullptr) {
                return dotProduct(*p_qua);
            }
            else {
                Logger::get().debug("The Quaternion you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Quaternion object.");
        }

        return 0.0f;
    }

    QScriptValue Quaternion::scriptCrossProduct(QScriptValue other) const
    {
        if(other.isQObject()) {
            Quaternion* p_qua = (Quaternion*)other.toQObject();
            if(p_qua != nullptr) {
                return crossProduct(*p_qua).toQtScriptObject();
            }
            else {
                Logger::get().debug("The Quaternion you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Quaternion object.");
        }

        return QScriptValue::UndefinedValue;
    }

    void Quaternion::scriptFromAngleAxis(float angle, QScriptValue axis)
    {
        if(axis.isQObject()) {
            Vector3* p_qua = (Vector3*)axis.toQObject();
            if(p_qua != nullptr) {
                fromAngleAxis(angle, *p_qua);
            }
            else {
                Logger::get().debug("The Quaternion you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Quaternion object.");
        }
    }

    void Quaternion::scriptToAngleAxis(float &angle, QScriptValue &axis) const
    {
        if(axis.isQObject()) {
            Vector3* p_qua = (Vector3*)axis.toQObject();
            if(p_qua != nullptr) {
                toAngleAxis(angle, *p_qua);
            }
            else {
                Logger::get().debug("The Quaternion you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Quaternion object.");
        }
    }

    QScriptValue Quaternion::toQtScriptObject()
    {
        return ScriptManager::get()->getScriptEngine()->newQObject(this);
    }

    QScriptValue Quaternion::scriptAdd(QScriptValue other) const
    {
        if(other.isQObject()) {
            Quaternion* p_qua = (Quaternion*)other.toQObject();
            if(p_qua != nullptr) {
                return (*this + *p_qua).toQtScriptObject();
            }
            else {
                Logger::get().debug("The Quaternion you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Quaternion object.");
        }

        return QScriptValue::UndefinedValue;
    }

    QScriptValue Quaternion::scriptSubtract(QScriptValue other) const
    {
        if(other.isQObject()) {
            Quaternion* p_qua = (Quaternion*)other.toQObject();
            if(p_qua != nullptr) {
                return (*this - *p_qua).toQtScriptObject();
            }
            else {
                Logger::get().debug("The Quaternion you are trying to use has been deleted.");
            }
        }
        else {
            Logger::get().error("Invalid Quaternion object.");
        }

        return QScriptValue::UndefinedValue;
    }

    QScriptValue Quaternion::scriptScale(float scalar) const
    {
        return ((*this) * scalar).toQtScriptObject();
    }
}