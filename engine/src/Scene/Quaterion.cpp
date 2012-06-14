
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Scene/Quaterion.hpp>

namespace dt {
    std::vector<Quaternion*> Quaternion::mPool(32);

    Quaternion::Quaternion() : mQua(Ogre::Quaternion::IDENTITY) {}

    Quaternion::Quaternion(const float w, const float x, const float y, const float z)
        : mQua(w, x, y, z) {}

    Quaternion::Quaternion(const Quaternion& other)
        : mQua(other.mQua) {}

    Quaternion::Quaternion(const Ogre::Quaternion& ogre_quaternion)
        : mQua(ogre_quaternion) {}

    Quaternion::Quaternion(const btQuaternion& bt_quaternion)
        : mQua(bt_quaternion.getW(), bt_quaternion.getX(), bt_quaternion.getY(), bt_quaternion.getZ()) {}

    Ogre::Quaternion & Quaternion::getOgreQuaternion()
    {
        return mQua;
    }

    const Ogre::Quaternion & Quaternion::getOgreQuaternion() const
    {
        return mQua;
    }

    btQuaternion Quaternion::getBulletQuaternion() const
    {
        return btQuaternion(mQua.x, mQua.y, mQua.z, mQua.w);
    }

    const Quaternion Quaternion::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
    const Quaternion Quaternion::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f);

    inline Ogre::Real Quaternion::operator [] (const uint32_t i) const
    {
        return mQua[i];
    }

    inline Ogre::Real& Quaternion::operator [] (const uint32_t i)
    {
        return mQua[i];
    }

    Quaternion& Quaternion::operator = (const Quaternion& other)
    {
        mQua = other.mQua;
        return *this;
    }

    inline Quaternion Quaternion::operator + (const Quaternion& other) const
    {
        return Quaternion(mQua + other.mQua);
    }

    inline Quaternion Quaternion::operator - (const Quaternion& other) const
    {
        return Quaternion(mQua - other.mQua);
    }

    Quaternion Quaternion::operator * (const Quaternion& other) const
    {
        return Quaternion(mQua * other.mQua);
    }

    inline Quaternion Quaternion::operator * (const float scalar) const
    {
        return Quaternion(mQua * scalar);
    }

    Quaternion Quaternion::operator- () const
    {
        return Quaternion(-mQua);
    }

    inline bool Quaternion::operator== (const Quaternion& rhs) const
    {
        return mQua == rhs.mQua;
    }

    inline bool Quaternion::operator!= (const Quaternion& rhs) const
    {
        return mQua != rhs.mQua;
    }

    Vector3 Quaternion::operator * (const Vector3& v)
    {
        return Vector3(mQua * v.getOgreVector3());
    }

    Vector3 Quaternion::operator * (const Ogre::Vector3& v)
    {
        return Vector3(mQua * v);
    }

    float Quaternion::getW() const { return mQua.w; }
    float Quaternion::getX() const { return mQua.x; }
    float Quaternion::getY() const { return mQua.y; }
    float Quaternion::getZ() const { return mQua.z; }
    void Quaternion::setW(const float w) { mQua.w = w; }
    void Quaternion::setX(const float x) { mQua.x = x; }
    void Quaternion::setY(const float y) { mQua.y = y; }
    void Quaternion::setZ(const float z) { mQua.z = z; }

    void Quaternion::swap(Quaternion& other)
    {
        mQua.swap(other.mQua);
    }

    float Quaternion::dotProduct(const Quaternion& other) const
    {
        return mQua.Dot(other.mQua);
    }

    Quaternion Quaternion::crossProduct(const Quaternion& other) const
    {
        return mQua * other.mQua;
    }

    void Quaternion::toRotationMatrix(Ogre::Matrix3& rot) const
    {
        mQua.ToRotationMatrix(rot);
    }

    float Quaternion::normalise()
    {
        return mQua.normalise();
    }

    float Quaternion::getRoll() const
    {
        return mQua.getRoll().valueRadians();
    }

    float Quaternion::getPitch() const
    {
        return mQua.getPitch().valueRadians();
    }

    float Quaternion::getYaw() const
    {
        return mQua.getYaw().valueRadians();
    }

    void Quaternion::fromAngleAxis(const float angle, Vector3& axis)
    {
        mQua.FromAngleAxis(Ogre::Radian(angle), axis.getOgreVector3());
    }

    void Quaternion::fromRotationMatrix(const Ogre::Matrix3& rot)
    {
        mQua.FromRotationMatrix(rot);
    }

    void Quaternion::toAngleAxis(float angle, Vector3& axis) const
    {
        mQua.ToAngleAxis(Ogre::Degree(angle), axis.getOgreVector3());
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

    void Quaternion::scriptToAngleAxis(float& angle, QScriptValue& axis) const
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
                mPool.push_back(new Quaternion(*this + *p_qua));
                return mPool.back()->toQtScriptObject();
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
        mPool.push_back(new Quaternion((*this) * scalar));
        return mPool.back()->toQtScriptObject();
    }
}