//
// Created by merom on 6/21/2023.
//

#ifndef HOMEWORK3_FACTORY_H
#define HOMEWORK3_FACTORY_H
#include <map>
#include <memory>
#include <vector>
#include "../../Utilities/Geometry.h"


using defaultIDKeyType2 = std::string;

/**
    The abstract factory.
    Implemented using the Singleton pattern
*/
template <class manufacturedObj, typename classIDKey=defaultIDKeyType2>
class genericFactory2
{
    /* The following is C++11's typedef for a pointer to a function!
	 a BASE_CREATE_FN2 is a static factory method: a function that
     returns an smart pointer to a manufactuedObj.  Note that you can customize
     the type of parameters to allow overloaded ctors*/
    using BASE_CREATE_FN =    std::shared_ptr<manufacturedObj> (*) (const std::string &par, const Point & p, int init_crate, int rate);

    /* FN_REGISTRY2 is the registry2 of all the BASE_CREATE_FN2
     pointers registered.  Functions are registered using the
     regCreateFn member function (see below).*/
    using FN_REGISTRY = std::map<classIDKey, BASE_CREATE_FN>;
    FN_REGISTRY registry;

    /* Singleton implementation */
    genericFactory2();
    genericFactory2(const genericFactory2&) = delete; // Ruled out
    genericFactory2 &operator=(const genericFactory2&) = delete; // Ruled out
public:

    /// Singleton access.
    static genericFactory2 &instance();

    /// Classes derived from manufacturedObj call this function once
    /// per program to register the class ID key, and a pointer to
    /// the function that creates the class.
    void regCreateFn(const classIDKey &, BASE_CREATE_FN);

    /// Create a new class of the type specified by className.
       std::shared_ptr<manufacturedObj> create(const classIDKey &className,
                                            const std::string &param, const Point & xy, int init_crate, int rate ) const;
};

template <class manufacturedObj, typename classIDKey>
genericFactory2<manufacturedObj, classIDKey>::genericFactory2()
{
}

template <class manufacturedObj, typename classIDKey>
genericFactory2<manufacturedObj, classIDKey> &genericFactory2<manufacturedObj, classIDKey>::instance()
{
    // Note that this is not thread-safe!
    static genericFactory2 theInstance;
    return theInstance;
}

/// Register the creation function.  This simply associates the classIDKey
/// with the function used to create the class.  The return value is a dummy
/// value, which is used to allow static initialization of the registry2.
template <class manufacturedObj, typename classIDKey>
void genericFactory2 < manufacturedObj, classIDKey>::regCreateFn(const classIDKey &clName, BASE_CREATE_FN func)
{
    registry[clName]=func;
}

/// The create function simple looks up the class ID, and if it's in the list,
/// the statement "(*i).second();" calls the function.
template <class manufacturedObj, typename classIDKey>
   std::shared_ptr<manufacturedObj> genericFactory2<manufacturedObj, classIDKey>::create(const classIDKey &className, const std::string &parms, const Point & xy , int init_crate, int rate ) const
{
    std::shared_ptr<manufacturedObj> ret(nullptr);

    typename FN_REGISTRY::const_iterator regEntry = registry.find(className);
    if (regEntry != registry.end()) {
        return (*regEntry).second(parms,xy,init_crate,rate);
    }
    return ret;
}

/// Helper template to make registration simple.
template <class ancestorType,
        class manufacturedObj,
        typename classIDKey2=defaultIDKeyType2 >
class registerInFactory2{
public:
    static std::shared_ptr<ancestorType> createInstance(const std::string &pa ,  const Point & xy , int init_crate, int rate )
    {
        return std::shared_ptr<ancestorType>(manufacturedObj::createInstance(pa, xy,init_crate,rate));
    }

    explicit registerInFactory2(const classIDKey2 &id  )
    {

        genericFactory2<ancestorType>::instance().regCreateFn(id, createInstance);
    }
};

#endif //HOMEWORK3_FACTORY_H
