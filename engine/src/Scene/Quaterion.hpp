
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
//#include <Scene/Vector3.hpp>

#include <OGRE/OgreQuaternion.h>
#include <OGRE/OgreVector3.h>

#include <QScriptProgram>
#include <QObject>

namespace dt {

    //class Vector3d;

    /**
      * A class to hold a 4-dimensional vector.
      */
    class Quaternion : public QObject, IMPLEMENTS IScriptable {
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
        Quaternion(void);

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
        Quaternion(const Ogre::Quaternion &ogre_quaternion);

        /**
          * Convert this Quaternion to an Ogre Quaternion.
          * @returns The Ogre Quaternion.
          */
        Ogre::Quaternion getOgreQuaternion() const;

#pragma region operator_override
        float operator [] (const uint32_t i) const;
        float& operator [] (const uint32_t i);
        Quaternion& operator = (const Quaternion &q);
        Quaternion operator + (const Quaternion &q) const;
        Quaternion operator - (const Quaternion &q) const;
        Quaternion operator * (const Quaternion &q) const;
        Quaternion operator * (const float scalar) const;
        Quaternion operator- () const;
        bool operator== (const Quaternion &rhs) const;
        bool operator!= (const Quaternion &rhs) const;
        Ogre::Vector3 operator * (const Ogre::Vector3 &vec) const;
#pragma endregion

        /**
          * Gets the w value of this Quaternion.
          * @returns The w value.
          */
        float getW();

        /**
          * Gets the x value of this Quaternion.
          * @returns The x value.
          */
        float getX();

        /**
          * Gets the y value of this Quaternion.
          * @returns The y value.
          */
        float getY();

        /**
          * Gets the z value of this Quaternion.
          * @returns The z value.
          */
        float getZ();

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

        void assign(const Quaternion &q);
        void add(const Quaternion &q);
        void subtract(const Quaternion &q);
        void scale(const float scalar);

        /**
          * Swaps two the value of two quaternion.
          * @param other The other Quaternion.
          */
        void swap(Quaternion& other);

        /**
          * Dot product of two quaternion.
          * @param q The other Quaternion.
          * @returns The result of dot product.
          */
        float dotProduct(const Quaternion &q) const;

        /**
          * Cross product of two quaternion.
          * @param q The other Quaternion.
          * @returns The result of cross product.
          */
        Quaternion crossProduct(const Quaternion &q) const;

        /**
          * Normalise quaternion.
          * @returns Length of quaternion before normalise.
          */
        float normalise();

        /**
          * Get the length of the Quaternion.
          * @returns The length of the Quaternion.
          */
        float getLength() const;

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
        void fromAngleAxis(const float &angle, const Ogre::Vector3 &axis);

        /**
          * Construct angle and axis from quaternion.
          * @param angle Angle to rotate.
          * @param axis Axis to rotate around.
          */
        void toAngleAxis(float &angle, Ogre::Vector3 &axis) const;

#pragma region script_function
        /**
          * Swaps two the value of two quaternion. For script use.
          * @param other The other Quaternion.
          */
        void scriptSwap(QScriptValue q);

        /**
          * Dot product of two quaternion. For script use.
          * @param q The other Quaternion.
          * @returns The result of dot product.
          */
        float scriptDotProduct(QScriptValue q) const;

        /**
          * Cross product of two quaternion. For script use.
          * @param q The other Quaternion.
          * @returns The result of cross product.
          */
        QScriptValue scriptCrossProduct(QScriptValue q) const;

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
        void scriptToAngleAxis(float &angle, QScriptValue &axis) const;

        void scriptAssign(QScriptValue q) const;
        QScriptValue scriptAdd(QScriptValue q) const;
        QScriptValue scriptSubtract(QScriptValue q) const;
        QScriptValue scriptScale(QScriptValue q) const;
#pragma endregion

        /**
          * Returns a QtScript object.
          * @returns A QtScript object.
          * @see IScriptable
          */
        virtual QScriptValue toQtScriptObject();
    private:
        float mW;         //!< The w value of the Quaternion.
        float mX;         //!< The x value of the Quaternion.
        float mY;         //!< The y value of the Quaternion.
        float mZ;         //!< The z value of the Quaternion.
    };
}

#endif