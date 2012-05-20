
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

    inline Quaternion& Quaternion::operator = (const Quaternion &q)
    {
        mX = q.mX;
        mY = q.mY;
        mZ = q.mZ;
        mW = q.mW;
        return *this;
    }

    inline Quaternion Quaternion::operator + (const Quaternion &q) const
    {
        return Quaternion(mX + q.mX, mY + q.mY, mZ + q.mZ, mW + q.mW);
    }

    inline Quaternion Quaternion::operator - (const Quaternion &q) const
    {
        return Quaternion(mX - q.mX, mY - q.mY, mZ - q.mZ, mW - q.mW);
    }

    inline Quaternion Quaternion::operator * (const Quaternion &q) const
    {
        return Quaternion(
            mW * q.mW - mX * q.mX - mY * q.mY - mZ * q.mZ,
            mW * q.mX + mX * q.mW + mY * q.mZ - mZ * q.mY,
            mW * q.mY + mY * q.mW + mZ * q.mX - mX * q.mZ,
            mW * q.mZ + mZ * q.mW + mX * q.mY - mY * q.mX
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

    Ogre::Vector3 Quaternion::operator * (const Ogre::Vector3 &v) const
    {
        // nVidia SDK implementation
        Ogre::Vector3 uv, uuv;
        Ogre::Vector3 qvec(mX, mY, mZ);
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

    inline void Quaternion::assign(const Quaternion &q) { (*this) = q; }
    inline void Quaternion::add(const Quaternion &q) { (*this) = (*this) + q; }
    inline void Quaternion::subtract(const Quaternion &q) { (*this) = (*this) - q; }
    inline void Quaternion::scale(const float scalar) { (*this) = (*this) * scalar;}

    void Quaternion::swap(Quaternion &q)
    {
        std::swap(mX, q.mX);
        std::swap(mY, q.mY);
        std::swap(mZ, q.mZ);
        std::swap(mW, q.mW);
    }

    float Quaternion::dotProduct(const Quaternion &q) const
    {
        return mX * q.mX + mY * q.mY + mZ * q.mZ + mW * q.mW;
    }

    Quaternion Quaternion::crossProduct(const Quaternion &q) const
    {
        return (*this) * q;
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

    void Quaternion::fromAngleAxis(const float &angle, const Ogre::Vector3 &axis)
    {
        // from Ogre
        float halfAngle = 0.5f * angle;
        float sin = sinf(halfAngle);
        mW = cos(halfAngle);
        mX = sin * axis.x;//getX();
        mY = sin * axis.y;//getY();
        mZ = sin * axis.z;//getZ();
    }

    void Quaternion::toAngleAxis(float &angle, Ogre::Vector3 &axis) const
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
            axis.x = (mX * invLength);
            axis.y = (mY * invLength);
            axis.z = (mZ * invLength);
        }
        else
        {
            // angle is 0 (mod 2*pi), so any axis will do
            angle = 0.0f;
            axis.x = (1.0f);
            axis.y = (0.0f);
            axis.z = (0.0f);
        }
    }

    void Quaternion::scriptSwap(QScriptValue q)
    {
        if(q.isQObject()) {
            Quaternion* p_qua = (Quaternion*)q.toQObject();
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

    float Quaternion::scriptDotProduct(QScriptValue q) const
    {
        if(q.isQObject()) {
            Quaternion* p_qua = (Quaternion*)q.toQObject();
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

    QScriptValue Quaternion::scriptCrossProduct(QScriptValue q) const
    {
        if(q.isQObject()) {
            Quaternion* p_qua = (Quaternion*)q.toQObject();
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
            Ogre::Vector3* p_qua = (Ogre::Vector3*)axis.toQObject();
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
            Ogre::Vector3* p_qua = (Ogre::Vector3*)axis.toQObject();
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

    //bool Quaternion::equals(const Quaternion &q, const float tolerance) const
    //{
    //}
}