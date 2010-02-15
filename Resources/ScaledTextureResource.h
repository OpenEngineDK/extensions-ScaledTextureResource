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

#include <Resources/Texture2D.h>
#include <Logging/Logger.h>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/split_member.hpp>

namespace OpenEngine {
namespace Resources {

using namespace std;

/**
 * Scaled texture resource.
 *
 * @class ScaledTextureResource ScaledTextureResource.h Resources/ScaledTextureResource.h
 */
template <class T> class ScaledTextureResource : public Texture2D<T> {
private:
    Texture2DPtr(T) originalResource;
    unsigned int scale;

public:

    /**
     * Constructor
     *
     * @param resource the texture to scale.
     * @param scale number of pixels to skip.
     */
    ScaledTextureResource(Texture2DPtr(T) resource, unsigned int scale)
        : Texture2D<T>(), 
          originalResource(resource), scale(scale) {}

    //friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & boost::serialization::base_object<ITexture2D>(*this);
    }

    ~ScaledTextureResource(){
        Unload();
    }

    // resource methods
    void Load() {
        if (this->data) return;
        originalResource->Load();
    
        unsigned int scalex = scale, scaley = scale;
    
        // @todo: test that width, height % scale != 0 works
        if (originalResource->GetWidth() % scalex != 0 ||
            originalResource->GetHeight() % scaley != 0) {
            logger.warning << "scaled texture cannot be divided with scaling factor";
            logger.warning << logger.end;
        }

        this->channels = originalResource->GetChannels();
        this->width = originalResource->GetWidth() / scalex;
        this->height = originalResource->GetHeight() / scaley;
        this->format = originalResource->GetColorFormat();
        unsigned int size = this->width * this->height * this->channels;
    
        T* data = new T[size];

        T* originalData = originalResource->GetData();

        for (unsigned int y=0, j=0; y<this->height;
             y++, j+=scaley) {
            
            for (unsigned int x=0,i=0; x<this->width*this->channels;
                 x+=this->channels,i+=scalex*this->channels) {

                for(unsigned int k=0; k<this->channels; k++) {
                    this->data[x+k + y*this->width*this->channels] = 
                        originalData[i+k + j*originalResource->GetWidth()*this->channels];
                }
            }
        }

        this->data = data;
    }

    void Unload(){
        originalResource->Unload();
        if (this->data) {
            delete[] (T*) this->data;
            this->data = NULL;
        }
    }

};

} //NS Resources
} //NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Resources::ScaledTextureResource)

#endif // _SCALED_TEXTURE_RESOURCE_H_
