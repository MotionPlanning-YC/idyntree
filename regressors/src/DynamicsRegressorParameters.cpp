/**
 * Copyright (C) 2013 IIT - Istituto Italiano di Tecnologia - http://www.iit.it
 * Author: Silvio Traversaro
 * CopyPolicy: Released under the terms of the GNU LGPL v2.0 (or any later version)
 *
 * The development of this software was supported by the FP7 EU project
 * CoDyCo (No. 600716 ICT 2011.2.1 Cognitive Systems and Robotics (b))
 * http://www.codyco.eu
 */

#include "iDynTree/Regressors/DynamicsRegressorParameters.h"

#include <string>
#include <cassert>
#include <sstream>

namespace iDynTree
{

namespace Regressors
{

typedef std::vector<DynamicsRegressorParameter> ParamSet;

unsigned int DynamicsRegressorParametersList::getNrOfParameters() const
{
    return this->parameters.size();
}

bool DynamicsRegressorParametersList::addParam(const DynamicsRegressorParameter& param)
{
    // We store the parameters in the DynamicsRegressorParametersList as a ordered list
    // of parameters.. hence we will keep the vector ordered by performing insertion only
    // in an ordered way
    for(ParamSet::iterator it  = this->parameters.begin();
        it != this->parameters.end(); it++)
    {
        // if param is equal to an element of the vector, we can avoid adding it
        if( param == *it )
        {
            return true;
        }

        // if param is lower then the current element, we insert it in the vector and we exit
        if( param < *it )
        {
            this->parameters.insert(it,param);
            return true;
        }
    }

    // if no element in the vector is bigger than param, add it at the end of the vector
    this->parameters.insert(this->parameters.end(),param);
    return true;
}


bool DynamicsRegressorParametersList::addList(const DynamicsRegressorParametersList& new_params)
{
    for(ParamSet::const_iterator it  = new_params.parameters.begin();
        it != new_params.parameters.end(); it++)
    {
        this->addParam(*it);
    }

    return true;
}

bool DynamicsRegressorParameter::operator<(const DynamicsRegressorParameter& other) const
{
    if( this->category < other.category )
    {
        return true;
    }
    else if( this->category > other.category )
    {
        return false;
    }

    // If they are in the same category
    //the index will decide the order

    if( this->index < other.index )
    {
        return true;
    }
    else if( this->index > other.index )
    {
        return false;
    }

    // If they are in the same category & index
    // the type will decide the order

    if( this->type < other.type )
    {
        return true;
    }
    else if( this->type > other.type )
    {
        return false;
    }

    //if they are equal then < is false
    assert(*this == other);
    return false;
}

bool DynamicsRegressorParameter::operator==(const DynamicsRegressorParameter& other) const
{
    return (this->category == other.category) &&
           (this->index    == other.index)    &&
           (this->type     == other.type);
}


DynamicsRegressorParameterCategory getCategory(const DynamicsRegressorParameterType paramType)
{
    switch(paramType)
    {
        case LINK_MASS:
        case LINK_FIRST_MOMENT_OF_MASS_X:
        case LINK_FIRST_MOMENT_OF_MASS_Y:
        case LINK_FIRST_MOMENT_OF_MASS_Z:
        case LINK_MOMENT_OF_INERTIA_XX:
        case LINK_MOMENT_OF_INERTIA_XY:
        case LINK_MOMENT_OF_INERTIA_XZ:
        case LINK_MOMENT_OF_INERTIA_YY:
        case LINK_MOMENT_OF_INERTIA_YZ:
        case LINK_MOMENT_OF_INERTIA_ZZ:
            return LINK_PARAM;
        case SENSOR_FT_OFFSET_FORCE_X:
        case SENSOR_FT_OFFSET_FORCE_Y:
        case SENSOR_FT_OFFSET_FORCE_Z:
        case SENSOR_FT_OFFSET_TORQUE_X:
        case SENSOR_FT_OFFSET_TORQUE_Y:
        case SENSOR_FT_OFFSET_TORQUE_Z:
            return SENSOR_FT_PARAM;
    }

    assert(false);
    return LINK_PARAM;
}

// \todo add a function that accepts an UndirectedTree and a SensorsTree to resolve link and sensors
// indices to names
std::string DynamicsRegressorParametersList::getDescriptionOfParameter(unsigned int parameter_index) const
{
    std::stringstream ss;
    std::string inertial_parameter_type;

    if( parameter_index >= this->getNrOfParameters() ) {
        ss << "DynamicRegressorGenerator::getDescriptionOfParameter error: parameter_index "
           << parameter_index << " is greater the number of parameters " << this->getNrOfParameters();
        return ss.str();
    }

    if( parameters[parameter_index].category == LINK_PARAM )
    {
        switch( parameters[parameter_index].type )
        {
            case LINK_MASS:
                inertial_parameter_type = "mass";
                break;
            case LINK_FIRST_MOMENT_OF_MASS_X:
                inertial_parameter_type = "x component of first moment of mass";
                break;
            case LINK_FIRST_MOMENT_OF_MASS_Y:
                inertial_parameter_type = "y component of first moment of mass";
                break;
            case LINK_FIRST_MOMENT_OF_MASS_Z:
                inertial_parameter_type = "z component of first moment of mass";
                break;
            case LINK_MOMENT_OF_INERTIA_XX:
                inertial_parameter_type = "xx component of inertia matrix";
                break;
            case LINK_MOMENT_OF_INERTIA_XY:
                inertial_parameter_type = "xy component of inertia matrix";
                break;
            case LINK_MOMENT_OF_INERTIA_XZ:
                inertial_parameter_type = "xz component of inertia matrix";
                break;
            case LINK_MOMENT_OF_INERTIA_YY:
                inertial_parameter_type = "yy component of inertia matrix";
                break;
            case LINK_MOMENT_OF_INERTIA_YZ:
                inertial_parameter_type = "yz component of inertia matrix";
                break;
            case LINK_MOMENT_OF_INERTIA_ZZ:
                inertial_parameter_type = "zz component of inertia matrix";
                break;
        }
        ss << "Parameter " << parameter_index << ": "
        << inertial_parameter_type << " of link " << parameters[parameter_index].index;
    }

    if( parameters[parameter_index].category == SENSOR_FT_PARAM )
    {
        std::string ft_offset_type;
        switch( parameters[parameter_index].type )
        {
            case SENSOR_FT_OFFSET_FORCE_X:
                ft_offset_type = "x component of force offset";
                break;
            case SENSOR_FT_OFFSET_FORCE_Y:
                ft_offset_type = "y component of force offset";
                break;
            case SENSOR_FT_OFFSET_FORCE_Z:
                ft_offset_type = "z component of force offset";
                break;
            case SENSOR_FT_OFFSET_TORQUE_X:
                ft_offset_type = "x component of torque offset";
                break;
            case SENSOR_FT_OFFSET_TORQUE_Y:
                ft_offset_type = "y component of torque offset";
                break;
            case SENSOR_FT_OFFSET_TORQUE_Z:
                ft_offset_type = "z component of torque offset";
                break;
        }

        ss << "Parameter "
           << parameter_index
           << ": " << ft_offset_type << " of ft sensor " << parameters[parameter_index].index;
    }

    return ss.str();

}


}

}
