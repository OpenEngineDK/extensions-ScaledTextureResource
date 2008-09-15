//  Scaled image resource
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _SCALED_TEXTURE_RESOURCE_H_
#define _SCALED_TEXTURE_RESOURCE_H_

#include <Resources/ITextureResource.h>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/split_member.hpp>

namespace OpenEngine {
namespace Resources {

using namespace std;

/**
 * TGA image resource.
 *
 * @class TGAResource TGAResource.h Resources/TGAResource.h
 */
class ScaledTextureResource : public ITextureResource {
private:
    ITextureResourcePtr originalResource;
    bool loaded;
    int id;                     //!< material identifier
    unsigned char* data;        //!< binary material data
    int width;                  //!< texture width
    int height;                 //!< texture height
    int depth;                  //!< texture depth/bits
    unsigned int scale;
    //@todo: width, height and depth should be unsigned

public:

    /**
     * Constructor
     *
     * @param resource the texture to scale.
     * @param scale number of pixels to skip.
     */
    ScaledTextureResource(ITextureResourcePtr resource, unsigned int scale)
        : originalResource(resource), loaded(false), data(NULL), scale(scale) {
        width = height = depth = id = 0;
    };

    //friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & boost::serialization::base_object<ITextureResource>(*this);
    }

    ~ScaledTextureResource();

    // resource methods
    void Load();
    void Unload();

    // texture resource methods
	int GetID();
	void SetID(int id);   
    int GetWidth();
	int GetHeight();
	int GetDepth();
	unsigned char* GetData();

};

} //NS Resources
} //NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Resources::ScaledTextureResource)

#endif // _SCALED_TEXTURE_RESOURCE_H_