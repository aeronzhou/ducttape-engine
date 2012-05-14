
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Config.hpp>

#include <Logic/IScriptable.hpp>

#include <OGRE/OgreVector3.h>

namespace dt {
    /**
      * A class to hold a 3-dimensional vector.
      */
    class Vector3 : IMPLEMENTS IScriptable {
    public:
        /**
          * Non-parameter constructor which constructs a Vector3 with (0.0f, 0.0f, 0.0f).
          */
        Vector3();

        /**
          * Uses the given x, y and z value to construct a Vector3.
          * @param x The x value.
          * @param y The y value.
          * @param z The z value.
          */
        Vector3(const float x, const float y, const float z);

        /**
          * Swaps two the value of two Vector3.
          * @param other The other Vector3.
          */
        void swap(Vector3& other);

        /**
          * 

    };
}