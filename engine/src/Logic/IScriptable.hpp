
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_LOGIC_ISCRIPTABLE
#define DUCTTAPE_ENGINE_LOGIC_ISCRIPTABLE

#include <Config.hpp>

#include <qscriptprogram.h>
#include <qscriptvalue.h>

namespace dt {
    /**
      * An interface for script accessing. All the instances of classes that implement this interface will be available in script.
      */
    INTERFACE(IScriptable)
        /**
          * Returns a QtScript object.
          * @returns A QtScript object.
          */
        virtual QScriptValue toQtScriptObject() = 0;
    END_INTERFACE(IScriptable)
}

#endif