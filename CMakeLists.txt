SET( EXTENSION_NAME "Extensions_ScaledTextureResource")

ADD_LIBRARY( ${EXTENSION_NAME}
  Resources/ScaledTextueResource.cpp
)

TARGET_LINK_LIBRARIES( ${EXTENSION_NAME}
  OpenEngine_Core
)
