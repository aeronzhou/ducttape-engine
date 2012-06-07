
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_SCENE_VECTOR3
#define DUCTTAPE_ENGINE_SCENE_VECTOR3

#include <Config.hpp>

#include <Logic/IScriptable.hpp>
#include <Logic/ScriptManager.hpp>
//#include <Scene/Quaterion.hpp>

#include <btBulletDynamicsCommon.h>
#include <OGRE/OgreQuaternion.h>
#include <OGRE/OgreVector3.h>

#include <QScriptProgram>
#include <QObject>

namespace dt {

    //class Quaternion;

    /**
      * A class to hold a 3-dimensional vector. Refers to Ogre::Vector3.
      */
    class Vector3 : public QObject, public IScriptable {
        Q_OBJECT
        Q_PROPERTY(float x READ getX WRITE setX FINAL)
        Q_PROPERTY(float y READ getY WRITE setY FINAL)
        Q_PROPERTY(float z READ getZ WRITE setZ FINAL)
    public:
        /**
          * Non-parameter constructor which constructs a Vector3 with (0.0f, 0.0f, 0.0f).
          */
        Vector3();

        /**
          * Copy constructor. (to avoid inaccessibility of QObject copy constructor)
          */
        Vector3(const Vector3 &other);

        /**
          * Uses the given x, y and z value to construct a Vector3.
          * @param x The x value.
          * @param y The y value.
          * @param z The z value.
          */
        Vector3(const float x, const float y, const float z);

        /**
          * Uses the given Ogre Vector3 to construct a Vector3.
          * @param ogre_vector The Ogre Vector3.
          */
        Vector3(const Ogre::Vector3 &ogre_vector);

        /**
          * Uses the given Bullet Vector3 to construct a Vector3.
          * @param bt_vector The Bullet Vector3.
          */
        Vector3(const btVector3 &bt_vector);

        /**
          * Convert this Vector3 to an Ogre Vector3.
          * @returns The Ogre Vector3.
          */
        Ogre::Vector3 & getOgreVector3();

        const Ogre::Vector3 & getOgreVector3() const;

        /**
          * Convert this Vector3 to a Bullet Vector3.
          * @returns The Bullet Vector3.
          */
        btVector3 getBulletVector3() const;

        // special values
        static const Vector3 ZERO;
        static const Vector3 UNIT_X;
        static const Vector3 UNIT_Y;
        static const Vector3 UNIT_Z;
        static const Vector3 NEGATIVE_UNIT_X;
        static const Vector3 NEGATIVE_UNIT_Y;
        static const Vector3 NEGATIVE_UNIT_Z;
        static const Vector3 UNIT_SCALE;

        /**
          * Swaps two the value of two Vector3.
          * @param other The other Vector3.
          */
        void swap(Vector3& other);

        /**
          * Gets the distance between this Vector3 and another Vector3.
          * @param other The other Vector3.
          * @returns The distance between this Vector3 and another Vector3.
          */
        Ogre::Real getDistance(const Vector3& other) const;

        /**
          * Gets the dot product of this Vector3 and another Vector3.
          * @param other The other Vector3.
          * @returns The dot product.
          */
        Ogre::Real dotProduct(const Vector3& other) const;

        /**
          * Gets the cross product of this Vector3 and another Vector3.
          * @param other The other Vector3.
          * @returns The cross product.
          */
        Vector3 crossProduct(const Vector3& other) const;

        /**
          * Returns a QtScript object.
          * @returns A QtScript object.
          * @see IScriptable
          */
        QScriptValue toQtScriptObject();

        /**
          * Gets a Vector3 that deviates from this Vector3 within a given angle range randomly.
          * @param angle_range The angle range, represents in degree.
          * @returns The random Vector3.
          */
        Vector3 getRandomDeviant(float angle_range) const;

        /**
          * Gets the angle between this Vector3 and another Vector3.
          * @param other The other Vector3.
          * @returns The angle between this Vector3 and another Vector3.
          */
        Ogre::Real getAngleBetween(const Vector3& other);

        /**
          * Gets the quaterion to rotate from the direction of this Vector3 to the direction of another Vector3.
          * @param other The other Vector3.
          * @returns The rotation quaterion.
          */
        Ogre::Quaternion getRotationTo(const Vector3& other) const;

        /**
          * Gets the reflection Vector3 of this Vector3 from a normal Vector3.
          * @param normal The normal Vector3.
          * @returns The reflection Vector3.
          */
        Vector3 getReflection(Vector3& normal) const;

        Vector3 operator + (const Vector3& other) const;

        Vector3 operator - (const Vector3& other) const;

        Vector3 operator - () const;

        Vector3 operator * (const float multiplier) const;

        Vector3 operator * (const Vector3& multiplier) const;

        Vector3 operator = (const Vector3& other);

        bool operator == (const Vector3& other) const;

        bool operator != (const Vector3& other) const;

        inline DUCTTAPE_API friend std::ostream& operator <<
            ( std::ostream& o, const Vector3& v )
        {
            o << v.mVec.x << " " << v.mVec.y << " " << v.mVec.z;
            return o;
        }

        inline DUCTTAPE_API friend std::istream& operator >>
            ( std::istream& i, Vector3& v )
        {
            i >> v.mVec.x >> v.mVec.y >> v.mVec.z;
            return i;
        }

        inline DUCTTAPE_API friend sf::Packet& operator >>
            ( sf::Packet& i, Vector3& v )
        {
            i >> v.mVec.x >> v.mVec.y >> v.mVec.z;
            return i;
        }

        inline DUCTTAPE_API friend sf::Packet& operator <<
            ( sf::Packet& o, const Vector3& v )
        {
            o << v.mVec.x << v.mVec.y << v.mVec.z;
            return o;
        }

        inline DUCTTAPE_API friend const YAML::Node& operator >> (const YAML::Node& node, Vector3& v) {
            node[0] >> v.mVec.x;
            node[1] >> v.mVec.y;
            node[2] >> v.mVec.z;
            return node;
        }

        inline DUCTTAPE_API friend YAML::Emitter& operator << (YAML::Emitter& emitter, Vector3& v) {
            emitter << YAML::Flow << YAML::BeginSeq << v.mVec.x << v.mVec.y << v.mVec.z << YAML::EndSeq;
            return emitter;
        }

    public slots:
        /**
          * Normalises the Vector3.
          */
        void normalise();

        /**
          * Gets whether the Vector3's length is 0 or not.
          * @returns Whether the Vector3's length is 0 or not.
          */
        bool isZero() const;

        /**
          * Gets the x value of this Vector3.
          * @returns The x value.
          */
        float getX() const;

        /**
          * Gets the y value of this Vector3.
          * @returns The y value.
          */
        float getY() const;

        /**
          * Gets the z value of this Vector3.
          * @returns The z value.
          */
        float getZ() const;

        /**
          * Sets the x value of this Vector3.
          * @param x The new x value.
          */
        void setX(const float x);

        /**
          * Sets the y value of this Vector3.
          * @param y The new y value.
          */
        void setY(const float y);

        /**
          * Sets the z value of this Vector3.
          * @param z The new z value.
          */
        void setZ(const float z);

        /**
          * Gets the length of the Vector3.
          * @returns The length of the Vector3.
          */
        float getLength() const;

        /**
          * Swaps two the value of two Vector3. For script use.
          * @param other The other Vector3.
          */
        void scriptSwap(QScriptValue other);

        /**
          * Gets the distance between this Vector3 and another Vector3. For script use.
          * @param other The other Vector3.
          * @returns The distance between this Vector3 and another Vector3.
          */
        float scriptGetDistance(QScriptValue other) const;

        /**
          * Gets the dot product of this Vector3 and another Vector3. For script use.
          * @param other The other Vector3.
          * @returns The dot product.
          */
        float scriptDotProduct(QScriptValue other) const;

        /**
          * Gets the cross product of this Vector3 and another Vector3. For script use.
          * @param other The other Vector3.
          * @returns The cross product.
          */
        QScriptValue scriptCrossProduct(QScriptValue other) const;

        /**
          * Gets a Vector3 that deviates from this Vector3 within a given angle range randomly. For script use.
          * @param angle_range The angle range.
          * @returns The random Vector3.
          */
        QScriptValue scriptGetRandomDeviant(float angle_range) const;

        /**
          * Gets the angle between this Vector3 and another Vector3. For script use.
          * @param other The other Vector3.
          * @returns The angle between this Vector3 and another Vector3.
          */
        float scriptGetAngleBetween(QScriptValue other);

        /**
          * Gets the quaterion to rotate from the direction of this Vector3 to the direction of another Vector3. For script use.
          * @param other The other Vector3.
          * @returns The rotation quaterion.
          */
        QScriptValue scriptGetRotationTo(QScriptValue other) const;

        /**
          * Gets the reflection Vector3 of this Vector3 from a normal Vector3. For script use.
          * @param normal The normal Vector3.
          * @returns The reflection Vector3.
          */
        QScriptValue scriptGetReflection(QScriptValue normal) const;

        /**
          * Adds this Vector3 with another Vector3. For script use.
          * @param other The other Vector3.
          * @returns The result.
          */
        QScriptValue scriptAdd(QScriptValue other) const;

        /**
          * Subtracts this Vector3 by another Vector3. For script use.
          * @param other The other Vector3.
          * @returns The result.
          */
        QScriptValue scriptSubtract(QScriptValue other) const;

        /**
          * Multiplies this Vector3 by a number. For script use.
          * @param multiplier The multiplier.
          * @returns The result.
          */
        QScriptValue scriptMultiply(float multiplier) const;

    private:
        Ogre::Vector3 mVec; //!< The vector3.
    };
}

#endif