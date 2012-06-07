
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_SCENE_QUATERNION
#define DUCTTAPE_ENGINE_SCENE_QUATERNION

#include <Config.hpp>

#include <Logic/IScriptable.hpp>
#include <Logic/ScriptManager.hpp>
#include <Scene/Vector3.hpp>

#include <OGRE/OgreQuaternion.h>

#include <QScriptProgram>
#include <QObject>

#include <vector>

namespace dt {

    class Vector3;

    /**
      * A class to hold a 4-dimensional vector.
      */
    class Quaternion : public QObject, public IScriptable {
        Q_OBJECT
        Q_PROPERTY(float w READ getW WRITE setW)
        Q_PROPERTY(float x READ getX WRITE setX)
        Q_PROPERTY(float y READ getY WRITE setY)
        Q_PROPERTY(float z READ getZ WRITE setZ)
        Q_PROPERTY(float roll READ getRoll)
        Q_PROPERTY(float pitch READ getPitch)
        Q_PROPERTY(float yaw READ getYaw)

    public:
        /**
          * Non-parameter constructor which constructs a Quaternion with (0.0f, 0.0f, 0.0f, 0.0f).
          */
        Quaternion();

        /**
          * Copy constructor. (to avoid inaccessibility of QObject copy constructor)
          */
        Quaternion(const Quaternion& other);

        /**
          * Uses the given x, y, z, w value to construct a Quaternion.
          * @param x The x value.
          * @param y The y value.
          * @param z The z value.
          * @param w The w value.
          */
        Quaternion(const float x, const float y, const float z, const float w);

        /**
          * Uses the given Ogre Quaternion to construct a Quaternion.
          * @param ogre_quaternion The Ogre Quaternion.
          */
        Quaternion(const Ogre::Quaternion& ogre_quaternion);

        /**
          * Uses the given Bullet Quaternion to construct a Quaternion.
          * @param bt_quaternion The Bullet Quaternion.
          */
        Quaternion(const btQuaternion& bt_quaternion);

        /**
          * Convert this Quaternion to an Ogre Quaternion.
          * @returns The Ogre Quaternion.
          */
        Ogre::Quaternion & getOgreQuaternion();

        const Ogre::Quaternion & getOgreQuaternion() const;

        /**
          * Convert this Quaternion to a Bullet Quaternion.
          * @returns The Bullet Quaternion.
          */
        btQuaternion getBulletQuaternion() const;

        // special values
        static const Quaternion ZERO;
        static const Quaternion IDENTITY;

#pragma region operator_override
        Ogre::Real operator [] (const uint32_t i) const;
        Ogre::Real& operator [] (const uint32_t i);
        Quaternion& operator = (const Quaternion& other);
        Quaternion operator + (const Quaternion& other) const;
        Quaternion operator - (const Quaternion& other) const;
        Quaternion operator * (const Quaternion& other) const;
        Quaternion operator * (const float scalar) const;
        Quaternion operator- () const;
        bool operator== (const Quaternion& rhs) const;
        bool operator!= (const Quaternion& rhs) const;
        Vector3 operator * (const Vector3& v);
        Vector3 operator * (const Ogre::Vector3& v);

        inline DUCTTAPE_API friend std::ostream& operator <<
            ( std::ostream& o, const Quaternion& q )
        {
            o << q.mQua.w << " " << q.mQua.x << " " << q.mQua.y << " " << q.mQua.z;
            return o;
        }

        inline DUCTTAPE_API friend std::istream& operator >>
            ( std::istream& i, Quaternion& q )
        {
            i >> q.mQua.w >> q.mQua.x >> q.mQua.y >> q.mQua.z;
            return i;
        }

        inline DUCTTAPE_API friend sf::Packet& operator >>
            ( sf::Packet& i, Quaternion& q )
        {
            i >> q.mQua.w >> q.mQua.x >> q.mQua.y >> q.mQua.z;
            return i;
        }

        inline DUCTTAPE_API friend sf::Packet& operator <<
            ( sf::Packet& o, const Quaternion& q )
        {
            o << q.mQua.w << q.mQua.x << q.mQua.y << q.mQua.z;
            return o;
        }

        inline DUCTTAPE_API friend const YAML::Node& operator >> (const YAML::Node& node, Quaternion& q) {
            node[0] >> q.mQua.w;
            node[1] >> q.mQua.x;
            node[2] >> q.mQua.y;
            node[3] >> q.mQua.z;
            return node;
        }

        inline DUCTTAPE_API friend YAML::Emitter& operator << (YAML::Emitter& emitter, Quaternion& q) {
            emitter << YAML::Flow << YAML::BeginSeq << q.mQua.w << q.mQua.x << q.mQua.y << q.mQua.z << YAML::EndSeq;
            return emitter;
        }

#pragma endregion

        /**
          * Swaps two the value of two quaternion.
          * @param other The other Quaternion.
          */
        void swap(Quaternion& other);

        /**
          * Dot product of two quaternion.
          * @param other The other Quaternion.
          * @returns The result of dot product.
          */
        float dotProduct(const Quaternion& other) const;

        /**
          * Cross product of two quaternion.
          * @param other The other Quaternion.
          * @returns The result of cross product.
          */
        Quaternion crossProduct(const Quaternion& other) const;

        /**
          * Construct rotation matrix from quaternion.
          * @param rot The rotation matrix.
          */
        void toRotationMatrix(Ogre::Matrix3& rot) const;

        /**
          * Returns a QtScript object.
          * @returns A QtScript object.
          * @see IScriptable
          */
        virtual QScriptValue toQtScriptObject();

    public slots:

#pragma region getter_setter
        /**
          * Gets the w value of this Quaternion.
          * @returns The w value.
          */
        float getW() const;

        /**
          * Gets the x value of this Quaternion.
          * @returns The x value.
          */
        float getX() const;

        /**
          * Gets the y value of this Quaternion.
          * @returns The y value.
          */
        float getY() const;

        /**
          * Gets the z value of this Quaternion.
          * @returns The z value.
          */
        float getZ() const;

        /**
          * Sets the w value of this Quaternion.
          * @param w The new w value.
          */
        void setW(const float w);

        /**
          * Sets the x value of this Quaternion.
          * @param x The new x value.
          */
        void setX(const float x);

        /**
          * Sets the y value of this Quaternion.
          * @param y The new y value.
          */
        void setY(const float y);

        /**
          * Sets the z value of this Quaternion.
          * @param z The new z value.
          */
        void setZ(const float z);
#pragma endregion

        /**
          * Normalise quaternion.
          * @returns Length of quaternion before normalise.
          */
        float normalise();

        /**
          * Get the local roll element of this quaternion.
          * @returns Roll element.
          */
        float getRoll() const;

        /**
          * Get the local pitch element of this quaternion.
          * @returns Pitch element.
          */
        float getPitch() const;

        /**
          * Get the local yaw element of this quaternion.
          * @returns Yaw element.
          */
        float getYaw() const;

        /**
          * Construct quaternion from angle and axis.
          * @param angle Angle to rotate.
          * @param axis Axis to rotate around.
          */
        void fromAngleAxis(const float angle, Vector3& axis);

        /**
          * Construct quaternion from rotation matrix
          * @param rot Rotation matrix.
          */
        void fromRotationMatrix(const Ogre::Matrix3& rot);

        /**
          * Construct angle and axis from quaternion.
          * @param angle Angle to rotate.
          * @param axis Axis to rotate around.
          */
        void toAngleAxis(float angle, Vector3& axis) const;

#pragma region script_function
        /**
          * Swaps two the value of two quaternion. For script use.
          * @param other The other Quaternion.
          */
        void scriptSwap(QScriptValue other);

        /**
          * Dot product of two quaternion. For script use.
          * @param other The other Quaternion.
          * @returns The result of dot product.
          */
        float scriptDotProduct(QScriptValue other) const;

        /**
          * Cross product of two quaternion. For script use.
          * @param other The other Quaternion.
          * @returns The result of cross product.
          */
        QScriptValue scriptCrossProduct(QScriptValue other) const;

        /**
          * Construct quaternion from angle and axis. For script use.
          * @param angle Angle to rotate.
          * @param axis Axis to rotate around.
          */
        void scriptFromAngleAxis(float angle, QScriptValue axis);

        /**
          * Construct angle and axis from quaternion. For script use.
          * @param angle Angle to rotate.
          * @param axis Axis to rotate around.
          */
        void scriptToAngleAxis(float& angle, QScriptValue& axis) const;

        /**
          * Adds this Quaternion with another Quaternion. For script use.
          * @param other The other Quaternion.
          * @returns The result.
          */
        QScriptValue scriptAdd(QScriptValue other) const;

        /**
          * Subtracts this Quaternion by another Quaternion. For script use.
          * @param other The other Quaternion.
          * @returns The result.
          */
        QScriptValue scriptSubtract(QScriptValue other) const;

        /**
          * Scales this Quaternion by a number. For script use.
          * @param scalar The scalar.
          * @returns The result.
          */
        QScriptValue scriptScale(const float scalar) const;
#pragma endregion
    private:
        Quaternion * _newInstance(Quaternion

    private:
        Ogre::Quaternion mQua;   //!< The Quaternion.
        static std::vector<Quaternion*> mPool; // For script use.
    };
}

#endif