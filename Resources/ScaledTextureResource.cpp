// Scaled image resource
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Resources/ScaledTextureResource.h>
#include <cmath>

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Resources {

ScaledTextureResource::~ScaledTextureResource() {
    Unload();
}

void ScaledTextureResource::Load() {
    if (this->data) return;
    originalResource->Load();

    this->channels = originalResource->GetChannels();

    unsigned int scalex = scale, scaley = scale;

    // @todo: test that width, height % scale != 0 works
    if (originalResource->GetWidth() % scalex != 0 ||
        originalResource->GetHeight() % scaley != 0) {
        logger.warning << "scaled texture cannot be divided with scaling factor";
        logger.warning << logger.end;
    }

    this->width = originalResource->GetWidth() / scalex;
    this->height = originalResource->GetHeight() / scaley;
    this->format = originalResource->GetColorFormat();
    unsigned int size = this->width * this->height * this->channels;
    
    this->data = new unsigned char[size];

    unsigned char* originalData = originalResource->GetData();

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
}

void ScaledTextureResource::Unload() {
    originalResource->Unload();
    if (this->data) {
        delete[] this->data;
        this->data = NULL;
    }
}

} //NS Resources
} //NS OpenEngine
