/**
 * Copyright  (C) 2015 Fondazione Istituto Italiano di Tecnologia
 * Author: Silvio Traversaro
 * website: http://www.codyco.eu
 */

/**
 * Header to mantain iDynTree parser compatible both with the official
 * urdfdom parser available at github.com/ros/urdfdom(_headers) and from
 * deb packages and with the internal fork of urdfdom in which boost has been
 * removed for the sake of an easy installation on Windows.
 */
#ifndef IDYNTREE_MODELIO_URDFCOMPATIBILITY_H
#define IDYNTREE_MODELIO_URDFCOMPATIBILITY_H

#include <urdf_model/model.h>
#include <urdf_parser/urdf_parser.h>

#ifdef IDYNTREE_USE_INTERNAL_URDFDOM

namespace urdf
{


typedef std::vector< LinkPtr > LinkVector;
typedef std::map<std::string, JointPtr > JointPtrMap;

}

#else

namespace urdf
{

typedef boost::shared_ptr<Joint> JointPtr;
typedef boost::shared_ptr<Link>  LinkPtr;
typedef boost::shared_ptr<const Link>  ConstLinkPtr;
typedef boost::shared_ptr<Inertial> InertialPtr;
typedef std::vector<boost::shared_ptr<urdf::Link> > LinkVector;
typedef boost::shared_ptr<urdf::ModelInterface> ModelInterfacePtr;
typedef std::map<std::string, boost::shared_ptr<urdf::Joint> > JointPtrMap;
template<class PtrType> inline void resetPtr(PtrType & ptr) { ptr.reset(); }
template<class PtrType, class PlainType> inline void resetPtr(PtrType & ptr, PlainType * plain_ptr) { ptr.reset(plain_ptr); }


}

#endif

#endif
