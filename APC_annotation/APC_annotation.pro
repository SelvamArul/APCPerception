TEMPLATE = app
TARGET = APC_annotation 

QT        += core gui svg opengl webkit 

HEADERS   += apc_annotation.h
SOURCES   += main.cpp \
    apc_annotation.cpp
FORMS     += apc_annotation.ui    
RESOURCES +=
INCLUDEPATH+=/usr/include/opencv2
INCLUDEPATH+=/usr/include/opencv
LIBS+=`pkg-config opencv –cflags –libs`
CONFIG+=c++11
CONFIG+=link_pkgconfig 
PKGCONFIG+=opencv
