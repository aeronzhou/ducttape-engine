#ifndef DUCTTAPE_ENGINE_SCENE_COMPONENT
#define DUCTTAPE_ENGINE_SCENE_COMPONENT

#include <string>

namespace dt {

/**
  * @author zetaron
  */
class Component {
public:

    /**
      * Default constructor.
      */
    Component();

    /**
      * Constructor with set name.
      * @param name The Component name.
      */
    Component(const std::string& name);

    /**
      * Returns the name of the Component.
      * @returns The name of the Component.
      */
    const std::string& GetName() const;

    /**
      * This is the place where the magic happens.
      * @param time_delta The time passed since last call.
      */
    virtual void Update(float time_delta);

private:
    std::string mName;  //!< The Component name.
};

}

#endif