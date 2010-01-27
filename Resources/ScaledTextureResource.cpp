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
    if (loaded) return;
    originalResource->Load();

    this->channels = originalResource->GetChannels();

    unsigned int scalex = scale, scaley = scale;

    // @todo: test that width, height % scale != 0 works
    if (originalResource->GetWidth() % scalex != 0 ||
        originalResource->GetHeight() % scaley != 0) {
        logger.warning << "scaled texture cannot be divided with scaling factor";
        logger.warning << logger.end;
    }

    width = originalResource->GetWidth() / scalex;
    height = originalResource->GetHeight() / scaley;
    colorFormat = originalResource->GetColorFormat();
    unsigned int size = width * height * this->channels;
    
    data = new unsigned char[size];

    unsigned char* originalData = originalResource->GetData();

    for (unsigned int y=0, j=0; y<height;
         y++, j+=scaley) {
            
        for (unsigned int x=0,i=0; x<width*this->channels;
             x+=this->channels,i+=scalex*this->channels) {

            for(unsigned int k=0; k<this->channels; k++) {
                data[x+k + y*width*this->channels] = 
                    originalData[i+k + j*originalResource->GetWidth()*this->channels];
            }
        }
    }

    loaded = true;
}

void ScaledTextureResource::Unload() {
    if (loaded) {
        delete[] data;
        loaded = false;
    }
}

int ScaledTextureResource::GetID(){
    return id;
}

void ScaledTextureResource::SetID(int id){
    this->id = id;
}

unsigned int ScaledTextureResource::GetWidth(){
    return width;
}

unsigned int ScaledTextureResource::GetHeight(){
    return height;
}

ColorFormat ScaledTextureResource::GetColorFormat() {
    return colorFormat;
}

unsigned char* ScaledTextureResource::GetData(){
    return data;
}

} //NS Resources
} //NS OpenEngine
